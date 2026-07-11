#pragma once

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Theme.hpp"
#include "UI/Navigation/Menu/OpenMenuButton.hpp"

namespace pizda {
	using namespace YOBA;

	class Page : public Layout {
		public:
			static void setDefaultContentMargin(MarginTransform* marginTransform);
	};

	// ----------------------------- Templates -----------------------------

	class TitlePageTemplate : public Page {
		public:
			TitlePageTemplate();

			TextView title {};
	};

	class StackRowsPageTemplate : public TitlePageTemplate {
		public:
			StackRowsPageTemplate();

			MarginTransform rowsMargin {};
			StackLayout rows {};
	};

	// ----------------------------- Ready to use -----------------------------

	class ScrollViewPage : public StackRowsPageTemplate {
		public:
			ScrollViewPage();

			ScrollView scrollView {};
	};

	class RelativeRowsPage : public TitlePageTemplate {
		public:
			RelativeRowsPage();

			MarginTransform rowsMargin {};
			RelativeStackLayout rows {};
	};
}