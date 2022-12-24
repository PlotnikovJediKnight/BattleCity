#pragma once
#include "tank.h"

namespace pv {

	class LightTank : public Tank {
	public:
		using Tank::Tank;
		virtual std::string GetName() const override;
	};

}
