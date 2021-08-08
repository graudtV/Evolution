#pragma once

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

} // detail namespace end
} // evo namespace end