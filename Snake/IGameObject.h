#pragma once

#include "game_defs.h"
#include <vector>

namespace evo {
namespace snake {

class GameModel;

/*  GameObjectLocation class represents list of segments, which 
 * are occupied by some game object
 *  There are two different list of segments, associated with each
 * game object: visible segments and staging segments
 *  Visible segments stand for location of game object after each
 * game model cycle. It is updated only when each game object made
 * its move. This enables game objects to access location of each
 * other, not depending on order of movements of game objects
 *  Staging segments stand for location which some game object
 * wants to occupy during current game cycle. After all game objects
 * made decision, GameModel runs collision resolution, and if
 * there is no collisions with the object, updates game object
 * visible segments exactly to the staging ones. Otherwise, if
 * collisions occured, it tries to resolve them somehow or kill
 * game object */
class GameObjectLocation {
public:
	using CoordArray = std::vector<Coord>;

	const CoordArray& visible_segments() const { return m_visible_segments; }
	const CoordArray& staging_segments() const { return m_staging_segments;}

protected:
	CoordArray& staging_segments() { return m_staging_segments; }

private:
	CoordArray m_visible_segments;
	CoordArray m_staging_segments;

	// invoked by GameModel after each cycle
	void update_visible_segments() { m_visible_segments = m_staging_segments; }

	friend class GameModel;
};

class IGameObject : public GameObjectLocation {
public:
	explicit IGameObject(GameModel& game_model) :
		m_game_model(game_model) {}

	virtual ~IGameObject() {}

	GameModel& game_model() { return m_game_model; }
	const GameObjectLocation& location() { return m_location; }

	/* Runs some logic to make decision. Result should be
	 * written is m_location.staging_segments() */
	virtual void make_move(CoordArray *staging_segments) = 0;

private:
	GameModel& m_game_model;
	GameObjectLocation m_location;
};

} // snake namespace end
} // evo namespace end