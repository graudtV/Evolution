#pragma once

#include "IGameObject.h"

namespace evo {
namespace snake {

class ISnakeKernel;

class Snake : public IGameObject {
public:
	explicit Snake(GameModel& game_model) :
		IGameObject(game_model), m_kernel(nullptr) {}

	void attach_kernel(ISnakeKernel& kernel);
	void detach_kernel();
	bool is_kernel_attached() const { return m_kernel != nullptr; }
	ISnakeKernel *kernel() { return m_kernel; }

private:
	ISnakeKernel *m_kernel;
};

} // snake namespace end
} // evo namespace end