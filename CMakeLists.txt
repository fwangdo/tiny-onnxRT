cmake_minimum_required(VERSION 3.16)
project(tiny_onnxrt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: protobuf 의존성 설정
#   - find_package(Protobuf REQUIRED)
#   - onnx.proto3에서 C++ 소스 생성
#   - protobuf_generate_cpp()로 .pb.h / .pb.cc 생성

# TODO: 소스 파일 수집 및 실행 바이너리 타겟 정의
#   - src/ 하위 모든 .cpp를 수집
#   - add_executable(tiny_onnxrt main.cpp ${SOURCES})
#   - target_include_directories로 src/ 및 generated proto 헤더 경로 추가
#   - target_link_libraries로 protobuf 링크

# TODO: Google Test 설정
#   - FetchContent로 googletest 가져오기
#   - tests/ 하위 테스트 파일별 add_test 등록
#   - enable_testing()
