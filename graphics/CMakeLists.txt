add_library(graphics STATIC
	graphics.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET graphics PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(graphics PUBLIC 
	${OPENGL_INCLUDE_DIR})

target_link_libraries(graphics 
	${OPENGL_LIBRARIES})