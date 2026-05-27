#pragma once

// profiler.h — Runtime 성능 측정
//
// 역할:
//   Op별 실행 시간, 메모리 사용량을 측정해서
//   runtime 개선의 근거 데이터를 제공한다.
//   "profiling 결과를 보고 runtime을 어떻게 개선하는가?"에 답하기 위한 모듈.
//
// 포함해야 할 것:
//   - Profiler 클래스:
//     - begin_op(const std::string& op_name)
//       → 타이머 시작. chrono::high_resolution_clock 사용.
//     - end_op(const std::string& op_name)
//       → 타이머 종료. 소요 시간 기록.
//     - report() → 프로파일링 결과 출력
//       - 각 op의 실행 시간 (us 단위)
//       - 전체 추론 시간
//       - op별 비율 (%)
//       - (M3에서) 메모리 할당량, 재사용 비율
//
//   - OpProfile 구조체:
//     - op_name: string
//     - call_count: int
//     - total_time_us: double
//     - min_time_us / max_time_us: double
//
// 설계 고려사항:
//   - Profiler는 optional이다. Dispatcher 생성 시 nullptr이면 측정 안 함.
//   - 측정 오버헤드를 최소화: begin/end는 clock 읽기만 한다.
//   - report()는 stderr 또는 별도 파일로 출력.
//   - M3에서 MemoryArena의 stats()와 결합하면
//     "어떤 op가 메모리를 많이 쓰는가"도 확인 가능.
