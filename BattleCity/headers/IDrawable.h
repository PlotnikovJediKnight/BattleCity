#pragma once
#include "GraphicsContext.h"

namespace pv {

	class IDrawable {
	public:
		virtual void Draw(GraphicsContext& g) = 0;
	};
}
