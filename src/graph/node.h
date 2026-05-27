#pragma once

// node.h — Graph IR의 연산 노드 표현
//
// 역할:
//   ONNX graph의 NodeProto에 대응하는 내부 표현.
//   하나의 Node = 하나의 op 호출 (예: MatMul, Add, Relu, Softmax).
//
// 포함해야 할 것:
//   - op_type: string — "MatMul", "Add", "Relu", "Softmax" 등
//   - name: string — 노드 이름 (디버깅/프로파일링용)
//   - inputs: vector<string> — 입력 tensor 이름 목록
//     - 예: MatMul 노드의 inputs = {"input", "weight"}
//     - 이름으로 Graph의 tensor를 참조한다
//   - outputs: vector<string> — 출력 tensor 이름 목록
//   - attributes: map<string, Attribute> — op별 속성 (MNIST MLP에서는 거의 안 씀)
//     - Attribute는 int, float, string, tensor 등을 담을 수 있는 variant
//
// 설계 고려사항:
//   - Node는 데이터(tensor)를 직접 들고 있지 않다.
//     tensor 이름(string)으로 참조하고, 실제 tensor는 Graph나 Session이 관리.
//   - ONNX NodeProto → Node 변환은 onnx_parser가 담당.
//   - attribute는 MNIST MLP에서는 거의 필요 없지만,
//     나중에 Reshape의 shape 같은 속성을 처리하려면 필요.
