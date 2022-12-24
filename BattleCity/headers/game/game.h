#pragma once
#include "level.h"
#include <vector>

namespace pv {

	class Game final {
	public:
		static Game& Instance();

		Game(const Game&) = delete;
		Game& operator = (const Game&) = delete;

		size_t GetHighestScore() const;
		void LoadLevel();

	private:
		Game() = default;
		~Game() = default;

		static const size_t LEVEL_COUNT = 70;
		std::vector<Level> levels_;

		size_t curret_level_idx_;
		size_t highest_score_ever_;
	};

}