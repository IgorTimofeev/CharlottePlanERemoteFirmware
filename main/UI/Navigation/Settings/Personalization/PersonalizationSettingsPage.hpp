#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/Page.hpp"

namespace pizda {
	using namespace YOBA;

	class PersonalizationSettingsPage : public ScrollViewPage {
		public:
			PersonalizationSettingsPage();
			~PersonalizationSettingsPage() override;

		private:
			static int32_t _scrollPosition;

			// -------------------------------- General --------------------------------

			TextAndSwitch _generalDarkTheme { "Dark theme" };
			TextAndSwitch _generalAudioFeedback { "Audio feedback" };
			TextAndSwitch _generalDataInterpolation { "Data interpolation" };
			TextAndSwitch _generalDebugOverlay { "Debug overlay" };
	};
}