#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

namespace pizda {
	using namespace YOBA;

	class DebugOverlay : public Control {
		public:
			DebugOverlay();

		protected:
			void onTick() override;
			void onRender(Renderer* renderer, const Rectangle& bounds) override;
	};
}