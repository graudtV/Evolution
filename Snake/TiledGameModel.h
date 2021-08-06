#pragma once

#include "IGameModelNotifications.h"
#include "GameObjectLocation.h"
#include "Support/TiledMap.h"
#include <unordered_map>

namespace evo {
namespace snake {

class TiledGameModel : public IGameModelNotifications {
public:
	using GameMap = TiledMap<IGameObject *>;

	TiledGameModel(size_t height, size_t width) : m_map(height, width) {}

	GameMap& game_map() { return m_map; }
	const GameMap& game_map() const { return m_map; }

	GameObjectLocation& location_of(const IGameObject& object);
	const GameObjectLocation& location_of(const IGameObject& object) const;

	void add_object(IGameObject *object, const CoordArray& initial_location);

	void start_game();

	/* Should be invoked from some game model observer to stop game.
	 * Then invoked, TiledGameModel completes all pending events, invokes
	 * on_game_finish() for each observers and returns from start_game()
	 * (if no observer restarted the game) */
	void finish_game();

	bool is_running() const { return m_is_model_running; }

private:
	GameMap m_map;
	bool m_is_model_running = false;
	std::unordered_map<IGameObject *, GameObjectLocation> m_locations;
};

} // snake namespace end
} // evo namespace end