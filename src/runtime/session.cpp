// session.cpp — Session 구현
//
// 구현해야 할 것:
//   - load_model(): parser → (pass) → planner → registry 순서로 초기화
//   - run(): tensor map 구성 → dispatcher 실행 → 결과 추출 → arena reset
//
// 주의:
//   - initializer tensor의 lifetime은 Session과 같다 (모델 로드 ~ Session 소멸).
//   - 중간 tensor의 lifetime은 run() 1회와 같다 (run 시작 ~ arena reset).
