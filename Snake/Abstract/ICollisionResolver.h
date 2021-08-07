#pragma once

namespace evo {
namespace snake {

class TiledGameModel;

class ICollisionResolver {
public:
	/* runs after all objects moved to resolve collisions and
	 * update game map */
	virtual void resolve_collisions(TiledGameModel& model) = 0;
};

} // snake namespace end
} // evo namespace end