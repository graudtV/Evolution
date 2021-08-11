#pragma once

#include "Snake/Abstract/IGameFinalizer.h"

namespace evo {
namespace snake {

class IGameObject;

/* Finalizes game if specified object is not attached to the game.
 * In practise object becomes detached when it is killed */
class FinalizeOnDeath : public IGameFinalizer {
public:
	FinalizeOnDeath(IGameObject *monitored_object);

	bool is_game_finished(const TiledGameModel& model) override;
	
private:
	IGameObject *m_monitored_object;
};

} // snake namespace end
} // evo namespace end