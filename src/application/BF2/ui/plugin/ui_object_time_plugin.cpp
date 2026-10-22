#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "classes/ui/UIObjectTimePlugin.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/mtl/FixStr.h"
#include "fw/LangUtil.h"
#include "ui/UIObjectPluginUtil.h"
#include "ui/UIUtil.h"

namespace ui {

UIObjectTimePlugin::~UIObjectTimePlugin() {
    ;  // the original stores the table before the base's destructor; clang drops the store for an empty body
}

UIObjectTimePlugin* UIObjectTimePlugin::create(unsigned int handle, unsigned char type) {
#line 46
    UIObjectTimePlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectTimePlugin();
    plugin->addRef();
    UIObjectAcc acc(handle);
    if (type == TYPE_NONE) {
        return nullptr;
    }
    const char* text;
    if (acc.m_object != nullptr && acc.isText() && UIObjectPluginUtil::attachPlugin(handle, plugin) &&
        (text = acc.getTextPtr()) != nullptr && checkTimeTextFormat(text, type)) {
        plugin->m_format = acc.getTextPtr();
        plugin->m_type = type;
    } else if (plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

void UIObjectTimePlugin::setYear(unsigned short year) {
    if (year > 0x1FFF) {
        year = 0x1FFF;
    }
    if (m_time.year != year) {
        m_time.year = year;
        m_updateFlags |= 1;
    }
}

void UIObjectTimePlugin::setMonth(unsigned char month) {
    if (month > 12) {
        month = 12;
    }
    if (m_time.month != month) {
        m_time.month = month;
        m_updateFlags |= 1;
    }
}

void UIObjectTimePlugin::setDay(unsigned char day) {
    if (day > 31) {
        day = 31;
    }
    if (m_time.day != day) {
        m_time.day = day;
        m_updateFlags |= 1;
    }
}

void UIObjectTimePlugin::setHour(unsigned char hour) {
    if (hour > 99) {
        hour = 99;
    }
    if (m_time.hour != hour) {
        m_time.hour = hour;
        m_updateFlags |= 1;
    }
}

void UIObjectTimePlugin::setMin(unsigned char min) {
    if (m_type == TYPE_MIN_SEC || m_type == TYPE_SEC_MSEC) {
        if (min > 99) {
            min = 99;
        }
    } else if (min > 59) {
        min = 59;
    }
    if (m_time.minute != min) {
        m_time.minute = min;
        m_updateFlags |= 1;
    }
}

void UIObjectTimePlugin::setSec(unsigned char sec) {
    if (sec > 59) {
        sec = 59;
    }
    if (m_time.sec != sec) {
        m_time.sec = sec;
        m_updateFlags |= 1;
    }
}

void UIObjectTimePlugin::setMSec(unsigned char msec) {
    if (msec > 99) {
        msec = 99;
    }
    if (m_time.msec != msec) {
        m_time.msec = msec;
        m_updateFlags |= 1;
    }
}

void UIObjectTimePlugin::setElapseHour(unsigned short hour) {
    if (hour > 999) {
        hour = 999;
    }
    if (m_elapseHour != hour) {
        m_elapseHour = hour;
        m_updateFlags |= 1;
    }
}

void UIObjectTimePlugin::reload(UIObjectAcc& acc) {
    m_format = acc.getTextPtr();
    if (!checkTimeTextFormat(m_format, m_type)) {
        m_format = nullptr;
    }
    m_updateFlags |= 1;
}

void UIObjectTimePlugin::execute(UIObjectAcc& acc) {
    mm::mtl::FixStr<128> text;
    if (m_format == nullptr) {
        return;
    }
    switch (m_type) {
    case TYPE_DATE:
        if (fw::LangUtil::getLangType() == 0 || fw::LangUtil::getLangType() == 6 ||
            fw::LangUtil::getLangType() == 11 || fw::LangUtil::getLangType() == 7) {
            text.format(m_format, m_time.year, m_time.month, m_time.day);
        } else {
            text.format(m_format, m_time.day, m_time.month, m_time.year);
        }
        break;
    case TYPE_MONTH_DAY:
        if (fw::LangUtil::getLangType() == 0 || fw::LangUtil::getLangType() == 6 ||
            fw::LangUtil::getLangType() == 11 || fw::LangUtil::getLangType() == 7) {
            text.format(m_format, m_time.month, m_time.day);
        } else {
            text.format(m_format, m_time.day, m_time.month);
        }
        break;
    case TYPE_HOUR_MIN_SEC:
        text.format(m_format, m_time.hour, m_time.minute, m_time.sec);
        break;
    case TYPE_MIN_SEC:
        text.format(m_format, m_time.minute, m_time.sec);
        break;
    case TYPE_SEC_MSEC:
        text.format(m_format, m_time.sec, m_time.msec);
        break;
    case TYPE_HOUR_MIN:
        text.format(m_format, m_time.hour, m_time.minute);
        break;
    case TYPE_ELAPSE_MIN_SEC:
        text.format(m_format, m_elapseHour, m_time.minute, m_time.sec);
        break;
    }
    if (text.m_str[0] != '\0') {
        acc.applyText(text.m_str);
    }
    UIObjectDispPlugin::execute(acc);
}

mm::mtl::RTTI UIObjectTimePlugin::m_rtti("UIObjectTimePlugin", &UIObjectDispPlugin::m_rtti, nullptr);

}  // namespace ui
