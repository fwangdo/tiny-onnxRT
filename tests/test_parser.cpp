// test_parser.cpp — ONNX 파서 테스트
//
// 테스트해야 할 것:
//   - ONNX 파일 로드 → Graph IR 변환이 정상 동작하는지
//   - 노드 개수, op_type, input/output 이름이 기대값과 일치하는지
//   - initializer(weight) 로드: shape, data 값 확인
//   - 그래프 input/output 이름 확인
//   - 존재하지 않는 파일 로드 시 에러 처리
//
// 테스트용 모델:
//   - models/mnist_mlp.onnx 사용
//   - 또는 테스트용 간단한 ONNX 파일을 별도로 만들어서 사용
//     (MatMul 하나만 있는 최소 모델)
