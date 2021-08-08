#pragma once

namespace evo {
namespace detail {

template <class TiledMap>
class RegionIterator {
public:
	using TileType = typename TiledMap::TileType;

	/* Checks if iterator is const or non-const */
	static constexpr bool is_const_iterator()
		{ return std::is_const<TiledMap>::value; }

private:
	using PossiblyConstQualifiedTileType = std::conditional_t<is_const_iterator(),
		const TileType,
		TileType
	>;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = TileType;
	using reference = PossiblyConstQualifiedTileType&;
	using pointer = PossiblyConstQualifiedTileType *;
	using difference_type = std::ptrdiff_t;

	explicit RegionIterator(RegionType& region) :
		m_region(&region),
		m_row(0),
		m_column(0)
	{}

	RegionIterator(RegionType& region, size_t row, size_t column) :
		m_region(&region),
		m_row(row),
		m_column(column)
	{}

	RegionIterator& operator ++() {
		++m_column;
		if (m_column >= m_region->width()) {
			++m_row;
			m_column = 0;
		}
		return *this;
	}

	RegionIterator& operator --() {
		if (m_column == 0) {
			m_row = m_region->width();
			--m_column;
		}
		--m_row;
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
	RegionType *m_region;
	size_t m_row;
	size_t m_column;
};

template <class Region>
using ConstRegionIterator = RegionIterator<const Region>;


/* See note for equal() */
template <class Region>
bool operator ==(RegionIterator<Region> fst, RegionIterator<Region> last)
	{ return fst.equal(last); }

/* See note for equal() */
template <class Region>
bool operator !=(RegionIterator<Region> fst, RegionIterator<Region> last)
	{ return !fst.equal(last); }

template <class Region>
auto make_region_begin(Region& region) {
	return RegionIterator<Region>(region);
}

template <class Region>
auto make_region_end(Region& region) {
	return RegionIterator<Region>(region, region.height(), 0);
}

} // detail namespace end
} // evo namespace end