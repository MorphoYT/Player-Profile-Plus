#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class ProfilePlusPopup : public geode::Popup<> {
protected:
    bool setup() override {
        this->setTitle("PLAYER PROFILE PLUS");

        auto title = CCLabelBMFont::create(
            "PLAYER STATISTICS",
            "goldFont.fnt"
        );
        title->setScale(0.45f);
        title->setPosition({
            m_size.width / 2.f,
            m_size.height - 42.f
        });
        m_mainLayer->addChild(title);

        const char* names[] = {
            "STARS",
            "DIAMONDS",
            "DEMONS",
            "USER COINS"
        };

        for (int i = 0; i < 4; i++) {
            float x = m_size.width / 2.f
                + ((i % 2 == 0) ? -57.f : 57.f);
            float y = m_size.height - 79.f
                - (i / 2) * 48.f;

            auto name = CCLabelBMFont::create(
                names[i],
                "goldFont.fnt"
            );
            name->setScale(0.35f);
            name->setPosition({x, y});
            m_mainLayer->addChild(name);

            auto value = CCLabelBMFont::create(
                "COMING SOON",
                "bigFont.fnt"
            );
            value->setScale(0.27f);
            value->setPosition({x, y - 17.f});
            m_mainLayer->addChild(value);
        }

        auto footer = CCLabelBMFont::create(
            "MORE FEATURES SOON!",
            "bigFont.fnt"
        );
        footer->setScale(0.32f);
        footer->setPosition({
            m_size.width / 2.f,
            24.f
        });
        m_mainLayer->addChild(footer);

        return true;
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
