project(snake)

add_executable(snake)

target_sources(snake PRIVATE
	main.cpp
	IGameModelNotifications.cpp
	ISnakeKernel.cpp
	Snake.cpp
)

target_include_directories(snake PRIVATE ${CMAKE_SOURCE_DIR})