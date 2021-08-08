#pragma once

#include "game_defs.h"

namespace evo {
namespace snake {

class TiledGameModel;

class IGameObject {
public:
	virtual ~IGameObject() {}

	/* Object can make some stuff to change it location internally.
	 * The visible_location() of object, accessible throw TiledGameModel
	 * interface, doesn't change. The latter is update by ICollisionResolver,
	 * when all game object make move */
	virtual void make_move() = 0;

	const TiledGameModel *game_model() const { return m_game_model; }
private:
	const TiledGameModel *m_game_model;

	friend class TiledGameModel;
};

} // snake namespace end
} // evo namespace end