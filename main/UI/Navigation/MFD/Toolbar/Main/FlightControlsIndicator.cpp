#include "UI/Navigation/MFD/Toolbar/Main/FlightControlsIndicator.hpp"
#include "UI/Theme.hpp"
#include "RC.hpp"

namespace pizda {
	FlightControlsIndicator::FlightControlsIndicator() {
		setSize(Size(21, 21));
	}

	void FlightControlsIndicator::onRender(Renderer* renderer, const Rectangle& bounds) {
		auto& rc = RC::getInstance();

		const auto center = bounds.getCenter();
		const auto radius = bounds.getWidth() / 2 - 2;
		
		renderer->strokeCircle(center, radius, &Theme::fg7);
		
		// Blackout
		renderer->fillRectangle(Rectangle(bounds.getX(), center.getY() - 1, bounds.getWidth(), 3), &Theme::bg1);
		renderer->fillRectangle(Rectangle(center.getX() - 1, bounds.getY(), 3, bounds.getHeight()), &Theme::bg1);
		
		// Lines
		const auto lineLength = bounds.getWidth() / 2 - 1;
		renderer->strokeHorizontalLine(Point(bounds.getX(), center.getY()), lineLength, &Theme::bg5);
		renderer->strokeHorizontalLine(Point(center.getX() + 2, center.getY()), lineLength, &Theme::bg5);
		
		renderer->strokeVerticalLine(Point(center.getX(), bounds.getY()), lineLength, &Theme::bg5);
		renderer->strokeVerticalLine(Point(center.getX(), center.getY() + 2), lineLength, &Theme::bg5);
		
		// Joys
		const auto joyH = bounds.getX() + rc.getAxes().getJoystickHorizontal().getFilteredValueUint8() * bounds.getWidth() / 0xFF;
		const auto joyV = bounds.getY() + (0xFF - rc.getAxes().getJoystickVertical().getFilteredValueUint8()) * bounds.getWidth() / 0xFF;
		
		renderer->putPixel(Point(joyH - 1, joyV), &Theme::yellow);
		renderer->putPixel(Point(joyH + 1, joyV), &Theme::yellow);
		renderer->putPixel(Point(joyH, joyV - 1), &Theme::yellow);
		renderer->putPixel(Point(joyH, joyV + 1), &Theme::yellow);
		
		// Ring
		const auto ring = (rc.getAxes().getRing().getFilteredValueUint8() - 0xFF / 2) * bounds.getWidth() / 0xFF;
		renderer->strokeHorizontalLine(
			Point(
				ring >= 0 ? center.getX() : center.getX() + ring,
				bounds.getY2()
			),
			std::abs(ring),
			&Theme::yellow
		);
		
		// Levers
		constexpr static uint8_t maxLeverHeight = 8;

		renderer->strokeVerticalLine(
			Point(bounds.getX2(), center.getY()),
			rc.getAxes().getLeverRight().getFilteredValueUint8() * maxLeverHeight / 0xFF,
			&Theme::bad1
		);
	}
}