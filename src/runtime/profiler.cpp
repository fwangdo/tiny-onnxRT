// profiler.cpp — Profiler 구현
//
// 구현해야 할 것:
//   - begin_op(): clock 읽어서 시작 시간 저장
//   - end_op(): clock 읽어서 duration 계산, OpProfile에 누적
//   - report(): 수집된 OpProfile들을 정리해서 출력
//     - 시간 기준 정렬 (가장 오래 걸린 op 먼저)
//     - 전체 대비 비율 계산
//
// 내부 저장소:
//   - std::unordered_map<string, OpProfile> profiles_
//   - 현재 진행 중인 op의 시작 시간 (stack 또는 단일 변수)
