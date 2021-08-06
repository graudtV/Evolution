#pragma once

namespace evo {
namespace snake {

class TiledGameModel;
class IGameObject;

class IGameModelObserver {
public:
	/* called each time new object is added to TiledGameModel with
	 * TiledGameModel::add_object(). That object is passed as argument */
	virtual void on_object_attachment(TiledGameModel& model, IGameObject& object) {}

	/* called then game starts running */
	virtual void on_game_start(TiledGameModel& model) {}

	/* called each time after IGameObject::make_move() is invoked for
	 * some object. That object is passed as argument */
	virtual void on_object_move(TiledGameModel& model, IGameObject& object) {}

	/* called then IGameObject::make_move() was invoked for all objects */
	virtual void on_cycle_end(TiledGameModel& model) {}

	/* called then game is stopped, but previously was running */
	virtual void on_game_finish(TiledGameModel& model) {}
};

// TODO
// class IGameModelReadonlyObserver() : public IGameModelObserver {
// 
// }

} // snake namespace end
} // evo namespace end