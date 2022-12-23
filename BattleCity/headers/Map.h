#pragma once
#include <map>

namespace pv {

	class Map {
	private:
		static const size_t MAP_ROWS_ = 13;
		static const size_t MAP_COLUMNS_ = 13;

		using AsciiMapPointer = char(*)[MAP_ROWS_][MAP_COLUMNS_];

	public:
		Map(AsciiMapPointer asciiMapPointer);

	private:

		//static std::map<char, 
	};

}