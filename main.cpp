
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
            button->setID("profile-plus-button"_spr);
            this->getChildByID("bottom-menu")
                ->addChild(button);
            button->setPosition({0, 0});
        }

        return true;
    }

    void openProfile(CCObject*) {
        FLAlertLayer::create(
            "Player Profile Plus",
            "Welcome to your profile, MorphoTheNoob!",
            "Close"
        )->show();
    }
};
