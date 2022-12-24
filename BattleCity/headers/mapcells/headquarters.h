#pragma once
#include "obstacle.h"

namespace pv {

	class Headquarters : Obstacle {
	public:

		virtual void Draw(GraphicsContext&) const override;
		virtual bool IsBlockingActor() const override;
		virtual bool IsAbsorbingMissile() const override;

		virtual void CollideWith(Missile& missile) override;

	private:
		void FinishGame();
	};

}
