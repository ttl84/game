cmake_minimum_required(VERSION 2.9.0)
project(game)

# additional search paths
include_directories(../include ./include)
link_directories(../lib)

# get file list
file(GLOB SOURCES "src/*.cpp")

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic-errors -Wall")

# set libraries to link
set(LIBS SDL2main SDL2 SDL2_image)
if(MINGW)
	set(LIBS mingw32 ${LIBS})
	message(STATUS "MinGW is detected. Prepending -lmingw32 to link libraries.")
	message(STATUS "Libraries to link are: ${LIBS}")
endif(MINGW)


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_SOURCE_DIR}/bin")
