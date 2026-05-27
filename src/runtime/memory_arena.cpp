// memory_arena.cpp — MemoryArena 구현
//
// 구현해야 할 것:
//   1단계: malloc/free wrapper + 통계 수집
//     - allocate(): malloc + 할당 횟수/크기 기록
//     - free(): free + 해제 기록
//     - reset(): 모든 추적 중인 포인터 해제
//     - stats(): 현재까지의 할당 통계 반환
//
//   2단계: free list 기반 재사용
//     - free() 시 buffer를 실제 해제하지 않고 free_list에 보관
//     - allocate() 시 free_list에서 적절한 크기의 buffer 검색
//     - 재사용 성공/실패 카운트 추적
