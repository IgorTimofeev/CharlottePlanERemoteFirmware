#include "UI/Navigation/Menu/MenuView.hpp"
#include "UI/Navigation/Menu/Menu.hpp"
#include "UI/Theme.hpp"

namespace pizda {
	MenuView::MenuView() {
		// setGap(10);
		// setMargin(Margin(15, 15, 15, 10));

		marginTransform.setMargin(Margin(12, 15, 12, 10));
		setLayoutTransform(&marginTransform);

		setGap(12, 10);
	}

	void MenuView::setup() {

	}

	Menu* MenuView::getMenu() const {
		return dynamic_cast<Menu*>(getParent()->getParent()->getParent());
	}
}