#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/MFD/Toolbar/SevenRotaryControl.hpp"

namespace pizda {
	using namespace YOBA;
	
	class SpeedRotaryControl : public SevenRotaryControl {
		public:
			SpeedRotaryControl();
		
		protected:
			std::string_view variantIndexToTitle(uint8_t index) override;
			bool isVariantEditable(uint8_t index) override;
			void onRotate(bool clockwise, bool big) override;
			void onPress() override;
			void onTick() override;
	};
}