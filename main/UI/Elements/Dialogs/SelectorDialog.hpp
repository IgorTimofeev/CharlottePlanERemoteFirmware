#pragma once

#include <functional>
#include <span>

#include <YOBA/UI.hpp>
#include <YOBA/Core.hpp>

#include "UI/Elements/Dialogs/ScrollViewDialog.hpp"
#include "UI/Elements/Referencer.hpp"

namespace pizda {
	using namespace YOBA;

	class SelectorDialog;

	class SelectorDialogItem : public Button {
		public:
			SelectorDialogItem(SelectorDialog* comboBoxDialog, const uint8_t index);

		protected:
			void onClick() override;

		private:
			SelectorDialog* _comboBoxDialog;
			uint8_t _index;
	};

	class SelectorDialog : public ScrollViewDialog {
		public:
			SelectorDialog(
				const std::string_view& title,
				const std::span<const std::string_view> items,
				uint8_t selectedIndex,
				const std::function<void(uint8_t)>& onItemSelected
			);

			~SelectorDialog() override;

			std::span<const std::string_view> getItems() const;
			const std::function<void(uint8_t)>& getOnItemSelected();

		protected:
			void onAddedToParent(Parent* parent) override;

		private:
			const std::span<const std::string_view> _items;
			uint8_t _selectedIndex;
			std::function<void(uint8_t)> _onItemSelected;

			RelativeStackLayout _itemRows {};
	};
}