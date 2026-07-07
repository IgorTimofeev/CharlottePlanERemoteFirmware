#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/Menu/MenuViewButton.hpp"
#include "UI/Navigation/Route.hpp"

namespace pizda {
	using namespace YOBA;

	class PageMenuViewButton : public MenuViewButton {
		public:
			PageMenuViewButton(const Image* image, std::string_view text, const Route* route);

			const Route* getRoute() const;

		protected:
			void onClick() override;

		private:
			const Route* _route;
	};
}