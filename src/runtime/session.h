#pragma once

// session.h — 추론 실행의 전체 흐름을 관리하는 Session
//
// 역할:
//   사용자(main)가 호출하는 최상위 인터페이스.
//   모델 로드부터 추론 실행까지의 전체 lifecycle을 관리한다.
//
// 포함해야 할 것:
//   - Session 클래스:
//     - load_model(const std::string& model_path)
//       1. OnnxParser로 .onnx → Graph IR 변환
//       2. (나중에) Compiler pass 적용
//       3. Planner로 Graph → ExecutionPlan 생성
//       4. KernelRegistry에 기본 kernel 등록
//       → 이 시점에서 추론 준비 완료
//
//     - run(const std::map<std::string, Tensor>& inputs)
//           → std::map<std::string, Tensor>
//       1. 입력 tensor를 tensor map에 추가
//       2. initializer를 tensor map에 추가 (이미 로드됨)
//       3. Dispatcher.run(plan, tensor_map) 호출
//       4. 그래프 출력 이름으로 결과 tensor 추출
//       5. MemoryArena reset
//       6. 결과 반환
//
// 소유하는 멤버:
//   - Graph graph_
//   - ExecutionPlan plan_
//   - KernelRegistry registry_
//   - MemoryArena arena_
//   - Dispatcher dispatcher_
//   - Profiler profiler_ (optional)
//
// 설계 고려사항:
//   - Session은 "조립자"이다. 각 컴포넌트를 생성하고 연결한다.
//   - run()은 여러 번 호출할 수 있다 (여러 이미지 추론).
//     매 호출마다 arena를 reset해서 중간 buffer를 정리.
//   - thread safety는 고려하지 않는다 (single-threaded 실행).
