#ifndef CLASSES_GF_GFMENUOBJQUESTREWARD_H
#define CLASSES_GF_GFMENUOBJQUESTREWARD_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B64588
class GfMenuObjQuestReward : public ::gf::GfMenuObject {
public:
    class RewardListener;
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
