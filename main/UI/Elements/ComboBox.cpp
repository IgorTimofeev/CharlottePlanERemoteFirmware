#include "UI/Elements/ComboBox.hpp"
#include "UI/Theme.hpp"
#include "UI/Elements/Dialogs/SelectorDialog.hpp"

namespace pizda {
	ComboBox::ComboBox() {
		setHeight(Theme::elementHeight);
	}

	std::span<const std::string_view> ComboBox::getItems() const {
		return _items;
	}

	void ComboBox::setItems(const std::span<const std::string_view> items) {
		_items = items;
	}

	uint8_t ComboBox::getSelectedIndex() const {
		return _selectedIndex;
	}

	void ComboBox::setSelectedIndex(const uint8_t value) {
		_selectedIndex = value;
	}

	const std::string& ComboBox::getDialogTitle() {
		return _dialogTitle;
	}

	void ComboBox::setDialogTitle(const std::string_view& title) {
		_dialogTitle = title;
	}

	void ComboBox::onClick() {
		Referencer::onClick();

		Theme::openDialog(new SelectorDialog(
			getDialogTitle(),
			_items,
			_selectedIndex,
			[this](const uint8_t index) {
				setSelectedIndex(index);
			}
		));
	}

	void ComboBox::onRender(Renderer* renderer, const Rectangle& bounds) {
		Referencer::onRender(renderer, bounds);

		if (_items.empty())
			return;

		renderer->putText(
			Point(
				bounds.getX() + 10,
				bounds.getYCenter() - Theme::fontNormal.getLineHeight() / 2
			),
			&Theme::fontNormal,
			&Theme::fg1,
			_items[_selectedIndex]
		);
	}
}
