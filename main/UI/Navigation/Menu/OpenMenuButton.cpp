#include "UI/Navigation/Menu/OpenMenuButton.hpp"

#include "UI/Theme.hpp"
#include "RC.hpp"

#include "UI/Navigation/Menu/Menu.hpp"

namespace pizda {
	OpenMenuButton::OpenMenuButton() {
		constexpr static uint8_t size = 32;

		setAlignment(Alignment::center, Alignment::end);
		setMargin(Margin(0, 0, 0, -(size / 2 + 3)));

		_button.setSize(Size(size));
		_button.setCornerRadius(size / 2 - 1);
		_button.setContentMargin(Margin(0, 0, 0, 5));

		_button.setDefaultBackgroundColor(&Theme::bg2);
		_button.setDefaultBorderColor(&Theme::bg3);
		_button.setDefaultTextColor(&Theme::fg5);

		_button.setActiveBackgroundColor(&Theme::fg1);
		_button.setActiveBorderColor(nullptr);
		_button.setActiveTextColor(&Theme::bg1);
		
		_button.setFont(&Theme::fontSmall);
		_button.setText("^");

		_button.setOnClick([] {
			(new Menu())->show();
		});

		*this += &_button;
	}
}
