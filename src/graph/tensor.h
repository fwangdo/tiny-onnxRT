#pragma once

// tensor.h — 런타임 내부에서 사용하는 Tensor 표현
//
// 역할:
//   ONNX 모델의 weight(initializer)와 중간 연산 결과를 담는 자료구조.
//   runtime의 memory arena가 할당한 buffer를 이 Tensor가 참조한다.
//
// 포함해야 할 것:
//   - name: string — tensor 이름 (ONNX graph에서의 이름과 매핑)
//   - shape: vector<int64_t> — 각 차원의 크기 (예: {1, 784}, {256, 10})
//   - data_type: enum — float32, int64 등. ONNX의 TensorProto::DataType에 대응
//   - data: void* 또는 float* — 실제 데이터 버퍼 포인터
//     - initializer의 경우: ONNX에서 로드한 weight 데이터
//     - 중간 결과의 경우: memory arena가 할당한 buffer
//   - size_in_bytes(): shape와 data_type으로부터 계산
//
// 설계 고려사항:
//   - Tensor가 메모리를 소유(own)하는가, 참조만 하는가?
//     → initializer는 파서가 소유, 중간 tensor는 arena가 소유.
//       Tensor는 포인터만 들고 있고, lifetime은 외부에서 관리.
//   - data_type은 일단 float32만 지원해도 MNIST MLP에는 충분하다.
//     나중에 확장할 수 있도록 enum으로 정의해 둔다.
