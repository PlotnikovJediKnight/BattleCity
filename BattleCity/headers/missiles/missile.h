#pragma once
#include "interfaces/idrawable.h"

namespace pv {

	class Obstacle;
	class Wall;
	class BrickWall;
	class ConcreteWall;
	class Bush;
	class Ice;
	class Water;

	class Missile : public IDrawable {
	public:
		Missile(double);

		virtual void CollideWith(Obstacle&);
		virtual void CollideWith(Wall&);
		virtual void CollideWith(BrickWall&);
		virtual void CollideWith(ConcreteWall&);
		virtual void CollideWith(Bush&);
		virtual void CollideWith(Ice&);
		virtual void CollideWith(Water&);

	private:
		double missile_speed_;
	};
}