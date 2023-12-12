cmake_minimum_required(VERSION 3.5)

message("############# build nertc_sdk demo ############")

project(nertc_demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)

# sdk api & lib
if (TARGET_ARCH STREQUAL "x86_64" OR TARGET_ARCH STREQUAL "arm64")
    include_directories("${PROJECT_SOURCE_DIR}/NERTC_Linux_SDK_V5.4.10/${TARGET_ARCH}/include")
    link_directories("${PROJECT_SOURCE_DIR}/NERTC_Linux_SDK_V5.4.10/${TARGET_ARCH}/lib")
else ()
    message (FATAL_ERROR "TARGET_ARCH should be one of them: x86_64, arm64")
endif()

include_directories("${PROJECT_SOURCE_DIR}/cmdline")

file(GLOB SRC ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} -Wl,--start-group)
# static link libstdc++ and libgcc for compatibility
target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++)
target_link_libraries(${PROJECT_NAME} -Wl,--exclude-libs,ALL)
target_link_libraries(${PROJECT_NAME}  nertc_sdk)
target_link_libraries(${PROJECT_NAME}  protoopp)
target_link_libraries(${PROJECT_NAME}  pthread)
target_link_libraries(${PROJECT_NAME} -Wl,--end-group)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(FILES ${PROJECT_SOURCE_DIR}/run.sh DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/resource DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/NERTC_Linux_SDK_V5.4.10/${TARGET_ARCH}/lib DESTINATION .)
install(FILES ${PROJECT_SOURCE_DIR}/README.md DESTINATION .)
