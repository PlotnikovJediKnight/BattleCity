#pragma once
#include "interfaces/idrawable.h"


namespace pv {

	class MapCell : public IDrawable {
	public:
		virtual bool IsBlockingActor() const = 0;
		virtual bool IsAbsorbingMissile() const = 0;
	};
}
