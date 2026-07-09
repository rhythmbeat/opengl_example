cmake_minimum_required(VERSION 3.13)
# spdlog 등 하위 의존성에서 발생하는 구버전 정책 경고 무시
cmake_policy(SET CMP0148 NEW)

set(PROJECT_NAME first_opengl_example)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "First Opengl Example")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(${PROJECT_NAME})
#이 유니코드 적용 코드는 내가 제미나이 보고 추가한 것
# MSVC(Visual Studio 컴파일러)를 사용할 때만 /utf-8 플래그를 추가함
if(MSVC)
    add_compile_options(/utf-8)
endif()

add_executable(${PROJECT_NAME} src/main.cpp)

include(Dependency.cmake)

# 우리 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})
#DEP_LIBS는 spdlog(디버그일 때는 spdlogd), glfw3를 담고 있음. 즉, 이 두 라이브러리를 링크하도록 설정

target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
    )
    #소스 코드 안에서의 define 매크로를 이용한 단축어 지정과 같음
    #define WINDOW_NAME "Hello, OpenGL!"

# Dependency들이 먼저 build 될 수 있게 관계 설정
add_dependencies(${PROJECT_NAME} ${DEP_LIST})
#DEP_LIST는 dep_glfw와 dep_spdlog(컴파일/설치를 어떻게할지 설정하는 옵션들의 이름표)를 담고 있음.
#즉, 이 두 dependency가 먼저 build 되도록 설정