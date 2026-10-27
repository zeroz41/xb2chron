#ifndef CLASSES_GF_GFMENUOBJPARTYFORM3_H
#define CLASSES_GF_GFMENUOBJPARTYFORM3_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf { class GfMenuCallContext; }

namespace gf {
// table 0x7100B63E48
class GfMenuObjPartyForm3 : public ::gf::GfMenuObject {
public:
    class BGListener;
    class DriverSelectListener;
    class MainListener;
    // what registOpenParam keeps for the next open (ScriptPlayText's ui settingPartyFormBeforeBattle passes 1);
    // the name is not the original's
    struct OpenParam {
        unsigned short m_value;
    };
    static void registOpenParam(const OpenParam& param);
    virtual ~GfMenuObjPartyForm3();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    bool seqAnnounceChange();
    bool seqWaitOpenEnd();

    // field names are not the original's
    unsigned char pad_24[0xC];  // from the end of GfMenuObject (0x24)
    unsigned short m_openType;  // 0x30: the open's type (seqAnnounceChange skips the announcement for 2)
    unsigned char pad_32[0x4E];
    GfMenuSequence<GfMenuObjPartyForm3, 8> m_seq;  // 0x80
    GfMenuCallContext* m_announceContext;          // 0x310: seqAnnounceChange's common text (text 13)
};
}  // namespace gf

#endif
