# CMakeList.txt : openglstudy の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable (openglstudy 
	openglstudy.cpp 
	engine.cpp  "../graphics/graphics.h" "../graphics/graphics.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET openglstudy PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(openglstudy PUBLIC 
	${OPENGL_INCLUDE_DIR})

target_link_libraries(openglstudy 
	${OPENGL_LIBRARIES}
	graphics)

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。
