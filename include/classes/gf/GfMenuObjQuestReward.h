#ifndef CLASSES_GF_GFMENUOBJQUESTREWARD_H
#define CLASSES_GF_GFMENUOBJQUESTREWARD_H

#include "classes/gf/GfMenuObject.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/IntrusivePtr.h"

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
}  // namespace gf

#endif
