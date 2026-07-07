#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>
#include <YOBA/UI/Spatial.hpp>

#include "UI/Elements/Spatial/RunwayElement.hpp"

namespace pizda {
	using namespace YOBA;
	using namespace YOBA::spatial;

	class NDRunwayElement : public RunwayElement {
		public:
			NDRunwayElement(uint16_t runwayIndex);

			void onRender(Renderer* renderer, const Scene& scene, const Vector3F* projectedVertices) override;
	};
}
