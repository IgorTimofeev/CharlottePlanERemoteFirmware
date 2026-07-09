#include "UI/Navigation/MFD/PFD/PFDRunwayElement.hpp"
#include "RC.hpp"
#include "UI/Theme.hpp"

namespace pizda {
	PFDRunwayElement::PFDRunwayElement(const uint16_t runwayIndex): RunwayElement(runwayIndex, &Theme::bg1) {

	}

	void PFDRunwayElement::onRender(Renderer* renderer, const Scene& scene, const Vector3F* projectedVertices) {
		const auto& waypointVertex = projectedVertices[4];

		if (waypointVertex.getZ() < scene.getNearPlaneDistance())
			return;

		auto& rc = RC::getInstance();

		// Close enough, rendering runway mesh
		if (waypointVertex.getZ() <= 16'000) {
			RunwayElement::onRender(renderer, scene, projectedVertices);
		}

		// Waypoint labels
		if (!rc.getSettings().personalization.MFD.PFD.waypointLabels || waypointVertex.getZ() < 1'000)
			return;

		const auto& runway = rc.getNavigationData().runways[getRunwayIndex()];
		const auto& waypoint = rc.getNavigationData().waypoints[runway.waypointIndex];

		constexpr static uint8_t lineLength = 25;
		constexpr static uint8_t textOffset = 2;

		renderer->strokeVerticalLine(
			Point(waypointVertex.getX(), waypointVertex.getY() - lineLength),
			lineLength - 1,
			&Theme::fg1
		);

		renderer->fillCircle(
			Point(waypointVertex.getX(), waypointVertex.getY()),
			2,
			&Theme::fg1
		);

		renderer->putText(
			Point(
				waypointVertex.getX() - Theme::fontNormal.getWidth(waypoint.name) / 2,
				waypointVertex.getY() - lineLength - textOffset - Theme::fontNormal.getLineHeight()
			),
			&Theme::fontNormal,
			&Theme::fg1,
			waypoint.name
		);
	}
}
