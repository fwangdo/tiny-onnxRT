# tiny-onnxRT

AI runtime을 직접 구현하면서, compiler가 만든 결과물이 runtime에서 어떻게 실행되는지 이해하기 위한 작은 end-to-end ONNX inference runtime.

## 목적

런타임 엔지니어링을 중심으로 AI 시스템 실행 구조를 이해하는 프로젝트.

- **메인 관심사**: Runtime (execution, memory, dispatch, profiling)
- **보조 관심사**: Compiler-runtime boundary (compiler pass가 만든 graph/execution plan이 runtime에서 어떻게 소비되는지)

## 핵심 질문

이 프로젝트는 다음 질문에 답하기 위해 존재한다.

1. AI 모델은 runtime에서 실제로 어떻게 실행되는가?
2. Tensor buffer는 누가 만들고, 언제 재사용되는가?
3. Op는 어떤 방식으로 dispatch되는가?
4. Execution plan은 어떻게 만들어지고 소비되는가?
5. Profiling 결과를 보고 runtime을 어떻게 개선하는가?
6. Compiler 최적화는 runtime 실행에 어떤 형태로 영향을 주는가?

## 타겟 모델

MNIST MLP — MatMul, Add, Relu, Softmax 수준의 op만 사용하는 간단한 모델.
고성능 커널이 아니라 runtime 구조 자체에 집중하기 위한 선택.

## 아키텍처

```
ONNX protobuf
    |
    v
[ONNX Parser] --- onnx.proto3 로드, node/initializer 추출
    |
    v
[Graph IR] --- 내부 표현: Node, Tensor, Graph
    |
    v
[Compiler Pass] --- (현재 빈칸) conv-bn fusion 등 graph rewrite 자리
    |
    v
[Execution Planner] --- topological sort → linear execution plan
    |
    v
[Runtime]
    ├── Kernel Registry --- op name → kernel function 매핑
    ├── Dispatch --- execution plan 순회하며 kernel 호출
    ├── Memory Arena --- tensor buffer 할당/재사용
    ├── Session --- 실행 루프 전체를 관리
    └── Profiler --- op별 실행 시간, 메모리 사용량 측정
```

## 프로젝트 구조

```
tiny-onnxRT/
├── CMakeLists.txt
├── README.md
├── third_party/
│   └── onnx/                  # onnx proto 정의
├── src/
│   ├── onnx_parser/           # ONNX protobuf → Graph IR
│   │   ├── onnx_parser.h
│   │   └── onnx_parser.cpp
│   ├── graph/                 # 내부 Graph IR 정의
│   │   ├── graph.h
│   │   ├── node.h
│   │   └── tensor.h
│   ├── compiler/              # graph rewrite passes (빈칸)
│   │   └── pass.h
│   ├── planner/               # Graph IR → execution plan
│   │   ├── execution_plan.h
│   │   └── planner.cpp
│   ├── runtime/               # 프로젝트의 핵심
│   │   ├── kernel_registry.h  # op → kernel 매핑
│   │   ├── kernel_registry.cpp
│   │   ├── dispatch.h         # plan 순회 + kernel 호출
│   │   ├── dispatch.cpp
│   │   ├── memory_arena.h     # buffer 할당/재사용
│   │   ├── memory_arena.cpp
│   │   ├── session.h          # 실행 루프 전체 관리
│   │   ├── session.cpp
│   │   ├── profiler.h         # 실행 시간/메모리 측정
│   │   └── profiler.cpp
│   └── kernels/               # op 구현 (naive, 최적화 목적 아님)
│       ├── matmul.cpp
│       ├── add.cpp
│       ├── relu.cpp
│       └── softmax.cpp
├── models/
│   └── mnist_mlp.onnx         # 테스트용 모델
└── tests/
    ├── test_parser.cpp
    ├── test_planner.cpp
    ├── test_runtime.cpp
    └── test_e2e.cpp           # ONNX 로드 → 추론 → 결과 검증
```

## 마일스톤

### M1: 단일 op 실행
- ONNX에서 MatMul 하나 로드
- Graph IR 변환 → execution plan 생성 → kernel dispatch → 결과 검증
- 목표: 전체 파이프라인을 end-to-end로 관통

### M2: MNIST MLP 추론
- MatMul, Add, Relu, Softmax 커널 구현
- Memory arena로 중간 tensor buffer 관리
- MNIST 테스트 이미지로 추론 결과 검증

### M3: Profiling & 개선
- Op별 실행 시간 측정
- Buffer 할당/재사용 패턴 분석
- 측정 결과 기반 runtime 개선 (buffer reuse, dispatch overhead 감소 등)

### M4: Compiler pass 연결
- 간단한 graph rewrite pass 추가 (예: constant folding, dead node elimination)
- Pass 적용 전후 runtime 성능 비교
- Compiler가 runtime에 미치는 영향을 수치로 확인

## 하지 않는 것

- MLIR/LLVM backend를 깊게 파는 것
- ONNX graph optimizer만 만드는 것
- 고성능 kernel library를 새로 만드는 것

커널은 correctness만 보장하는 naive 구현이면 충분하다. 관심사는 커널 바깥의 runtime 구조.

## 빌드 & 실행

```bash
# 빌드
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

# 테스트
cd build && ctest

# 추론 실행
./build/tiny_onnxrt models/mnist_mlp.onnx
```

## 기술 스택

- **언어**: C++17
- **빌드**: CMake
- **ONNX 파싱**: protobuf (onnx.proto3)
- **테스트**: Google Test
