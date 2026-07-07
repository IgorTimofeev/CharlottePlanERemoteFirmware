#pragma once

#include <array>

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/Menu/MenuView.hpp"
#include "UI/Navigation/Menu/MenuViewButton.hpp"
#include "Resources/Images.hpp"

namespace pizda {
	using namespace YOBA;

	class MFDMenuViewTopToolbarButton : public MenuViewButton {
		public:
			explicit MFDMenuViewTopToolbarButton(const Image* image, std::string_view text, PersonalizationSettingsMFDToolbarMode mode);

		protected:
			void onClick() override;

		private:
			PersonalizationSettingsMFDToolbarMode _mode;
	};

	class MFDMenuView : public MenuView {
		public:
			explicit MFDMenuView();

			MFDMenuViewTopToolbarButton
				autopilotButton { &Images::menuIconMFDAutopilot, "A/P", PersonalizationSettingsMFDToolbarMode::autopilot },
				pressureButton { &Images::menuIconMFDBaro, "BARO", PersonalizationSettingsMFDToolbarMode::baro },
				trimButton { &Images::menuIconMFDTrim, "Trim", PersonalizationSettingsMFDToolbarMode::trim },
				lightsButton { &Images::menuIconMFDLights, "Lights", PersonalizationSettingsMFDToolbarMode::lights },
				cameraButton { &Images::menuIconMFDCameraImage, "Camera", PersonalizationSettingsMFDToolbarMode::camera };

			std::array<MFDMenuViewTopToolbarButton*, 5> topToolbarButtons {
				&autopilotButton,
				&pressureButton,
				&trimButton,
				&lightsButton,
				&cameraButton
			};

			const Route* getRoute() override;
	};
}