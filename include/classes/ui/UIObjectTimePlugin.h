#ifndef CLASSES_UI_UIOBJECTTIMEPLUGIN_H
#define CLASSES_UI_UIOBJECTTIMEPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "ui/UIUtil.h"
#include "ui/uiDateTime.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75320
class UIObjectTimePlugin : public ::ui::UIObjectDispPlugin {
public:
    // which fields execute formats into the text (m_type); the names are not the original's
    enum {
        TYPE_NONE,
        TYPE_DATE,            // year, month, day (day, month, year in some languages)
        TYPE_MONTH_DAY,       // month, day (day, month in some languages)
        TYPE_HOUR_MIN_SEC,
        TYPE_MIN_SEC,         // setMin takes minutes up to 99
        TYPE_SEC_MSEC,        // setMin takes minutes up to 99
        TYPE_HOUR_MIN,
        TYPE_ELAPSE_MIN_SEC,  // m_elapseHour, minutes, seconds
        TYPE_NUM,
    };
    // inline: 3.0.1 has no out-of-line copy (1.0.0's is 0x71006E8D0C; create holds its stores)
    UIObjectTimePlugin() : m_time(), m_type(TYPE_NONE), m_elapseHour(0) {}  // m_format is left as it is
    virtual ~UIObjectTimePlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void reload(ui::UIObjectAcc&);  // slot 3
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    static UIObjectTimePlugin* create(unsigned int handle, unsigned char type);
    // whether text is a format for type's fields; inline: 3.0.1 has no out-of-line copy (1.0.0's is 0x71006E8F14)
    static bool checkTimeTextFormat(const char* text, unsigned char type) {
        switch (type) {
        case TYPE_DATE:
        case TYPE_HOUR_MIN_SEC:
        case TYPE_SEC_MSEC:
        case TYPE_ELAPSE_MIN_SEC:
            return UIUtil::checkNumberTextFormat(text, 3);
        case TYPE_MONTH_DAY:
        case TYPE_MIN_SEC:
        case TYPE_HOUR_MIN:
            return UIUtil::checkNumberTextFormat(text, 2);
        }
        return false;
    }
    void setYear(unsigned short year);
    void setMonth(unsigned char month);
    void setDay(unsigned char day);
    void setHour(unsigned char hour);
    void setMin(unsigned char min);
    void setSec(unsigned char sec);
    void setMSec(unsigned char msec);
    void setElapseHour(unsigned short hour);
    static mm::mtl::RTTI m_rtti;
    uiDateTime m_time;          // the setters' fields
    const char* m_format;       // the text's format, null when it does not fit m_type
    unsigned char m_type;       // TYPE_*
    unsigned char pad_91[0x1];
    unsigned short m_elapseHour;  // setElapseHour
    unsigned char pad_94[0x4];
};
}  // namespace ui

#endif
