#pragma once

#include "UI/Navigation/MFD/ND/NDScene.hpp"

namespace pizda {
	using namespace YOBA;

	class NDActionButtonDialog : public TitleStackLayoutBottomSheetDialog {
		public:
			NDActionButtonDialog(NDScene* scene);

		private:
			Button _addWaypointButton {};
			Button _setHomeButton {};
	};

	class ND : public Layout {
		public:
			ND();

			NDScene scene {};

		private:

			StackLayout _buttonRows {};

			Button _splitButton {};
			Button _viewModeButton {};
			Button _latLongButton {};
			Button _actionButton {};

			void updateViewModeButtonText();
			void updateSplitButtonText();
			void addGovnoButton(Button* button, const std::function<void()>& onClick);
	};
}
