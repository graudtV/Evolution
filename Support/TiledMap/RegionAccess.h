#pragma once

#include "ProxyRow.h"
#include "TiledMapTraits.h"
// #include "RegionIterator.h"

namespace evo {

/* Provides not-owning access to arbitrary square region in TiledMap */
template <class TiledMap>
class RegionAccess {
private:
	static_assert(!std::is_const<typename TiledMap::TileType>::value,
		"TiledMap-s with const-qualified TileType are not supported "
		"since it is useless but complicates TiledMap implementation");

	using Traits         = detail::TiledMapTraits<TiledMap>;
	using ProxyRow       = typename Traits::ProxyRow;
	using ConstProxyRow  = typename Traits::ConstProxyRow;
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

	RegionAccess(StorageTypeRef data,
			size_t row, size_t column, size_t height, size_t width) :
		m_data(data),
		m_row(row),
		m_column(column),
		m_height(height),
		m_width(width) {}

	/* returns new accessor, not modifying this one */
	Region cut(size_t height, size_t width) const;

	Region access(size_t row, size_t column);
	ConstRegion access(size_t row, size_t column) const { return const_access(row, column); }
	ConstRegion const_access(size_t row, size_t column) const;

	size_t width() const { return m_width; }
	size_t height() const { return m_height; }

	ProxyRow operator [](size_t row);
	ConstProxyRow operator [](size_t column) const;

	// Iterator begin() { return detail::make_region_begin(*this); }
	// Iterator end() { return detail::make_region_end(*this); }

	// ConstIterator begin() const { return cbegin(); }
	// ConstIterator end() const { return cend(); }

	// ConstIterator cbegin() const { return detail::make_region_begin(*this); }
	// ConstIterator cend() const { return detail::make_region_end(*this); }

private:
	StorageTypeRef m_data;
	size_t m_row, m_column, m_height, m_width;
};

} // evo namespace end

#include "RegionAccessImpl.h"