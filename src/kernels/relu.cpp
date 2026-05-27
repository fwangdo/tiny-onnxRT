// relu.cpp — Relu kernel
//
// 역할:
//   Y = max(0, X) (element-wise)
//   MNIST MLP에서 활성화 함수.
//
// 구현해야 할 것:
//   - relu(inputs, outputs):
//     - inputs[0]: X
//     - outputs[0]: Y (shape은 X와 동일)
//     - element-wise: Y[i] = std::max(0.0f, X[i])
//
// 참고:
//   - in-place 실행 가능성: 입력과 출력이 같은 buffer를 쓸 수 있다.
//     → M3에서 memory arena 최적화 시 in-place 실행을 고려할 수 있다.
//     → 일단은 별도 output buffer에 결과를 쓰는 것으로 구현.
