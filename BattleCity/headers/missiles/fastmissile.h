#pragma once
#include "missile.h"

namespace pv {

	class FastMissile : public Missile {
	public:
		using Missile::Missile;
		virtual void Draw(GraphicsContext&) const override;

		virtual void CollideWith(Obstacle&) override;
		virtual void CollideWith(Wall&) override;
		virtual void CollideWith(BrickWall&) override;
		virtual void CollideWith(ConcreteWall&) override;
		virtual void CollideWith(Bush&) override;
		virtual void CollideWith(Ice&) override;
		virtual void CollideWith(Water&) override;
	};

}