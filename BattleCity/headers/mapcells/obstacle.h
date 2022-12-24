#pragma once
#include "mapcell.h"

namespace pv {

	class Missile;

	class Obstacle : MapCell {
	public:
		virtual void CollideWith(Missile& missile);
	};

}
