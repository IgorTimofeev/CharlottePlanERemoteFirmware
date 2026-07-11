#pragma once

#include <functional>

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Theme.hpp"
#include "UI/Navigation/MFD/Toolbar/ToolbarSection.hpp"

namespace pizda {
	using namespace YOBA;
	
	class ToolbarButton : public ToolbarSection {
		public:
			ToolbarButton(const std::string_view title) : ToolbarSection(title) {
			
			}
			
	};
	
	class ImageToolbarButton : public ToolbarSection, public ActiveElement {
		public:
			ImageToolbarButton(const std::string_view title, const Image* image) : ToolbarSection(title) {
				_imageViewMargin.setMargin(Margin(Toolbar::contentHorizontalMargin, 2, Toolbar::contentHorizontalMargin, 0));
				_imageView.setLayoutTransform(&_imageViewMargin);

				_imageView.setAlignment(Alignment::center);
				_imageView.setImage(image);
				*this += &_imageView;
			}

			std::function<void()> onPressed = nullptr;

		protected:
			void onEventBeforeChildren(Event* event) override {
				if (event->getTypeID() == PointerDownEvent::typeID || event->getTypeID() == PushButtonEncoderDownEvent::typeID) {
					if (isFocused()) {
						if (onPressed)
							onPressed();
						
						event->setHandled(true);
					}
				}
				
				ToolbarSection::onEventBeforeChildren(event);
			}
			
			void onIsActiveChanged() override {
				ActiveElement::onIsActiveChanged();
				
				setBorderColor(isActive() ? &Theme::fg1 : nullptr);
			}
		
		private:
			MarginTransform _imageViewMargin {};
			ImageView _imageView {};
	};
}