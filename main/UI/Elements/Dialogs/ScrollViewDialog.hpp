#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Elements/Dialogs/Dialog.hpp"

namespace pizda {
	using namespace YOBA;

	class ScrollViewDialog : public Dialog {
		public:
			ScrollViewDialog();

			ScrollView scrollView {};
			MarginLayout rowsMarginLayout {};
			StackLayout rows {};
			TextView title {};
	};
}