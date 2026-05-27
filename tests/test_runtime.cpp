// test_runtime.cpp — Runtime 컴포넌트 개별 테스트
//
// 테스트해야 할 것:
//
// [KernelRegistry]
//   - kernel 등록 후 조회가 정상 동작하는지
//   - 등록되지 않은 op 조회 시 에러 처리
//
// [MemoryArena]
//   - allocate() → 유효한 포인터 반환
//   - free() → 이후 allocate()에서 재사용 (2단계)
//   - reset() → 모든 할당 해제
//   - stats() → 할당 횟수/크기가 올바른지
//
// [Kernels]
//   - MatMul: 작은 행렬(2x3 * 3x2)로 결과 검증
//   - Add: element-wise 덧셈 + broadcasting 케이스
//   - Relu: 음수 → 0, 양수 → 그대로
//   - Softmax: 결과의 합이 1.0인지, 값이 [0,1] 범위인지
//
// [Profiler]
//   - begin_op/end_op 후 report()에 기록이 남는지
//   - 여러 번 호출 시 call_count 증가하는지
