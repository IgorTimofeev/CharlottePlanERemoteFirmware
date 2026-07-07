#pragma once

#include <memory>

#include "UI/Navigation/Page.hpp"

#include "UI/Navigation/MFD/PFD/PFD.hpp"
#include "UI/Navigation/MFD/ND/ND.hpp"

#include "UI/Navigation/MFD/Toolbar/Main/MainToolbar.hpp"
#include "UI/Navigation/MFD/Toolbar/Autopilot/AutopilotToolbar.hpp"
#include "UI/Navigation/MFD/Toolbar/Baro/BaroToolbar.hpp"
#include "UI/Navigation/MFD/Toolbar/Trim/TrimToolbar.hpp"
#include "UI/Navigation/MFD/Toolbar/Lights/LightsToolbar.hpp"
#include "UI/Navigation/MFD/Toolbar/Camera/CameraToolbar.hpp"

namespace pizda {
	using namespace YOBA;

	class MFDLayout : public RelativeStackLayout {
		public:
			void deleteShit();
			void createShit();
			void updateSplitRatio();

			std::unique_ptr<PFD> _PFD {};
			std::unique_ptr<ND> _ND {};
	};

	class MFDPage : public Page {
		public:
			explicit MFDPage();
			~MFDPage() override;

			static MFDPage* getInstance();

			void fromSettings();
			MFDLayout& getMFDLayout();

		private:
			static MFDPage* _instance;

			RelativeStackLayout _rows {};

			MFDLayout _MFDLayout {};

			MainToolbar _mainToolbar {};
			std::unique_ptr<AutopilotToolbar> _autopilotToolbar {};
			std::unique_ptr<BaroToolbar> _baroToolbar {};
			std::unique_ptr<TrimToolbar> _trimToolbar {};
			std::unique_ptr<LightsToolbar> _lightsToolbar {};
			std::unique_ptr<CameraToolbar> _cameraToolbar {};
	};
}