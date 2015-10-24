include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib) 

set(MRAA_DIR  ${CMAKE_SOURCE_DIR}/lib/mraa)
include_directories(${MRAA_DIR}/include)
link_directories(${MRAA_DIR}/lib ${MRAA_DIR}/lib64) 


include(ExternalProject)
ExternalProject_Add(
    Mraa
    GIT_REPOSITORY    https://github.com/intel-iot-devkit/mraa
    GIT_TAG           v0.8.0
    CMAKE_ARGS        -DBUILDSWIG=OFF -DBUILDSWIGNODE=OFF -DBUILDSWIGPYTHON=OFF -DCMAKE_INSTALL_PREFIX=${MRAA_DIR} 
    SOURCE_DIR        ${CMAKE_SOURCE_DIR}/build/mraa
)


#add_library(zrobot STATIC ZRobot.cpp)
#install(TARGETS zrobot DESTINATION lib)

#these are all compiled the same way
set(CPP_PROGRAMS ziroba)
set(C_PROGRAMS mraa-gpio)
set(CORELIBS ncurses mraa sfml-system sfml-network)

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


