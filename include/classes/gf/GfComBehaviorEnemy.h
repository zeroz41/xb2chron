#ifndef CLASSES_GF_GFCOMBEHAVIORENEMY_H
#define CLASSES_GF_GFCOMBEHAVIORENEMY_H

#include "classes/gf/GfComBehavior.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class CallBackCache; }
namespace gf { class GfComAsm; }

namespace gf {
// a base of gf::GfComBehaviorEnemy no evidence names yet
class TUnk_B65E98 {
public:
    virtual void getTransform() const = 0;
    virtual void getTransformToSearchPlayer() const = 0;
    virtual void getBdatId_CHR_EnArrange() const = 0;
    virtual void getGmkBattleLockInfo(int&, int&) const = 0;
};
// table 0x7100B65E30; base at 0x98 unknown (TUnk_B65E98)
class GfComBehaviorEnemy : public ::gf::GfComBehavior, public TUnk_B65E98 {
public:
    class Listener;
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComBehaviorEnemy();  // slot 1
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    virtual void procAnimCallback(gf::GfComAsm*, gf::CallBackCache const&);  // slot 6
    virtual void getTransformToSearchPlayer() const;  // slot 7
    virtual void getTransform() const;  // slot 8
    virtual void getBdatId_CHR_EnArrange() const;  // slot 9
    virtual void getGmkBattleLockInfo(int&, int&) const;  // slot 10
};
}  // namespace gf

#endif
