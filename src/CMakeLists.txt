include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(MRAA_DIR  ${CMAKE_SOURCE_DIR}/lib/mraa)
include_directories(${MRAA_DIR}/include)
link_directories(${MRAA_DIR}/lib ${MRAA_DIR}/lib64)


include(ExternalProject)
ExternalProject_Add(
    Mraa
    GIT_REPOSITORY    https://github.com/intel-iot-devkit/mraa
    GIT_TAG           v0.8.1
    CMAKE_ARGS        -DBUILDSWIG=OFF -DBUILDSWIGNODE=OFF -DBUILDSWIGPYTHON=OFF -DENABLEEXAMPLES=OFF -DCMAKE_INSTALL_PREFIX=${MRAA_DIR}
    SOURCE_DIR        ${CMAKE_SOURCE_DIR}/build/mraa
)


add_library(zrobot STATIC zcommon.cpp znet.cpp zmotion.cpp zirobarobot.cpp)
install(TARGETS zrobot DESTINATION lib)

#these are all compiled the same way
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -std=gnu++11")
set(MAIN_PROGRAM zmain)
set(BINARY_NAME ziroba)
set(CORELIBS mraa sfml-system sfml-network zrobot)
add_executable(${BINARY_NAME} zmain.cpp)
target_link_libraries(${BINARY_NAME} ${CORELIBS})
install(TARGETS ${BINARY_NAME} DESTINATION bin)
