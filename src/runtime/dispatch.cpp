// dispatch.cpp — Dispatcher 구현
//
// 구현해야 할 것:
//   - run(): ExecutionPlan 순회하며 kernel 호출하는 메인 루프
//   - gather_tensors(): step의 input names로 tensor map에서 수집
//   - allocate_outputs(): output tensor를 arena에서 할당
//     → kernel이 output shape을 미리 알려주거나,
//       kernel 호출 후 결과로부터 shape을 결정
//   - store_tensors(): kernel 실행 결과를 tensor map에 저장
