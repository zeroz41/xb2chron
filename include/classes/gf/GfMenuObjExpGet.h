#ifndef CLASSES_GF_GFMENUOBJEXPGET_H
#define CLASSES_GF_GFMENUOBJEXPGET_H

#include "classes/gf/GfMenuObject.h"
#include "mm/mtl/FixedQueue.h"

namespace ui { class UIObjectAcc; }

namespace gf {
class GF_OBJ_HANDLE;

// table 0x7100B621C8: the experience, SP and WP got (and level up) screens over a driver, on copies of LAY_main_root;
// open objects of types 0, 2 and 3 are GfMenuManyObjects' kind 4, of type 1 its kind 5
class GfMenuObjExpGet : public ::gf::GfMenuObject {
public:
    class ExpGetInfo;
    class ListListener;
    // what open shows (1.0.0's open(OpenParam const&) names the type; the field names are not the original's)
    struct OpenParam {
        // user-provided: the copies stop at the data's end (0x1C), not the struct's. It zeroes every field:
        // GfGameScene::gevDriverLevel stores zeros under the fields it then sets, and ExpGetInfo's construction
        // (default then assigned) splits the copy at m_object in myOpen
        OpenParam() : m_type(0), m_value(0), m_bonus(false), m_object(nullptr), m_extra(0) {}
        int m_type;  // 0 experience, 1 SP, 2 WP, 3 a level up
        int m_value;  // the amount got: myOpen shows nothing for 0
        bool m_bonus;  // shows the type's IMG_*_bonus
        GF_OBJ_HANDLE* m_object;  // the driver the screen follows
        // passed on in the open event's sixth short; nothing here reads it (the name is not the original's)
        int m_extra;
    };
    GfMenuObjExpGet(unsigned int handle);
    virtual ~GfMenuObjExpGet();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // a screen of that param on a LAY_main_root copy, its object queued (1.0.0 symbol; the same code at the same size
    // in 3.0.1; 2.0.0's symbols name it myOpen): the copy's handle, or 0 when none opens (a level up only tells
    // GfMenuObjPartyStatus2)
    static unsigned int myOpen(const OpenParam& param);
    // 2.0.0's symbols name it. What it does: pushes a copy of the param on the file-static queue of 64 that update
    // hands to myOpen, dropping the oldest when it is full; answers 0 (no screen yet, where myOpen answers the copy's
    // handle).
    static unsigned int open(const OpenParam& param);
    // the screen off kind 4's queue and terminated (1.0.0 symbol; inline here, the original's calls are inlined)
    static void removeObject(ui::UIObjectAcc screen);
    // the same off kind 5's queue (1.0.0 symbol)
    static void removeObject2(ui::UIObjectAcc screen);
    // sends root the open event (0x21) of that object (1.0.0 symbol)
    static void sendOpen(unsigned int root, const ExpGetInfo& info);
    // a screen's end: off its queue, then the next of kind 5 opened or kind 5 closed (1.0.0 symbol)
    static void removeExpGet(ui::UIObjectAcc root, ui::UIObjectAcc screen, unsigned int type);
    static void close2(unsigned int handle);  // fades that copy out (event 0x22, kind 5)
    // shows the type's layer with its value and bonus image; returns the layer's name (the parameter names are not
    // the original's; the fourth is unused and myOpen passes nothing in it)
    static const char* setupScreen(unsigned int handle, int type, int value, int unused, int bonus);
    static void setupPlugin(unsigned int handle, unsigned int type);  // fits the type's background (types 0-2)
    static void close(unsigned int handle);  // fades that copy out (event 0x22, kind 4)
    static void closeAll();  // GfMenuManager::gevSalvageStateChange(6) calls it (1.0.0 symbol)
    // the opens open queues for update to hand to myOpen, each update (a global: its code loads it through the
    // GOT; 2.0.0's symbols name it)
    static mm::mtl::FixedQueue<OpenParam, 64> s_queue;
};
}  // namespace gf

#endif
