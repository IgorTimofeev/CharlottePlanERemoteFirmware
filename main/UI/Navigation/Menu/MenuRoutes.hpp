#pragma once

#include "UI/Navigation/Route.hpp"
#include "UI/Navigation/MFD/MFDMenuView.hpp"
#include "UI/Navigation/NAV/NavMenuView.hpp"
#include "UI/Navigation/Settings/SettingsMenuView.hpp"

namespace pizda {
	class MenuRoutes {
		public:
			constexpr static ElementRoute<MFDMenuView> MFD {};
			constexpr static ElementRoute<NavMenuView> nav {};
			constexpr static ElementRoute<SettingsMenuView> settings {};
	};
}