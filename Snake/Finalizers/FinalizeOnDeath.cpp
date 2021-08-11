#include "FinalizeOnDeath.h"
#include "Snake/Abstract/IGameObject.h"
#include <cassert>

namespace evo {
namespace snake {

FinalizeOnDeath::FinalizeOnDeath(IGameObject *monitored_object) :
	m_monitored_object(monitored_object)
{
	assert(monitored_object != nullptr
		&& "monitored_object must be a valid pointer");
}

bool FinalizeOnDeath::is_game_finished(const TiledGameModel& model)
	{ return m_monitored_object->game_model() != &model; }

} // snake namespace end
} // evo namespace end