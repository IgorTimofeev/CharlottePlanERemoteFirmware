#include "UI/Elements/Dialogs/SelectorDialog.hpp"
#include "UI/Theme.hpp"

namespace pizda {
	SelectorDialogItem::SelectorDialogItem(SelectorDialog* comboBoxDialog, const uint8_t index) : _comboBoxDialog(comboBoxDialog), _index(index) {
		Theme::applySecondary(this);

		setToggle(true);
		setActiveBorderColor(&Theme::accent1);
		setText(_comboBoxDialog->getItems()[index]);
	}

	void SelectorDialogItem::onClick() {
		Button::onClick();

		Application::getCurrent()->invokeLater([this] {
			_comboBoxDialog->getOnItemSelected()(_index);

			Theme::closeDialog(_comboBoxDialog);
		});
	}

	SelectorDialog::SelectorDialog(
		const std::string_view& title,
		const std::span<const std::string_view> items,
		const uint8_t selectedIndex,
		const std::function<void(uint8_t)>& onItemSelected
	) :
		_items(items),
		_selectedIndex(selectedIndex),
		_onItemSelected(onItemSelected)
	{
		Theme::apply(this);

		this->titleTextView.setText(title);

		_itemRows.setGap(Theme::verticalGap);
		contentStackLayout += &_itemRows;

		for (uint16_t i = 0; i < _items.size(); ++i) {
			const auto item = new SelectorDialogItem(this, i);
			item->setActive(i == _selectedIndex);

			_itemRows += item;
		}
	}

	SelectorDialog::~SelectorDialog() {
		for (const auto child : _itemRows)
			delete child;
	}

	std::span<const std::string_view> SelectorDialog::getItems() const {
		return _items;
	}

	const std::function<void(uint8_t)>& SelectorDialog::getOnItemSelected() {
		return _onItemSelected;
	}

	void SelectorDialog::onAddedToParent(Parent* parent) {
		TitleStackLayoutBottomSheetDialog::onAddedToParent(parent);

		_itemRows[_selectedIndex]->scrollIntoView();
	}
}
