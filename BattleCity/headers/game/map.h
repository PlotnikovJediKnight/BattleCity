#pragma once
#include "mapcells/mapcell.h"
#include <map>
#include <memory>

namespace pv {

	class Map {
	private:
		static const size_t MAP_ROWS_ = 13;
		static const size_t MAP_COLUMNS_ = 13;

		using AsciiMapPointer = char(*)[MAP_ROWS_][MAP_COLUMNS_];

	public:
		Map(AsciiMapPointer asciiMapPointer);

	private:
		using MapCellHolder = std::unique_ptr<MapCell>;
		MapCellHolder map_array_[MAP_ROWS_][MAP_COLUMNS_];

		friend class Wall;

		void RemoveDestroyedWall();
	};

}