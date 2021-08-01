#include "Snake.h"
#include "ISnakeKernel.h"
#include <cassert>

namespace evo {
namespace snake {

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

} // snake namespace end
} // evo namespace end