#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>
#include <YOBA/Hardware/Encoder.hpp>

#include "UI/Theme.hpp"
#include "UI/Navigation/MFD/Toolbar/Toolbar.hpp"

namespace pizda {
	using namespace YOBA;

	class ToolbarSection : public Layout, public BorderElement {
		public:
			ToolbarSection() {
				_titleMargin.setMargin({ Toolbar::contentHorizontalMargin, 0, Toolbar::contentHorizontalMargin, 0 });
				_title.setLayoutTransform(&_titleMargin);

				_title.setAlignment(Alignment::center, Alignment::stretch);
				_title.setFont(&Theme::fontSmall);
				*this += &_title;

				updateColors();
			}
			
			ToolbarSection(const std::string_view title) : ToolbarSection() {
				setTitle(title);
			}
			
			ToolbarSection(const std::string_view title, Element* element) : ToolbarSection(title) {
				*this += element;
			}
			
			void setTitle(const std::string_view title) {
				_title.setText(title);
			}
			
			static void setDefaultMargin(MarginTransform* marginTransform, const uint8_t topOffset = 0) {
				marginTransform->setMargin(Margin(Toolbar::contentHorizontalMargin, Toolbar::topPanelHeight + topOffset, Toolbar::contentHorizontalMargin, 0));
			}
			
		protected:
			void onEventBeforeChildren(Event* event) override {
				Layout::onEventBeforeChildren(event);
				
				if (event->getTypeID() == PointerDownEvent::typeID && !isFocused()) {
					setFocused(true);
					
					event->setHandled(true);
				}
			}
			
			void onFocusChanged() override {
				Element::onFocusChanged();
				
				updateColors();
			}
			
			void onRender(Renderer* renderer, const Rectangle& bounds) override {
				if (isFocused()) {
					// Panel
					renderer->fillRectangle(
						Rectangle(bounds.getX(), bounds.getY(), bounds.getWidth(), Toolbar::topPanelHeight),
						&Theme::bg4
					);

					// Background
					renderer->fillRectangle(
						Rectangle(bounds.getX(), bounds.getY() + Toolbar::topPanelHeight, bounds.getWidth(), bounds.getHeight() - Toolbar::topPanelHeight),
						&Theme::bg3
					);
				}
				
				Layout::onRender(renderer, bounds);
				
				if (getBorderColor()) {
					renderer->strokeHorizontalLine(
						Point(
							bounds.getX(),
							bounds.getY2()
						),
						bounds.getWidth(),
						getBorderColor()
					);
				}
			}

		private:
			MarginTransform _titleMargin {};
			TextView _title {};
			
			void updateColors() {
				_title.setTextColor(isFocused() ? &Theme::fg1 : &Theme::fg5);
			}
	};
	
}