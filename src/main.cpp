
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class ProfilePlusPopup : public geode::Popup<> {
protected:
    bool setup() override {
        this->setTitle("PLAYER PROFILE PLUS");

        auto title = CCLabelBMFont::create(
            "PLAYER PROFILE PLUS",
            "goldFont.fnt"
        );
        title->setScale(0.42f);
        title->setPosition({
            m_size.width / 2.f,
            m_size.height - 30.f
        });
        m_mainLayer->addChild(title);

        auto statsTitle = CCLabelBMFont::create(
            "PLAYER STATISTICS",
            "goldFont.fnt"
        );
        statsTitle->setScale(0.38f);
        statsTitle->setPosition({
            m_size.width / 2.f,
            m_size.height - 57.f
        });
        m_mainLayer->addChild(statsTitle);

        auto statsNote = CCLabelBMFont::create(
            "Stats API integration needed",
            "bigFont.fnt"
        );
        statsNote->setScale(0.31f);
        statsNote->setPosition({
            m_size.width / 2.f,
            m_size.height - 82.f
        });
        m_mainLayer->addChild(statsNote);

        auto mod = Mod::get();

        bool darkTheme = mod->getSavedValue<bool>(
            "dark-theme",
            false
        );

        auto themeLabel = CCLabelBMFont::create(
            darkTheme ? "THEME: DARK" : "THEME: DEFAULT",
            "goldFont.fnt"
        );
        themeLabel->setScale(0.34f);
        themeLabel->setPosition({
            m_size.width / 2.f,
            m_size.height - 112.f
        });
        m_mainLayer->addChild(themeLabel);

        auto themeButton = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(
                "TOGGLE THEME",
                "goldFont.fnt",
                "GJ_button_01.png",
                0.65f
            ),
            this,
            menu_selector(ProfilePlusPopup::toggleTheme)
        );

        auto favoritesButton = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(
                "FAVORITES",
                "goldFont.fnt",
                "GJ_button_01.png",
                0.65f
            ),
            this,
            menu_selector(ProfilePlusPopup::showFavorites)
        );

        auto menu = CCMenu::create();
        menu->setPosition({
            m_size.width / 2.f,
            52.f
        });
        menu->addChild(themeButton);
        menu->addChild(favoritesButton);

        themeButton->setPosition({0.f, 10.f});
        favoritesButton->setPosition({0.f, -25.f});

        m_mainLayer->addChild(menu);

        auto footer = CCLabelBMFont::create(
            "PLAYER PROFILE PLUS",
            "bigFont.fnt"
        );
        footer->setScale(0.28f);
        footer->setPosition({
            m_size.width / 2.f,
            16.f
        });
        m_mainLayer->addChild(footer);

        return true;
    }

    void toggleTheme(CCObject*) {
        auto mod = Mod::get();

        bool current = mod->getSavedValue<bool>(
            "dark-theme",
            false
        );

        mod->setSavedValue<bool>("dark-theme", !current);

        FLAlertLayer::create(
            "Theme Preference Saved",
            "Your preference was saved. Reopen the popup "
            "to see the updated theme label.",
            "OK"
        )->show();

        this->onClose(nullptr);
        ProfilePlusPopup::create()->show();
    }

    void showFavorites(CCObject*) {
        auto favorites = Mod::get()->getSavedValue<std::string>(
            "favorite-level-ids",
            ""
        );

        FLAlertLayer::create(
            "Favorite Levels",
            favorites.empty()
                ? "You have no saved favorite level IDs yet."
                : favorites.c_str(),
            "OK"
        )->show();
    }

public:
    static ProfilePlusPopup* create() {
        auto ret = new ProfilePlusPopup();

        if (ret->init(260.f, 210.f)) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }
};

class $modify(ProfilePlusMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        auto menu = this->getChildByID("bottom-menu");
        if (!menu)
            return true;

        auto icon = CCSprite::createWithSpriteFrameName(
            "GJ_likeBtn_001.png"
        );

        if (!icon) {
            icon = CCSprite::createWithSpriteFrameName(
                "GJ_infoIcon_001.png"
            );
        }

        if (!icon)
            return true;

        auto sprite = CircleButtonSprite::create(
            icon,
            CircleBaseColor::Green,
            CircleBaseSize::Medium
        );

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(ProfilePlusMenu::openProfile)
        );

        button->setID("profile-plus-button"_spr);
        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

    void openProfile(CCObject*) {
        ProfilePlusPopup::create()->show();
    }
};
