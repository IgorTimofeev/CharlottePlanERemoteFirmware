#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>
#include <YOBA/UI/Spatial.hpp>

#include "Settings/Settings.hpp"
#include "Types/NavigationData.hpp"

namespace pizda {
	using namespace YOBA;
	using namespace YOBA::spatial;

	class WaypointElement : public SceneElement {
		public:
			explicit WaypointElement(uint16_t waypointIndex);

			void onRender(Renderer* renderer, const Scene& scene, const Vector3F* projectedVertices) override;
			const Vector3F* getVertices() override;
			uint16_t getVertexCount() override;

		private:
			uint16_t waypointIndex;
	};
}
