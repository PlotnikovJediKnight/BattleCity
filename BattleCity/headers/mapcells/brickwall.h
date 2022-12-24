#pragma once
#include "wall.h"

namespace pv {

	class BrickWall : Wall {
	public:

		virtual void Draw(GraphicsContext&) const override;
		virtual bool IsBlockingActor() const override;
		virtual bool IsAbsorbingMissile() const override;

		virtual void CollideWith(Missile& missile) override;
	};

}
