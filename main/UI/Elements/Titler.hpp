#pragma once

#include <YOBA/UI.hpp>
#include "UI/Theme.hpp"

namespace pizda {
	using namespace YOBA;

	class Titler : public StackLayout {
		public:
			Titler() {
				setGap(3);

				Theme::applyElementTitle(&title);
				*this += &title;
			}

			explicit Titler(std::string_view title) : Titler()  {
				this->title.setText(title);
			}

			Titler(std::string_view title, Element* element) : Titler(title) {
				*this += element;
			}

			explicit Titler(Element* element) : Titler() {
				*this += element;
			}

			TextView title {};
	};
}