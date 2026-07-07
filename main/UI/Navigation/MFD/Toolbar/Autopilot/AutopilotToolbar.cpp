#include "UI/Navigation/MFD/Toolbar/Autopilot/AutopilotToolbar.hpp"
#include "RC.hpp"
#include "Resources/Sounds.hpp"

namespace pizda {
	AutopilotToolbar::AutopilotToolbar() {
		auto& rc = RC::getInstance();
	
		// FD
		flightDirector.setActive(rc.getSettings().personalization.MFD.PFD.flightDirector);

		flightDirector.onPressed = [this, &rc] {
			rc.getSettings().personalization.MFD.PFD.flightDirector = !rc.getSettings().personalization.MFD.PFD.flightDirector;
			rc.getSettings().personalization.writeLater();
			
			flightDirector.setActive(rc.getSettings().personalization.MFD.PFD.flightDirector);
			
			rc.playFeedback();
		};

		row += &flightDirector;
		
		row += &speed;
		row += &lateral;
		row += &vertical;

		// Autopilot
		autopilot.onPressed = [&rc] {
			rc.getRemoteData().autopilot.autopilot = !RC::getInstance().getAircraftData().raw.autopilot.autopilot;

			rc.getTransceiver().enqueueSystemPacket(RemoteSystemPacketType::autopilotEnabled);

			rc.getAudioPlayer().play(
				rc.getRemoteData().autopilot.autopilot
				? static_cast<const Sound*>(&Sounds::engaged)
				: &Sounds::disengaged
			);
		};

		row += &autopilot;
	}
	
	void AutopilotToolbar::onTick() {
		Layout::onTick();
		
		autopilot.setActive(RC::getInstance().getAircraftData().raw.autopilot.autopilot);
	}
}