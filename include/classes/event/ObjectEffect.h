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

    EffectObj* m_effect;  // 0x68; the effect the commands play, kill and animate; the name is not the original's
    // the position and rotation setPosAxis/setRotAxis store (the script commands save and restore them); the
    // names are not the original's
    PosAxis m_pos;  // 0x70
    RotAxis m_rot;  // 0x90
};
}  // namespace event

#endif
