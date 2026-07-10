#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>
#include "UI/Navigation/Route.hpp"

namespace pizda {
	using namespace YOBA;

	class Menu;

	class MenuView : public MarginLayout {
		public:
			explicit MenuView();

			WrapLayout wrapLayout {};

			virtual void setup();

			Menu* getMenu() const;

			virtual const Route* getRoute() = 0;
	};
}