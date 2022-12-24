#pragma once
#include "GraphicsContext.h"

namespace pv {

	class IDrawable {
	public:
		virtual void Draw(GraphicsContext& g) const = 0;
		virtual void SetInvisible(bool isInvisible);

		virtual ~IDrawable() = default;
	};
}
