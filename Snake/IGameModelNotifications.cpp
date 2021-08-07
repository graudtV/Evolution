#include "IGameModelNotifications.h"
#include "IGameModelObserver.h"

namespace evo {
namespace snake {

void IGameModelNotifications::add_observer(IGameModelObserver *observer)
{
	assert(std::find(m_observers.begin(), m_observers.end(), observer)
		== m_observers.end() && "trying to add observer which has been already added");
	m_observers.push_back(observer);
}

void IGameModelNotifications::remove_observer(IGameModelObserver *observer)
{
	m_observers.erase(
		std::find(m_observers.begin(), m_observers.end(), observer)
	);
}

void IGameModelNotifications::notify_on_object_attachment(const TiledGameModel& model, const IGameObject& object) const
{
	std::for_each(m_observers.begin(), m_observers.end(),
		[&](IGameModelObserver *observer) {
			observer->on_object_attachment(model, object);
		}
	);
}

void IGameModelNotifications::notify_on_object_kill(const TiledGameModel& model, const IGameObject& object) const
{
	std::for_each(m_observers.begin(), m_observers.end(),
		[&](IGameModelObserver *observer) {
			observer->on_object_kill(model, object);
		}
	);
}

void IGameModelNotifications::notify_on_game_start(const TiledGameModel& model) const
{
	std::for_each(m_observers.begin(), m_observers.end(),
		[&](IGameModelObserver *observer) {
			observer->on_game_start(model);
		}
	);
}

void IGameModelNotifications::notify_on_game_finish(const TiledGameModel& model) const
{
	std::for_each(m_observers.begin(), m_observers.end(),
		[&](IGameModelObserver *observer) {
			observer->on_game_finish(model);
		}
	);
}

void IGameModelNotifications::notify_on_all_objects_moved(const TiledGameModel& model) const
{
	std::for_each(m_observers.begin(), m_observers.end(),
		[&](IGameModelObserver *observer) {
			observer->on_all_objects_moved(model);
		}
	);
}

void IGameModelNotifications::notify_on_collisions_resolved(const TiledGameModel& model) const
{
	std::for_each(m_observers.begin(), m_observers.end(),
		[&](IGameModelObserver *observer) {
			observer->on_collisions_resolved(model);
		}
	);
}

} // snake namespace end
} // evo namespace end