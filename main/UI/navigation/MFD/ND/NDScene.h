#pragma once

#include <YOBA/core.h>
#include <YOBA/UI.h>
#include <YOBA/UI/spatial.h>

#include "types/navigationData.h"
#include "settings/settings.h"
#include "UI/theme.h"
#include "aircraft.h"

namespace pizda {
	using namespace YOBA;
	using namespace YOBA::spatial;

	class NDScene : public Scene {
		public:
			NDScene();
			~NDScene() override;

			constexpr static uint32_t cameraAltitudeMinimum = 20;
			constexpr static uint32_t cameraAltitudeMaximum = GeoCoordinates::equatorialRadiusMeters * 2;

			const GeoCoordinates& getCameraOffset() const;
			GeoCoordinates getCameraCoordinates() const;
			void setCameraOffset(const GeoCoordinates& value);
			void resetCameraLateralOffset();
			bool isCameraShifted() const;
			void deleteSceneElements();
			void createSceneElementsFromNavigationData();

		protected:
			void onTick() override;
			void onBoundsChanged() override;
			void onEvent(Event* event) override;
			void onFocusChanged() override;
			void onRender(Renderer* renderer, const Rectangle& bounds) override;

		private:
			constexpr static uint8_t compassTickMarkUnitsDeg = 10;
			constexpr static uint8_t compassTickMarkUnitsBigDeg = 30;

			constexpr static uint8_t compassLateralOffsetCrossSize = 8;

			constexpr static uint8_t compassTickMarkSmallLength = 2;
			constexpr static uint8_t compassTickMarkBigLength = 4;
			constexpr static uint8_t compassTickMarkTextOffset = 4;

			constexpr static uint8_t compassCircleMarginTopPct = 8;
			constexpr static uint8_t compassCircleMarginBottomPct = 14;
			constexpr static uint8_t compassCircleMarginHorizontalPct = 6;

			constexpr static uint16_t compassArcViewportDeg = compassTickMarkUnitsDeg * 10;
			constexpr static uint16_t compassArcViewportHalfDeg = compassArcViewportDeg / 2;
			constexpr static uint16_t compassArcTriangleWidth = 6;
			constexpr static uint16_t compassArcTriangleHeight = 5;

			static GeoCoordinates _cameraOffset;
			GeoCoordinates _cameraCoordinates {};

			float _pinchLength = 0;
			Point _pointerDownPosition {};
			int64_t _focusingFrameTimeUs = 0;

			AircraftElement* _aircraftElement = nullptr;

			float getEquatorialRadiansPerPixel() const;
			void updatePivot();
	};
}