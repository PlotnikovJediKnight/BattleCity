#pragma once

namespace pv {

	enum class ActorOrientation{ NORTH, WEST, SOUTH, EAST };

	class IActor {
	public:
		virtual void MoveForward() = 0;
		virtual void SetOrientation() = 0;
		virtual void Fire() = 0;

		virtual ~IActor() = default;
	};

}
