#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

namespace pizda {
	using namespace YOBA;

	class DialogSlideLayoutBackground : public ChessPatternRectangularShape {
		public:
			DialogSlideLayoutBackground();

		protected:
			void onEvent(Event* event) override;
	};

	class Dialog : public RelativeStackLayout {
		public:
			Dialog();

			DialogSlideLayoutBackground ditheredBackground {};

			RectangularShape slideLayoutBackground {};
			Layout slideLayout {};

			void show();
			void hide();
	};
}