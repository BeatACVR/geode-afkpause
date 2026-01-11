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

		Mod* afkMod = Mod::get();

		if (m_fields->m_afkDeaths >= afkMod->getSettingValue<int64_t>("attempt-threshold")) {
			m_fields->m_afkDeaths = 1;
			if (afkMod->getSettingValue<bool>("enabled")) {
				this->pauseGame(false);
				if (afkMod->getSettingValue<bool>("suppress-notifications")) {
					Notification::create("Game paused due to inactivity.", CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"))->show();
				}
			}
		} else {
			m_fields->m_afkDeaths++;
		}
		return;
	}
};

class $modify(afkPlayerObject, PlayerObject) {
    struct Fields {
		afkPlayLayer* m_playLayer = static_cast<afkPlayLayer*>(PlayLayer::get());
	};
	
	bool pushButton(PlayerButton p0) {
        if (m_fields->m_playLayer) {
            m_fields->m_playLayer->m_fields->m_afkDeaths = 1;
        }
        return PlayerObject::pushButton(p0);
    }
};
