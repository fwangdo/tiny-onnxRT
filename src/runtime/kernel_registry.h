#pragma once

// kernel_registry.h — Op 이름 → Kernel 함수 매핑
//
// 역할:
//   "MatMul"이라는 문자열이 들어오면, 실제로 MatMul을 계산하는 함수를 반환.
//   Dispatcher가 ExecutionPlan의 각 step을 실행할 때 이 registry에서 kernel을 찾는다.
//
// 포함해야 할 것:
//   - KernelFunc 타입 정의:
//     using KernelFunc = std::function<void(const std::vector<Tensor*>& inputs,
//                                           std::vector<Tensor*>& outputs)>;
//     → kernel은 입력 tensor들을 받아 출력 tensor에 결과를 쓰는 함수.
//
//   - KernelRegistry 클래스:
//     - register_kernel(const std::string& op_type, KernelFunc func)
//       → op 이름과 kernel 함수를 등록
//     - get_kernel(const std::string& op_type) → KernelFunc
//       → op 이름으로 kernel 함수를 조회. 없으면 에러.
//
// 설계 고려사항:
//   - 내부 저장소는 std::unordered_map<string, KernelFunc>이면 충분.
//   - 등록은 프로그램 시작 시 한 번:
//     registry.register_kernel("MatMul", kernels::matmul);
//     registry.register_kernel("Add", kernels::add);
//     registry.register_kernel("Relu", kernels::relu);
//     registry.register_kernel("Softmax", kernels::softmax);
//   - dispatch 관점에서의 질문:
//     나중에 같은 op에 여러 구현(CPU naive, CPU optimized)을 두려면
//     어떻게 확장해야 하는가? → 지금은 1:1 매핑으로 시작.
