#include "UI/Navigation/Menu/PageMenuViewButton.hpp"
#include "UI/Navigation/Menu/PagesMenuView.hpp"

namespace pizda {
	PageMenuViewButton::PageMenuViewButton(const Image* image, std::string_view text, const Route* route) :
		MenuViewButton(image, text),
		_route(route)
	{

	}

	void PageMenuViewButton::onClick() {
		Button::onClick();

		reinterpret_cast<PagesMenuView*>(getMenuView())->setRoute(_route);
	}

	const Route* PageMenuViewButton::getRoute() const {
		return _route;
	}
}