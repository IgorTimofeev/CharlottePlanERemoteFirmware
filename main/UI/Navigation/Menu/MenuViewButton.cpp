#include "UI/Navigation/Menu/MenuViewButton.hpp"
#include "UI/Navigation/Menu/MenuView.hpp"
#include "UI/Navigation/Menu/Menu.hpp"
#include "RC.hpp"

namespace pizda {
	// -------------------------------- Default --------------------------------

	MenuViewButton::MenuViewButton(const Image* image, const std::string_view text) : _image(image) {
		setSize(Size(45, image->getSize().getHeight() + _textOffset + Theme::fontSmall.getLineHeight()));
		setText(text);

		setDefaultBackgroundColor(&Theme::bg3);
		setDefaultTextColor(&Theme::fg4);

		setActiveBackgroundColor(&Theme::bg3);
		setActiveBorderColor(&Theme::fg1);
		setActiveTextColor(&Theme::fg1);
	}

	void MenuViewButton::onRender(Renderer* renderer, const Rectangle& bounds) {
		constexpr static uint8_t cornerRadius = 3;

		// Background
		renderer->fillRectangle(
			Rectangle(bounds.getX() - 1, bounds.getY() - 1, bounds.getWidth() + 2, _image->getSize().getHeight() + 2),
			cornerRadius,
			isActive() ? getActiveBackgroundColor() : getDefaultBackgroundColor()
		);

		// Image
		renderer->putImage(bounds.getTopLeft(), _image);

		// Border
		if (isActive()) {
			renderer->strokeRectangle(
				Rectangle(bounds.getX() - 1, bounds.getY() - 1, bounds.getWidth() + 2, _image->getSize().getHeight() + 2),
				cornerRadius,
				getActiveBorderColor()
			);
		}

		// Text
		renderer->putText(
			Point(
				bounds.getXCenter() - Theme::fontSmall.getWidth(getText()) / 2,
				bounds.getY() + _image->getSize().getHeight() + _textOffset
			),
			&Theme::fontSmall,
			isActive() ? getActiveTextColor() : getDefaultTextColor(),
			getText()
		);
	}

	MenuView* MenuViewButton::getMenuView() const {
		return reinterpret_cast<MenuView*>(getParent()->getParent());
	}
}