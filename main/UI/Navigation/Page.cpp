#include "UI/Navigation/Page.hpp"

namespace pizda {
	// ----------------------------- Templates -----------------------------

	void Page::setDefaultContentMargin(MarginLayout* marginLayout) {
		marginLayout->setMargin(Margin(15, 15, 15, 20));
	}

	TitlePageTemplate::TitlePageTemplate() {
		// Title
		Theme::applyPageTitle(&title);
		title.setVerticalAlignment(Alignment::center);
	}

	StackRowsPageTemplate::StackRowsPageTemplate() {
		// Margin
		setDefaultContentMargin(&rowsMarginLayout);

		// Rows
		rows.setGap(Theme::verticalGap);
		rowsMarginLayout += &rows;

		// Title
		rows += &title;
	}

	// ----------------------------- Ready to use -----------------------------

	ScrollViewPage::ScrollViewPage() {
		// Scroll view
		Theme::apply(&scrollView);
		*this += &scrollView;

		// Rows
		scrollView += &rowsMarginLayout;
	}

	RelativeRowsPage::RelativeRowsPage() {
		// Margin
		setDefaultContentMargin(&rowsMarginLayout);
		*this += &rowsMarginLayout;

		// Rows
		rows.setGap(Theme::verticalGap);
		rowsMarginLayout += &rows;

		// Title
		rows += &title;
		rows.setAutoSize(&title);
	}
}
