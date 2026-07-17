#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Theme.hpp"
#include "Settings/Settings.hpp"

#include "UI/Navigation/Menu/MenuView.hpp"
#include "UI/Navigation/Menu/MenuTabButton.hpp"
#include "UI/Navigation/Menu/MenuRoutes.hpp"

namespace pizda {
	using namespace YOBA;

	class Menu : public BottomSheetDialog {
		public:
			Menu();
			~Menu() override;

			void setViewRoute(const Route* route);

		private:
			static const Route* _viewRoute;

			StackLayout _tabsAndContentRows {};
			RelativeStackLayout _tabsRow {};

			MenuView* _view = nullptr;

			MenuTabButton tabs[3] {
				{ "MFD", &MenuRoutes::MFD },
				{ "NAV", &MenuRoutes::nav },
				{ "CONF", &MenuRoutes::settings },
			};
	};
}