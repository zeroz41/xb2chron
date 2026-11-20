#ifndef CLASSES_UI_UIOBJECTFITPLUGIN_H
#define CLASSES_UI_UIOBJECTFITPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75120; fits its object over another (the target): execute sizes and centers it on the target's
// rectangle
class UIObjectFitPlugin : public ::ui::UIObjectPlugin {
public:
    UIObjectFitPlugin()
        : m_marginWidth(0), m_marginHeight(0), m_offsetWidth(0), m_offsetHeight(0), m_minWidth(0), m_minHeight(0),
          m_flags() {}
    virtual ~UIObjectFitPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    static UIObjectFitPlugin* create(unsigned int handle, unsigned int target, unsigned short marginWidth,
                                     unsigned short marginHeight);
    static mm::mtl::RTTI m_rtti;
    // execute's switches, the bits of m_flags (GfMenuObjUtil::createFitPlugin sets them from its FitOption; the
    // names are not the original's)
    enum Flag {
        FLAG_ADD_HALF_SIZE = 1 << 0,  // the margins grow by half the object's own size
        FLAG_KEEP_SCALE_X = 1 << 1,   // execute leaves the object's x scale alone
        FLAG_KEEP_SCALE_Y = 1 << 2,   // and its y scale
    };
    // sets or clears flags: createFitPlugin rewrites the whole word through a select (and of the mask's complement,
    // or of the mask) for each option; the name is not the original's
    void setFlag(unsigned int flag, bool on) { m_flags = !on ? (m_flags & ~flag) : (m_flags | flag); }
    bool isFlag(unsigned int flag) const { return (m_flags & flag) != 0; }  // the name is not the original's
    unsigned short m_marginWidth;   // create's: the target's rectangle grows by this on each side
    unsigned short m_marginHeight;
    short m_offsetWidth;            // added to the fitted size (the center moves by half of it)
    short m_offsetHeight;
    unsigned short m_minWidth;      // the fitted rectangle grows about its center to at least this
    unsigned short m_minHeight;
    unsigned int m_flags;  // Flag bits
    unsigned int m_target;          // create's: the handle of the object it fits over
};
}  // namespace ui

#endif
