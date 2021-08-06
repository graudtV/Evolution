#pragma once

#include "game_defs.h"

namespace evo {
namespace snake {

class GameObjectLocation {
public:
	CoordArray& staging_segments() { return m_staging_segments; }
	void update_visible_segments() { m_visible_segments = m_staging_segments; }

	const CoordArray& visible_segments() const { return m_visible_segments; }
	const CoordArray& staging_segments() const { return m_staging_segments; }

private:
	CoordArray m_visible_segments;
	CoordArray m_staging_segments;
};

} // snake namespace end
} // evo namespace end