cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("openglstudy")

#this gets us OPENGL_LIBRARY
find_package(OpenGL REQUIRED)

set(thirdparty ${CMAKE_SOURCE_DIR}/thirdparty)

include_directories(
	${thirdparty}/glew-2.1.0/include/
	${thirdparty}/glfw-3.3.8.bin.WIN64/include/
	${thirdparty}/glm-0.9.9.8/
)

link_directories(
	${thirdparty}/glew-2.1.0/lib/Release/x64
	${thirdparty}/glfw-3.3.8.bin.WIN64/lib-vc2022
)

link_libraries(
	${OPENGL_LIBRARY}
	glfw3
	glew32
)

add_subdirectory ("openglstudy")
add_subdirectory ("graphics")

configure_file(
	${CMAKE_SOURCE_DIR}/thirdparty/glew-2.1.0/bin/Release/x64/glew32.dll
	${CMAKE_BINARY_DIR}/out/glew32.dll
	COPYONLY)

configure_file(
	${CMAKE_SOURCE_DIR}/graphics/shaders/fragmentshader.glsl
	${CMAKE_BINARY_DIR}/out/shaders/fragmentshader.glsl
	COPYONLY
)

configure_file(
	${CMAKE_SOURCE_DIR}/graphics/shaders/vertexshader.glsl
	${CMAKE_BINARY_DIR}/out/shaders/vertexshader.glsl
	COPYONLY
)

configure_file(
	${CMAKE_SOURCE_DIR}/assets/bitmaps/triangle.bmp
	${CMAKE_BINARY_DIR}/out/assets/bitmaps/triangle.bmp
	COPYONLY
)