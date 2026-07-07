#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

namespace pizda {
	using namespace YOBA;

	class LegPlaceholderButton : public Button {
		public:
			LegPlaceholderButton();

		protected:
			void onClick() override;
	};
}