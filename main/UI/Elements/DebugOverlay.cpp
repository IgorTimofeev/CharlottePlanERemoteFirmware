#include <cstdio>
#include <inttypes.h>
#include <esp_private/esp_clk.h>

#include "UI/Elements/DebugOverlay.hpp"
#include "RC.hpp"

namespace pizda {
	DebugOverlay::DebugOverlay() {
		setVisibleForPointerEvents(false);
	}

	void DebugOverlay::onTick() {
		Element::onTick();

		invalidateRender();
	}

	void DebugOverlay::onRender(Renderer* renderer, const Rectangle& bounds) {
		auto& rc = RC::getInstance();

		int32_t y = 0;

		const auto tickDeltaTime = rc.getTickDeltaTimeUs();

		const auto renderLine = [&renderer, &y](const std::string_view text, const Color* color = &Theme::magenta1, const uint8_t scale = 1) {
			renderer->putText(Point(10, y), &Theme::fontNormal, scale, color, text);

			y += Theme::fontNormal.getLineHeight(scale) + 2;
		};

		// Big fucking FPS counter
		renderLine(
			std::to_string(tickDeltaTime > 0 ? 1'000'000 / tickDeltaTime : 0),
			&Theme::yellow,
			3
		);

		char buffer[64];

		std::snprintf(buffer, sizeof(buffer), "CPU frequency: %" PRIu32 " MHz", static_cast<uint32_t>(esp_clk_cpu_freq()) / 1'000'000);
		renderLine(buffer);

		std::snprintf(buffer, sizeof(buffer), "Heap free: %" PRIu32 " kB", esp_get_free_heap_size() / 1024);
		renderLine(buffer);

		std::snprintf(buffer, sizeof(buffer), "Tick: %" PRIu32 " ms", tickDeltaTime / 1000);
		renderLine(buffer);

		std::snprintf(buffer, sizeof(buffer), "Packet rate RX: %" PRIu16 ", TX: %" PRIu16, rc.getTransceiver().getRXPacketRate(), rc.getTransceiver().getTXPacketRate());
		renderLine(buffer);
	}
}
