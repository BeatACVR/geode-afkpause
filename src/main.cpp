#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(afkPlayLayer, PlayLayer) {
	struct Fields {
		int m_afkDeaths = 1;
	};
	
	void resetLevel() {
		PlayLayer::resetLevel();

		if (m_fields->m_afkDeaths >= Mod::get()->getSettingValue<int64_t>("attempt-threshold")) {
			m_fields->m_afkDeaths = 1;
			if (Mod::get()->getSettingValue<bool>("enabled")) {
				this->pauseGame(false);
				Notification::create("Game paused due to inactivity.", CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"))->show();
			}
		} else {
			m_fields->m_afkDeaths++;
		}
		return;
	}
};

class $modify(afkPlayerObject, PlayerObject) {
    bool pushButton(PlayerButton p0) {
        if (auto playLayer = static_cast<afkPlayLayer*>(PlayLayer::get())) {
            playLayer->m_fields->m_afkDeaths = 1;
        }
        return PlayerObject::pushButton(p0);
    }
};