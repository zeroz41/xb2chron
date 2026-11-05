#ifndef CLASSES_GF_GFMENUOBJQUESTREWARD_H
#define CLASSES_GF_GFMENUOBJQUESTREWARD_H

#include "classes/gf/GfMenuObject.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/ui/UIObjectListener.h"

namespace gf { class GfMenuItemList; }
namespace ui { struct EventData; }

namespace gf {
// table 0x7100B64588
class GfMenuObjQuestReward : public ::gf::GfMenuObject {
public:
    class RewardListener;
    // what create shows (create's symbol names the type; the field names
    // are not the original's): create copies it into the window's listener data with operator= on each reference
    struct OpenParam {
        OpenParam() : m_handle(0), pad_C(0) {}
        mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> m_quest;  // GfMenuObjQuestLog passes its quest reference
        unsigned int m_handle;  // the UI object the window duplicates its LAY_reward under (create's duplicate)
        unsigned int pad_C;     // copied with m_handle as one 8-byte word
        mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> pad_10;
    };
    // creates the window for the context (once GfMenuObjUtil::checkCCStart allows it) and, with the flag, opens it
    static void create(GfMenuCallContext* context, const OpenParam& param, bool);
    GfMenuObjQuestReward(unsigned int handle);
    virtual ~GfMenuObjQuestReward();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // sends the open event (0x21) to the reward window the context runs on, with the flag as its first parameter
    static void open(GfMenuCallContext* context, bool);
};

// table 0x7100B645D0 (_ZTVN2gf20GfMenuObjQuestReward14RewardListenerE): the reward window's listener; create makes
// one per window and sends it the OpenParam (event 0x101)
class GfMenuObjQuestReward::RewardListener : public ::ui::UIObjectListener {
public:
    // create's inline construction zeroes 0xC-0x1B, 0x20 and both references
    RewardListener() : pad_0C(), pad_20(), m_quest(), pad_38() {}
    virtual ~RewardListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    unsigned char pad_1C[4];
    unsigned char pad_20[8];
    GfMenuItemList* m_items;  // reciveEvent creates it (GfMenuItemList::create) and releases it (the name is not the original's)
    mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> m_quest;  // OpenParam::m_quest, from the open event (0x101)
    mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> pad_38;   // OpenParam::pad_10, from the same event
    unsigned char pad_40[8];
};
}  // namespace gf

#endif
