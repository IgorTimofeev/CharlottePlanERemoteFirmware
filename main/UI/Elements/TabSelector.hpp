#pragma once

#include <YOBA/UI.hpp>
#include <YOBA/Core.hpp>

#include "UI/Theme.hpp"

namespace pizda {
	using namespace YOBA;

	class TabSelectorItem : public SelectorItem, public TextElement {
		public:
			TabSelectorItem() {

			}

			explicit TabSelectorItem(std::string_view text) : TabSelectorItem() {
				setText(text);
			}

		protected:
			void onRender(Renderer* renderer, const Rectangle& bounds) override {
				if (isActive()) {
					renderer->fillRectangle(
						bounds,
						Theme::cornerRadius,
						&Theme::fg1
					);
				}

				renderer->putText(
					Point(
						bounds.getXCenter() - Theme::fontNormal.getWidth(getText()) / 2,
						bounds.getYCenter() - Theme::fontNormal.getLineHeight() / 2
					),
					&Theme::fontNormal,
					isActive() ? &Theme::bg1 : &Theme::fg4,
					getText()
				);
			}
	};

	class TabSelector : public Selector {
		public:
			TabSelector() {
				setHeight(Theme::elementHeight);

				applyPageStyle();

				backgroundRectangle.setCornerRadius(Theme::cornerRadius);
				*this += &backgroundRectangle;

				itemsLayout.setOrientation(Orientation::horizontal);
				itemsLayout.setGap(1);
				*this += &itemsLayout;
				setItemLayout(&itemsLayout);
			}

			RectangularShape backgroundRectangle {};
			RelativeStackLayout itemsLayout {};

			void applyPageStyle() {
				backgroundRectangle.setFillColor(&Theme::bg2);
				backgroundRectangle.setBorderColor(&Theme::bg3);
			}

			void applyDialogStyle() {
				backgroundRectangle.setFillColor(&Theme::bg1);
				backgroundRectangle.setBorderColor(&Theme::bg3);
			}
	};
}