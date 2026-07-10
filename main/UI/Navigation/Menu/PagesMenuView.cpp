#include "UI/Navigation/Menu/PagesMenuView.hpp"
#include "UI/Theme.hpp"
#include "RC.hpp"

namespace pizda {
	const Route* PagesMenuView::getRoute() {
		return *_lastRoute;
	}

	void PagesMenuView::setRoute(const Route* route) const {
		*_lastRoute = route;

		for (uint8_t i = 0; i < _buttonCount; i++) {
			const auto button = _buttons + i;

			button->setActive(button->getRoute() == *_lastRoute);
		}

		RC::getInstance().setRoute(*_lastRoute);
	}
	
	void PagesMenuView::setupButtons(PageMenuViewButton* buttons, const uint8_t buttonCount, const Route** lastRoute) {
		_buttons = buttons;
		_buttonCount = buttonCount;
		_lastRoute = lastRoute;
		
		if (*_lastRoute == nullptr)
			*_lastRoute = _buttons[0].getRoute();
		
		for (uint8_t i = 0; i < _buttonCount; i++) {
			const auto button = _buttons + i;
			
			if (button->getRoute() == *_lastRoute) {
				button->setActive(true);
			}
			
			wrapLayout += button;
		}
	}
}