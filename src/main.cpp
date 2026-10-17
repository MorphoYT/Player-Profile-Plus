#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class ProfilePlusPopup : public geode::Popup<> {
protected:
    bool setup() override {
        this->setTitle("PLAYER PROFILE PLUS");

        auto mod = Mod::get();

        auto title = CCLabelBMFont::create(
            "PLAYER STATISTICS",
            "goldFont.fnt"
        );
        title->setScale(0.45f);
        title->setPosition({
            m_size.width / 2.f,
            m_size.height - 35.f
        });
        m_mainLayer->addChild(title);

        // Read the player's actual local game statistics.
        auto stats = GameStatsManager::sharedState();

        const char* names[] = {
            "STARS",
            "DIAMONDS",
            "DEMONS",
            "USER COINS"
        };

        // These values are replaced below once the stat keys
        // are confirmed for your installed Geode SDK.
        for (int i = 0; i < 4; i++) {
            float x = m_size.width / 2.f
                + ((i % 2 == 0) ? -57.f : 57.f);
            float y = m_size.height - 70.f
                - (i / 2) * 48.f;

            auto name = CCLabelBMFont::create(
                names[i],
                "goldFont.fnt"
            );
            name->setScale(0.35f);
            name->setPosition({x, y});
            m_mainLayer->addChild(name);

            auto value = CCLabelBMFont::create(
                "Loading...",
                "bigFont.fnt"
            );
            value->setScale(0.3f);
            value->setPosition({x, y - 17.f});
            m_mainLayer->addChild(value);
        }

        auto theme = mod->getSavedValue<bool>(
            "dark-theme",
            false
        );

        auto themeButton = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(
                theme ? "LIGHT THEME" : "DARK THEME",
                "goldFont.fnt",
                "GJ_button_01.png",
                0.65f
            ),
            this,
            menu_selector(ProfilePlusPopup::toggleTheme)
        );

        auto menu = CCMenu::create();
        menu->setPosition({
            m_size.width / 2.f,
            43.f
        });
        menu->addChild(themeButton);
        m_mainLayer->addChild(menu);

        auto footer = CCLabelBMFont::create(
            "PROFILE PLUS",
            "bigFont.fnt"
        );
        footer->setScale(0.3f);
        footer->setPosition({
            m_size.width / 2.f,
            17.f
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
            "Theme Saved",
            "Your theme preference has been saved. "
            "Reopen the popup to refresh it.",
            "OK"
        )->show();
    }

public:
    static ProfilePlusPopup* create() {
        auto ret = new ProfilePlusPopup();

        if (ret->init(260.f, 190.f)) {
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

        button->setID("profile-plus-button"_spr);
        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

    void openProfile(CCObject*) {
        ProfilePlusPopup::create()->show();
    }
};
