#ifndef CLASSES_GF_TUNK_B63A48_H
#define CLASSES_GF_TUNK_B63A48_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectListener.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfMenuCallContext; class GfMenuIDList; }
namespace ui { class UISelectObjList; struct EventData; }

namespace gf {

// table 0x7100B63A48 (gf_menu_obj_npc_telop: the file suggests an NPC telop). The symbols leave the class unnamed
// and it has no RTTI. Attached as external call 0x8C; shows up to three faces (LAY_char@NN's IMG_char_face@NN).
class GfMenuObjNpcTelop : public ::gf::GfMenuObject {
public:
    class MainListener;
    class HitonowaListener;
    // what open shows (event::UIManager::openHitonowaUI fills one); the names are not the original's
    struct OpenParam {
        // one face: the id the caller was given, BDAT table 0x1B5 and its "Name" value of that id
        struct Entry {
            int m_id;
            unsigned char* m_bdat;
            unsigned int m_name;
        };
        unsigned int m_flag;  // the caller's param < 1
        mm::mtl::FixedVector<Entry, 3> m_entries;
    };
    GfMenuObjNpcTelop(unsigned int handle);
    virtual ~GfMenuObjNpcTelop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 2.0.0's symbols name it. What it does: with GfMenuObjUtil::isValidExpansion(3) and a context checkCCStart
    // accepts, copies param into g_npcTelopParam, sends an open event to the object's sibling LAY_dummy and starts the
    // context on it. Callers: event::UIManager::openHitonowaUI, GfPlayComOpenNpcEntry::start.
    static void open(GfMenuCallContext* context, const OpenParam& param);
    // 2.0.0's symbols name it. What it does: returns g_npcTelopParam. Caller: gf_menu_obj_hitonowa's GfMenuObjHitonowa::initialize.
    static OpenParam* getOpenParam();
    // 2.0.0's symbols name it. What it does: returns g_npcTelopOpen (HitonowaListener sets it on the open event 0x21,
    // clears it on close 0x22).
    static bool isOpen();
    // the sequences' jobs (placeholder names: new in 3.0.1, nothing in 1.0.0 names them)
    bool seqWaitStream();  // waits while a face (IMG_char_face@NN of LAY_main) is streaming, then counts m_waitCount
    bool seqWaitCloseFullscreen();  // waits while a full-screen menu is open
    bool seqEndHitonowa();  // sends LAY_dummy a close event
    bool seqStart();  // sends LAY_main event 0x100 per entry of m_idList, 0.1 s apart
    unsigned char pad_24[4];
    ui::UISelectObjList* m_selectList;  // 0x28 the constructor creates them, the destructor releases them
    GfMenuIDList* m_idList;             // 0x30
    GfMenuSequence<GfMenuObjNpcTelop, 4> m_seq0;  // 0x38 (the name is not the original's)
    unsigned int m_waitCount;  // 0x198 seqWaitStream's frames (the name is not the original's)
    unsigned char pad_19C[4];
    GfMenuSequence<GfMenuObjNpcTelop, 4> m_seq1;  // 0x1A0 (the name is not the original's)
};

// table 0x7100B63A90: LAY_main's listener (2.0.0's symbols name it; its reciveEvent is not written yet)
class GfMenuObjNpcTelop::MainListener : public ::ui::UIObjectListener {
public:
    MainListener(GfMenuObjNpcTelop* owner) : m_state(0), pad_10(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_state;
    unsigned char pad_10[0xC];  // cleared with m_state by the constructor
    unsigned char pad_1C[4];
    GfMenuObjNpcTelop* m_owner;
};

// table 0x7100B63AB8: LAY_dummy's listener
class GfMenuObjNpcTelop::HitonowaListener : public ::ui::UIObjectListener {
public:
    HitonowaListener(GfMenuObjNpcTelop* owner) : m_state(0), pad_10(), m_owner(owner) {}
    virtual ~HitonowaListener() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_state;  // 1 between the open event (0x21) and the close event (0x22) (the name is not the original's)
    unsigned char pad_10[0xC];  // cleared with m_state by the constructor
    unsigned char pad_1C[4];
    GfMenuObjNpcTelop* m_owner;
};

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB8D0)
extern GfMenuObjNpcTelop::OpenParam g_npcTelopParam;
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB928)
extern bool g_npcTelopOpen;

}  // namespace gf

#endif
