#pragma once

#include "UI/Navigation/MFD/ND/NDScene.hpp"
#include "UI/Theme.hpp"
#include "UI/Elements/Dialogs/ScrollViewDialog.hpp"

namespace pizda {
	using namespace YOBA;

	class NDActionButtonDialog : public ScrollViewDialog {
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
