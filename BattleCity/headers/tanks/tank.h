#pragma once
#include "missiles/missile.h"
#include <memory>
#include <string>

namespace pv {

	class Tank {
	private:
		using MissileHolder = std::unique_ptr<Missile>;
	public:
		virtual std::string GetName() const = 0;

		Tank(size_t, double, MissileHolder);

		size_t GetMaxHitCount() const;
		double GetTankSpeed() const;

	private:
		size_t hits_can_withstand_;
		double tank_speed_;
		MissileHolder missile_holder_;
	};

}