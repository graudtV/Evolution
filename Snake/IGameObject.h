#pragma once

#include "game_defs.h"

namespace evo {
namespace snake {

class TiledGameModel;

class IGameObject {
public:
	virtual ~IGameObject() {}

	/* new_location is filled with visible location of the
	 * object, to which it is passed. Object may either change
	 * new_location to its new desired (i.e. staging)
	 * location (which will be then considered during collision
	 * resolution) or remain it unchanged, if it doesn't want to move
	 */
	virtual void make_move(CoordArray *new_location) = 0;

	const TiledGameModel *game_model() const { return m_game_model; }
private:
	const TiledGameModel *m_game_model;

	friend class TiledGameModel;
};

} // snake namespace end
} // evo namespace end