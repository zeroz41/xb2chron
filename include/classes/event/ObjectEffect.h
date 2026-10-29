#ifndef CLASSES_EVENT_OBJECTEFFECT_H
#define CLASSES_EVENT_OBJECTEFFECT_H

#include "classes/event/IBouCallback.h"
#include "classes/event/IManiCallback.h"
#include "classes/event/Object.h"

namespace mm { class Col4; }
namespace event { class IAttachActor; enum ATTACH_TYPE : int; }
#include "classes/event/EffectObj.h"
#include "classes/event/PosAxis.h"
#include "classes/event/RotAxis.h"
#include "event/CvType.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"

namespace event {
// table 0x7100B3DF50
class ObjectEffect : public ::event::Object {
public:
    virtual ~ObjectEffect();  // slot 0
    virtual void OnBouRectSelect(event::IBouCallback::SelectParam const&);  // slot 2
    virtual void OnBouRender(event::IBouCallback::RenderParam const&);  // slot 3
    virtual void start();  // slot 5
    virtual void end();  // slot 6
    virtual void update();  // slot 7
    virtual void render(mm::Col4 const&);  // slot 8
    virtual void tail();  // slot 9
    virtual void OnManiStartPos(event::IManiCallback::StartParam&);  // slot 11
    virtual void OnManiSetPos(event::IManiCallback::SetParam&);  // slot 12
    virtual void OnManiStartRot(event::IManiCallback::StartParam&);  // slot 13
    virtual void OnManiSetRot(event::IManiCallback::SetParam&);  // slot 14
    virtual void OnManiRender(event::IManiCallback::RenderParam&);  // slot 15
    void setPosAxis(const PosAxis& pos);
    void setRotAxis(const RotAxis& rot);
    void linerPosAxis(const PosAxis& pos, float time, CV_TYPE type);
    void linerRotAxis(const RotAxis& rot, float time, CV_TYPE type);
    void setMount(IAttachActor* actor, const char* name, const mm::Vec3& pos, bool flag, ATTACH_TYPE type);
    // plays the effect and forgets the mount setMount stored (1.0.0's ObjectEffect::play 0x7100118C20, same
    // signature; 3.0.1 inlines it into ScriptEffectPlay::doit and redo)
    void play(const char* name, float a, float b, float c, int d, int e) {
        m_effect->play(name, a, b, c, d, e);
        pad_b0 = 0;
        m_mountActor = 0;
        m_mountName = "";
        m_mountPos = mm::Vec3::zero;
        m_mountFlag = false;
        m_mountType = (ATTACH_TYPE)0;
        m_mountMtx = mm::Mat44::identity;
        pad_150 = false;
        pad_190 = 0;
    }

    EffectObj* m_effect;  // 0x68; the effect the commands play, kill and animate; the name is not the original's
    // the position and rotation setPosAxis/setRotAxis store (the script commands save and restore them); the
    // names are not the original's
    PosAxis m_pos;  // 0x70
    RotAxis m_rot;  // 0x90
    // zeroed by setMount and play; no reader seen yet
    unsigned long pad_b0;  // 0xb0
    unsigned char pad_b8[0x8];
    // setMount's arguments (play clears them); the names are not the original's
    IAttachActor* m_mountActor;      // 0xc0
    mm::mtl::FixStr<32> m_mountName;  // 0xc8 (setMount cites fixstr.h's `m_nLen < LEN` with LEN 32)
    unsigned char pad_ec[0x4];
    mm::Vec3 m_mountPos;             // 0xf0
    bool m_mountFlag;                // 0x100
    ATTACH_TYPE m_mountType;         // 0x104
    unsigned char pad_108[0x8];
    // play resets it to the identity; the name is not the original's
    mm::Mat44 m_mountMtx;            // 0x110
    // play clears both; no reader seen yet
    bool pad_150;                    // 0x150
    unsigned char pad_151[0x3f];
    int pad_190;                     // 0x190
};
}  // namespace event

#endif
