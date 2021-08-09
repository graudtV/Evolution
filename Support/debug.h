#pragma once

#include <cstdio>

namespace evo {

template <class To, class From>
To safe_dynamic_cast(From *from)
{
	To res = dynamic_cast<To>(from);
	if (!res) {
		fprintf(stderr, "invalid dynamic_cast detected: %s\n", __PRETTY_FUNCTION__);
		abort();
	}
	return res;
}

} // evo namespace end

#ifdef NDEBUG
# define ON_DEBUG(...)
#else
# define ON_DEBUG(...) __VA_ARGS__
#endif

#ifdef NDEBUG
# define cast static_cast
#else
# define cast ::evo::safe_dynamic_cast
#endif