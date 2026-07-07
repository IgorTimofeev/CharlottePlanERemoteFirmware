#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Theme.hpp"
#include "UI/Navigation/MFD/Toolbar/Toolbar.hpp"
#include "UI/Navigation/MFD/Toolbar/Trim/TrimControls.hpp"

namespace pizda {
	using namespace YOBA;

	class TrimToolbar : public RowToolbar {
		public:
			TrimToolbar();
			
		private:
			TrimControl _ailerons;
			TrimControl _elevator;
			TrimControl _rudder;
	};
}