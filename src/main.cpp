
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(ProfilePlusMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto sprite = ButtonSprite::create(
            "PROFILE+",
            90,
            0,
            0.7f,
            true,
            "goldFont.fnt",
            "GJ_button_01.png",
            30.0f
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
        FLAlertLayer::create(
            "PLAYER PROFILE PLUS",
            "Welcome to your enhanced profile!\\n\\n"
            "PLAYER STATS\\n"
            "Your Geometry Dash statistics will appear here.\\n\\n"
            "ACHIEVEMENTS\\n"
            "Your milestones are coming soon!",
            "LET'S GO!"
        )->show();
    }
};
