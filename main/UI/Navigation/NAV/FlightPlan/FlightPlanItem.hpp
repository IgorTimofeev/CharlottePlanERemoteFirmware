#pragma once

#include <format>

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Elements/Navigation/WaypointButton.hpp"

namespace pizda {
	using namespace YOBA;

	class FlightPlanItem : public WaypointButton {
		public:
			explicit FlightPlanItem(uint16_t legIndex);

		protected:
			void onClick() override;
			void onRender(Renderer* renderer, const Rectangle& bounds) override;

		private:
			uint16_t _legIndex;
	};
}