#ifndef CLASSES_GF_GFMENUOBJMERCENARYTOP_H
#define CLASSES_GF_GFMENUOBJMERCENARYTOP_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf {
// table 0x7100B63608. Field names are not the original's.
class GfMenuObjMercenaryTop : public ::gf::GfMenuObject {
public:
    class MainListener;
    class MissionListener;
    class ZoneListener;
    // what registOpenParam passes on as the layer param's menu word (the name is not the original's)
    struct OpenParam {
        unsigned int m_value;
    };
    virtual ~GfMenuObjMercenaryTop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // registers the param of full-screen layer 0x34 (this menu's)
    static void registOpenParam(OpenParam const& param);
    bool seqExit();

    unsigned char pad_24[0x7C];  // from the end of GfMenuObject (0x24)
    GfMenuSequence<GfMenuObjMercenaryTop, 8> m_seq;  // 0xA0
    bool pad_330;
    unsigned int m_exitHandle;  // 0x334: seqExit sends it event 0x100 and clears it
    unsigned char pad_338[8];
    bool m_canClose;            // 0x340: the constructor sets it; MainListener fades out on 2/0x22 only while set
};
}  // namespace gf

#endif
