#include "UI/Elements/Dialogs/ScrollViewDialog.hpp"
#include "UI/Theme.hpp"

namespace pizda {
	ScrollViewDialog::ScrollViewDialog() {
		// ScrollView
		Theme::apply(&scrollView);
		slideLayout += &scrollView;

		// Rows
		rows.setMargin(Margin(15));
		rows.setGap(Theme::verticalGap);
		scrollView += &rows;

		// Title
		Theme::applyPageTitle(&title);
		rows += &title;
	}
}
