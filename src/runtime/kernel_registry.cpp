// kernel_registry.cpp — KernelRegistry 구현
//
// 구현해야 할 것:
//   - register_kernel(): map에 삽입. 중복 등록 시 경고 또는 덮어쓰기.
//   - get_kernel(): map에서 조회. 없으면 예외 또는 에러 메시지.
//   - 기본 kernel 등록 함수: register_default_kernels(KernelRegistry&)
//     → MatMul, Add, Relu, Softmax를 한꺼번에 등록하는 헬퍼
