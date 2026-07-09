#include "UI/Navigation/NAV/FlightPlan/FlightPlanItem.hpp"
#include "UI/Navigation/NAV/FlightPlan/FlightPlanItemDialog.hpp"
#include "Utilities/Rendering.hpp"
#include "RC.hpp"

namespace pizda {
	FlightPlanItem::FlightPlanItem(const uint16_t legIndex) : _legIndex(legIndex) {
		setWaypointIndex(RC::getInstance().getNavigationData().flightPlan.legs[legIndex].waypointIndex);
	}

	void FlightPlanItem::onClick() {
		(new FlightPlanItemDialog(_legIndex))->show();
	}

	void FlightPlanItem::onRender(Renderer* renderer, const Rectangle& bounds) {
		if (getWaypointIndex() < 0)
			return;

		auto& rc = RC::getInstance();
		const auto& waypointData = rc.getNavigationData().waypoints[getWaypointIndex()];
		const auto isActiveLeg = rc.getNavigationData().flightPlan.activeLegIndex == _legIndex;

		// Background
		renderer->fillRectangle(
			bounds,
			Theme::cornerRadius,
			isActive() ? &Theme::bg4 : &Theme::bg3
		);

		// Frame
		renderer->strokeRectangle(
			bounds,
			Theme::cornerRadius,
			isActiveLeg ? &Theme::magenta1 : (isActive() ? &Theme::fg1 : &Theme::bg4)
		);

		auto x = bounds.getX() + 15;
		const auto yCenter = bounds.getYCenter();
		const auto color = RenderingUtils::getWaypointColor(waypointData);

		// Icon
		RenderingUtils::renderWaypointIcon(
			renderer,
			Point(x, yCenter),
			color,
			waypointData
		);

		x += 15;

		// Name
		renderer->putText(
			Point(
				x,
				yCenter - Theme::fontNormal.getLineHeight() / 2
			),
			&Theme::fontNormal,
			&Theme::fg1,
			waypointData.name
		);

		// Distance
		const auto coordsText = std::format(
			"{} nm",
			YOBA::round(getDistanceNm(), 1)
		);

		x = bounds.getX2() - 10 - Theme::fontNormal.getWidth(coordsText);

		renderer->putText(
			Point(
				x,
				yCenter - Theme::fontNormal.getLineHeight() / 2
			),
			&Theme::fontNormal,
			&Theme::fg4,
			coordsText
		);

		// Active leg
		if (isActiveLeg && _legIndex > 0) {
			constexpr static uint8_t lineWidth = 5;
			constexpr static uint8_t arrowWidth = 4;
			constexpr static uint8_t arrowHeightDiv2 = 2;

			const auto lineHeight = bounds.getHeight() + 5;
			const auto yPrev = yCenter - lineHeight;

			x = bounds.getX() - lineWidth - arrowWidth;

			renderer->strokeHorizontalLine(Point(x, yPrev), lineWidth, &Theme::magenta1);
			renderer->strokeVerticalLine(Point(x, yPrev + 1), lineHeight - 1, &Theme::magenta1);
			renderer->strokeHorizontalLine(Point(x, yCenter), lineWidth, &Theme::magenta1);

			x += lineWidth;

			renderer->fillTriangle(
				Point(x, yCenter - arrowHeightDiv2),
				Point(x + arrowWidth, yCenter),
				Point(x, yCenter + arrowHeightDiv2),
				&Theme::magenta1
			);
		}
	}
}
