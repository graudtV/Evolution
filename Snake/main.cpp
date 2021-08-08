#include "Snake.h"
#include "Abstract/TiledGameModel.h"
#include "SnakeGameCollisionResolver.h"
#include <iostream>
#include "Support/debug.h"

using namespace evo::snake;

int main()
{
	size_t height = 10;
	size_t width = 30;

	SnakeGameCollisionResolver resolver(height, width);
	IGameFinalizer *finalizer = nullptr;

	TiledGameModel model(height, width, &resolver, finalizer);

	Coord coords[] = {{1, 2}, {3, 4}, {5, 6}};
	SnakeBody body(std::begin(coords), std::end(coords));
	Snake snake(body);

	model.add_object(&snake, snake.staging_body().segments());

	return 0;
}