#pragma once

namespace evo {
namespace snake {

class TiledGameModel;

class IGameFinalizer {
public:
	virtual ~IGameFinalizer() {}

	/* runs after all objects moved and collisions resolved to
	 * check, if game should be finished */
	virtual bool is_game_finished(const TiledGameModel& model) = 0;
};

} // snake namespace end
} // evo namespace end