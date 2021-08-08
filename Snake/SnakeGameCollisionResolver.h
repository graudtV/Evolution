#pragma once

#include "Abstract/ICollisionResolver.h"

namespace evo {
namespace snake {

/* Collision resolver for snake-only game.
 * If there are any other objects in game model except
 * Snake, behaviour is undefined. 
 *
 * Collision resolution policy:
 * - If any segment of some snake is collided by a head
 * of any snake on game map (including the snake itself),
 * then the former snake dies
 * - This rule is applyed to each snake, even to those, who
 * turned out to be killed during the current resolution process.
 * For example, two snakes, who collides with their heads, kills
 * each other
 */
class SnakeGameCollisionResolver : public ICollisionResolver {
public:
	void resolve_collisions(TiledGameModel& model) override;
};

} // snake namespace end
} // evo namespace end