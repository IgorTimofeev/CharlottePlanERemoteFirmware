#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Theme.hpp"
#include "UI/Navigation/Page.hpp"
#include "UI/Navigation/Route.hpp"
#include "Settings/Settings.hpp"

namespace pizda {
	using namespace YOBA;

	class MenuView;

	class MenuViewButton : public Button {
		public:
			MenuViewButton(const Image* image, std::string_view text);

		protected:
			void onRender(Renderer* renderer, const Rectangle& bounds) override;

			MenuView* getMenuView() const;

		private:
			constexpr static uint8_t _textOffset = 4;

			const Image* _image;
	};
}