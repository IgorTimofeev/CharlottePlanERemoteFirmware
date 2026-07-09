#pragma once

#include <YOBA/UI.hpp>

#include "UI/Theme.hpp"

namespace pizda {
	using namespace YOBA;

	class HorizontalSeparator : public Shape {
		public:
			HorizontalSeparator() {
				setHeight(1);
				setFillColor(&Theme::bg3);
			}
			
			void onRender(Renderer* renderer, const Rectangle& bounds) override {
				auto color = getFillColor();
				
				if (color)
					renderer->strokeHorizontalLine(bounds.getTopLeft(), bounds.getWidth(), color);
			}
	};
	
	class VerticalSeparator : public Shape {
		public:
			VerticalSeparator() {
				setWidth(1);
				setFillColor(&Theme::bg3);
			}
			
			void onRender(Renderer* renderer, const Rectangle& bounds) override {
				auto color = getFillColor();
				
				if (color)
					renderer->strokeVerticalLine(bounds.getTopLeft(), bounds.getHeight(), color);
			}
	};
}