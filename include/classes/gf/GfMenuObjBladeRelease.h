#ifndef CLASSES_GF_GFMENUOBJBLADERELEASE_H
#define CLASSES_GF_GFMENUOBJBLADERELEASE_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GAME_VOICE_HANDLE; class GfMenuBladeList; class GfMenuCallContext; class GfMenuDriverList;
               class GfMenuIDList; class GfMenuItemList; }
namespace mm { namespace mtl { class ReferenceObject; } }
namespace ui { class UICtrlCursorSelect; class UISelectObjList; }

namespace gf {
// table 0x7100B60250. Field names are not the original's.
class GfMenuObjBladeRelease : public ::gf::GfMenuObject {
public:
    class ListListener;
    class MainListener;
    GfMenuObjBladeRelease(unsigned int handle);
    virtual ~GfMenuObjBladeRelease();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    bool seqOpenImage();
    bool seqConfirmRelease();
    bool seqSubMenuOpen();
    bool seqEffReleaseA();
    bool seqEffReleaseB();
    bool seqExecRelease();
    bool seqConfirmBoosterGet();
    bool seqResumeRelease();
    bool seqSubMenuEnd();
    bool seqSubMenuOpenCustomize();
    bool seqSubMenuErrorOvdOnly();
    bool seqSubMenuErrorOvdLastOne();
    bool seqSubMenuDrChange();
    bool seqSubMenuConfSetRex();
    bool seqSubMenuConfRemoveRex();
    bool seqSubMenuOwnerChange();
    bool seqSubMenuWaitLoadCustomize();
    bool seqSubMenuWaitEndCustomize();

    mm::mtl::ReferenceObject* pad_28;          // the constructor zeroes it, the destructor releases it
    GfMenuBladeList* m_bladeList;              // initialize's: the releasable blades
    ui::UISelectObjList* m_list;               // initialize's ("LAY_list_bl@%02d")
    ui::UICtrlCursorSelect* m_cursor;          // initialize's ("IMG_list_bl_cursor")
    GfMenuCallContext* m_context;              // seqConfirmBoosterGet's openGetItem
    GfMenuCallContext* m_subContext;
    GfMenuSequence<GfMenuObjBladeRelease, 8> m_seq;     // 0x58
    bool m_seqStep;                            // 0x2E8: a job's first step done
    GfMenuSequence<GfMenuObjBladeRelease, 4> m_subSeq;  // 0x2F0: MainListener queues seqOpenImage on it
    GfMenuItemList* m_itemList;                // 0x450: the boosters seqConfirmBoosterGet shows
    bool pad_458;
    GfMenuIDList* m_idList;                    // 0x460
    bool pad_468;
    unsigned int pad_46C;                      // the constructor sets -1
    GfMenuDriverList* m_driverList;            // 0x470
    mm::mtl::FixedVector<unsigned short, 32> m_drivers;  // 0x478: GfPartySelect::getDriverList's
    bool m_hasRex;                             // 0x4C0: initialize sets it when the list holds driver 1
    unsigned int m_sortType;                   // 0x4C4: GfMenuObjSort::open's
    int pad_4C8;
    GAME_VOICE_HANDLE* m_voice;                // 0x4D0: finalize stops it
    bool m_voicePlayed;                        // 0x4D8
};
}  // namespace gf

#endif
