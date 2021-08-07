#pragma once

#include <vector>

namespace evo {
namespace snake {

class TiledGameModel;
class IGameObject;
class IGameModelObserver;

/* Interface for registering observers of TiledGameModel
 * One observer may be added only once
 * It is guaranteed that observers are invoked in the same order as they were added */
class IGameModelNotifications {
public:
	void add_observer(IGameModelObserver *observer);
	void remove_observer(IGameModelObserver *observer);

protected:
	void notify_on_object_attachment(const TiledGameModel& model, const IGameObject& object) const;
	void notify_on_object_kill(const TiledGameModel& model, const IGameObject& object) const;

	void notify_on_game_start(const TiledGameModel& model) const;
	void notify_on_game_finish(const TiledGameModel& model) const;

	void notify_on_all_objects_moved(const TiledGameModel& model) const;
	void notify_on_collisions_resolved(const TiledGameModel& model) const;

	IGameModelNotifications() {}
	
private:
	std::vector<IGameModelObserver *> m_observers;
};

} // snake namespace end
} // evo namespace end