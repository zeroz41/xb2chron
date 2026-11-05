#ifndef CLASSES_EVENT_OBJECTCHARA_H
#define CLASSES_EVENT_OBJECTCHARA_H

#include "classes/event/IBouCallback.h"
#include "classes/event/IManiCallback.h"
#include "classes/event/Object.h"

namespace mm { class Col4; }
#include "classes/event/CharaObj.h"
#include "classes/event/PosAxis.h"
#include "classes/event/RotAxis.h"
#include "classes/event/TarAxis.h"
#include "event/CvType.h"

// EVT_poscvtype and EVT_rotcvtype: classes/event/CharaObj.h (CharaObj::walkPos and turnRot take them too)

namespace event {
// table 0x7100B3DD70 (its first slots are event::Object's)
class ObjectChara : public ::event::Object {
public:
    virtual ~ObjectChara();  // slot 0
    virtual bool OnBouRectSelect(event::IBouCallback::SelectParam const&);  // slot 2
    virtual void OnBouRender(event::IBouCallback::RenderParam const&);  // slot 3
    virtual void clear();  // slot 4
    virtual void start();  // slot 5
    virtual void end();  // slot 6
    virtual void update();  // slot 7
    virtual void render(mm::Col4 const&);  // slot 8
    virtual void tail();  // slot 9
    virtual bool isLoading() const;  // slot 10
    virtual bool OnManiStartPos(event::IManiCallback::StartParam&);  // slot 11
    virtual void OnManiSetPos(event::IManiCallback::SetParam&);  // slot 12
    virtual bool OnManiStartRot(event::IManiCallback::StartParam&);  // slot 13
    virtual void OnManiSetRot(event::IManiCallback::SetParam&);  // slot 14
    virtual bool OnManiStartTar(event::IManiCallback::StartParam&);  // slot 15
    virtual void OnManiSetTar(event::IManiCallback::SetParam&);  // slot 16
    virtual void OnManiRender(event::IManiCallback::RenderParam&);  // slot 17
    void setPosAxis(const PosAxis& pos);
    void setRotAxis(const RotAxis& rot);
    void linerPosAxis(const PosAxis& pos, bool flag, float time, CV_TYPE type);
    void linerRotAxis(const RotAxis& rot, float time, CV_TYPE type);
    void walkPosAxis(const PosAxis& pos, EVT_poscvtype type, bool flag);
    void turnRotAxis(const RotAxis& rot, EVT_rotcvtype type, float time);

    unsigned char pad_68[0x8];
    CharaObj* m_chara;  // 0x70; the character the commands drive; the name is not the original's
    unsigned char pad_78[0x8];
    // the position and rotation setPosAxis/setRotAxis store (the script commands save and restore them); the
    // names are not the original's
    PosAxis m_pos;  // 0x80
    RotAxis m_rot;  // 0xa0
    // the target ScriptCharaTgt stores before CharaObj::setTar (and saves for undo); the name is not the original's
    TarAxis m_tar;  // 0xc0
};
}  // namespace event

#endif
