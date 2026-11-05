#ifndef CLASSES_EVENT_OBJECTCAMERA_H
#define CLASSES_EVENT_OBJECTCAMERA_H

#include "classes/event/IBouCallback.h"
#include "classes/event/IManiCallback.h"
#include "classes/event/Object.h"
#include "classes/event/CamObj.h"
#include "classes/event/PosAxis.h"
#include "classes/event/TarAxis.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

namespace mm { class Col4; }

namespace event {
// table 0x7100B3DE68
class ObjectCamera : public ::event::Object {
public:
    ObjectCamera(const char* name, unsigned int id);
    virtual ~ObjectCamera();  // slot 0
    virtual bool OnBouRectSelect(event::IBouCallback::SelectParam const&);  // slot 2
    virtual void OnBouRender(event::IBouCallback::RenderParam const&);  // slot 3
    virtual void start();  // slot 5
    virtual void end();  // slot 6
    virtual void update();  // slot 7
    virtual void render(mm::Col4 const&);  // slot 8
    virtual void tail();  // slot 9
    virtual bool OnManiStartPos(event::IManiCallback::StartParam&);  // slot 11
    virtual void OnManiSetPos(event::IManiCallback::SetParam&);  // slot 12
    virtual bool OnManiStartTar(event::IManiCallback::StartParam&);  // slot 13
    virtual void OnManiSetTar(event::IManiCallback::SetParam&);  // slot 14
    virtual void OnManiRender(event::IManiCallback::RenderParam&);  // slot 15
    // the camera the object drives (tail calls its slot 4, CamObj::tail); the name is not the original's
    CamObj* m_cam;  // 0x68
    int pad_70;  // OnBouRender draws the camera info only while it is 0
    unsigned char pad_74[0xc];
    // the camera position the campos command sets (its undo restores the previous one) and the queue it restarts
    // with it (the command clears the queue and pushes the new position); the names are not the original's
    PosAxis m_pos;  // 0x80
    mm::mtl::FixedVector<PosAxis, 16> m_posQueue;  // 0xa0, count 0x2a0
    // the same for the target (camtar); the names are not the original's
    TarAxis m_tar;  // 0x2b0
    mm::mtl::FixedVector<TarAxis, 16> m_tarQueue;  // 0x2d0, count 0x4d0
    // the index of the m_posQueue key OnManiSetPos edits (0 also moves m_pos)
    unsigned int pad_4e0;
    unsigned int pad_4e4;
    // the cut name the camcut command sets (its undo restores the previous one); the name is not the original's
    mm::mtl::FixStr<64> m_cutName;  // 0x4e8
};
}  // namespace event

#endif
