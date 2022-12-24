#pragma once
#include "tank.h"

namespace pv {

	class UltraLightTank : public Tank {
	public:
		using Tank::Tank;
		virtual std::string GetName() const override;
	};

}
