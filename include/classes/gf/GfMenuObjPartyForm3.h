#ifndef CLASSES_GF_GFMENUOBJPARTYFORM3_H
#define CLASSES_GF_GFMENUOBJPARTYFORM3_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { class GfMenuCallContext; class GfMenuDriverList; }
namespace ui { class UIObjectAcc; }

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
    GfMenuObjPartyForm3(unsigned int handle);
    virtual ~GfMenuObjPartyForm3();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    bool seqAnnounceChange();
    bool seqWaitOpenEnd();
    // the operation info's action 9 (remove/add a driver) enabled and its text by the party's driver count against
    // count, while no driver is being moved (m_moveIndex < 0)
    void refreshRemoveAddOperation(unsigned int handle, int count);

    // field names are not the original's
    unsigned char pad_24[0x4];  // from the end of GfMenuObject (0x24)
    GfMenuDriverList* m_driverList;  // 0x28: initialize's GfMenuDriverList::create (type 2), released by the destructor
    unsigned short m_openType;  // 0x30: the open's type (seqAnnounceChange skips the announcement for 2)
    unsigned char pad_32[0x2];
    unsigned int m_partyCount;    // 0x34: GfPartySelect::getDriverList's list 0 size (the party's drivers)
    unsigned int m_standbyCount;  // 0x38: GfPartySelect::getDriverList's list 1 size
    unsigned int m_select;        // 0x3C: zeroed by the constructor; the listeners keep a driver index in it
    int m_moveIndex;              // 0x40: -1 while no driver is being moved (refreshRemoveAddOperation)
    bool m_moving;                // 0x44
    // 0x48: initialize's seven numbers (each value 3)
    mm::mtl::FixedArray<mm::mtl::IntrusivePtr<GfMenuReferenceNumber>, 7> m_numbers;
    GfMenuSequence<GfMenuObjPartyForm3, 8> m_seq;  // 0x80
    GfMenuCallContext* m_announceContext;          // 0x310: seqAnnounceChange's common text (text 13)
    // 0x318: the remove/add operation allowed: cleared without game condition 0xA70, with a one-driver list or
    // (with GfMenuObjUtil::isValidExpansion(3)) without menu condition 0x2F
    bool m_canRemoveAdd;
    bool pad_319;  // zeroed by the constructor; DriverSelectListener clears and reads it
};
}  // namespace gf

#endif
