#pragma once

#include <vector>

namespace evo {
namespace snake {

struct Coord {
	unsigned row = 0;
	unsigned column = 0;
};

using CoordArray = std::vector<Coord>;

} // snake namespace end
} // evo namespace end