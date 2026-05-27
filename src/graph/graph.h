#pragma once

// graph.h — 내부 Graph IR 정의
//
// 역할:
//   ONNX 모델 전체를 내부 표현으로 변환한 결과.
//   노드(연산)와 텐서(데이터)의 관계를 담고 있으며,
//   execution planner가 이 Graph를 입력으로 받아 실행 계획을 만든다.
//
// 포함해야 할 것:
//   - nodes: vector<Node> — 연산 노드 목록 (순서는 ONNX 파일 순서, 정렬은 planner가)
//   - initializers: map<string, Tensor> — weight/bias 등 모델 파라미터
//     - ONNX의 GraphProto::initializer에서 로드
//     - 이름으로 참조: Node의 input name → initializer에서 lookup
//   - inputs: vector<string> — 그래프 입력 tensor 이름 (예: "input")
//   - outputs: vector<string> — 그래프 출력 tensor 이름 (예: "output")
//
// 핵심 관계:
//   Node.inputs[i] → initializer에 있으면 weight, 없으면 이전 노드의 출력
//   이 관계가 topological sort의 기반이 된다.
//
// 설계 고려사항:
//   - Graph는 "구조"만 표현한다. 실행 상태(buffer, 할당)는 runtime이 관리.
//   - compiler pass는 이 Graph를 변환(rewrite)하는 형태로 동작할 예정.
//     예: constant folding → initializer에 새 tensor 추가, node 제거
//   - ONNX의 subgraph(If, Loop 등)는 MNIST MLP에서 불필요하므로 무시.
