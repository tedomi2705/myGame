cmake_minimum_required(VERSION 3.0.0)
project(loldodge VERSION 0.1.0)

include(CTest)
enable_testing()
find_package(
    SDL2 REQUIRED
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
include_directories(
    ${PROJECT_SOURCE_DIR}/src/include
    ${PROJECT_SOURCE_DIR}/src
)
file(GLOB game_SRC
    "${PROJECT_SOURCE_DIR}/src/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)    

if (WIN32)
    set(SDL2_INCLUDE_DIR "C:/SDL2-2.0.22/x86_64-w64-mingw32/include/SDL2")
    set(SDL2_LIBRARY_DIR "C:/SDL2-2.0.22/x86_64-w64-mingw32/lib")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mwindows -static-libgcc -static-libstdc++")
    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIBRARY_DIR})
else ()
    include_directories(/usr/include/SDL2)
    include_directories(/usr/include/SDL)
endif ()

add_executable(loldodge ${game_SRC})
if (WIN32)
    target_link_libraries(loldodge -lmingw32)
endif ()
target_link_libraries(loldodge
    -lSDL2main
    -lSDL2
    -lSDL2_image
    -lSDL2_mixer
    -lSDL2_ttf
)

# install(DIRECTORY res DESTINATION res)
file(COPY res setting.ini highscore DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
if (WIN32)
    file(GLOB lib
        "${SDL2_LIBRARY_DIR}/../bin/*.dll"
        "${SDL2_LIBRARY_DIR}/../bin/*.txt"
    )    
    file(COPY ${lib} "C:/mingw64/bin/libwinpthread-1.dll" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif ()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
