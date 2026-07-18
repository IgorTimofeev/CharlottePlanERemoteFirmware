#pragma once

#include <esp_log.h>

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Theme.hpp"
#include "UI/Elements/TabSelector.hpp"
#include "Types/NavigationData.hpp"
#include "RC.hpp"

namespace pizda {
	using namespace YOBA;

	class LatLonRow : public RelativeStackLayout {
		public:
			LatLonRow() {
				setOrientation(Orientation::horizontal);
				setGap(Theme::verticalGap);

				Theme::apply(&latitude);
				*this += &latitude;

				Theme::apply(&longitude);
				*this += &longitude;
			}

			TextField latitude {};
			TextField longitude {};

			void fromRadians(const float lat, const float lon) {
				latitude.setText(std::to_string(Math::toDegrees(lat)));
				longitude.setText(std::to_string(Math::toDegrees(lon)));
			}

			bool toRadians(float& lat, float& lon) {
				// Lat
				if (!Text::tryParseFloat(latitude.getText().data(), lat)) {
					latitude.setDefaultBorderColor(&Theme::bad1);
					return false;
				}

				lat = YOBA::Math::toRadians(lat);

				// Lon
				if (!Text::tryParseFloat(longitude.getText().data(), lon)) {
					longitude.setDefaultBorderColor(&Theme::bad1);
					return false;
				}

				lon = YOBA::Math::toRadians(lon);

				return true;
			}
	};

	class AddWaypointDialog : public TitleStackLayoutBottomSheetDialog {
		public:
			static void create(const GeoCoordinates& coordinates, const std::function<void()>& onConfirm) {
				const auto dialog = new AddWaypointDialog(coordinates, onConfirm);
				Theme::openDialog(dialog);
			}

		private:
			std::function<void()> _onConfirm;

			TabSelectorItem _enrouteTypeItem {};
			TabSelectorItem _runwayTypeItem {};
			TabSelector _typeSelector {};

			TextField _nameTextField {};
			Titler _nameTitle { "Name", &_nameTextField };

			RelativeStackLayout _latitudeAndLongitudeRow { Orientation::horizontal, 10 };

			LatLonRow _latLon {};
			Titler _latLonTitle { "Latitude & longitude", &_latLon };

			TextButton _confirmButton {};

			AddWaypointDialog(const GeoCoordinates& coordinates, const std::function<void()>& onConfirm) : _onConfirm(onConfirm) {
				auto& rc = RC::getInstance();
				auto& nd = rc.getNavigationData();

				Theme::apply(this);

				titleTextView.setText("Create waypoint");

				// Type
				_enrouteTypeItem.setText("Enroute");
				_typeSelector.addItem(&_enrouteTypeItem);

				_runwayTypeItem.setText("Runway");
				_typeSelector.addItem(&_runwayTypeItem);

				_typeSelector.applyDialogStyle();
				_typeSelector.setSelectedIndex(0);

				contentStackLayout += &_typeSelector;

				// Name
				Theme::apply(&_nameTextField);
				Theme::apply(&_nameTitle);
				contentStackLayout += &_nameTitle;

				// Latitude & longitude
				_latLon.fromRadians(coordinates.getLatitude(), coordinates.getLongitude());
				Theme::apply(&_latLonTitle);
				contentStackLayout += &_latLonTitle;

				// Confirm
				Theme::applyPrimary(&_confirmButton);
				_confirmButton.setText("Confirm");

				_confirmButton.setOnClick([this, &nd, &rc] {
					// Name
					if (_nameTextField.getText().size() == 0) {
						_nameTextField.setDefaultBorderColor(&Theme::bad1);
						return;
					}

					// Lat
					float lat, lon;

					if (!_latLon.toRadians(lat, lon))
						return;

					// Finally
					rc.getApplication().invokeLater([this, &nd, lat, lon] {
						nd.addEnrouteWaypoint(
							NavigationWaypointType::enroute,
							_nameTextField.getText(),
							GeoCoordinates(lat, lon, 0)
						);

						_onConfirm();

						Theme::closeDialog(this);
					});
				});

				contentStackLayout += &_confirmButton;
			}
	};
}