#ifndef CLASSES_GF_GFMENUOBJBUTTONCHALLENGE2_H
#define CLASSES_GF_GFMENUOBJBUTTONCHALLENGE2_H

#include "classes/gf/GfMenuObject.h"

namespace gf { class GfMenuCallContext; }

namespace gf {
// table 0x7100B609E8
class GfMenuObjButtonChallenge2 : public ::gf::GfMenuObject {
public:
    class MainListener;
    class RingListener;
    virtual ~GfMenuObjButtonChallenge2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // how a challenge opens (the names are not the original's: StateSalvageDiveStart gives a speed of 0.16)
    struct OptionParam {
        OptionParam() {
            m_unk2 = false;
            m_unk0 = 0;
            m_speed = 0.16f;
        }
        unsigned short m_unk0;
        bool m_unk2;
        float m_speed;
    };
    static void open(GfMenuCallContext* context, unsigned int id, const OptionParam& param);
    static void close(GfMenuCallContext* context);
};
}  // namespace gf

#endif
