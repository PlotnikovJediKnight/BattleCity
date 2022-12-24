#pragma once
#include "tank.h"

namespace pv {

	class HeavyTank : public Tank {
	public:
		using Tank::Tank;
		virtual std::string GetName() const override;
	};

}