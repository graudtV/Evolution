project(snake)

find_package(Boost REQUIRED)

add_executable(snake)

target_sources(snake PRIVATE
	main.cpp
	IGameModelNotifications.cpp
	ISnakeKernel.cpp
	Snake.cpp
	TiledGameModel.cpp
)

target_include_directories(snake PRIVATE
	${CMAKE_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
	)