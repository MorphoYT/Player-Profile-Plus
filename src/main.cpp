
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(ProfilePlusMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto button = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("My Profile"),
            this,
            menu_selector(ProfilePlusMenu::openProfile)
        );

        if (button) {
            if (auto menu = this->getChildByID("bottom-menu")) {
                menu->addChild(button);
                button->setPosition({-100.f, 0.f});
                button->setID("profile-plus-button"_spr);
            }
        }

        return true;
    }

    void openProfile(CCObject*) {
        FLAlertLayer::create(
            "Player Profile Plus",
            "Welcome, MorphoTheNoob! Your profile starts here.",
            "Close"
        )->show();
    }
};
