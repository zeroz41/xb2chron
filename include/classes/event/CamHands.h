#ifndef CLASSES_EVENT_CAMHANDS_H
#define CLASSES_EVENT_CAMHANDS_H

#include "classes/event/CamBase.h"

#include "event/CvType.h"
#include "classes/event/AnmVec.h"
#include "classes/event/AnmF32.h"
#include "classes/event/PosAxis.h"
#include "classes/event/TarAxis.h"
#include "mm/mtl/FixedVector.h"

namespace event { class FrameInfo; }
namespace mm { class Col4; }

namespace event {
// table 0x7100B3C900
class CamHands : public ::event::CamBase {
public:
    // inline: D2 is emitted after its first use (CamObj's destructor), D0 sits in CharaObj's tail
    virtual ~CamHands() {}  // slot 0
    virtual void update(event::FrameInfo const&);  // slot 2
    virtual void render(mm::Col4 const&);  // slot 3
    void setPos(PosAxis const& pos, CV_TYPE type);
    void setTar(TarAxis const& tar, CV_TYPE type);
    void setFov(float fov, CV_TYPE type);
    void addAnmPos(float time, PosAxis const& pos, CV_TYPE type);
    void addAnmTar(float time, TarAxis const& tar, CV_TYPE type);
    void addAnmFov(float time, float fov, CV_TYPE type);
    void setRotZ(float rotZ, CV_TYPE type);
    void addAnmRotZ(float time, float rotZ, CV_TYPE type);

    // bit 0: the camera follows the target object's position, bit 1: its target (the camfollowpos / camfollowtar
    // commands set and save them; playFade-style set/clear of the whole word); the name is not the original's
    unsigned int m_flags;  // 0x40
    // the rest follows CamObj's constructor (it builds CamHands in place) and the destructor; the names are not the
    // original's. Size 0xB00.
    AnmVec m_anmPos;  // @0x50
    AnmVec m_anmTar;  // @0x240
    AnmF32 m_anmFov;  // @0x430 (setFov writes its key count at 0x480)
    AnmF32 m_anmRotZ;  // @0x540
    mm::mtl::FixedVector<PosAxis, 16> m_posKeys;  // @0x650, count @0x850 (insertAnmPos takes a PosAxis)
    mm::mtl::FixedVector<TarAxis, 16> m_tarKeys;  // @0x860, count @0xA60 (insertAnmTar takes a TarAxis)
    // two more lists the destructor clears (counts @0xAB0 and @0xAF8); the element types are not known, only the
    // space they take
    mm::mtl::FixedVector<float, 16> pad_a70;
    mm::mtl::FixedVector<float, 16> pad_ab8;
};
}  // namespace event

#endif
