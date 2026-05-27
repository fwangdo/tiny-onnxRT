// add.cpp — Add kernel (element-wise 덧셈)
//
// 역할:
//   C = A + B (element-wise)
//   MNIST MLP에서 bias 더하기에 사용.
//
// 구현해야 할 것:
//   - add(inputs, outputs):
//     - inputs[0]: A
//     - inputs[1]: B (bias일 경우 shape이 다를 수 있음)
//     - outputs[0]: C
//     - element-wise: C[i] = A[i] + B[i]
//
// Broadcasting 처리:
//   ONNX Add는 numpy-style broadcasting을 지원한다.
//   MNIST MLP에서의 전형적인 케이스:
//     - A: [1, 256] (MatMul 결과)
//     - B: [256] (bias)
//     - C: [1, 256]
//   → B를 A의 각 row에 더하는 형태.
//   일단 이 케이스만 처리하면 충분.
//   완전한 broadcasting은 필요 시 확장.
