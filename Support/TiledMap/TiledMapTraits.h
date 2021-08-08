#pragma once

namespace evo {

template <class T> class TiledMap;

namespace detail {

template <class TiledMap> struct TiledMapTraits;

/* non-const map traits */
template <class T>
struct TiledMapTraits<::evo::TiledMap<T>> {
	using TileType      = T;
	using StorageType   = typename TiledMap<T>::StorageType;

	using Reference      = T &;
	using Pointer        = T *;
	using StorageTypeRef = StorageType&;
	using Region         = typename TiledMap<T>::Region;
	using ConstRegion    = typename TiledMap<T>::ConstRegion;
	using Iterator       = typename TiledMap<T>::Iterator;
	using ConstIterator  = typename TiledMap<T>::ConstIterator;
	using ProxyRow       = typename TiledMap<T>::ProxyRow;
	using ConstProxyRow  = typename TiledMap<T>::ConstProxyRow;
};

/* const map traits */
template <class T>
struct TiledMapTraits<const ::evo::TiledMap<T>> {
	using TileType       = T;
	using StorageType    = typename TiledMap<T>::StorageType;

	using Reference      = const T &;
	using Pointer        = const T *;
	using StorageTypeRef = const StorageType&;
	using Region         = typename TiledMap<T>::ConstRegion;
	using ConstRegion    = typename TiledMap<T>::ConstRegion;	
	using Iterator       = typename TiledMap<T>::ConstIterator;
	using ConstIterator  = typename TiledMap<T>::ConstIterator;
	using ProxyRow       = typename TiledMap<T>::ConstProxyRow;
	using ConstProxyRow  = typename TiledMap<T>::ConstProxyRow;
};

} // detail namespace end
} // evo namespace end