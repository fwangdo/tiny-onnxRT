#pragma once

// memory_arena.h — Tensor buffer 할당 및 재사용 관리
//
// 역할:
//   Runtime에서 중간 tensor의 메모리를 관리한다.
//   핵심 질문: "tensor buffer는 누가 만들고, 언제 재사용되는가?"
//
// 포함해야 할 것:
//   - MemoryArena 클래스:
//     - allocate(size_t size_in_bytes) → void*
//       → 중간 tensor를 위한 buffer 할당
//     - free(void* ptr)
//       → buffer 반환 (재사용 풀로 돌려놓기)
//     - reset()
//       → 모든 할당을 초기화 (추론 1회 끝난 후)
//     - stats() → 할당 횟수, 총 할당량, 재사용 횟수 등 통계
//
// 구현 전략 (단계별):
//   1단계 (M1): 단순 malloc/free wrapper
//     - 동작 확인이 목적. 최적화 없음.
//     - 할당마다 malloc, 해제마다 free.
//
//   2단계 (M2): 간단한 재사용 풀
//     - 해제된 buffer를 크기별로 보관
//     - 같은 크기(또는 더 큰) 요청이 오면 재사용
//     - std::map<size_t, vector<void*>> free_list
//
//   3단계 (M3): Profiling 기반 최적화
//     - 실행 전에 모든 tensor의 lifetime을 분석해서
//       buffer를 미리 계획(static memory planning)
//     - 이 정보는 Planner에서 ExecutionPlan에 포함시킬 수 있다
//
// 설계 고려사항:
//   - Arena는 execution plan 1회 실행의 lifetime과 맞춘다.
//     추론 시작 시 할당, 추론 끝나면 reset.
//   - Initializer(weight)는 arena가 관리하지 않는다.
//     weight는 모델 로드 시 한 번 할당하고 계속 유지.
//   - alignment: SIMD 최적화를 위해 16 또는 64 byte 정렬.
//     일단은 alignof(float) 정도로 충분.
