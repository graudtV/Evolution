#include "FinalizeIfNObjectsRemain.h"
#include "Snake/Abstract/TiledGameModel.h"

namespace evo {
namespace snake {

FinalizeIfNObjectsRemain::FinalizeIfNObjectsRemain(size_t nobjects) :
	m_nobjects(nobjects)
{
	assert(nobjects > 0 && "game will never finalize if nobjects == 0");
}

bool FinalizeIfNObjectsRemain::is_game_finished(const TiledGameModel& model)
	{ return model.objects().size() <= m_nobjects; }

} // snake namespace end
} // evo namespace end