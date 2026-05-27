// test_planner.cpp — Execution planner 테스트
//
// 테스트해야 할 것:
//   - 단순 linear graph → topological sort 결과가 올바른 순서인지
//   - ExecutionPlan의 step 수 == 그래프 노드 수
//   - 각 step의 input/output names가 올바른지
//   - 의존성이 꼬인 경우(cycle) 에러 처리
//
// 테스트용 Graph:
//   - 코드로 직접 Graph를 구성 (파서 없이)
//   - 예: A → MatMul → B → Relu → C
//     expected plan: [MatMul, Relu]
