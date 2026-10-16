
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class ProfilePlusPopup : public Popup<> {
protected:
    bool setup() override {
        this->setTitle("PLAYER PROFILE PLUS", "goldFont.fnt", 0.6f);

        auto heading = CCLabelBMFont::create(
            "PLAYER STATISTICS",
            "bigFont.fnt"
        );
        heading->setScale(0.45f);
        heading->setColor({255, 220, 55});
        heading->setPosition({m_size.width / 2, m_size.height - 55});
        m_mainLayer->addChild(heading);

        auto stats = CCLabelBMFont::create(
            "STARS: COMING SOON\n"
            "DIAMONDS: COMING SOON\n"
            "DEMONS: COMING SOON\n"
            "USER COINS: COMING SOON",
            "bigFont.fnt"
        );
        stats->setScale(0.35f);
        stats->setAlignment(kCCTextAlignmentCenter);
        stats->setColor({255, 255, 255});
        stats->setPosition({m_size.width / 2, m_size.height / 2 + 8});
        m_mainLayer->addChild(stats);

        auto achievements = CCLabelBMFont::create(
            "ACHIEVEMENTS",
            "bigFont.fnt"
        );
        achievements->setScale(0.4f);
        achievements->setColor({100, 255, 100});
        achievements->setPosition({m_size.width / 2, 48});
        m_mainLayer->addChild(achievements);

        auto note = CCLabelBMFont::create(
            "MORE FEATURES COMING SOON!",
            "goldFont.fnt"
        );
        note->setScale(0.3f);
        note->setPosition({m_size.width / 2, 27});
        m_mainLayer->addChild(note);

        return true;
    }

public:
    static ProfilePlusPopup* create() {
        auto ret = new ProfilePlusPopup();

        if (ret->init(240.f, 180.f)) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }
};

class $modify(ProfilePlusMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto sprite = ButtonSprite::create(
            "PROFILE+",
            "goldFont.fnt",
            "GJ_button_01.png",
            0.8f
        );

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(ProfilePlusMenu::openProfile)
        );

        if (auto menu = this->getChildByID("bottom-menu")) {
            menu->addChild(button);
            button->setID("profile-plus-button"_spr);
            menu->updateLayout();
        }

        return true;
    }

    void openProfile(CCObject*) {
        ProfilePlusPopup::create()->show();
    }
};
