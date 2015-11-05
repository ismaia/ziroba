include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(MRAA_DIR  ${CMAKE_SOURCE_DIR}/lib/mraa)
include_directories(${MRAA_DIR}/include)
link_directories(${MRAA_DIR}/lib ${MRAA_DIR}/lib64)

set(BLIBDIR ${CMAKE_SOURCE_DIR}/lib/blackib)
include_directories(${BLIBDIR}/include)
link_directories(${BLIBDIR}/lib)


include(ExternalProject)
ExternalProject_Add(
    Mraa
    GIT_REPOSITORY    https://github.com/intel-iot-devkit/mraa
    GIT_TAG           v0.8.1
    CMAKE_ARGS        -DBUILDSWIG=OFF -DBUILDSWIGNODE=OFF -DBUILDSWIGPYTHON=OFF -DCMAKE_INSTALL_PREFIX=${MRAA_DIR}
    SOURCE_DIR        ${CMAKE_SOURCE_DIR}/build/mraa
)

include(ExternalProject)
ExternalProject_Add(
    BlackLib
    GIT_REPOSITORY    https://github.com/yigityuce/BlackLib
    SOURCE_DIR        ${CMAKE_SOURCE_DIR}/build/BlackLib
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    UPDATE_COMMAND    ""
    PATCH_COMMAND     ""
    INSTALL_COMMAND   ""
)

add_library(zrobot STATIC zcommon.cpp znet.cpp zmotion.cpp pinmapper.cpp)
install(TARGETS zrobot DESTINATION lib)

#add_library(blacklib STATIC   )
#SOURCES=./BlackADC/BlackADC.cpp ./BlackDirectory/BlackDirectory.cpp  ./BlackGPIO/BlackGPIO.cpp ./BlackI2C/BlackI2C.cpp ./BlackMutex/BlackMutex.cpp ./BlackPWM/BlackPWM.cpp ./BlackSPI/BlackSPI.cpp ./BlackThread/BlackThread.cpp ./BlackTime/BlackTime.cpp  ./BlackUART/BlackUART.cpp ./BlackCore.cpp

#these are all compiled the same way
set(CPP_PROGRAMS ziroba)
set(C_PROGRAMS )
set(CORELIBS mraa sfml-system sfml-network zrobot)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -std=c99")
foreach(program ${C_PROGRAMS})
    string(TOLOWER ${program} lcaseprogram)
    add_executable(${lcaseprogram} ${program}.c)
    target_link_libraries(${lcaseprogram} ${CORELIBS})
    install(TARGETS ${lcaseprogram} DESTINATION bin)
endforeach(program)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -std=gnu++11")
foreach(program ${CPP_PROGRAMS})
    string(TOLOWER ${program} lcaseprogram)
    add_executable(${lcaseprogram} ${program}.cpp)
    target_link_libraries(${lcaseprogram} ${CORELIBS})
    install(TARGETS ${lcaseprogram} DESTINATION bin)
endforeach(program)
