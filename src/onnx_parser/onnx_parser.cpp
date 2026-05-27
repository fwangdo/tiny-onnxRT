// onnx_parser.cpp — ONNX protobuf 파싱 구현
//
// 구현 순서:
//   1. ModelProto를 파일에서 로드
//   2. GraphProto 순회하며:
//      - initializer(TensorProto) → Tensor 변환
//      - node(NodeProto) → Node 변환
//      - graph input/output 이름 수집
//   3. Graph 객체 조립 후 반환
//
// 참고: protobuf generated 헤더 (#include "onnx.pb.h") 필요.
//       CMakeLists.txt에서 protobuf_generate_cpp()로 생성.
