#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

namespace pizda {
	using namespace YOBA;

	class Toolbar : public Layout {
		public:
			Toolbar();

			constexpr static uint8_t topPanelHeight = 7;
			constexpr static uint8_t contentHorizontalMargin = 7;

		protected:
			RectangularShape topPanel {};
	};
	
	class RowToolbar : public Toolbar {
		public:
			RowToolbar();
		
		protected:
			StackLayout row {};
	};
}