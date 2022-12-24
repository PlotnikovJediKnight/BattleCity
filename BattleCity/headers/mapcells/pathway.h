#pragma once
#include "mapcell.h"

namespace pv {

	class Pathway : public MapCell {
	public:
		virtual void Draw(GraphicsContext&) const override;
		virtual bool IsBlockingActor() const override;
		virtual bool IsAbsorbingMissile() const override;
	};

}
