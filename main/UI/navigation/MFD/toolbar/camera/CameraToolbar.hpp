#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>
#include "UI/Theme.hpp"
#include "Config.hpp"
#include "Resources/Images.hpp"

#include "UI/Navigation/MFD/Toolbar/Toolbar.hpp"
#include "UI/Navigation/MFD/Toolbar/Camera/CameraControls.hpp"
#include "UI/Navigation/MFD/Toolbar/ToolbarButton.hpp"

namespace pizda {
	using namespace YOBA;

	class CameraToolbar : public RowToolbar {
		public:
			CameraToolbar();

		protected:
			void onTick() override;

		private:
			CameraControl _pitch;
			CameraControl _yaw;
			ImageToolbarButton _reset { "Reset", &resources::images::menuIconMFDCameraResetImage };
	};
}