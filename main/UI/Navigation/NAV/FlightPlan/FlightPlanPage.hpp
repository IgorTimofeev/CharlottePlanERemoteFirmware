#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/Page.hpp"
#include "UI/Navigation/NAV/FlightPlan/LegPlaceholderButton.hpp"

namespace pizda {
	using namespace YOBA;

	class FlightPlanPage : public ScrollViewPage {
		public:
			explicit FlightPlanPage();
			~FlightPlanPage() override;

			static FlightPlanPage* getInstance();

			void updateFromNavigationData();

		private:
			static FlightPlanPage* _instance;
			static int32_t _scrollPosition;

			StackLayout _itemsLayout {};

			StackLayout _legsLayout {};
			LegPlaceholderButton _addLegButton {};

			static void applyTitleStyle(TextView& text);
	};
}