#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/Menu/PagesMenuView.hpp"
#include "UI/Navigation/Menu/PageMenuViewButton.hpp"
#include "UI/Navigation/Routes.hpp"
#include "Resources/Images.hpp"

namespace pizda {
	using namespace YOBA;

	class NavMenuView : public PagesMenuView {
		public:
			void setup() override;
		
		private:
			static const Route* _lastRoute;

			std::array<PageMenuViewButton, 2> _buttons {
				PageMenuViewButton(&Images::menuIconFlightPlan, "Flight plan", &Routes::navFlightPlan),
				PageMenuViewButton(&Images::menuIconWaypointsImage, "Database", &Routes::navWaypoints)
			};
	};
}