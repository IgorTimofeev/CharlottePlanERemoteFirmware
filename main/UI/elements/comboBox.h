#pragma once

#include <functional>
#include <span>

#include <YOBA/UI.h>
#include <YOBA/core.h>

#include "UI/elements/referencer.h"

namespace pizda {
	using namespace YOBA;

	class ComboBox : public Referencer {
		public:
			ComboBox();

			std::span<const std::string_view> getItems() const;
			void setItems(const std::span<const std::string_view> items);

			uint8_t getSelectedIndex() const;
			void setSelectedIndex(const uint8_t value);

			const std::string& getDialogTitle();
			void setDialogTitle(const std::string_view& title);

		protected:
			void onClick() override;

			void onRender(Renderer* renderer, const Rectangle& bounds) override;

		private:
			std::span<const std::string_view> _items {};
			uint8_t _selectedIndex = 0;
			std::string _dialogTitle;
	};
}