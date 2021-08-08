#pragma once

#include "Support/debug.h"

namespace evo {

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