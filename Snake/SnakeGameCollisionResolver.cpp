#include "SnakeGameCollisionResolver.h"
#include "Abstract/TiledGameModel.h"
#include "Snake.h"
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <set>

namespace evo {
namespace snake {

namespace {

const auto cast_game_object_to_snake = [](IGameObject *object) {
	return cast<Snake *>(object);
};

/* result: [index, snake_ptr] */
const auto enumerate_snakes = [](TiledGameModel& model) {
	return model.objects()
		| boost::adaptors::transformed(cast_game_object_to_snake)
		| boost::adaptors::indexed(0); 
};

class all_except_idx {
public:
	all_except_idx(size_t idx) : m_idx(idx) {}

	bool operator ()(size_t other_idx) const
		{ return other_idx != m_idx; }
private:
	size_t m_idx;
};

} // anonymous namespace end

void SnakeGameCollisionResolver::resolve_collisions(TiledGameModel& model)
{
	/* Implimentation relies on the fact that objects in model
	 * doesn't change order unless they are added/killed */
	BOOST_CONCEPT_ASSERT(( boost::ForwardRangeConcept<decltype(model.objects())> ));

	assert(model.game_map().height() == m_collision_map.height()
		&& model.game_map().width() == m_collision_map.width()
		&& "model must have the same game map size as the one specified "
		"during SnakeGameCollisionResolver creation");

	fill_collision_map(model);

	m_is_object_killed.clear();
	m_is_object_killed.resize(model.objects().size());

	/* main collision resolution routine. markes killed objects
	 * in m_is_object_killed */
	for (auto&& [idx, snake] : enumerate_snakes(model)) {
		Coord snake_head = snake->staging_body().head();
		for (ObjectIdx idx : m_collision_map[snake_head.row][snake_head.column]
				| boost::adaptors::filtered(all_except_idx(idx))) {
			m_is_object_killed[idx] = true;
		}
	}

	/* objects cannot be killed during iteration,
	 * putting them in pending killings list */
	m_to_be_killed.clear();
	for (auto&& [idx, snake] : enumerate_snakes(model)) {

		if (m_is_object_killed[idx])
			m_to_be_killed.push_back(snake);
	}

	/* killing them now */
	for (IGameObject *object : m_to_be_killed)
		model.kill_object(*object);
}

void SnakeGameCollisionResolver::fill_collision_map(TiledGameModel& model)
{
	m_collision_map.clear();

	for (auto&& [idx, snake] : enumerate_snakes(model))
		for (Coord segment : snake->staging_body().segments())
			m_collision_map[segment.row][segment.column].push_back(idx);
}

} // snake namespace end
} // evo namespace end