#pragma once

#include <vector>
#include <cassert>

namespace evo {

namespace detail {

template <class ValueType>
class UnsafeProxyRow {
public:
	UnsafeProxyRow(ValueType *data) : m_data(data) {}

	ValueType& operator [](size_t column) { return m_data[column]; }
private:
	ValueType *m_data;
};

template <class ValueType>
class SafeProxyRow {
public:
	SafeProxyRow(ValueType *data, size_t width) :
		m_data(data), m_width(width) {}

	ValueType& operator [](size_t column) {
		assert(column < m_width && "invalid access");
		return m_data[column];
	}
private:
	ValueType *m_data;
	size_t m_width;
};

#ifdef NDEBUG
	template <class T> using ProxyRow = UnsafeProxyRow<T>;
#else
	template <class T> using ProxyRow = SafeProxyRow<T>;
#endif

template <class T> using ConstProxyRow = ProxyRow<const T>;

}; // detail namespace end

/* Provides not-owning access to arbitrary square region in TiledMap */
template <class TiledMap>
class RegionAccess {
public:
	static_assert(!std::is_const<typename TiledMap::TileType>::value,
		"TiledMap-s with const-qualified TileType are not supported "
		"since it is useless but complicates TiledMap implementation");

	/*  Checks if this instantion cannot modify underlying map
	 *  Note. Function relies on the fact, that map has non-const
	 * TileType. This is checked in static_assert above */
	static constexpr bool is_readonly()
		{ return std::is_const<TiledMap>::value; }

	using TileType = typename TiledMap::TileType;
	using StorageType = typename TiledMap::StorageType;
	using ProxyRow = std::conditional_t<is_readonly(),
		detail::ConstProxyRow<TileType>,
		detail::ProxyRow<TileType>
	>;
	using ConstProxyRow = detail::ConstProxyRow<TileType>;
	using Region = RegionAccess; // is the same as ConstRegion for readonly accessors
	using ConstRegion = typename TiledMap::ConstRegion;

private:
	using StorageTypeRef = std::conditional_t<is_readonly(),
		const StorageType&,
		StorageType&
	>;
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

private:
	StorageTypeRef m_data;
	size_t m_row, m_column, m_height, m_width;
};

template <class T> using ConstRegionAccess = RegionAccess<const T>;

/*  TiledMap is a class for representing square game maps, which 
 * consist of cells, or tiles, i.e. looking like a matrix */
template <class T>
class TiledMap {
public:
	static_assert(!std::is_const<T>::value,
		"TiledMap-s with const-qualified TileType are not supported "
		"since it is useless but complicates TiledMap implementation");

	using TileType = T;
	using StorageType = std::vector<std::vector<TileType>>;
	using Region = RegionAccess<TiledMap>;
	using ConstRegion = ConstRegionAccess<TiledMap>;
	using ProxyRow = detail::ProxyRow<TileType>;
	using ConstProxyRow = detail::ConstProxyRow<TileType>;

	TiledMap(size_t height, size_t width) :
		m_data(height, std::vector<TileType>(width))
		{ assert(width > 0 && height > 0 && "empty tiled map is not supported"); }

	size_t width() const { return m_data[0].size(); }
	size_t height() const { return m_data.size(); }

	/*  Accessors to the down right corner starting from (row, column)
	 *  Access to arbitrary region can be granted with the following idiom:
	 * map.access(row, column).cut(width, height) */
	Region access(size_t row, size_t column);
	ConstRegion access(size_t row, size_t column) const { return const_access(row, column); }
	ConstRegion const_access(size_t row, size_t column) const;

	/*  Accessors to the whole tiled map */
	Region access_whole() { return access(0, 0); }
	ConstRegion access_whole() const { return access(0, 0); }
	ConstRegion const_access_whole() const { return access(0, 0); }

	ProxyRow operator [](size_t row);
	ConstProxyRow operator [](size_t row) const;

private:
	StorageType m_data;
};

} // evo namespace end

#include "TiledMapImpl.h"