#pragma once

// onnx_parser.h — ONNX protobuf 파일을 Graph IR로 변환
//
// 역할:
//   .onnx 파일(protobuf binary)을 읽어서 내부 Graph IR로 변환한다.
//   protobuf의 ModelProto → GraphProto를 파싱하고,
//   각 NodeProto → Node, TensorProto → Tensor로 매핑한다.
//
// 구현해야 할 것:
//   - load(const std::string& model_path) → Graph
//     1. 파일을 열고 ModelProto::ParseFromIstream()으로 파싱
//     2. GraphProto에서:
//        - node → Node 변환: op_type, name, inputs, outputs 추출
//        - initializer → Tensor 변환: name, shape, data_type, raw_data 추출
//        - input/output → 그래프 입출력 이름 추출
//     3. 변환된 Graph 반환
//
// TensorProto → Tensor 변환 시 주의:
//   - raw_data가 있으면 그대로 사용 (little-endian float 배열)
//   - float_data가 있으면 float 배열로 복사
//   - shape는 TensorProto::dims에서 가져옴
//
// 설계 고려사항:
//   - protobuf 의존성은 이 모듈에만 격리한다.
//     Graph IR (graph.h, node.h, tensor.h)는 protobuf에 의존하지 않는다.
//   - 에러 처리: 지원하지 않는 op_type이 있으면 로그 출력 후 진행.
//     MNIST MLP에서 쓰는 op만 정상 처리되면 충분.
