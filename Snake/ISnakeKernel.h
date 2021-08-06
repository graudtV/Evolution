#pragma once

#include "Snake.h"

namespace evo {
namespace snake {

/*  ISnakeKernel is a "brain" of snake, which is responsible for
 * make decisions on each cycle. There is an endless variety of
 * movement strategies, with which one can make experiments by
 * inheriting from this class
 *  Each snake has only one kernel and each kernel can be attached
 * to only one snake */
class ISnakeKernel {
public:
	bool is_attached_to_snake() const { return m_snake != nullptr; }
	Snake *snake() { return m_snake; }

	const TiledGameModel *game_model() const
		{ return is_attached_to_snake() ? m_snake->game_model() : nullptr; }

private:
	Snake *m_snake = nullptr;

	friend class Snake;
};

} // snake namespace end
} // evo namespace end