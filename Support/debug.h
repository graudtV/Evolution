#pragma once

#ifdef NDEBUG
# define ON_DEBUG(...)
#else
# define ON_DEBUG(...) __VA_ARGS__
#endif