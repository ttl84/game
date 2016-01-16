cmake_minimum_required(VERSION 2.9.0)
project(game)

# additional search paths
include_directories(./include)

# get file list
file(GLOB SOURCES "src/*.cpp")

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic-errors -Wall -static-libstdc++")

# set libraries to link
message(STATUS "Setting up library names for glew, glu and opengl.")
if(WIN32 OR MSYS)
	message(STATUS "Windows/MSYS is detected.")
	set(LIBGLEW glew32)
	set(LIBGLU glu32)
	set(LIBOPENGL opengl32)
elseif(UNIX)
	message(STATUS "UNIX is detected.")
	set(LIBGLEW GLEW)
	set(LIBGLU GLU)
	set(LIBOPENGL GL)
endif(WIN32 OR MSYS)

set(LIBS SDL2 SDL2_image ${LIBGLEW} ${LIBGLU} ${LIBOPENGL})

if(MINGW)
	message(STATUS "MinGW is detected.")
	message(STATUS "Adding extra libraries to link.")
	set(LIBS mingw32 SDL2main ${LIBS})
endif(MINGW)


message(STATUS "Libraries to link are: ${LIBS}")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_SOURCE_DIR}/bin")
