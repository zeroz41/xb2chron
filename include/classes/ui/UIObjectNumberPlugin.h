#ifndef CLASSES_UI_UIOBJECTNUMBERPLUGIN_H
#define CLASSES_UI_UIOBJECTNUMBERPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "classes/ui/UICtrlSimple.h"
#include "classes/ui/UICtrlSimpleUpdater.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75160; its destructor ends in UIObjectDispPlugin's
class UIObjectNumberPlugin : public ::ui::UIObjectDispPlugin {
public:
    // what create found its object to be (m_type); the names are not the original's
    enum {
        TYPE_NONE,
        TYPE_TEXT,        // a text: execute formats the number with the text's own format
        TYPE_TEXT_MONEY,  // a text whose format takes a string (%s): the number's digits with separators
        TYPE_IMAGE,       // an image: the number picks its image (or its animation's frame)
        TYPE_EXT,         // an image of an extended type: execute gives it the number's share of its range
    };
    // inline: 3.0.1 has no out-of-line copy (1.0.0's is 0x71006E6EE0; create holds its stores)
    UIObjectNumberPlugin()
        : m_number(0), m_min(0), m_max(9999), m_type(TYPE_NONE), m_reverse(false), m_interpolate(false),
          m_format(nullptr), m_interpolateTime(0.0f) {}
    virtual ~UIObjectNumberPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void reload(ui::UIObjectAcc&);  // slot 3
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    static UIObjectNumberPlugin* create(unsigned int handle);
    static UIObjectNumberPlugin* getPlugin(unsigned int handle);  // the object's plugin, if it is one of these
    void setMin(int min);
    void setMax(int max);
    void setNumber(int number);
    void setInterpolate(float time);
    static void refreshMoneySeparetor();
    static mm::mtl::RTTI m_rtti;
    static char s_MoneySeparetor;  // the language's thousands separator (refreshMoneySeparetor), 0 for none
    int m_number;  // setNumber
    int m_min;     // setMin
    int m_max;     // setMax
    unsigned char m_type;  // TYPE_*
    bool m_reverse;        // execute shows m_max - m_number (the name is not the original's)
    bool m_interpolate;    // setInterpolate: setNumber moves to the new number over m_interpolateTime
    unsigned char pad_8B[0x5];
    const char* m_format;  // the text's format (TYPE_TEXT, TYPE_TEXT_MONEY)
    UICtrlSimple<1> m_numberCtrl;  // the number while setNumber moves it
    UICtrlSimpleUpdater<UICtrlSimple<1> > m_numberUpdater;  // runs m_numberCtrl while UICtrlManager has it
    float m_interpolateTime;  // setInterpolate
};
}  // namespace ui

#endif
