#include "Snake.h"
#include "Abstract/TiledGameModel.h"
#include "SnakeGameCollisionResolver.h"
#include "Finalizers/FinalizeOnDeath.h"
#include <iostream>
#include "Support/debug.h"

using namespace evo::snake;

int main()
{
	size_t height = 10;
	size_t width = 30;

	Coord coords[] = {{1, 2}, {3, 4}, {5, 6}};
	SnakeBody body(std::begin(coords), std::end(coords));
	Snake snake(body);

	SnakeGameCollisionResolver resolver(height, width);
	FinalizeOnDeath finalizer(&snake);

	TiledGameModel model(height, width, &resolver, &finalizer);

	model.add_object(&snake, snake.staging_body().segments());
	model.start_game();

	return 0;
}