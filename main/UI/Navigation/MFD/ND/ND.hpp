#pragma once

#include "UI/Navigation/MFD/ND/NDScene.hpp"

namespace pizda {
	using namespace YOBA;

	class NDActionButtonDialog : public TitleStackLayoutBottomSheetDialog {
		public:
			NDActionButtonDialog(NDScene* scene);

		private:
			TextButton _addWaypointButton {};
			TextButton _setHomeButton {};
	};

	class ND : public Layout {
		public:
			ND();

			NDScene scene {};

		private:

			StackLayout _buttonRows {};

			TextButton _splitButton {};
			TextButton _viewModeButton {};
			TextButton _latLongButton {};
			TextButton _actionButton {};

			void updateViewModeButtonText();
			void updateSplitButtonText();
			void addGovnoButton(TextButton* button, const std::function<void()>& onClick);
	};
}
