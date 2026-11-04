#ifndef CLASSES_GF_TUNK_B62D58_H
#define CLASSES_GF_TUNK_B62D58_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62D58: the menu object of gf_menu_obj_loading_ira.cpp (new in 3.0.1; nothing names the class yet).
// GfMenuManager::reciveEvent makes it; it shows LAY_loading and LAY_saving for GfMenuObjFade's dispLoading and
// dispSaving
class GfMenuObjLoadingIra : public ::gf::GfMenuObject {
public:
    GfMenuObjLoadingIra(unsigned int handle);
    virtual ~GfMenuObjLoadingIra();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 2.0.0's symbols name them. What they do: event 0x21 (open true) or 0x22 to its LAY_loading (dispLoading) or
    // LAY_saving (dispSaving) child, m_param0 the fade's frames; GfMenuObjFade::dispLoading and dispSaving call them
    // with their own arguments.
    static void dispLoading(bool open, unsigned short frames);
    static void dispSaving(bool open, unsigned short frames);
    unsigned char pad_24[4];
    // the open events (0x21) not yet closed (0x22): only the first fades in, only the last fades out (the name is not
    // the original's)
    signed char m_dispCount;
};

// table 0x7100B62DA0: GfMenuObjLoadingIra's listener on LAY_loading and LAY_saving (nothing names the class yet)
class TUnk_B62DA0 : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    TUnk_B62DA0(GfMenuObjLoadingIra* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B62DA0() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjLoadingIra* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
