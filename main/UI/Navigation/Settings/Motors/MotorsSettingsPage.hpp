#pragma once

#include <functional>

#include <YOBA/Core.hpp>
#include <YOBA/UI.hpp>

#include "UI/Navigation/Page.hpp"
#include "Types/Generic.hpp"
#include "UI/Elements/Referencer.hpp"

namespace pizda {
	using namespace YOBA;

	class MotorEditor;

	class MotorEditorDialog : public TitleStackLayoutBottomSheetDialog {
		public:
			MotorEditorDialog(const std::string_view title, MotorEditor* motorEditor);

		private:
			MotorEditor* _motorEditor;

			RelativeStackLayout _textFieldsRow {
				Orientation::horizontal,
				10
			};

			TextField _midpointTextField {};
			Titler _midpointTextFieldTitle { "Midpoint", &_midpointTextField };

			TextField _rangeTextField {};
			Titler _rangeTextFieldTitle { "Range", &_rangeTextField };

			TextAndSwitch _reverseTextAndSwitch {"Reverse" };

			TextView _previewTextView {};

			Button _confirmButton {};

			void tryParse(uint16_t& min, uint16_t& max) const;
			void updatePreview();
	};

	class MotorEditor : public Referencer {
		public:
			MotorEditor(const std::string_view dialogTitle, const MotorType motorType);

			MotorType getMotorType() const;

			void fromSettings();

		protected:
			void onClick() override;

		private:
			const std::string_view _dialogTitle;
			const MotorType _motorType;

			StackLayout _row {
				Orientation::horizontal
			};

			MarginTransform _rowMargin {};
			TextView _rangeTextViews[3] {};

			TextView _reverseTextView {};
			MarginTransform _reverseTextViewMargin {};
	};

	class MotorsSettingsPage : public ScrollViewPage {
		public:
			MotorsSettingsPage();
			~MotorsSettingsPage() override;

		private:
			static int32_t _scrollPosition;

			// Throttle
			MotorEditor _throttleLeft { "Left throttle", MotorType::throttleLeft };
			Titler _throttleLeftTitle { "Left", &_throttleLeft };

			MotorEditor _throttleRight { "Right throttle", MotorType::throttleRight };
			Titler _throttleRightTitle { "Right", &_throttleRight };

			// Ailerons
			Divider _aileronsDivider {};
			TextView _aileronsTitle { "Ailerons" };

			MotorEditor _aileronLeft { "Left aileron", MotorType::aileronLeft };
			Titler _aileronLeftTitle { "Left", &_aileronLeft };

			MotorEditor _aileronRight { "Right aileron", MotorType::aileronRight };
			Titler _aileronRightTitle { "Right", &_aileronRight };

			// Flaps
			Divider _flapsDivider {};
			TextView _flapsTitle { "Flaps" };

			MotorEditor _flapLeft { "Left flap", MotorType::flapLeft };
			Titler _flapLeftTitle { "Left", &_flapLeft };

			MotorEditor _flapRight { "Right flap", MotorType::flapRight };
			Titler _flapRightTitle { "Right", &_flapRight };

			// Tail
			Divider _tailDivider {};
			TextView _tailTitle { "Tail" };

			MotorEditor _tailLeft { "Left tail", MotorType::tailLeft };
			Titler _tailLeftTitle { "Left", &_tailLeft };

			MotorEditor _tailRight { "Right tail", MotorType::tailRight };
			Titler _tailRightTitle { "Right", &_tailRight };

			// Nose
			Divider _noseDivider {};
			TextView _noseTitle { "Nose" };

			MotorEditor _cameraPitch { "Camera pitch", MotorType::cameraPitch };
			Titler _cameraPitchTitle { "Camera pitch", &_cameraPitch };

			MotorEditor _cameraYaw { "Camera yaw", MotorType::cameraYaw };
			Titler _cameraYawTitle { "Camera yaw", &_cameraYaw };

			MotorEditor _noseWheel { "Nose wheel", MotorType::noseWheel };
			Titler _noseWheelTitle { "Wheel", &_noseWheel };

			void penisula(TextView& titleTextView);
			void vaginoz(Titler& titler);
	};
}
