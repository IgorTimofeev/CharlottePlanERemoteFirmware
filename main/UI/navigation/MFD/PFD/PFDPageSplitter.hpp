#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

namespace pizda {
	using namespace YOBA;

	class PFDPageSplitter : public Control, public ActiveElement {
		protected:
			void onEvent(Event* event) override;
			void onRender(Renderer* renderer, const Rectangle& bounds) override;

		private:
			int32_t _pointerY = -1;
			bool _draggedDohuya = false;
	};
}