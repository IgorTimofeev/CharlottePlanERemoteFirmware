#include "UI/Navigation/Page.hpp"

namespace pizda {
	// ----------------------------- Templates -----------------------------

	void Page::setDefaultContentMargin(MarginTransform* marginTransform) {
		marginTransform->setMargin(Margin(15, 15, 15, 20));
	}

	TitlePageTemplate::TitlePageTemplate() {
		// Title
		Theme::applyPageTitle(&title);
		title.setVerticalAlignment(Alignment::center);
	}

	StackRowsPageTemplate::StackRowsPageTemplate() {
		// Margin
		setDefaultContentMargin(&rowsMargin);
		rows.setLayoutTransform(&rowsMargin);

		// Rows
		rows.setGap(Theme::verticalGap);

		// Title
		rows += &title;
	}

	// ----------------------------- Ready to use -----------------------------

	ScrollViewPage::ScrollViewPage() {
		// Scroll view
		Theme::apply(&scrollView);
		*this += &scrollView;

		// Rows
		scrollView += &rows;
	}

	RelativeRowsPage::RelativeRowsPage() {
		// Margin
		setDefaultContentMargin(&rowsMargin);
		rows.setLayoutTransform(&rowsMargin);

		// Rows
		rows.setGap(Theme::verticalGap);
		*this += &rows;

		// Title
		rows += &title;
		rows.setAutoSize(&title);
	}
}
