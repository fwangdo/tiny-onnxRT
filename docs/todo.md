# Implementation Steps

각 step은 독립적으로 구현 → 빌드 → 테스트 확인이 가능하도록 설계.
이전 step이 완료되어야 다음 step을 진행할 수 있다.

---

## Step 1: 빌드 시스템 + Tensor/Node/Graph 자료구조

**구현**: CMakeLists.txt, tensor.h, node.h, graph.h

**내용**:
- CMake 프로젝트 설정 (C++17, protobuf 의존성은 아직 빈칸)
- Tensor 클래스: name, shape, data_type, data pointer, size_in_bytes()
- Node 클래스: op_type, name, inputs, outputs, attributes
- Graph 클래스: nodes, initializers, graph inputs/outputs

**확인 방법**:
- `cmake -B build && cmake --build build` 성공
- 간단한 main.cpp에서 Graph를 수동 생성하고 노드/텐서 정보 출력
- Google Test 설정 + test_runtime.cpp에서 Tensor 생성/shape 검증 테스트

---

## Step 2: ONNX 파서

**구현**: onnx_parser.h, onnx_parser.cpp, protobuf 연동

**내용**:
- protobuf 빌드 설정 (onnx.proto3 → .pb.h/.pb.cc 생성)
- OnnxParser::load() 구현: .onnx 파일 → Graph IR 변환
- TensorProto → Tensor, NodeProto → Node 매핑

**확인 방법**:
- MNIST MLP .onnx 파일을 로드해서 Graph 정보 출력
- test_parser.cpp: 노드 개수, op_type, initializer shape 검증
- `./build/test_parser` 통과

**사전 준비**: models/mnist_mlp.onnx 파일 준비 (PyTorch로 학습 후 export, 또는 ONNX Model Zoo에서 다운로드)

---

## Step 3: Execution Planner

**구현**: execution_plan.h, planner.cpp

**내용**:
- ExecutionStep, ExecutionPlan 자료구조 정의
- Planner::plan(): Graph → topological sort → ExecutionPlan
- Kahn's algorithm으로 실행 순서 결정

**확인 방법**:
- test_planner.cpp: 수동 구성한 Graph → plan → 순서 검증
- ONNX 파서로 로드한 MNIST MLP Graph → plan → step 순서 출력
- 각 step의 op_type, input/output names 확인

---

## Step 4: Kernel 구현 (MatMul만)

**구현**: kernels/matmul.cpp, kernel_registry.h, kernel_registry.cpp

**내용**:
- KernelFunc 타입 정의
- KernelRegistry: register/get 구현
- MatMul kernel: 3중 루프, row-major, shape 검증

**확인 방법**:
- test_runtime.cpp: 작은 행렬(2x3 * 3x2)로 MatMul 결과 검증
- KernelRegistry에 등록 후 이름으로 조회 → 호출 → 결과 확인

---

## Step 5: MemoryArena (1단계: malloc wrapper)

**구현**: memory_arena.h, memory_arena.cpp

**내용**:
- allocate(): malloc + 통계 기록
- free(): free + 기록
- reset(): 모든 추적 포인터 해제
- stats(): 할당 횟수, 총 크기 반환

**확인 방법**:
- test_runtime.cpp: allocate → write → read → free → stats 확인
- reset 후 stats가 초기화되는지 확인
- 메모리 누수 없는지 확인 (valgrind 또는 AddressSanitizer)

---

## Step 6: Dispatcher + 단일 op end-to-end

**구현**: dispatch.h, dispatch.cpp

**내용**:
- Dispatcher::run(): ExecutionPlan 순회 → kernel 조회 → tensor 수집 → 호출
- gather_tensors(), allocate_outputs(), store_tensors() 구현

**확인 방법 (M1 마일스톤)**:
- MatMul 하나만 있는 ONNX 로드 → parse → plan → dispatch → 결과 검증
- 수동 계산과 비교해서 값이 일치하는지 확인
- 이 시점에서 전체 파이프라인이 end-to-end로 관통

---

## Step 7: 나머지 Kernel 구현 (Add, Relu, Softmax)

**구현**: kernels/add.cpp, kernels/relu.cpp, kernels/softmax.cpp

**내용**:
- Add: element-wise + bias broadcasting ([1,N] + [N])
- Relu: max(0, x)
- Softmax: max 빼기 + exp + normalize

**확인 방법**:
- test_runtime.cpp: 각 kernel 개별 테스트
  - Add: broadcasting 케이스 포함
  - Relu: 음수/양수/0 경계값
  - Softmax: 합 == 1.0, 값 범위 [0,1], 수치 안정성 (큰 값 입력)

---

## Step 8: Session + MNIST MLP 추론

**구현**: session.h, session.cpp

**내용**:
- Session::load_model(): parser → planner → registry 초기화
- Session::run(): tensor map 구성 → dispatch → 결과 추출 → arena reset

**확인 방법 (M2 마일스톤)**:
- test_e2e.cpp: MNIST MLP 로드 → 테스트 이미지 추론
- 출력이 10차원, softmax 합 ~1.0 확인
- onnxruntime 결과와 비교 (ground truth)
- 여러 이미지 연속 추론 → 결과 일관성 확인

---

## Step 9: Profiler

**구현**: profiler.h, profiler.cpp, dispatcher에 profiler 연동

**내용**:
- begin_op/end_op: chrono 기반 시간 측정
- report(): op별 실행 시간, 비율, call_count 출력
- Dispatcher에서 kernel 호출 전후에 profiler 호출

**확인 방법**:
- MNIST MLP 추론 실행 후 profiler report 출력
- MatMul이 가장 오래 걸리는지 확인 (기대값)
- op별 시간 합 ≈ 전체 시간인지 확인

---

## Step 10: MemoryArena 개선 (2단계: buffer 재사용)

**구현**: memory_arena.cpp 확장

**내용**:
- free_list: 크기별 해제된 buffer 보관
- allocate() 시 free_list에서 재사용 가능한 buffer 검색
- 재사용 성공/실패 통계 추적

**확인 방법 (M3 마일스톤 일부)**:
- 동일 모델 추론 2회 → 2회차에서 재사용 비율 확인
- stats()에서 reuse_count > 0 확인
- 1단계 대비 총 malloc 호출 횟수 감소 확인
- profiler report에 메모리 통계 추가

---

## Step 11 (선택): Compiler pass 연결

**구현**: compiler/pass.h 확장, constant folding 등

**내용**:
- Pass 인터페이스 정의
- ConstantFoldingPass: 상수 노드 미리 계산
- Pass 적용 전후 profiler 결과 비교

**확인 방법 (M4 마일스톤)**:
- pass 적용 전: 노드 N개, 실행 시간 T
- pass 적용 후: 노드 < N개, 실행 시간 < T
- 수치로 차이 확인

---

## Step 12 (선택): 비동기 실행 / Device 추상화

**구현**: runtime에 device abstraction layer 추가

**내용**:
- Device 인터페이스: allocate, copy, submit, sync
- CPUDevice 구현
- Command queue + event 기반 비동기 실행 모델

**확인 방법**:
- 동기 실행과 동일한 결과 확인
- 비동기 submit → sync 패턴 동작 확인
- profiler에서 queue/dispatch overhead 측정
