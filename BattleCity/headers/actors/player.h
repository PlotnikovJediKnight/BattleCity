#pragma once
#include "interfaces/iactor.h"
#include "interfaces/idrawable.h"
#include "tanks/tank.h"
#include <memory>

namespace pv {

	class Player : public IActor, public IDrawable {
	public:
		virtual void MoveForward() override;
		virtual void SetOrientation() override;
		virtual void Fire() override;
	
		virtual void Draw(GraphicsContext&) const override;
		virtual void SetInvisible(bool setInvisible) override;

		void AddStarsCount(size_t addStars);
		void SetStarsCount(size_t starsCount);
		size_t GetStarsCount() const;

		void AddPlayerScore(size_t enemyKilledPoints);
		void SetPlayerScore(size_t playerScore);
		size_t GetPlayerScore() const;

	private:
		ActorOrientation player_orientation_;

		using TankHolder = std::unique_ptr<Tank>;
		TankHolder tank_holder_;

		size_t stars_count_;
		size_t player_score_;
	};

}
