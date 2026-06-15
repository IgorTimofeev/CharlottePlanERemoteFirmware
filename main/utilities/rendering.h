#pragma once

#include <YOBA/core.h>
#include <YOBA/UI.h>

#include "types/navigationData.h"

namespace pizda {
	using namespace YOBA;

	class RenderingUtils {
		public:
			static const Color* getWaypointColor(const NavigationWaypointData& waypointData) {
				switch (waypointData.type) {
					case NavigationWaypointType::enroute: {
						return &Theme::magenta1;
					}
					default: {
						return &Theme::ocean;
					}
				}
			}

			static void renderWaypointIcon(Renderer* renderer, const Point& center, const Color* color, const NavigationWaypointData& waypointData) {
				switch (waypointData.type) {
					case NavigationWaypointType::enroute: {
						renderer->renderRectangle(
							Rectangle(
								center.getX() - 1,
								center.getY() - 1,
								3,
								3
							),
							color
						);

						renderer->renderHorizontalLine(
							Point(
								center.getX() - 3,
								center.getY()
							),
							2,
							color
						);

						renderer->renderHorizontalLine(
							Point(
								center.getX() + 2,
								center.getY()
							),
							2,
							color
						);

						renderer->renderVerticalLine(
							Point(
								center.getX(),
								center.getY() - 3
							),
							2,
							color
						);

						renderer->renderVerticalLine(
							Point(
								center.getX(),
								center.getY() + 2
							),
							2,
							color
						);
						break;
					}
					case NavigationWaypointType::runway: {
						renderer->renderCircle(
							center,
							4,
							color
						);

						break;
					}
				}
			}

			static void renderWaypointName(Renderer* renderer, const Point& center, const Color* color, const NavigationWaypointData& waypointData) {
				renderer->renderText(
					Point(center.getX() + 7, center.getY() - 7),
					&Theme::fontSmall,
					color,
					waypointData.name
				);
			}

			static void renderFocusFrame(Renderer* renderer, const Rectangle& bounds, const uint8_t lineLength, const Color* color) {
				const auto x2 = bounds.getX2();
				const auto y2 = bounds.getY2();

				// Top left
				renderer->renderHorizontalLine(bounds.getTopLeft(), lineLength, color);
				renderer->renderVerticalLine(bounds.getTopLeft(), lineLength, color);

				// Top right
				renderer->renderHorizontalLine(Point(x2 - lineLength + 1, bounds.getY()), lineLength, color);
				renderer->renderVerticalLine(Point(x2, bounds.getY()), lineLength, color);

				// Bottom right
				renderer->renderHorizontalLine(Point(x2 - lineLength + 1, y2), lineLength, color);
				renderer->renderVerticalLine(Point(x2, y2 - lineLength + 1), lineLength, color);

				// Bottom left
				renderer->renderHorizontalLine(Point(bounds.getX(), y2), lineLength, color);
				renderer->renderVerticalLine(Point(bounds.getX(), y2 - lineLength + 1), lineLength, color);
			}
	};
}