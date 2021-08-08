#pragma once

#include "Abstract/ICollisionResolver.h"
#include "Support/TiledMap/TiledMap.h"

namespace evo {
namespace snake {

class IGameObject;

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
    SnakeGameCollisionResolver(size_t map_height, size_t map_width) :
        m_collision_map(map_height, map_width) {}

	void resolve_collisions(TiledGameModel& model) override;
private:
    TiledMap<std::vector<IGameObject *>> m_collision_map;
};

} // snake namespace end
} // evo namespace end