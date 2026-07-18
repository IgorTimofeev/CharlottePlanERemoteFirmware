#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>
#include <YOBA/Resources/Fonts/PIXY10Font.hpp>
#include <YOBA/Resources/Fonts/Vaticanus8Font.hpp>
// #include <YOBA/Resources/Fonts/unscii8Font.hpp>

namespace pizda {
	using namespace YOBA;

	class Theme {
		public:
			// -------------------------------- Colors --------------------------------

			// Background
			static RGB565Color bg1;
			static RGB565Color bg2;
			static RGB565Color bg3;
			static RGB565Color bg4;
			static RGB565Color bg5;
			static RGB565Color bg6;
			static RGB565Color bg7;
			// Foreground
			static RGB565Color fg1;
			static RGB565Color fg2;
			static RGB565Color fg3;
			static RGB565Color fg4;
			static RGB565Color fg5;
			static RGB565Color fg6;
			static RGB565Color fg7;
			// Overlay
			static RGB565Color overlay;
			// Accent
			static RGB565Color accent1;
			static RGB565Color accent2;
			// Good
			static RGB565Color good1;
			static RGB565Color good2;
			// Bad
			static RGB565Color bad1;
			static RGB565Color bad2;
			static RGB565Color bad3;
			// Red
			static RGB565Color red;
			// Green
			static RGB565Color green1;
			static RGB565Color green2;
			// Blue
			static RGB565Color blue;
			// Magenta
			static RGB565Color magenta1;
			static RGB565Color magenta2;
			// Ocean
			static RGB565Color ocean;
			// Yellow
			static RGB565Color yellow;
			// Ground
			static RGB565Color ground1;
			static RGB565Color ground2;
			// Sky
			static RGB565Color sky1;
			static RGB565Color sky2;

			// -------------------------------- Fonts --------------------------------

			constexpr static PIXY10Font fontNormal {};
			constexpr static Vaticanus8Font fontSmall {};
			// constexpr static Unscii8Font fontSmall {};

			// -------------------------------- UI elements --------------------------------

			constexpr static uint16_t elementHeight = 27;
			constexpr static uint16_t cornerRadius = 3;
			constexpr static uint16_t verticalGap = 9;
			constexpr static uint16_t horizontalGap = 7;

			static void setup();
			static void updateColorScheme();
			static void applyPrimary(TextButton* button);
			static void applySecondary(TextButton* button);
			static void applyCritical(TextButton* button);
			static void applyPlaceholder(TextButton* button);
			static void apply(Slider* slider);
			static void apply(TextField* textField);
			static void apply(ScrollView* scrollView);
			static void apply(Switch* sw);
			static void apply(ProgressBar* progressBar);
			static void apply(TextView* text);
			static void applyPageTitle(TextView* text);
			static void applyElementTitle(TextView* text);
			static void applyDescription(TextView* text);
			static void apply(Divider* divider);
			static void apply(Badge* badge);
			static void apply(Titler* titler);
			static void apply(BottomSheetDialog* dialog);
			static void apply(StackLayoutBottomSheetDialog* dialog);
			static void apply(TitleStackLayoutBottomSheetDialog* dialog);
			static void apply(ColorPickerDialog* dialog);
			static void apply(ColorPicker* colorPicker);
			static void apply(TextAndSwitch* textAndSwitch);
			static void openDialog(BottomSheetDialog* dialog);
			static void closeDialog(BottomSheetDialog* dialog);
	};
}