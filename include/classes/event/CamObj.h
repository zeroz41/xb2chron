#ifndef CLASSES_EVENT_CAMOBJ_H
#define CLASSES_EVENT_CAMOBJ_H

#include "classes/event/CamBase.h"
#include "classes/event/CamHands.h"
#include "classes/event/CmdQueue.h"
#include "classes/event/CamMotion.h"
#include "classes/event/CamField.h"
#include "classes/event/ICmd.h"

namespace event { class FrameInfo; }
namespace mm { class Col4; }

namespace event {
// table 0x7100B3C970
class CamObj {
public:
    // table 0x7100B3EF40
    class SetEnable : public ::event::ICmd {
    public:
        // inline: the table's complete-object slot holds ICmd's destructor, D0 sits in CharaObj's tail
        virtual ~SetEnable() {}  // slot 0
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EFB0
    class SetFov : public ::event::ICmd {
    public:
        // inline: the table's complete-object slot holds ICmd's destructor, D0 sits in CharaObj's tail
        virtual ~SetFov() {}  // slot 0
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EFE8
    class SetNearfar : public ::event::ICmd {
    public:
        // inline: the table's complete-object slot holds ICmd's destructor, D0 sits in CharaObj's tail
        virtual ~SetNearfar() {}  // slot 0
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EF78
    class SetTargetPos : public ::event::ICmd {
    public:
        // inline: the table's complete-object slot holds ICmd's destructor, D0 sits in CharaObj's tail
        virtual ~SetTargetPos() {}  // slot 0
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    virtual ~CamObj();  // slot 0
    virtual void update(event::FrameInfo const&);  // slot 2
    virtual void render(mm::Col4 const&);  // slot 3
    virtual void tail();  // slot 4
    void changeActive(CamBase* cam);

    unsigned char pad_8[0x28];
    float m_fov;   // 0x30; the camcommands save it before changing it; the name is not the original's
    float m_rotZ;  // 0x34; the name is not the original's
    unsigned char pad_38[0x8];
    // the commands the constructor builds in place (changeActive queues m_setEnable); the names are not the
    // original's
    SetEnable m_setEnable;  // 0x40
    SetTargetPos m_setTargetPos;  // 0x48
    SetFov m_setFov;  // 0x50
    SetNearfar m_setNearfar;  // 0x58
    unsigned int pad_60;
    unsigned int pad_64;  // changeActive passes it as the SetEnable command's first value
    unsigned long pad_68;
    CamField m_field;  // 0x70; changeActive queues no command for it; the name is not the original's
    CamHands m_hands;  // 0xb0; the name is not the original's
    CamMotion m_motion;  // 0xbb0; ScriptCamMotion plays it; the name is not the original's
    // 1.0.0's CamObj::end (0x71000B5748; 3.0.1 inlines it into ObjectCamera::end): the queued commands erased
    // first to last, then the motion stopped
    void end() {
        m_cmdQueue.eraseAll();
        m_motion.stop();
    }
    // the camera update runs and copies its fields from (0x70 holds one of them); render/tail work only while one is
    // set; the name is not the original's
    CamBase* m_activeCam;  // 0xc70
    CmdQueue<8, 0> m_cmdQueue;  // 0xc78; erased by end (CmdQueue<8,0>::erase); the name is not the original's

};
}  // namespace event

#endif
