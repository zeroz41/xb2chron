#ifndef CLASSES_GF_GFCOMBEHAVIORGMK_H
#define CLASSES_GF_GFCOMBEHAVIORGMK_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/gf/GfComBehavior.h"
#include "gf/GfBigObjUnique.h"

namespace fw { class ColiMoveObject; }
namespace fw { class ColiObject; }
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GfMenuCallContext; }
namespace gf { class MsgPcFieldGetAccessType; }
namespace gf { class MsgPcFieldNotifyAction; }
namespace gf { class MsgPcFieldNotifySkillEvent; }
namespace gf { class MsgPcGetElvLift; }
namespace gf { class MsgPcGetLookPoint; }
namespace gmk { class GmkRouteNavi; }

namespace gf {
// table 0x7100B66470; a gimmick object's behavior: answers the PC's access messages for the bound gimmick,
// opens its target-info menu, and moves a routed gimmick along its route
class GfComBehaviorGmk : public ::gf::GfComBehavior {
public:
    GfComBehaviorGmk();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorGmk();  // slot 1
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    void procMsgPcFieldNotifyAction(fw::MessageObject* sender, MsgPcFieldNotifyAction& msg);
    // 1.0.0's (names from its symbols); recieveMessage inlines them and 3.0.1's linker dropped them
    void procMsgPcFieldGetAccessType(fw::MessageObject* sender, MsgPcFieldGetAccessType& msg);
    void procMsgPcGetLookPoint(fw::MessageObject* sender, MsgPcGetLookPoint& msg);
    void procMsgPcFieldNotifySkillEvent(fw::MessageObject* sender, MsgPcFieldNotifySkillEvent& msg);
    void procMsgPcGetElvLift(fw::MessageObject* sender, MsgPcGetElvLift& msg);
    void setup();
    void createMenuObj();
    void cleanup();
    void disposeMenuObj();
    void setActivateCollison(bool activate);
    // the collider's first collision object when it is a moving one
    fw::ColiMoveObject* getColiObject() const;
    static mm::mtl::RTTI m_rtti;

    // (the field names are not the original's)
    fw::ColiObject* m_coliObject;       // a routed gimmick's collision (setup's): update moves it
    gmk::GmkRouteNavi* m_routeNavi;     // a routed gimmick's (setup's)
    GfMenuCallContext* m_menuContext;   // the target-info menu's (createMenuObj's); disposeMenuObj closes it
    GfBigObjUnique m_bigObj;
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_frame;  // the transform's frame (setup's)
};
}  // namespace gf

#endif
