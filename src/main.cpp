
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

        if (button) {
            button->setID("profile-plus-button"_spr);

            if (auto menu = this->getChildByID("bottom-menu")) {
                menu->addChild(button);
                menu->updateLayout();
            }
        }

        return true;
    }

    void openProfile(CCObject*) {
        FLAlertLayer::create(
            "PLAYER PROFILE PLUS",
            "WELCOME, PLAYER!\n\n"
            "====================\n"
            "PLAYER STATISTICS\n"
            "====================\n\n"
            "Stars: Coming soon\n"
            "Diamonds: Coming soon\n"
            "Demons: Coming soon\n"
            "User Coins: Coming soon\n\n"
            "====================\n"
            "ACHIEVEMENTS\n"
            "====================\n\n"
            "Your milestones are coming soon!\n\n"
            "Thanks for playing!",
            "CLOSE"
        )->show();
    }
};
