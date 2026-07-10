#include "UI/Elements/Dialogs/ScrollViewDialog.hpp"
#include "UI/Theme.hpp"

namespace pizda {
	ScrollViewDialog::ScrollViewDialog() {
		// ScrollView
		Theme::apply(&scrollView);
		slideLayout += &scrollView;

		// Rows margin
		rowsMarginLayout.setMargin(Margin(15));
		scrollView += &rowsMarginLayout;

		// Rows
		rows.setGap(Theme::verticalGap);
		rowsMarginLayout += &rows;

		// Title
		Theme::applyPageTitle(&title);
		rows += &title;
	}
}
