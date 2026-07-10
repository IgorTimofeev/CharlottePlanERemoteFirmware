#pragma once

#include "UI/Navigation/MFD/Toolbar/ToolbarSection.hpp"
#include "UI/Navigation/MFD/Toolbar/Main/ThrottleIndicator.hpp"

namespace pizda {
	using namespace YOBA;

	class ThrottleSection : public ToolbarSection {
		public:
			explicit ThrottleSection();

			MarginLayout rowMarginLayout {};
			StackLayout row {};
			ThrottleIndicator throttleIndicator1 {};
			ThrottleIndicator throttleIndicator2 {};

		protected:
			void onTick() override;
	};
}