#pragma once

// dispatch.h — ExecutionPlan을 순회하며 kernel을 호출하는 dispatcher
//
// 역할:
//   ExecutionPlan의 각 ExecutionStep을 순서대로 돌면서:
//   1. step의 op_type으로 KernelRegistry에서 kernel 조회
//   2. step의 input names로 tensor들을 수집
//   3. step의 output names로 출력 tensor(buffer) 준비
//   4. kernel 호출
//   5. (선택) profiler에 실행 시간 기록
//
// 포함해야 할 것:
//   - Dispatcher 클래스:
//     - 생성 시 KernelRegistry, MemoryArena, (optional) Profiler 참조
//     - run(const ExecutionPlan&, TensorMap& tensors)
//       → tensors: 현재 살아있는 tensor들의 이름 → Tensor* 매핑
//       → initializer + 그래프 입력 + 중간 결과가 모두 여기에 있다
//
// 실행 루프 (핵심):
//   for (auto& step : plan.steps) {
//       auto kernel = registry.get_kernel(step.op_type);
//       auto inputs = gather_tensors(step.input_names, tensors);
//       auto outputs = allocate_outputs(step.output_names, arena);
//       kernel(inputs, outputs);
//       store_tensors(step.output_names, outputs, tensors);
//   }
//
// 설계 고려사항:
//   - Dispatcher는 "실행만" 한다. 스케줄링 결정은 Planner가 이미 했다.
//   - output tensor의 shape/size는 어떻게 알 수 있는가?
//     → 방법 1: planner가 미리 shape inference를 해서 plan에 포함
//     → 방법 2: kernel이 output shape을 계산하고 arena에서 할당
//     → MNIST MLP에서는 방법 2가 더 간단. 나중에 방법 1로 최적화 가능.
//   - profiler 연동: kernel 호출 전후에 시간 측정.
//     profiler가 없으면(nullptr) 측정 skip.
