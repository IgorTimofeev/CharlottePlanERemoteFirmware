#include "UI/Elements/Dialogs/ScrollViewDialog.hpp"
#include "UI/Theme.hpp"

namespace pizda {
	ScrollViewDialog::ScrollViewDialog() {
		// ScrollView
		Theme::apply(&scrollView);
		slideLayout += &scrollView;

		// Rows margin
		rowsMargin.setMargin(Margin(15));
		rows.setLayoutTransform(&rowsMargin);

		// Rows
		rows.setGap(Theme::verticalGap);
		scrollView += &rows;

		// Title
		Theme::applyPageTitle(&title);
		rows += &title;
	}
}
