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
    // execute's switches (GfMenuObjUtil::createFitPlugin sets them from its FitOption)
    struct Flags {
        unsigned int addHalfSize : 1;  // the margins grow by half the object's own size
        unsigned int keepScaleX : 1;   // execute leaves the object's x scale alone
        unsigned int keepScaleY : 1;   // and its y scale
        unsigned int pad : 29;
    };
    unsigned short m_marginWidth;   // create's: the target's rectangle grows by this on each side
    unsigned short m_marginHeight;
    short m_offsetWidth;            // added to the fitted size (the center moves by half of it)
    short m_offsetHeight;
    unsigned short m_minWidth;      // the fitted rectangle grows about its center to at least this
    unsigned short m_minHeight;
    Flags m_flags;
    unsigned int m_target;          // create's: the handle of the object it fits over
};
}  // namespace ui

#endif
