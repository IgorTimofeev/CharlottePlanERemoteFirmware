#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>
#include <YOBA/UI/Spatial.hpp>

#include "Settings/Settings.hpp"
#include "Types/NavigationData.hpp"

namespace pizda {
	using namespace YOBA;
	using namespace YOBA::spatial;

	class RouteElement : public SceneElement {
		public:
			RouteElement(uint16_t legIndex);

			const Vector3F* getVertices() override;
			uint16_t getVertexCount() override;
			void onRender(Renderer* renderer, const Scene& scene, const Vector3F* projectedVertices) override;

		private:
			uint16_t _legIndex;
			Vector3F _vertices[2];
	};
}
