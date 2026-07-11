#pragma once

#include <functional>
#include <YOBA/UI.hpp>

#include "UI/Theme.hpp"

namespace pizda {
	using namespace YOBA;

	class Referencer : public Layout {
		public:
			constexpr static uint8_t arrowOffset = 10;
			constexpr static uint8_t arrowWidth = 5;
			constexpr static uint8_t arrowHeightDiv2 = 5;

			static void setDefaultMargin(MarginTransform* marginTransform, const Margin& margin) {
				marginTransform->setMargin(Margin {
					margin.getLeft(),
					margin.getTop(),
					static_cast<uint16_t>(margin.getRight() + arrowWidth + arrowOffset),
					margin.getBottom()
				});
			}

			void setOnClick(const std::function<void()>& onClick) {
				_onClick = onClick;
			}

		protected:
			virtual void onClick() {

			}

			void onEventBeforeChildren(Event* event) override {
				Layout::onEventBeforeChildren(event);

				if (event->getTypeID() == PointerDownEvent::typeID) {
					setFocused(true);

					event->setHandled(true);
				}
				else if (event->getTypeID() == PointerUpEvent::typeID) {
					setFocused(false);

					onClick();

					if (_onClick)
						_onClick();

					event->setHandled(true);
				}
			}

			void onPointerOverChanged() override {
				if (!isPointerOver())
					setFocused(false);
			}

			void onRender(Renderer* renderer, const Rectangle& bounds) override {
				renderer->fillRectangle(bounds, Theme::cornerRadius, isFocused() ? &Theme::bg4 : &Theme::bg3);
				renderer->strokeRectangle(bounds, Theme::cornerRadius, isFocused() ? &Theme::bg5 : &Theme::bg4);

				const Point arrowPos {
					bounds.getX2() - arrowOffset,
					bounds.getYCenter()
				};

				renderer->strokeLine(
					arrowPos,
					Point {
						arrowPos.getX() - arrowWidth,
						arrowPos.getY() - arrowHeightDiv2
					},
					&Theme::fg5
				);

				renderer->strokeLine(
					arrowPos,
					Point {
						arrowPos.getX() - arrowWidth,
						arrowPos.getY() + arrowHeightDiv2
					},
					&Theme::fg5
				);

				Layout::onRender(renderer, bounds);
			}

		private:
			std::function<void()> _onClick = nullptr;
	};
}