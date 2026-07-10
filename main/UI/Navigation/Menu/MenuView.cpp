#include "UI/Navigation/Menu/MenuView.hpp"
#include "UI/Navigation/Menu/Menu.hpp"
#include "UI/Theme.hpp"

namespace pizda {
	MenuView::MenuView() {
		// setSpacing(10);
		// setMargin(Margin(15, 15, 15, 10));

		setMargin(Margin(12, 15, 12, 10));

		wrapLayout.setGap(12, 10);
		*this += &wrapLayout;
	}

	void MenuView::setup() {

	}

	Menu* MenuView::getMenu() const {
		return reinterpret_cast<Menu*>(getParent()->getParent()->getParent());
	}
}