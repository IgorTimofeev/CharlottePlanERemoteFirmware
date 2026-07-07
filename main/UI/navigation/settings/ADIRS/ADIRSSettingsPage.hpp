#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/Page.hpp"
#include "UI/Elements/Titler.hpp"
#include "UI/Elements/Separator.hpp"

namespace pizda {
	using namespace YOBA;

	class ADIRSSettingsPage : public ScrollViewPage {
		public:
			ADIRSSettingsPage();
			~ADIRSSettingsPage() override;

		protected:
			void onTick() override;
		
		private:
			static int32_t _scrollPosition;

			// ----------------------------- ADIRS -----------------------------

			TextField _ADIRSMagneticDeclinationTextField {};
			Titler _ADIRSMagneticDeclinationTitle { "Magnetic declination (deg)", &_ADIRSMagneticDeclinationTextField };

			// ----------------------------- Calibration -----------------------------

			HorizontalSeparator _calSeparator {};

			TextView _calTitle {};

			TextView _calDescriptionText {};

			ProgressBar _calProgressBar {};
			TextView _calProgressText {};
			
			Button _calAccelAndGyroButton {};
			Button _calMagButton {};
	};
}