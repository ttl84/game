cmake_minimum_required(VERSION 2.9.0)
project(game)

# additional search paths
include_directories(./include)

# get file list
file(GLOB SOURCES "src/*.cpp")

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic-errors -Wall")

# set libraries to link
set(LIBS SDL2 SDL2_image)
if(MINGW)
	message(STATUS "MinGW is detected.")
	
	message(STATUS "Setting up link flags for sdl.")
	set(LIBS mingw32 SDL2main ${LIBS})
	
endif(MINGW)

if(MSYS)
	message(STATUS "MSYS is detected.")
	
	message(STATUS "Setting up link flags for opengl.")
	set(LIBS ${LIBS} glew32 glu32 opengl32)
endif(MSYS)

message(STATUS "Libraries to link are: ${LIBS}")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_SOURCE_DIR}/bin")
