#pragma once

#include "ISnakeKernel.h"

namespace evo {
namespace snake {

/* Just always runs up */
class DummySnakeKernel : public ISnakeKernel {
public:
	SnakeDirection make_decision() override { return SnakeDirection::eUp; }
};

} // snake namespace end
} // evo namespace end