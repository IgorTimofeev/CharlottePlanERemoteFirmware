#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/MFD/Toolbar/SevenRotaryControl.hpp"

namespace pizda {
	using namespace YOBA;
	
	class TrimControl : public SevenRotaryControl {
		public:
			TrimControl(std::string_view title, int8_t* settingsValue);
			
		protected:
			std::string_view variantIndexToTitle(uint8_t index) override;
			bool isVariantEditable(uint8_t index) override;
			void onRotate(bool clockwise, bool big) override;
			
		private:
			std::string _title;
			int8_t* _settingsValue;
	};
}