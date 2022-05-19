cmake_minimum_required(VERSION 3.0.0)
project(loldodge VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
include_directories(
        ${PROJECT_SOURCE_DIR}/src/include
        ${PROJECT_SOURCE_DIR}/src
)
file(GLOB game_SRC
    "${PROJECT_SOURCE_DIR}/src/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

set(SDL2_INCLUDE_DIR "C:/SDL2-2.0.20/x86_64-w64-mingw32/include/SDL2")
set(SDL2_LIBRARY_DIR "C:/SDL2-2.0.20/x86_64-w64-mingw32/lib")
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY_DIR})

add_executable(loldodge ${game_SRC})

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mwindows")
target_link_libraries(loldodge
    -lmingw32
    -lSDL2main
    -lSDL2
    -lSDL2_image
    -lSDL2_mixer
    -lSDL2_ttf
    )
# install(DIRECTORY res DESTINATION res)
file(COPY res setting.ini DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
