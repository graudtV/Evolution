/* This is the main file for TiledMap. It includes all others */

#pragma once

#include "RegionAccess.h"
#include <vector>

/********** Member type hierarchy **********\
 * The diagram below shows important member types in TiledMap, Region
 * and subregions. Not all types shown here, for mor details see
 * particular classes
 *
 * Design goal in this hierarchy was to collapse subregions of
 * regions to the same region type to minimize template instantiations
 * 
 * using SomeTileType = ...; // any copyable non-const (!) type
 * using Map = TiledMap<SomeTileType>;
 *
 * Map:
 * | -- Region          = RegionAccess<Map>
 * |                      | -- Region        = RegionAccess<Map>
 * |                      | -- ConstRegion   = RegionAccess<const Map>
 * |                      | -- Iterator      = RegionIterator<Map>
 * |                      | -- ConstIterator = RegionIterator<const Map>
 * |                      | -- .....
 * |
 * | -- ConstRegion     = RegionAccess<const Map>
 * |                      | -- Region        = RegionAccess<const Map>
 * |                      | -- ConstRegion   = RegionAccess<const Map>
 * |                      | -- Iterator      = RegionIterator<const Map>
 * |                      | -- ConstIterator = RegionIterator<const Map>
 * |                      | -- .....
 * |
 * | -- Iterator        = RegionIterator<Map>
 * |                      | -- value_type    = SomeTileType
 * |                      | -- reference     = SomeTileType &
 * |                      | -- pointer       = SomeTileType *
 * |                      | -- .....
 * |
 * | -- ConstIterator   = RegionIterator<const Map>
 * |                      | -- value_type    = SomeTileType
 * |                      | -- reference     = const SomeTileType &
 * |                      | -- pointer       = const SomeTileType *
 * |                      | -- .....
 * | -- .....
*/

namespace evo {

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
	using ConstRegion = RegionAccess<const TiledMap>;

	/*  Iterators iterate over all map/region elements sequentially,
	 * starting from (0, 0) and iterating column number on the 0-th
	 * row, then moving to the begining of the next row and so on
	 * until the end
	 *  Iterators are both implemented for TiledMap itself and Region-s */
	using Iterator = detail::RegionIterator<TiledMap>;
	using ConstIterator = detail::RegionIterator<const TiledMap>;

private:
	using ProxyRow = detail::ProxyRow<TileType>;
	using ConstProxyRow = detail::ConstProxyRow<TileType>;

	friend class detail::TiledMapTraits<TiledMap>;
	friend class detail::TiledMapTraits<const TiledMap>;

public:
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

	Iterator begin() { return access_whole().begin(); }
	Iterator end() { return access_whole().end(); }

	ConstIterator begin() const { return cbegin(); }
	ConstIterator end() const { return cend(); }

	ConstIterator cbegin() const { return access_whole().begin(); }
	ConstIterator cend() const { return access_whole().end(); }

	void clear() { access_whole().clear(); }
private:
	StorageType m_data;
};

} // evo namespace end

#include "TiledMapImpl.h"