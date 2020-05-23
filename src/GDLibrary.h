#pragma once

#include <Godot.hpp>

template <size_t SIZE>
struct FixedString
{
	char str[SIZE];
	FixedString(godot::String from) {
		size_t outsize;
		wcstombs_s(&outsize, str, from.unicode_str(), SIZE);
	}
};
