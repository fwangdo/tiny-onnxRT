// softmax.cpp — Softmax kernel
//
// 역할:
//   입력 벡터를 확률 분포로 변환.
//   MNIST MLP의 마지막 layer에서 10개 클래스의 확률을 구한다.
//
// 구현해야 할 것:
//   - softmax(inputs, outputs):
//     - inputs[0]: X (shape: [1, 10] 등)
//     - outputs[0]: Y (shape: X와 동일)
//     - axis: 마지막 차원 (default, ONNX opset 13+)
//
//   계산 순서 (수치 안정성 포함):
//     1. max_val = max(X[i]) — overflow 방지
//     2. exp_sum = sum(exp(X[i] - max_val))
//     3. Y[i] = exp(X[i] - max_val) / exp_sum
//
// 참고:
//   - axis 속성: ONNX Softmax의 axis 기본값은 opset에 따라 다르다.
//     opset 13+에서는 axis=-1 (마지막 차원).
//     MNIST MLP에서는 마지막 차원에 적용하면 충분.
//   - 수치 안정성을 위해 반드시 max 빼기를 해야 한다.
//     하지 않으면 exp()에서 inf가 나올 수 있다.
