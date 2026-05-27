#pragma once

// pass.h — Compiler pass 인터페이스 (현재 빈칸)
//
// 역할:
//   Graph IR를 받아 변환(rewrite)하는 pass의 인터페이스.
//   M4에서 구현 예정. 지금은 runtime에 집중하므로 비워둔다.
//
// 나중에 구현할 것:
//   - Pass 인터페이스: virtual Graph run(const Graph&) = 0
//   - ConstantFoldingPass: 상수 입력만 가진 노드를 미리 계산해서 initializer로 대체
//   - DeadNodeEliminationPass: 출력에 도달하지 않는 노드 제거
//   - PassManager: 여러 pass를 순서대로 적용
//
// Compiler-runtime boundary 관점:
//   Pass의 출력은 여전히 Graph IR이다.
//   → Planner가 이 Graph를 받아 execution plan을 만든다.
//   → Pass가 graph를 어떻게 바꾸느냐에 따라 execution plan이 달라지고,
//     그것이 runtime 성능에 직접적으로 영향을 준다.
//   이 경계를 M4에서 실험적으로 확인할 예정.
