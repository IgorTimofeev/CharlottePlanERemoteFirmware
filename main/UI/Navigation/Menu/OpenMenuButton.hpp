#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

namespace pizda {
	using namespace YOBA;

	class OpenMenuButton : public TextButton {
		public:
			OpenMenuButton();

		protected:
			void onClick() override;

		private:
			TranslateTransform _transform {};
	};
}