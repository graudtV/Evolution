#pragma once

#include "game_defs.h"
#include "IGameModelNotifications.h"
#include "IGameObject.h"
#include "Support/TiledMap/TiledMap.h"
#include <unordered_map>

namespace evo {
namespace snake {

class ICollisionResolver;
class IGameFinalizer;

class TiledGameModel : public IGameModelNotifications {
public:
	class Error;
	class BadLocationError;

	using GameMap = TiledMap<IGameObject *>;
	using ObjectArray = std::vector<IGameObject *>;

	TiledGameModel(size_t height, size_t width, ICollisionResolver *resolver, IGameFinalizer *finalizer);

	GameMap& game_map() { return m_map; }
	const GameMap& game_map() const { return m_map; }

	const ObjectArray& objects() const { return m_objects; }

	template <class CoordRange>
	void add_object(IGameObject *object, CoordRange&& initial_location);

	void kill_object(IGameObject& object);

	void start_game();

	bool is_running() const { return m_is_model_running; }

private:
	ICollisionResolver& m_collision_resolver;
	IGameFinalizer& m_finalizer;
	GameMap m_map;
	ObjectArray m_objects;
	bool m_is_model_running = false;

	void move_game_objects();
};

/* Base class for all TiledGameModel errors */
class TiledGameModel::Error : public std::runtime_error {
protected:
	Error(const char *what_arg) : std::runtime_error(what_arg) {}
};

class TiledGameModel::BadLocationError : public TiledGameModel::Error {
public:
	BadLocationError(const char *what_arg) : Error(what_arg) {}
};

} // snake namespace end
} // evo namespace end

#include "TiledGameModelImpl.h"