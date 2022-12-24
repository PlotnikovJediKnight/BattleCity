#pragma once
#include "interfaces/iactor.h"
#include "interfaces/idrawable.h"
#include "tanks/tank.h"
#include <memory>

namespace pv {

	class Enemy : public IActor, public IDrawable {
	public:
		virtual void MoveForward() override;
		virtual void SetOrientation() override;
		virtual void Fire() override;

		virtual void Draw(GraphicsContext&) const override;
		virtual void SetInvisible(bool setInvisible) override;

	private:
		ActorOrientation enemy_orientation_;

		using TankHolder = std::unique_ptr<Tank>;
		TankHolder tank_holder_;

		size_t points_worth_;
		size_t health_;
	};

}