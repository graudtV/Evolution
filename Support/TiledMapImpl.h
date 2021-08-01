#pragma once

#include "debug.h"

namespace evo {

template <class TiledMap>
RegionAccess<TiledMap>
RegionAccess<TiledMap>::cut(size_t height, size_t width) const
{
	assert(height <= m_height && width <= m_width && "invalid access");
	return RegionAccess<TiledMap>(m_data, m_row, m_column, height, width);
}

template <class TiledMap>
typename RegionAccess<TiledMap>::ProxyRow
RegionAccess<TiledMap>::operator [](size_t row)
{
	assert(row < m_height && "invalid access");
	return ProxyRow(m_data[row + m_row].data() + m_column
		ON_DEBUG(, m_width));
}

template <class TiledMap>
typename RegionAccess<TiledMap>::ConstProxyRow
RegionAccess<TiledMap>::operator [](size_t row) const
{
	assert(row < m_height && "invalid access");
	return ConstProxyRow(m_data[row + m_row].data() + m_column
		ON_DEBUG(, m_width));
}

template <class T>
typename TiledMap<T>::Region
TiledMap<T>::access(size_t row, size_t column)
{
	assert(row < height() && column < width() && "invalid access");
	return Region(m_data, row, column, height() - row, width() - column);
}

template <class T>
typename TiledMap<T>::ConstRegion
TiledMap<T>::const_access(size_t row, size_t column) const
{
	assert(row < height() && column < width() && "invalid access");
	return ConstRegion(m_data, row, column, height() - row, width() - column);
}

template <class T>
typename TiledMap<T>::ProxyRow
TiledMap<T>::operator [](size_t row)
{
	assert(row < height() && "invalid access");
	return ProxyRow(m_data[row].data()
		ON_DEBUG(, width()));
}

template <class T>
typename TiledMap<T>::ConstProxyRow
TiledMap<T>::operator [](size_t row) const
{
	assert(row < height() && "invalid access");
	return ConstProxyRow(m_data[row].data()
		ON_DEBUG(, width()));
}

} // evo namespace end