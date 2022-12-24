#pragma once
#include <map>
#include <string>
#include <functional>
#include <memory>
#include "tanks/tank.h"

namespace pv {

	class TankFactory final {
	private:
		using TankHolder = std::unique_ptr<Tank>;
		using MakeFunctionPtr = TankHolder(TankFactory::*)(void);

	public:
		static TankFactory& Instance();

		TankHolder MakeTank(const std::string& tankName);

		TankFactory(const TankFactory&) = delete;
		TankFactory& operator = (const TankFactory&) = delete;

	private:

		TankHolder MakeUltraLightTank(void);
		TankHolder MakeLightTank(void);
		TankHolder MakeMediumTank(void);
		TankHolder MakeHeavyTank(void);

		TankFactory();
		~TankFactory();

		std::map<std::string, MakeFunctionPtr> name_to_make_func_;
	};

}