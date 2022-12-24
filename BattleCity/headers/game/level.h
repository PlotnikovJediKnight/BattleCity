#pragma once
#include "map.h"
#include <memory>

namespace pv {

	class Level {
	private:
		using MapHolder = std::unique_ptr<Map>;
	public:
		Level(size_t enemiesLeft, size_t levelNumber, MapHolder);

		void SpawnNewEnemy();
		void RespawnPlayer();

	private:
		size_t enemies_to_kill_left_;
		size_t level_number_;
		MapHolder map_holder_;
	};

}
