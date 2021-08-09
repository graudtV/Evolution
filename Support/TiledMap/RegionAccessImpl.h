#pragma once

#include "Support/debug.h"
#include <algorithm>

namespace evo {

template <class TiledMap>
typename RegionAccess<TiledMap>::Region
RegionAccess<TiledMap>::cut(size_t height, size_t width) const
{
	assert(height <= m_height && width <= m_width && "invalid access");
	return RegionAccess<TiledMap>(m_data, m_row, m_column, height, width);
}

template <class TiledMap>
typename RegionAccess<TiledMap>::ProxyRow
RegionAccess<TiledMap>::operator [](size_t row) const
{
	assert(row < m_height && "invalid access");
	return ProxyRow(m_data[row + m_row].data() + m_column
		ON_DEBUG(, m_width));
}

template <class TiledMap>
void RegionAccess<TiledMap>::clear()
	{ std::fill(begin(), end(), TileType()); }


} // evo namespace end