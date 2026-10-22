#include <string.h>
#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "classes/ui/UIObjectNumberPlugin.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UICtrlManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/mtl/FixStr.h"
#include "fw/LangUtil.h"
#include "ui/UIObjectPluginUtil.h"
#include "ui/UIUtil.h"

namespace ui {

UIObjectNumberPlugin::~UIObjectNumberPlugin() {
    if (m_numberUpdater.m_ctrl != nullptr) {
        UICtrlManager::get()->delUpdater(m_numberUpdater);
    }
    m_numberUpdater.m_ctrl = nullptr;
}

UIObjectNumberPlugin* UIObjectNumberPlugin::create(unsigned int handle) {
#line 56
    UIObjectNumberPlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectNumberPlugin();
    plugin->addRef();
    UIObjectAcc acc(handle);
    if (acc.m_object != nullptr) {
        unsigned int max;
        if (acc.isText()) {
            const char* text = acc.getTextPtr();
            plugin->m_format = text;
            if (text == nullptr || !UIUtil::checkNumberTextFormat(text, 1)) {
                plugin->m_format = "e%d";
            }
            plugin->m_type = strstr(text, "%s") != nullptr ? TYPE_TEXT_MONEY : TYPE_TEXT;
            max = 9999;
        } else if (acc.isImage()) {
            max = acc.getImageMax();
            plugin->m_type = TYPE_IMAGE;
        } else if (acc.isLayout()) {
            plugin->setDispControl(false);
            max = 9999;
        } else {
            goto fail;
        }
        if (UIObjectPluginUtil::attachPlugin(handle, plugin)) {
            plugin->m_max = max;
            plugin->m_number = 0;
            plugin->m_min = 0;
            plugin->init(handle);
            return plugin;
        }
    }
fail:
    if (plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

UIObjectNumberPlugin* UIObjectNumberPlugin::getPlugin(unsigned int handle) {
    UIObjectPlugin* plugin = nullptr;
    UIObject* object = UIUtil::getObject(handle);
    if (object != nullptr) {
        plugin = object->m_plugins;
        if (plugin != nullptr && !plugin->getRTTI()->isKindOf(&m_rtti)) {
            plugin = nullptr;
        }
    }
    return static_cast<UIObjectNumberPlugin*>(plugin);
}

void UIObjectNumberPlugin::setMin(int min) {
    if (min >= m_max) {
        m_max = min + 1;
    }
    if (m_min != min) {
        m_min = min;
        m_updateFlags |= 1;
    }
}

void UIObjectNumberPlugin::setMax(int max) {
    if (max <= m_min) {
        max = m_min + 1;
    }
    if (max != m_max) {
        m_max = max;
        m_updateFlags |= 1;
    }
}

void UIObjectNumberPlugin::setNumber(int number) {
    int value = number < m_min ? m_min : number;
    value = value > m_max ? m_max : value;
    unsigned int current = m_numberCtrl.isBusy() ? (int)m_numberCtrl.m_range[0].m_end : m_number;
    if (current != value) {
        unsigned int flags = m_updateFlags;
        m_updateFlags |= 1;
        if (!(flags & 2) && m_interpolate && m_interpolateTime > 0.0f) {
            float from = m_numberCtrl.isBusy() ? m_numberCtrl.m_value[0] : current;
            UICtrlSimple<1>::Range range = {from, (float)value};
            m_numberCtrl.start(&range, m_interpolateTime, CURVE_LINEAR);
            m_numberUpdater.m_ctrl = &m_numberCtrl;
            UICtrlManager::get()->addUpdater(m_numberUpdater);
            return;
        }
        m_number = value;
    }
}

void UIObjectNumberPlugin::setInterpolate(float time) {
    m_interpolate = true;
    m_interpolateTime = time;
}

void UIObjectNumberPlugin::reload(UIObjectAcc& acc) {
    if (m_type == TYPE_TEXT || m_type == TYPE_TEXT_MONEY) {
        const char* text = acc.getTextPtr();
        m_format = text;
        if (text == nullptr || !UIUtil::checkNumberTextFormat(text, 1)) {
            m_format = "e%d";
        }
        m_type = strstr(text, "%s") != nullptr ? TYPE_TEXT_MONEY : TYPE_TEXT;
        m_updateFlags |= 1;
    }
}

void UIObjectNumberPlugin::refreshMoneySeparetor() {
    s_MoneySeparetor = UIUtil::getMoneySeparetor(static_cast<fw::LangType>(fw::LangUtil::getLangType()));
}

void UIObjectNumberPlugin::execute(UIObjectAcc& acc) {
    static char s_digits[32];
    static mm::mtl::FixStr<128> s_text;
    if (m_numberUpdater.m_ctrl != nullptr) {
        m_number = m_numberCtrl.m_value[0];
        if (!m_numberCtrl.isBusy()) {
            if (m_numberUpdater.m_ctrl != nullptr) {
                UICtrlManager::get()->delUpdater(m_numberUpdater);
            }
            m_numberUpdater.m_ctrl = nullptr;
        }
    }
    int number = m_number;
    if (m_reverse) {
        number = m_max - number;
    }
    if (acc.getExtType() != 0) {
        if (m_type != TYPE_EXT) {
            m_type = TYPE_EXT;
        }
        acc.setExtParam((float)number / (float)(m_max - m_min));
    } else {
        switch (m_type) {
        case TYPE_TEXT:
            s_text.format(m_format, number);
            acc.applyText(s_text.m_str);
            break;
        case TYPE_TEXT_MONEY:
            if (s_MoneySeparetor == 0) {
                s_text.format(m_format, number);
            } else {
                int digits;
                int unit;
                if (number < 10) {
                    unit = 1;
                    digits = 1;
                } else {
                    digits = 1;
                    int next = 10;
                    do {
                        unit = next;
                        digits++;
                        next = unit * 10;
                    } while (number >= next);
                }
                bool separate = true;
                if ((fw::LangUtil::getLangType() == 3 || fw::LangUtil::getLangType() == 4 ||
                    fw::LangUtil::getLangType() == 5 || fw::LangUtil::getLangType() == 11 || fw::LangUtil::getLangType() == 6) && digits < 5) {
                    separate = false;
                }
                int length = 0;
                for (int i = 0; i < digits; i++) {
                    int digit = number / unit;
                    if (separate && i != 0 && (digits - i) % 3 == 0) {
                        s_digits[length] = s_MoneySeparetor;
                        length++;
                    }
                    s_digits[length] = digit + '0';
                    length++;
                    number -= digit * unit;
                    unit /= 10;
                }
                s_digits[length] = '\0';
                s_text.format(m_format, s_digits);
            }
            acc.applyText(s_text.m_str);
            break;
        case TYPE_IMAGE:
            if (acc.hasAnimation()) {
                if (acc.isPlayingAnimation() && acc.isPlaybackControl()) {
                    float rate = (float)number / (float)(m_max - m_min);
                    acc.setAnimationPlaybackTime(acc.getAnimationPlaybackLength() * rate);
                } else {
                    acc.startAnimationFromIndex(number, false);
                }
            } else {
                acc.setImageIndex(number);
            }
            break;
        case TYPE_EXT:
            acc.setExtParam((float)number / (float)(m_max - m_min));
            break;
        }
    }
    UIObjectDispPlugin::execute(acc);
}

bool UIObjectNumberPlugin::isNeedUpdate(UIObjectAcc& acc) {
    return (m_updateFlags & 1) || m_numberUpdater.m_ctrl != nullptr || acc.isDisp() != m_disp ||
           m_fadeUpdater.m_ctrl != nullptr || m_followObjHandle != 0;
}

mm::mtl::RTTI UIObjectNumberPlugin::m_rtti("UIObjectNumberPlugin", &UIObjectDispPlugin::m_rtti, nullptr);
char UIObjectNumberPlugin::s_MoneySeparetor;

}  // namespace ui
