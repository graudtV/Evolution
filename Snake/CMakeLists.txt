project(snake)

find_package(Boost REQUIRED)

add_executable(snake)

target_sources(snake PRIVATE
	Abstract/IGameModelNotifications.cpp
	Abstract/TiledGameModel.cpp
	main.cpp
	ISnakeKernel.cpp
	Snake.cpp
)

target_include_directories(snake PRIVATE
	${CMAKE_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
	)