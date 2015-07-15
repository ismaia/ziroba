include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib) 

set(BLACKLIB_DIR  ${CMAKE_SOURCE_DIR}/lib/blacklib)
include_directories(${BLACKLIB_DIR})
link_directories(${BLACKLIB_DIR}) 


#include(ExternalProject)
#ExternalProject_Add(
#    BlackLib
#    PREFIX            ${CMAKE_SOURCE_DIR}/lib/blacklib
#    GIT_REPOSITORY    https://github.com/yigityuce/BlackLib
#    UPDATE_COMMAND    ""
#    PATCH_COMMAND     ""
#    CONFIGURE_COMMAND ""
#    BUILD_COMMAND     ""
#    SOURCE_DIR        "${CMAKE_SOURCE_DIR}/build/BlackLib"    
#    INSTALL_DIR       "${CMAKE_SOURCE_DIR}/lib"
#    INSTALL_COMMAND   ""
#)


add_library(zrobot STATIC ZRobot.cpp)
install(TARGETS zrobot DESTINATION lib)

#these are all compiled the same way
set(PROGRAMS ZKeypad ZBtJoystickClient ZBtJoystickServer)
set(CORELIBS ncurses zrobot blacklib)

foreach(program ${PROGRAMS})
    string(TOLOWER ${program} lcaseprogram)
    add_executable(${lcaseprogram} ${program}.cpp)
    target_link_libraries(${lcaseprogram} ${CORELIBS})
    install(TARGETS ${lcaseprogram} DESTINATION bin)
endforeach(program)



