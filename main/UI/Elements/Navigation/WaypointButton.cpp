#include <cstdio>

#include "UI/Elements/Navigation/WaypointButton.hpp"
#include "UI/Theme.hpp"
#include "Types/NavigationData.hpp"
#include "Utilities/Rendering.hpp"
#include "RC.hpp"

namespace pizda {
	WaypointButton::WaypointButton() {
		setHeight(height);
	}

	WaypointButton::WaypointButton(const uint32_t waypointIndex): WaypointButton() {
		setWaypointIndex(waypointIndex);
	}

	int32_t WaypointButton::getWaypointIndex() const {
		return _waypointIndex;
	}

	void WaypointButton::setWaypointIndex(const int32_t value) {
		_waypointIndex = value;

		if (_waypointIndex >= 0) {
			auto& rc = RC::getInstance();
			const auto& waypointData = rc.getNavigationData().waypoints[value];

			_distanceNm = YOBA::round(
				Units::convertDistance(
					(waypointData.cartesianCoordinates - rc.getAircraftData().computed.coordinates.toCartesian()).getLength(),
					DistanceUnit::meter,
					DistanceUnit::nauticalMile
				),
				1
			);
		}

		invalidate();
	}

	float WaypointButton::getDistanceNm() const {
		return _distanceNm;
	}

	void WaypointButton::onRender(Renderer* renderer, const Rectangle& bounds) {
		if (_waypointIndex < 0)
			return;

		const auto& waypointData = RC::getInstance().getNavigationData().waypoints[_waypointIndex];

		constexpr static uint8_t cornerRadius = 3;

		renderer->fillRectangle(
			bounds,
			cornerRadius,
			isActive() ? &Theme::bg4 : &Theme::bg3
		);

		renderer->strokeRectangle(
			bounds,
			cornerRadius,
			isActive() ? &Theme::fg1 : &Theme::bg4
		);

		auto x = bounds.getX() + 15;
		const auto y = bounds.getYCenter();

		const auto color = RenderingUtils::getWaypointColor(waypointData);

		RenderingUtils::renderWaypointIcon(
			renderer,
			Point(x, y),
			color,
			waypointData
		);

		x += 15;

		renderer->putText(
			Point(
				x,
				y - Theme::fontNormal.getLineHeight() / 2
			),
			&Theme::fontNormal,
			&Theme::fg1,
			waypointData.name
		);

		// Distance
		char coordsText[14];
		std::snprintf(coordsText, sizeof(coordsText), "%f nm" PRIi32, YOBA::round(_distanceNm, 1));

		x = bounds.getX2() - 10 - Theme::fontNormal.getWidth(coordsText);

		renderer->putText(
			Point(
				x,
				y - Theme::fontNormal.getLineHeight() / 2
			),
			&Theme::fontNormal,
			&Theme::fg4,
			coordsText
		);
	}
}
