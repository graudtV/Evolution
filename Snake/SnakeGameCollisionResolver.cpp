#include "SnakeGameCollisionResolver.h"
#include "Abstract/TiledGameModel.h"
#include "Snake.h"
#include <boost/range/algorithm.hpp>

namespace evo {
namespace snake {

void SnakeGameCollisionResolver::resolve_collisions(TiledGameModel& model)
{
	assert(model.game_map().height() == m_collision_map.height()
		&& model.game_map().width() == m_collision_map.width()
		&& "model must have the same game map size as the one specified "
		"during SnakeGameCollisionResolver creation");


}

// void SnakeGameCollisionResolver::init_collision_map(TiledGameModel& model)
// {
// 	// TODO: should be refactored when iterators for TiledMap are
// 	// implemented
// 	for (size_t row = 0; row < m_collision_map.height(); ++row)
// 		for (size_t column = 0; column < m_collision_map.width(); ++column) {

// 		}


// 	boost::for_each(model.objects(),
// 		[](IGameObject *object) {
// 			Snake *snake = cast<Snake *>(object);
// 		//	add_object_to_collision_map(static_cast<>)	
// 		}
// 	);
// }

} // snake namespace end
} // evo namespace end