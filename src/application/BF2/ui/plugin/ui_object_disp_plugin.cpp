#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "classes/ui/UIObjectAlphaParam.h"
#include "classes/ui/UICtrlManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ui/UIObjectPluginUtil.h"
#include "ui/UIUtil.h"

namespace ui {

UIObjectDispPlugin::UIObjectDispPlugin()
    : m_dispControl(true), m_disp(true), m_modeFlags(0), m_followObjHandle(0), m_alphaParam(nullptr),
      m_fadeTime(0.0f) {}

UIObjectDispPlugin::~UIObjectDispPlugin() {
    if (m_fadeUpdater.m_ctrl != nullptr) {
        UICtrlManager::get()->delUpdater(m_fadeUpdater);
    }
    m_fadeUpdater.m_ctrl = nullptr;
    if (m_alphaParam != nullptr) {
        delete m_alphaParam;
        m_alphaParam = nullptr;
    }
}

void UIObjectDispPlugin::setDisp(bool disp) {
    if (m_dispControl && m_followObjHandle == 0 && m_disp != disp) {
        m_disp = disp;
        m_updateFlags |= 1;
        if ((m_modeFlags & MODE_FADE) && m_alphaParam != nullptr) {
            float alpha = m_fade.isBusy() ? m_fade.m_value[0] : m_alphaParam->m_alpha;
            bool shown = disp;
            shown ^= (m_modeFlags & MODE_REVERSE) >> 1;
            UICtrlSimple<1>::Range range = {alpha, shown ? 1.0f : 0.0f};
            m_fade.start(&range, m_fadeTime, CURVE_LINEAR);
            m_fadeUpdater.m_ctrl = &m_fade;
            UICtrlManager::get()->addUpdater(m_fadeUpdater);
        }
    }
}

void UIObjectDispPlugin::setAlphaMode(bool on) {
    if (on != (m_modeFlags & MODE_ALPHA)) {
        if (on) {
            m_modeFlags |= MODE_ALPHA;
        } else {
            m_modeFlags &= ~MODE_ALPHA;
        }
        m_updateFlags |= 1;
    }
}

void UIObjectDispPlugin::setReverseMode(bool on) {
    if (on != ((m_modeFlags & MODE_REVERSE) != 0)) {
        if (on) {
            m_modeFlags |= MODE_REVERSE;
        } else {
            m_modeFlags &= ~MODE_REVERSE;
        }
        m_updateFlags |= 1;
    }
}

void UIObjectDispPlugin::setSuspendMode(bool on) {
    if (on != ((m_modeFlags & MODE_SUSPEND) != 0)) {
        if (on) {
            m_modeFlags |= MODE_SUSPEND;
        } else {
            m_modeFlags &= ~MODE_SUSPEND;
        }
        m_updateFlags |= 1;
    }
}

void UIObjectDispPlugin::setDispControl(bool on) {
    m_dispControl = on;
}

void UIObjectDispPlugin::setFollowObjHandle(unsigned int handle) {
    m_followObjHandle = handle;
}

void UIObjectDispPlugin::setFadeMode(float time) {
    m_fadeTime = time;
    m_modeFlags |= MODE_ALPHA | MODE_FADE;
}

UIObjectDispPlugin* UIObjectDispPlugin::create(unsigned int handle) {
#line 168
    UIObjectDispPlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectDispPlugin();
    plugin->addRef();
    if (UIObjectPluginUtil::attachPlugin(handle, plugin)) {
        plugin->init(handle);
    } else if (plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

void UIObjectDispPlugin::init(unsigned int handle) {
    UIObjectAcc acc(handle);
    m_disp = acc.isDisp();
}

void UIObjectDispPlugin::execute(UIObjectAcc& acc) {
    if (m_dispControl) {
        bool disp = m_disp;
        if (m_followObjHandle != 0) {
            UIObjectAcc follow(m_followObjHandle);
            disp = follow.isDisp();
        }
        disp ^= (m_modeFlags & MODE_REVERSE) >> 1;
        if (m_modeFlags & MODE_ALPHA) {
            acc.setDisp(true);
            if (m_modeFlags & MODE_FADE) {
                if (m_alphaParam == nullptr) {
#line 221
                    m_alphaParam = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectAlphaParam(acc.m_handle);
                    m_alphaParam->m_alpha = disp ? 1.0f : 0.0f;
                } else if (m_fadeUpdater.m_ctrl != nullptr) {
                    float alpha = m_fade.m_value[0];
                    m_alphaParam->m_alpha = alpha;
                    if (!m_fade.isBusy()) {
                        if (m_fadeUpdater.m_ctrl != nullptr) {
                            UICtrlManager::get()->delUpdater(m_fadeUpdater);
                        }
                        m_fadeUpdater.m_ctrl = nullptr;
                    }
                    if (m_modeFlags & MODE_SUSPEND) {
                        acc.setSuspend(alpha == 0.0f);
                    }
                } else if (m_modeFlags & MODE_SUSPEND) {
                    acc.setSuspend(m_alphaParam->m_alpha == 0.0f);
                }
            } else {
                acc.setAlpha(disp ? 1.0f : 0.0f);
                if (m_modeFlags & MODE_SUSPEND) {
                    acc.setSuspend(!disp);
                }
            }
        } else {
            if (m_modeFlags & MODE_SUSPEND) {
                acc.setSuspend(!disp);
            }
            acc.setDisp(disp);
        }
    }
    UIObjectPlugin::execute(acc);
}

bool UIObjectDispPlugin::isNeedUpdate(UIObjectAcc& acc) {
    return (m_updateFlags & 1) || acc.isDisp() != m_disp || m_fadeUpdater.m_ctrl != nullptr || m_followObjHandle != 0;
}

void UIObjectAlphaParam::apply(UIObjectParam::AdditionalParam& param) const {
    param.m_alpha *= m_alpha;
}

mm::mtl::RTTI UIObjectDispPlugin::m_rtti("UIObjectDispPlugin", &UIObjectPlugin::m_rtti, nullptr);

}  // namespace ui
