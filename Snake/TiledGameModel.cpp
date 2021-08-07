#include "TiledGameModel.h"
#include "IGameObject.h"
#include <cassert>

namespace evo {
namespace snake {

GameObjectLocation&
TiledGameModel::location_of(IGameObject& object)
{
	auto search = m_locations.find(&object);
	assert(search != m_locations.end() && "object is not attached to this game model");
	return search->second;
}

const GameObjectLocation&
TiledGameModel::location_of(const IGameObject& object) const
{
	auto *key = const_cast<IGameObject *>(&object);
	auto search = m_locations.find(key);
	assert(search != m_locations.end() && "object is not attached to this game model");
	return search->second;
}

/* If initial_location overlays some previously added object location,
 * when BadLocationError is thrown, and TiledGameModel is in
 * unspecified state (base exception guarantee), game object
 * remains unchanged */
void TiledGameModel::add_object(IGameObject *object, const CoordArray& initial_location)
{
	assert(object != nullptr && "object must be a valid pointer");
	assert(object->game_model() == nullptr && "object is already attached to some game");

	auto& object_location = m_locations[object];
	object_location.staging_segments() = initial_location;
	object_location.update_visible_segments();

	std::for_each(initial_location.begin(), initial_location.end(),
		[this, object](Coord coord){
			auto& tile = m_map[coord.row][coord.column];
			if (tile) {
				throw BadLocationError("TiledGameModel::add_object: "
					"trying to place new object on already occupied position");
			}
			tile = object;
		}
	);

	object->m_game_model = this;
}

void TiledGameModel::kill_object(IGameObject& object)
{
	assert(object.game_model() == this && "object is not attached to this game model");

	auto& segments = location_of(object).visible_segments();
	std::for_each(segments.begin(), segments.end(),
		[this, &object] (Coord coord) {
			auto& tile = m_map[coord.row][coord.column];
			assert(tile == &object);
			tile = nullptr;
		}
	);

	m_locations.erase(&object);
	object.m_game_model = nullptr;
}

} // snake namespace end
} // evo namespace end