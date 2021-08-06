#include "IGameModelNotifications.h"
#include "IGameModelObserver.h"

namespace evo {
namespace snake {

void IGameModelNotifications::add_observer(IGameModelObserver *observer)
{
	assert(std::find(m_observers.begin(), m_observers.end(), observer)
		== m_observers.end() && "trying to add observer which is already added");
	m_observers.push_back(observer);
}

void IGameModelNotifications::remove_observer(IGameModelObserver *observer)
{
	m_observers.erase(
		std::find(m_observers.begin(), m_observers.end(), observer)
	);
}

void IGameModelNotifications::notify_on_object_attachment(TiledGameModel& model, IGameObject& object)
{
	std::for_each(m_observers.begin(), m_observers.end(),
		[&](IGameModelObserver *observer) {
			observer->on_object_attachment(model, object);
		}
	);
}

void IGameModelNotifications::notify_on_game_start(TiledGameModel& model)
{
	std::for_each(m_observers.begin(), m_observers.end(),
		[&](IGameModelObserver *observer) {
			observer->on_game_start(model);
		}
	);
}

void IGameModelNotifications::notify_on_object_move(TiledGameModel& model, IGameObject& object)
{
	std::for_each(m_observers.begin(), m_observers.end(),
		[&](IGameModelObserver *observer) {
			observer->on_object_move(model, object);
		}
	);
}

void IGameModelNotifications::notify_on_cycle_end(TiledGameModel& model)
{
	std::for_each(m_observers.begin(), m_observers.end(),
		[&](IGameModelObserver *observer) {
			observer->on_cycle_end(model);
		}
	);
}

void IGameModelNotifications::notify_on_game_finish(TiledGameModel& model)
{
	std::for_each(m_observers.begin(), m_observers.end(),
		[&](IGameModelObserver *observer) {
			observer->on_game_finish(model);
		}
	);
}

} // snake namespace end
} // evo namespace end