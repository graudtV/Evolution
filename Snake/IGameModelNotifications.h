#pragma once

#include <vector>

namespace evo {
namespace snake {

class TiledGameModel;
class IGameObject;
class IGameModelObserver;

/* Interface for registering observers of TiledGameModel
 * One observer may be added only once
 * It is guaranteed that observers are invoked in the same order
 *  as they were added */
class IGameModelNotifications {
public:
	void add_observer(IGameModelObserver *observer);
	void remove_observer(IGameModelObserver *observer);

protected:
	void notify_on_object_attachment(TiledGameModel& model, IGameObject& object);
	void notify_on_game_start(TiledGameModel& model);
	void notify_on_object_move(TiledGameModel& model, IGameObject& object);
	void notify_on_cycle_end(TiledGameModel& model);
	void notify_on_game_finish(TiledGameModel& model);

	IGameModelNotifications() {}
	
private:
	std::vector<IGameModelObserver *> m_observers;
};

} // snake namespace end
} // evo namespace end