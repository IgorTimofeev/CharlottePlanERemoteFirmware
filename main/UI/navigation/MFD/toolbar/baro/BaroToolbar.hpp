#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/MFD/Toolbar/Toolbar.hpp"
#include "UI/Navigation/MFD/Toolbar/ToolbarButton.hpp"
#include "UI/Navigation/MFD/Toolbar/Baro/ReferencePressureRotaryControl.hpp"
#include "UI/Navigation/MFD/Toolbar/Baro/MinimumsRotaryControl.hpp"

#include "Resources/Images.hpp"

namespace pizda {
	using namespace YOBA;

	class BaroToolbar : public RowToolbar {
		public:
			BaroToolbar();

			ImageToolbarButton metricUnits { "Metric", &resources::images::menuIconMfdMetricUnits };
			ReferencePressureRotaryControl pressure {};
			MinimumsRotaryControl minimums {};
	};
}