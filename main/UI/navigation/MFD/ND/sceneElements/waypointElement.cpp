#include "UI/Navigation/MFD/ND/SceneElements/WaypointElement.hpp"
#include "UI/Navigation/MFD/ND/SceneElements/RouteElement.hpp"
#include "RC.hpp"
#include "UI/Theme.hpp"
#include "UI/Navigation/MFD/ND/NDScene.hpp"
#include "Utilities/Rendering.hpp"

namespace pizda {
	WaypointElement::WaypointElement(const uint16_t waypointIndex) : waypointIndex(waypointIndex) {

	}

	void WaypointElement::onRender(Renderer* renderer, const Scene& scene, const Vector3F* projectedVertices) {
		if (projectedVertices[0].getZ() < scene.getNearPlaneDistance())
			return;

		const auto& waypointData = RC::getInstance().getNavigationData().waypoints[waypointIndex];

		const auto& waypointPosition = Point(
			static_cast<int32_t>(projectedVertices[0].getX()),
			static_cast<int32_t>(projectedVertices[0].getY())
		);

		RenderingUtils::renderWaypointIcon(
			renderer,
			waypointPosition,
			&Theme::magenta1,
			waypointData
		);

		RenderingUtils::renderWaypointName(
			renderer,
			waypointPosition,
			&Theme::fg1,
			waypointData
		);
	}

	const Vector3F* WaypointElement::getVertices() {
		return &RC::getInstance().getNavigationData().waypoints[waypointIndex].cartesianCoordinates;
	}

	uint16_t WaypointElement::getVertexCount() {
		return 1;
	}
}
