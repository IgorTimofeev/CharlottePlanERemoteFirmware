#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

namespace pizda {
	using namespace YOBA;

	class OpenMenuButton : public MarginLayout {
		public:
			OpenMenuButton();

		private:
			Button _button {};
	};
}