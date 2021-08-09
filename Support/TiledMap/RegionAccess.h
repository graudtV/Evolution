#pragma once

#include "ProxyRow.h"
#include "RegionIterator.h"
#include <type_traits>

namespace evo {

/* Provides not-owning access to arbitrary square region in TiledMap
 *
 * Note. "const Region" != "ConstRegion"
 * "const Region" means the constness of the region itself, but
 * not the constness of underlying elements, i.e. one still
 * have read-write access to elements
 * "ConstRegion" stands for the opposite - one can modify the range,
 * but not the elements
 * It is different from TiledMap, where "const TiledMap" means,
 * that elements cannot be modified
 */
template <class TiledMap>
class RegionAccess {
private:
	static_assert(!std::is_const<typename TiledMap::TileType>::value,
		"TiledMap-s with const-qualified TileType are not supported "
		"since it is useless but complicates TiledMap implementation");

	using Traits         = detail::TiledMapTraits<TiledMap>;
	using ProxyRow       = typename Traits::ProxyRow;
	using StorageTypeRef = typename Traits::StorageTypeRef;

public:
	using TileType       = typename Traits::TileType;
	using StorageType    = typename Traits::StorageType;
	using Region         = typename Traits::Region;
	using ConstRegion    = typename Traits::ConstRegion;
	using Iterator       = typename Traits::Iterator;
	using ConstIterator  = typename Traits::ConstIterator;

public:
	RegionAccess(TiledMap& map) : RegionAccess(map.access_whole()) {}

	RegionAccess(StorageTypeRef data, size_t row, size_t column, size_t height, size_t width) :
		m_data(data),
		m_row(row),
		m_column(column),
		m_height(height),
		m_width(width)
	{}

	/* construct ConstRegion from Region
	 * Enable is neccessary to form SFINAE-context */
	template <bool Enable = Traits::is_map_const(), class = std::enable_if_t<Enable>>
	RegionAccess(const RegionAccess<std::remove_const_t<TiledMap>>& other) :
		RegionAccess(other.m_data, other.m_row, other.m_column, other.m_height, other.m_width)
	{}

	/* returns new accessor, not modifying this one */
	Region cut(size_t height, size_t width) const;

	Region access(size_t row, size_t column) const;
	ConstRegion const_access(size_t row, size_t column) const;

	size_t width() const { return m_width; }
	size_t height() const { return m_height; }

	ProxyRow operator [](size_t row) const;

	Iterator begin() const { return detail::make_region_begin<TiledMap>(*this); }
	Iterator end() const { return detail::make_region_end<TiledMap>(*this); }

	ConstIterator cbegin() const { return detail::make_region_begin<const TiledMap>(*this); }
	ConstIterator cend() const { return detail::make_region_end<const TiledMap>(*this); }

private:
	StorageTypeRef m_data;
	size_t m_row, m_column, m_height, m_width;

	template <class> friend class RegionAccess;
};

} // evo namespace end

#include "RegionAccessImpl.h"