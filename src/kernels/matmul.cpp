// matmul.cpp — MatMul kernel (naive 구현)
//
// 역할:
//   2D 행렬 곱셈. C = A * B
//   MNIST MLP에서 fully-connected layer의 핵심 연산.
//
// 구현해야 할 것:
//   - matmul(inputs, outputs):
//     - inputs[0]: A (shape: [M, K])
//     - inputs[1]: B (shape: [K, N])
//     - outputs[0]: C (shape: [M, N])
//     - 3중 루프: C[i][j] += A[i][k] * B[k][j]
//
// 참고:
//   - 고성능 구현이 목적이 아님. correctness만 보장.
//   - BLAS 호출 없이 순수 C++ 루프로 구현.
//   - shape 검증: A.shape[1] == B.shape[0] 확인.
//   - output shape 계산: [A.shape[0], B.shape[1]]
//   - 데이터는 row-major (C 스타일) 레이아웃 가정.
