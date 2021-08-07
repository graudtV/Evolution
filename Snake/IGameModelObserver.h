#pragma once

namespace evo {
namespace snake {

class TiledGameModel;
class IGameObject;

class IGameModelObserver {
public:
	virtual ~IGameModelObserver() {}

	virtual void on_object_attachment(const TiledGameModel& model, const IGameObject& object) {}
	virtual void on_object_kill(const TiledGameModel& model, const IGameObject& object) {}

	virtual void on_game_start(const TiledGameModel& model) {}
	virtual void on_game_finish(const TiledGameModel& model) {}

	virtual void on_all_objects_moved(const TiledGameModel& model) {}
	virtual void on_collisions_resolved(const TiledGameModel& model) {}
};

} // snake namespace end
} // evo namespace end