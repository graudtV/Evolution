#include "Snake.h"
#include "ISnakeKernel.h"
#include "Abstract/TiledGameModel.h"
#include <cassert>

namespace evo {
namespace snake {

Snake::Snake(const SnakeBody& body) :
	m_staging_body(body),
	m_visible_body(body),
	m_kernel(nullptr)
{
	assert(body.segments().size() >= 1 && "snake must have non-empty body");
}

void Snake::attach_kernel(ISnakeKernel& kernel)
{
	assert(!is_kernel_attached() && "snake already has attached kernel");
	assert(!kernel.is_attached_to_snake() && "kernel is already attached to some snake");
	m_kernel = &kernel;
	kernel.m_snake = this;
}

void Snake::detach_kernel()
{
	assert(is_kernel_attached() && "no kernel attached to this snake");
	assert(m_kernel->snake() == this && "broken link between snake and kernel");
	m_kernel = nullptr;
	m_kernel->m_snake = nullptr;
}

void Snake::make_move()
{
	assert(is_kernel_attached() && "no kernel attached to this snake");
	auto direction = m_kernel->make_decision();

	auto map_height = game_model()->game_map().height();
	auto map_width = game_model()->game_map().width();

	Coord head = m_staging_body.head();

	switch (direction) {
	case SnakeDirection::eUp:
		head.row = (head.row + map_height - 1) % map_height;
		break;
	case SnakeDirection::eDown:
		head.row = (head.row + 1) % map_height;
		break;
	case SnakeDirection::eLeft:
		head.column = (head.column + map_width - 1) % map_width;
		break;
	case SnakeDirection::eRight:
		head.column = (head.column + 1) & map_width;
		break;
	default:
		assert(0 && "unreachable");
		break;
	}
	m_staging_body.push_head(head);
	m_staging_body.pop_tail();
}

} // snake namespace end
} // evo namespace end