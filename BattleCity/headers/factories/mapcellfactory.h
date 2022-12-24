#pragma once
#include <map>
#include <string>
#include <functional>
#include <memory>
#include "mapcells/mapcell.h"

namespace pv {

	class MapCellFactory final {
	private:
		using MapCellHolder = std::unique_ptr<MapCell>;
		using MakeFunctionPtr = MapCellHolder(MapCellFactory::*)(void);

	public:
		static MapCellFactory& Instance();

		MapCellHolder MakeCell(const std::string& cellName);

		MapCellFactory(const MapCellFactory&) = delete;
		MapCellFactory& operator = (const MapCellFactory&) = delete;

	private:

		MapCellHolder MakeBrickWall(void);
		MapCellHolder MakeConcreteWall(void);
		MapCellHolder MakeBush(void);
		MapCellHolder MakeIce(void);
		MapCellHolder MakeWater(void);
		MapCellHolder MakePathway(void);
		MapCellHolder MakeHeadquarters(void);

		MapCellFactory();
		~MapCellFactory();

		std::map<std::string, MakeFunctionPtr> name_to_make_func_;
	};

}