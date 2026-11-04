#include "ui/EventData.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuObjFade.h"
#include "classes/gf/GfMenuObjFade/FadeListener.h"
#include "classes/gf/GfMenuObjFade/LoadingListener.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObjLoadingIra.h"
#include "mm/Col3.h"
#include "mm/Col4.h"
#include "mm/mtl/FixStr.h"
#include "mm/Pnt.h"
#include "mm/Vec2.h"
#include "ui/UIUtil.h"

namespace gf {

GfMenuObjFade::GfMenuObjFade(unsigned int handle) : GfMenuObject(handle), pad_24(), m_loadingCount(0) {}

GfMenuObjFade::~GfMenuObjFade() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

inline unsigned int GfMenuObjFade::getFadeImage(unsigned int handle, unsigned char channel) {
    if (channel >= 3) {
        return 0;
    }
    mm::mtl::FixStr<32> name;
    name.format("IMG_fade%02d", channel);
    return ui::UIObjectAcc(handle).searchChild(name.m_str);
}

void GfMenuObjFade::initialize() {
    for (int channel = 0; channel < 3; channel++) {
#line 68
        FadeListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) FadeListener(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(getFadeImage(m_handle, channel), listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc loading(m_handle, "LAY_loading");
#line 74
        LoadingListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) LoadingListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(loading.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc saving(m_handle, "LAY_saving");
#line 79
        LoadingListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) LoadingListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(saving.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::attachExternalCall(0x3B, m_handle);
    GfMenuObject::initialize();
}

void GfMenuObjFade::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjFade::update() {
    GfMenuObject::update();
}

// a fade's start (0xA) or end (0xB) on a channel, as a game event from the channel's image (the name is not the
// original's)
inline void GfMenuObjFade::FadeListener::pushFadeEvent(unsigned int handle, unsigned short type, unsigned char channel) {
    ui::UIEventManager::EventInfo info;
    info.m_handle = handle;
    info.m_data.m_type = type;
    info.m_data.m_param0 = channel;
    ui::UIEventManager::get()->pushGameEvent(info);
}

void GfMenuObjFade::FadeListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        short width, height;
        acc.getSize(false, width, height);
        mm::Vec2 scale;
        scale.x = ui::UIUtil::getScreenWidth() / (float)width;
        scale.y = ui::UIUtil::getScreenHeight() / (float)height;
        acc.setScale(scale);
        mm::Pnt<short> center(ui::UIUtil::getScreenWidth() / 2, ui::UIUtil::getScreenHeight() / 2);
        acc.setPosCenter(center);
        acc.setAlpha(0.0f);
        m_ctrl = -1;
        break;
    }
    case 3: {
        pushFadeEvent(acc.m_handle, 0xB, m_channel);
        m_ctrl = -1;
        break;
    }
    case 0x100: {
        float time = event.m_paramShort[0] / 30.0f;
        float alpha = event.m_paramShort[4];
        mm::Col3 color;
        color.r = event.m_paramShort[1] / 255.0f;
        color.g = event.m_paramShort[2] / 255.0f;
        color.b = event.m_paramShort[3] / 255.0f;
        m_channel = event.m_paramShort[5];
        acc.setAddColor(color);
        if (m_ctrl != -1) {
            GfMenuObjUtil::stopCtrl(m_ctrl);
            m_ctrl = -1;
        }
        alpha /= 255.0f;
        if (time == 0.0f) {
            acc.setAlpha(alpha);
            pushFadeEvent(acc.m_handle, 0xB, m_channel);
        } else {
            GfMenuObjUtil::CtrlParam param;
            bool changed;
            {
                float current;
                acc.getAlpha(current);
                changed = alpha != current;
            }
            if (changed) {
                param.m_methods = 4;
                param.m_alpha = alpha;
                param.m_time = time;
                m_ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
                pushFadeEvent(acc.m_handle, 0xA, m_channel);
            } else {
                param.m_time = time;
                pushFadeEvent(acc.m_handle, 0xB, m_channel);
            }
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjFade::LoadingListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 0x21:
        if (m_owner->m_loadingCount++ <= 0) {
            float time = event.m_param0 * (1.0f / 30.0f);
            if (time == 0.0f) {
                acc.setDisp(true);
            } else {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 1;
                param.m_time = time;
                GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            }
        }
        break;
    case 0x22:
        if (--m_owner->m_loadingCount <= 0) {
            m_owner->m_loadingCount = 0;
            float time = event.m_param0 * (1.0f / 30.0f);
            if (time == 0.0f) {
                acc.setDisp(false);
            } else {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 2;
                param.m_time = time;
                GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            }
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjFade::start(const StartParam& param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3B));
    if (acc.m_object != nullptr && !acc.isTerm() && param.channel < 3) {
        ui::UIObjectAcc fade(getFadeImage(acc.m_handle, param.channel));
        if (fade.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x100;
            event.m_paramShort[0] = param.time;
            event.m_paramShort[1] = param.color.r * 255.0f;
            event.m_paramShort[2] = param.color.g * 255.0f;
            event.m_paramShort[3] = param.color.b * 255.0f;
            event.m_paramShort[4] = param.color.a * 255.0f;
            event.m_paramShort[5] = param.channel;
            ui::UIManager::get()->requestObjectEvent(fade.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjFade::dispLoading(bool disp, unsigned short frames) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3B));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = disp ? 0x21 : 0x22;
        event.m_param0 = frames;
        GfMenuObject::sendEvent(acc.searchChild("LAY_loading"), event, 0.0f);
        ui::UIObjectAcc image(acc.m_handle, "IMG_loading");
        if (GfMenuObjUtil::isValidExpansion(3) && GfMenuObject::existAttachedObject(0x8F)) {
            image.setAlpha(0.0f);
            GfMenuObjLoadingIra::dispLoading(disp, frames);
        } else {
            image.setAlpha(1.0f);
        }
    }
}

void GfMenuObjFade::dispSaving(bool disp, unsigned short frames) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3B));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = disp ? 0x21 : 0x22;
        event.m_param0 = frames;
        GfMenuObject::sendEvent(acc.searchChild("LAY_saving"), event, 0.0f);
        ui::UIObjectAcc image(acc.m_handle, "IMG_saving");
        if (GfMenuObjUtil::isValidExpansion(3) && GfMenuObject::existAttachedObject(0x8F)) {
            image.setAlpha(0.0f);
            GfMenuObjLoadingIra::dispSaving(disp, frames);
        } else {
            image.setAlpha(1.0f);
        }
    }
}

void GfMenuObjFade::getFadeColor(unsigned char channel, mm::Col4& color) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3B));
    if (acc.m_object != nullptr && !acc.isTerm() && channel < 3) {
        ui::UIObjectAcc fade(getFadeImage(acc.m_handle, channel));
        if (fade.m_object != nullptr) {
            mm::Col3 add;
            fade.getAddColor(add);
            color.r = add.r;
            color.g = add.g;
            color.b = add.b;
            fade.getAlpha(color.a);
        }
    }
}

}  // namespace gf
