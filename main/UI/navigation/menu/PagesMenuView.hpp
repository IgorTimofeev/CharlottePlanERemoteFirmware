#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/Menu/MenuView.hpp"
#include "UI/Navigation/Menu/PageMenuViewButton.hpp"
#include "UI/Navigation/Routes.hpp"
#include "Resources/Images.hpp"

namespace pizda {
	using namespace YOBA;

	class PagesMenuView : public MenuView {
		public:
			const Route* getRoute() override;
			void setRoute(const Route* route) const;
			
		protected:
			void setupButtons(PageMenuViewButton* buttons, uint8_t buttonCount, const Route** lastRoute);
			
		private:
			const Route** _lastRoute = nullptr;
			PageMenuViewButton* _buttons = nullptr;
			uint8_t _buttonCount = 0;
	};
}