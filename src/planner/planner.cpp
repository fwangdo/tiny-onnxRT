// planner.cpp — Graph IR → ExecutionPlan 변환
//
// 구현해야 할 것:
//   - plan(const Graph&) → ExecutionPlan
//     1. Graph의 노드들을 topological sort
//        - 각 노드의 input이 initializer이거나
//          이미 실행된 노드의 output이면 실행 가능
//        - Kahn's algorithm (in-degree 기반) 또는 DFS 기반
//     2. 정렬된 순서대로 ExecutionStep 생성
//     3. ExecutionPlan 반환
//
// Topological sort 구현:
//   - 각 tensor name → 그것을 생성하는 node index 매핑 구축
//   - 각 node의 in-degree 계산 (input 중 initializer가 아닌 것의 수)
//   - in-degree가 0인 노드부터 큐에 넣고 BFS
//   - 큐에서 꺼낸 순서가 실행 순서
//
// 참고:
//   MNIST MLP는 linear graph(분기 없음)이므로
//   topological sort 결과 = ONNX 파일의 노드 순서와 동일할 가능성이 높다.
//   그래도 정확한 구현을 해야 나중에 분기 있는 그래프에서도 동작한다.
