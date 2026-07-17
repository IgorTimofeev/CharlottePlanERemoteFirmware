#include "UI/Elements/Navigation/SelectWaypointDialog.hpp"

#include "RC.hpp"
#include "UI/Theme.hpp"

namespace pizda {
	void SelectWaypointDialog::select(
		const std::string_view titleText,
		const std::function<void(const WaypointDialogSelectedItem& selectedItem)>& onConfirm
	) {
		Theme::openDialog(new SelectWaypointDialog(titleText, std::nullopt, onConfirm));
	}

	void SelectWaypointDialog::edit(
		const std::string_view titleText,
		const WaypointDialogSelectedItem& selectedItem,
		const std::function<void(const WaypointDialogSelectedItem& selectedItem)>& onConfirm
	) {
		const auto dialog = new SelectWaypointDialog(
			titleText,
			selectedItem,
			onConfirm
		);

		Theme::openDialog(dialog);
	}

	SelectWaypointDialog::SelectWaypointDialog(
		const std::string_view titleText,
		const std::optional<WaypointDialogSelectedItem>& selectedItem,
		const std::function<void(const WaypointDialogSelectedItem& selectedItem)>& onConfirm
	) {
		auto& rc = RC::getInstance();

		Theme::apply(this);

		titleTextView.setText(titleText);

		// Name
		Theme::apply(&_searchTextField);

		_searchTextField.setPlaceholder("Search");

		_searchTextField.setOnTextChanged([this, &rc] {
			if (!_searchTextField.isFocused())
				return;

			// Searching for waypoints by filter & name
			const auto it =
				_searchTextField.getText().length() == 0
				? rc.getNavigationData().waypoints.end()
				: std::ranges::find_if(
					rc.getNavigationData().waypoints,
					[this](const NavigationWaypointData& waypointData) {
						return Text::containsIgnoreCase(waypointData.name, _searchTextField.getText());
					}
				);

			// Not found
			if (it == rc.getNavigationData().waypoints.end()) {
				_waypointTitle.setVisible(false);
			}
			// Found
			else {
				_waypointTitle.setVisible(true);

				const auto waypointIndex = std::distance(rc.getNavigationData().waypoints.begin(), it);
				const auto& waypointData = rc.getNavigationData().waypoints[waypointIndex];

				updateVisualsFromWaypoint(waypointIndex, waypointData);
			}
		});

		Theme::apply(&_searchTextFieldTitle);
		contentStackLayout += &_searchTextFieldTitle;

		// Waypoint
		_waypointButton.setToggle(true);
		_waypointButton.setEnabled(false);

		Theme::apply(&_waypointTitle);
		contentStackLayout += &_waypointTitle;

		// Confirm button
		Theme::applyPrimary(&_confirmButton);
		_confirmButton.setText("Confirm");

		_confirmButton.setOnClick([&rc, this, onConfirm] {
			rc.getApplication().invokeLater([this, onConfirm] {
				if (_waypointButton.getWaypointIndex() < 0)
					return;

				onConfirm(WaypointDialogSelectedItem(_waypointButton.getWaypointIndex()));

				Theme::closeDialog(this);
			});
		});

		contentStackLayout += &_confirmButton;

		// Initialization
		if (selectedItem.has_value()) {
			_waypointTitle.setVisible(true);

			const auto& waypointData = rc.getNavigationData().waypoints[selectedItem.value().waypointIndex];

			_searchTextField.setText(waypointData.name);

			updateVisualsFromWaypoint(
				selectedItem.value().waypointIndex,
				waypointData
			);
		}
		else {
			_waypointTitle.setVisible(false);
		}
	}

	void SelectWaypointDialog::updateVisualsFromWaypoint(
		const uint16_t waypointIndex,
		const NavigationWaypointData& waypointData
	) {
		// const auto& nd = RC::getInstance().getNavigationData();

		_waypointButton.setWaypointIndex(waypointIndex);

		// Runway
		if (waypointData.type == NavigationWaypointType::runway) {
			_waypointTitle.titleTextView.setText("Runway");

			// const auto runwayIndex = nd.getRunwayIndex(waypointIndex);
			// const auto& runway = nd.runways[runwayIndex];
		}
		// Waypoint
		else {
			_waypointTitle.titleTextView.setText("Waypoint");
		}
	}
}
