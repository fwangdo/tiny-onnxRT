#pragma once

// execution_plan.h — 실행 계획 자료구조
//
// 역할:
//   Graph IR의 노드를 "어떤 순서로 실행할지" 정리한 결과물.
//   Planner가 생성하고, Runtime(Dispatcher)이 소비한다.
//   이것이 compiler → runtime의 핵심 인터페이스이다.
//
// 포함해야 할 것:
//   - ExecutionStep: 하나의 실행 단위
//     - node_index 또는 Node 참조: 어떤 노드를 실행할지
//     - input_names: 이 step에서 읽을 tensor 이름들
//     - output_names: 이 step에서 쓸 tensor 이름들
//   - ExecutionPlan: vector<ExecutionStep>
//     - 순서대로 실행하면 전체 그래프가 계산됨
//
// 설계 고려사항:
//   - 현재는 단순 topological sort 결과 = 실행 순서.
//     하지만 나중에 memory planning 정보를 여기에 추가할 수 있다:
//     - 각 step에서 어떤 buffer를 할당/해제할지
//     - 어떤 buffer를 재사용(in-place)할지
//   - ExecutionPlan은 Graph와 독립적인 자료구조여야 한다.
//     Graph가 바뀌면(compiler pass) 새 plan을 만들면 된다.
//   - 이 자료구조가 runtime의 "입력 계약"이다.
//     runtime은 Graph를 직접 보지 않고, ExecutionPlan만 보고 실행한다.
