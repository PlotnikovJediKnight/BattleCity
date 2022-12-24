#pragma once
#include <map>
#include <string>

namespace pv {

	class BitmapHandler;

	class BitmapKeeper final {
	public:
		static BitmapKeeper& Instance();

		BitmapKeeper(const BitmapKeeper&) = delete;
		BitmapKeeper& operator = (const BitmapKeeper&) = delete;

	private:
		BitmapKeeper();
		~BitmapKeeper();

		std::map<std::string, BitmapHandler> name_to_bitmap_;
	};

}
