#pragma once

#include <boost/range/concepts.hpp>
#include <boost/range/algorithm.hpp>

namespace evo {
namespace snake {

/* If initial_location overlays location of some previously added object,
 * then BadLocationError is thrown, and TiledGameModel is in
 * unspecified state (base exception guarantee), game object
 * remains unchanged */
template <class CoordRange>
void TiledGameModel::add_object(IGameObject *object, CoordRange&& initial_location)
{
	BOOST_CONCEPT_ASSERT(( boost::SinglePassRangeConcept<CoordRange> ));

	using RangeValueType = typename std::iterator_traits<
		typename boost::range_iterator<CoordRange>::type
	>::value_type;

	static_assert(std::is_convertible<RangeValueType, Coord>::value,
		"expected a range of coordinates"
	);

	assert(object != nullptr && "object must be a valid pointer");
	assert(object->game_model() == nullptr && "object is already attached to some game");

	boost::for_each(initial_location,
		[this, object](Coord coord) {
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

} // snake namespace end
} // evo namespace end