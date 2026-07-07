#include "UI/Navigation/Menu/OpenMenuButton.hpp"

#include "UI/Theme.hpp"
#include "RC.hpp"

#include "UI/Navigation/Menu/Menu.hpp"

namespace pizda {
	OpenMenuButton::OpenMenuButton() {
		constexpr static uint8_t size = 32;
		
		setSize(Size(size));
		setCornerRadius(getSize().getWidth() / 2 - 1);

		setDefaultBackgroundColor(&Theme::bg2);
		setDefaultBorderColor(&Theme::bg3);
		setDefaultTextColor(&Theme::fg5);

		setActiveBackgroundColor(&Theme::fg1);
		setActiveBorderColor(nullptr);
		setActiveTextColor(&Theme::bg1);
		
		setFont(&Theme::fontSmall);
		
		setText("^");
		
		setAlignment(Alignment::center, Alignment::end);
		setMargin(Margin(0, 0, 0, -(size / 2 + 3)));
		setContentMargin(Margin(0, 0, 0, 5));
	}
	
	void OpenMenuButton::onClick() {
		Button::onClick();

		(new Menu())->show();
	}
}
