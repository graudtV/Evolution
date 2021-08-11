#pragma once

#include "Snake/Abstract/IGameFinalizer.h"
#include <cstddef> // for size_t

namespace evo {
namespace snake {

/* Finalizes game if number of objects in game model
 * is equal to or less than specified number */
class FinalizeIfNObjectsRemain : public IGameFinalizer {
public:
	FinalizeIfNObjectsRemain(size_t nobjects);

	bool is_game_finished(const TiledGameModel& model) override;

private:
	size_t m_nobjects;
};

} // snake namespace end
} // evo namespace end