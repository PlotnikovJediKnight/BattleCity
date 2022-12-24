#pragma once
#include "obstacle.h"
#include "game/map.h"
#include <memory>

namespace pv {

	enum class WallState { FULL_HEALTH, SLIGHTLY_DAMAGED, AVERAGELY_DAMAGED, SEVERELY_DAMAGED, DESTROYED };

	class Wall : public Obstacle {
	private:
		using MapWeakHolder = std::weak_ptr<Map>;
	
	public:
		Wall(MapWeakHolder mapWeakHolder);

	protected:
		void DowngradeCurrentState();

		MapWeakHolder map_weak_holder_;
		WallState current_state_;
	};

}
