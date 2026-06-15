#pragma once

#include <YOBA/core.h>
#include <YOBA/UI.h>

namespace pizda {
	using namespace YOBA;

	class OpenMenuButton : public Button {
		public:
			OpenMenuButton();

		protected:
			void onClick() override;
	};
}