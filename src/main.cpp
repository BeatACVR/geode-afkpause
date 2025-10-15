#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

int afkDeaths = 1;

class $modify(afkPlayerObject, PlayerObject) {
	bool pushButton(PlayerButton p0) {
		if (!PlayerObject::pushButton(p0) || !GameManager::sharedState()->getPlayLayer()) return false;
		afkDeaths = 1;
		return true;
	}
};

class $modify(afkPlayLayer, PlayLayer) {
	void resetLevel() {
		PlayLayer::resetLevel();

		if (afkDeaths >= Mod::get()->getSettingValue<int64_t>("attempt-threshold")) {
			afkDeaths = 1;
			if (Mod::get()->getSettingValue<bool>("enabled")) {
				this->pauseGame(false);
			}
		} else {
			afkDeaths++;
		}
		return;
	}
};
