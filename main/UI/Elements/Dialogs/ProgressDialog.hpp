#pragma once

#include <cstdio>

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Elements/Dialogs/ScrollViewDialog.hpp"

namespace pizda {
	using namespace YOBA;

	class ProgressDialog : public ScrollViewDialog {
		public:
			ProgressDialog() {
				// Description text
				Theme::applyDescription(&descriptionText);
				descriptionText.setWrappingEnabled(true);
				rows += &descriptionText;

				// Progress bar
				Theme::apply(&progressBar);
				rows += &progressBar;

				// Progress text
				Theme::apply(&progressText);
				progressText.setHorizontalAlignment(Alignment::center);
				rows += &progressText;

				setProgress(0);
			}

			ProgressBar progressBar;
			TextView progressText;
			TextView descriptionText;

			void setProgress(float value) {
				progressBar.setValue(value);

				char text[8];
				std::snprintf(text, sizeof(text), "%d%", value * 100 / 0xFFFF);

				progressText.setText(text);
			}
	};
}