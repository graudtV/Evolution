#include "TiledGameModel.h"
#include "IGameObject.h"
#include "ICollisionResolver.h"
#include "IGameFinalizer.h"
#include <cassert>

namespace evo {
namespace snake {

TiledGameModel::TiledGameModel(size_t height, size_t width,
		ICollisionResolver *resolver, IGameFinalizer *finalizer) :
	m_collision_resolver(*resolver),
	m_finalizer(*finalizer),
	m_map(height, width)
{
	assert(resolver != nullptr && "resolver must be a valid pointer");
	assert(finalizer != nullptr && "finalizer must be a valid pointer");
}

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
	notify_on_object_attachment(*this, *object);
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
	notify_on_object_kill(*this, object);
}

void TiledGameModel::start_game()
{
	assert(m_is_model_running == false && "game is already running");
	m_is_model_running = true;

	notify_on_game_start(*this);

	while (m_is_model_running) {
		move_game_objects();
		notify_on_all_objects_moved(*this);
		m_collision_resolver.resolve_collisions(*this);
		update_objects_visible_segments();
		notify_on_collisions_resolved(*this);
		m_is_model_running = !m_finalizer.is_game_finished(*this);
	}

	notify_on_game_finish(*this);
}

void TiledGameModel::move_game_objects()
{
	std::for_each(m_locations.begin(), m_locations.end(),
		[](auto&& elt) {
			auto& object = *elt.first;
			auto& location = elt.second;

			object.make_move(&location.staging_segments());
		}
	);	
}

void TiledGameModel::update_objects_visible_segments()
{
	auto&& locations = m_locations | boost::adaptors::map_values;
	std::for_each(locations.begin(), locations.end(),
		[](GameObjectLocation& location) {
			location.update_visible_segments();
		}
	);
}

} // snake namespace end
} // evo namespace end