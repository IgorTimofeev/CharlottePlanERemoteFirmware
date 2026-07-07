#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Theme.hpp"
#include "Settings/Settings.hpp"
#include "UI/Navigation/Page.hpp"
#include "UI/Navigation/Route.hpp"

namespace pizda {
	using namespace YOBA;

	class Menu;
	class MenuView;

	class MenuTabButton : public Button {
		public:
			MenuTabButton(std::string_view text, const Route* route);

			const Route* getRoute() const;

		protected:
			void onClick() override;

			void onRender(Renderer* renderer, const Rectangle& bounds) override;

		private:
			const Route* _route;
	};
}