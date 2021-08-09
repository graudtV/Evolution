#pragma once

#include "TiledMapTraits.h"
#include <utility> // for std::move
#include <iterator> // for iterator tags

namespace evo {
namespace detail {

template <class TiledMap>
class RegionIterator {
private:
	using Traits             = TiledMapTraits<TiledMap>;
	using Region             = typename Traits::Region;

public:
	using iterator_category  = std::bidirectional_iterator_tag;
	using value_type         = typename Traits::TileType;
	using reference          = typename Traits::Reference;
	using pointer            = typename Traits::Pointer;
	using difference_type    = std::ptrdiff_t;

	RegionIterator(Region region, size_t row, size_t column) :
		m_region(std::move(region)),
		m_row(row),
		m_column(column)
	{}

	template <bool Enable = Traits::is_map_const(), class = std::enable_if_t<Enable>>
	RegionIterator(const RegionIterator<std::remove_const_t<TiledMap>>& other) :
		RegionIterator(other.m_region, other.m_row, other.m_column)
	{}

	RegionIterator& operator ++() {
		++m_column;
		if (m_column >= m_region.width()) {
			m_column = 0;
			++m_row;
		}
		return *this;
	}

	RegionIterator& operator --() {
		if (m_column == 0) {
			m_column = m_region.width();
			--m_row;
		}
		--m_column;
	}	

	RegionIterator operator ++(int) {
		RegionIterator buf(*this);
		++(*this);
		return buf;
	}

	RegionIterator operator --(int) {
		RegionIterator buf(*this);
		--(*this);
		return buf;
	}

	reference operator *() const { return m_region[m_row][m_column]; }
	pointer operator ->() const { return &m_region[m_row][m_column]; }

	/* Note. Only iterators from the same region can be compared.
	 * All other comparisons are undefined behaviour */
	bool equal(RegionIterator other) const
		{ return m_row == other.m_row && m_column == other.m_column; }

private:
	Region m_region;
	size_t m_row;
	size_t m_column;

	template <class> friend class RegionIterator;
};

/* See note for equal() */
template <class Region>
bool operator ==(RegionIterator<Region> fst, RegionIterator<Region> last)
	{ return fst.equal(last); }

/* See note for equal() */
template <class Region>
bool operator !=(RegionIterator<Region> fst, RegionIterator<Region> last)
	{ return !fst.equal(last); }

template <
	class TiledMap,
	class Region = typename TiledMapTraits<TiledMap>::Region>
auto make_region_begin(Region&& region)
{
	return RegionIterator<TiledMap>(std::forward<Region>(region), 0 , 0);
}

template <
	class TiledMap,
	class Region = typename TiledMapTraits<TiledMap>::Region>
auto make_region_end(Region&& region)
{
	auto height = region.height();
	return RegionIterator<TiledMap>(std::forward<Region>(region), height, 0);
}

} // detail namespace end
} // evo namespace end