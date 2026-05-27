// test_e2e.cpp — End-to-end 추론 테스트
//
// 테스트해야 할 것:
//   - ONNX 모델 로드 → 추론 → 결과 검증까지 전체 파이프라인
//
// 테스트 시나리오:
//   1. Session으로 models/mnist_mlp.onnx 로드
//   2. 테스트 입력 이미지(784차원 float 벡터) 준비
//      - 알려진 숫자의 MNIST 이미지 사용
//      - 또는 all-zeros 입력으로 결과 일관성만 확인
//   3. session.run(input) 호출
//   4. 출력이 10차원 벡터인지 확인
//   5. softmax 출력의 합이 ~1.0인지 확인
//   6. argmax가 기대하는 숫자인지 확인 (알려진 입력 사용 시)
//
// 선택 테스트:
//   - 같은 입력으로 여러 번 run() → 결과가 동일한지 (determinism)
//   - profiler 활성화 상태에서 run() → report() 출력 확인
//   - onnxruntime과 결과 비교 (ground truth)
