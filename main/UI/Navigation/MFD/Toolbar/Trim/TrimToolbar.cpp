#include "UI/Navigation/MFD/Toolbar/Trim/TrimToolbar.hpp"
#include "RC.hpp"

namespace pizda {
	TrimToolbar::TrimToolbar() :
		_ailerons(TrimControl { "Ailerons", &RC::getInstance().getSettings().controls.aileronsTrim }),
		_elevator(TrimControl { "Elevator", &RC::getInstance().getSettings().controls.elevatorTrim }),
		_rudder(TrimControl { "Rudder", &RC::getInstance().getSettings().controls.rudderTrim })
	{
		row += &_ailerons;
		row += &_elevator;
		row += &_rudder;
	}
}