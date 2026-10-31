#ifndef CLASSES_EVENT_CAMBASE_H
#define CLASSES_EVENT_CAMBASE_H

namespace event { class FrameInfo; }
namespace mm { class Col4; }

namespace event {
// table none (its derived classes')
class CamBase {
public:
    // inline: the constructors of CamFree (CamManager's), CamField, CamHands and CamMotion (CamObj's) store these
    // values for every camera before its own table, so they are the base's
    CamBase() : pad_8(0) {
        pad_10[0] = 0.0f;
        pad_10[1] = 1.0f;
        pad_10[2] = 2.0f;
        pad_20[0] = 0.0f;
        pad_20[1] = 1.0f;
        pad_20[2] = 1.0f;
        pad_30 = 40.0f;
        pad_34 = 0.0f;
        m_near = 0.5f;
        m_far = 40000.0f;
    }
    virtual ~CamBase() {}  // slot 0
    virtual void update(event::FrameInfo const&) = 0;  // slot 2
    virtual void render(mm::Col4 const&) {}  // slot 3
    virtual void tail() {}  // slot 4
    unsigned char pad_8;  // 0x8: CamFree's constructor clears it
    unsigned char pad_9[0x7];
    // 0x10 and 0x20: two float triples, (0, 1, 2) and (0, 1, 1) from CamFree's constructor (not mm::Vec3: the class
    // is not 16-aligned, CamObj's fields keep their offsets)
    float pad_10[3];
    unsigned char pad_1c[0x4];
    float pad_20[3];
    unsigned char pad_2c[0x4];
    float pad_30;  // 0x30: 40 from CamFree's constructor
    float pad_34;  // 0x34: 0 from CamFree's constructor
    // the near and far clip distances ScriptCamNearfar sets from EVT_nearfar; the name is not the original's
    float m_near;  // 0x38
    float m_far;   // 0x3c
};
}  // namespace event

#endif
