#include "External/Catch2/catch2.hpp"
#include "Support/TiledMap.h"
#include <iostream>
#include <array>
#include <iomanip>

template <class T> using is_readonly = std::is_const<std::remove_reference_t<T>>;

TEST_CASE("static assertions", "[TiledMap]") {
	using Map = evo::TiledMap<int>;

	static_assert(!is_readonly<
		decltype(std::declval<Map>()[0][0])
		>::value,
		"Map is not const, but element is readonly");

	static_assert(is_readonly<
		decltype(std::declval<const Map>()[0][0])
		>::value,
		"Map is const, but element is not readonly");

	static_assert(!is_readonly<
		decltype(std::declval<Map>().access(0, 0)[0][0])
		>::value,
		"Map is not const, but accessor is readonly");

	static_assert(is_readonly<
		decltype(std::declval<const Map>().access(0, 0)[0][0])
		>::value,
		"Map is const, but accessor is not readonly");

	static_assert(!is_readonly<
		decltype(std::declval<Map>().access(0, 0).access(0, 0)[0][0])
		>::value,
		"Map is not const, but second-level accessor is readonly");

	static_assert(is_readonly<
		decltype(std::declval<const Map>().access(0, 0).access(0, 0)[0][0])
		>::value,
		"Map is const, but second-level accessor is not readonly");
}

TEST_CASE("TiledMap::TiledMap()", "[TiledMap]") {
	evo::TiledMap<int> map{5, 10};
	CHECK(map.height() == 5);
	CHECK(map.width() == 10);
}

TEST_CASE("RegionAccess::access_whole()", "[TiledMap]") {
	evo::TiledMap<int> map{10, 20};
	auto&& access = map.access_whole();

	CHECK(access.height() == map.height());
	CHECK(access.width() == map.width());
}

TEST_CASE("TiledMap::access()", "[TiledMap]") {
	evo::TiledMap<int> map{10, 20};
	auto&& access = map.access(2, 5);

	CHECK(access.height() == 8);
	CHECK(access.width() == 15);
}

TEST_CASE("TiledMap::operator[]()", "[TiledMap]") {
	evo::TiledMap<int> map{10, 20};
	map[2][5] = 228;

	CHECK(map[2][5] == 228);
	CHECK(map[5][2] == 0);
}

TEST_CASE("TiledMap::Region::operator[]()", "[TiledMap]") {
	evo::TiledMap<int> map{10, 20};
	map.access_whole()[6][15] = 228;

	auto&& view = map.access(2, 4);
	CHECK(view[4][11] == 228);

	map.access(3, 13)[3][2] = 337;
	CHECK(view[4][11] == 337);
}

template <class Region, class InputIt>
void fill_region(Region&& dst_region, InputIt src_fst, InputIt src_last)
{
	for (size_t i = 0; i < dst_region.height(); ++i)
		for (size_t j = 0; j < dst_region.width(); ++j) {
			if (src_fst == src_last)
				return;
			dst_region[i][j] = *src_fst;
			++src_fst;
		}
}

template <class ConstRegion, class InputIt>
void cmp_region(ConstRegion&& region, InputIt fst, InputIt last)
{
	for (size_t i = 0; i < region.height(); ++i)
		for (size_t j = 0; j < region.width(); ++j) {
			if (fst == last)
				return;
			INFO("at region[" << i << "][" << j << "]")
			CHECK(region[i][j] == *fst);
			++fst;
		}
}

TEST_CASE("Checks TiledMap accessors", "[TiledMap]") {
	std::array<int, 35> expected{
		0,  0,  0,  0,  0,  0,  0,
		0,  0,  1,  2,  3,  4,  0,
		0,  0,  5,  6,  7,  8,  0,
		0,  0,  9,  10, 11, 12, 0,
		0,  0,  0,  0,  0,  0,  0
	};
	std::array<int, 12> filling;
	std::iota(filling.begin(), filling.end(), 1);

	evo::TiledMap<int> map{5, 7};
	fill_region(map.access(1, 2).cut(3, 4), filling.begin(), filling.end());
	cmp_region(map, expected.begin(), expected.end());
}