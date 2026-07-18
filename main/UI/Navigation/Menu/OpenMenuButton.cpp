#include "UI/Navigation/Menu/OpenMenuButton.hpp"

#include "UI/Theme.hpp"
#include "RC.hpp"

#include "UI/Navigation/Menu/Menu.hpp"

namespace pizda {
	OpenMenuButton::OpenMenuButton() {
		constexpr static uint8_t size = 32;

		_transform.setOffset(Point(0, size / 2 + 3));
		setLayoutTransform(&_transform);

		setAlignment(Alignment::center, Alignment::end);
		setSize(Size(size));
		setCornerRadius(size / 2 - 1);
		setTextMargin(Margin(0, 0, 0, 5));

		setDefaultBackgroundColor(&Theme::bg2);
		setDefaultBorderColor(&Theme::bg3);
		setDefaultTextColor(&Theme::fg5);

		setActiveBackgroundColor(&Theme::fg1);
		setActiveBorderColor(nullptr);
		setActiveTextColor(&Theme::bg1);

		setFont(&Theme::fontSmall);
		setText("^");
	}

	void OpenMenuButton::onClick() {
		Theme::openDialog(new Menu());
	}
}
