#ifndef CLASSES_GF_GFMENUOBJHANACUSTOM_H
#define CLASSES_GF_GFMENUOBJHANACUSTOM_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfItemBox.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "gf/GfGameUtilHana.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/gf/GfMenuHanaAdapter.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"

namespace gf { class GfMenuCallContext; class GfMenuIDList; class GfMenuItemList; class GfMenuReferenceItem; class MenuItemInfo; }
namespace ui { class UIObjectAcc; class UISelectObjList; }

namespace gf {
// table 0x7100B62688
class GfMenuObjHanaCustom : public ::gf::GfMenuObject {
public:
    class EquipListListener;
    class ItemListListener;
    class MainListener;
    class PartsListListener;
    class PlanListener;
    GfMenuObjHanaCustom(unsigned int handle);
    virtual ~GfMenuObjHanaCustom();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 1.0.0's helpers (out of line there), inlined into their callers in 3.0.1
    static void setupMain(ui::UIObjectAcc& acc) {
        GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hplist_etnum"), 0, 0, true);
    }
    static int setFadeIn(unsigned int handle, unsigned int type) {
        int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, type);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    static int setFadeOut(unsigned int handle, unsigned int type) {
        int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, type);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        ui::EventData event;
        event.m_type = type;
        event.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
    static void updatePartsList(ui::UIObjectAcc& acc, GfMenuIDList* list, ui::UISelectObjList* select,
                                mm::mtl::FixedArray<GfMenuIDList*, 7>& partsLists);
    static void setupPartsList(ui::UIObjectAcc& acc, GfMenuIDList* list, ui::UISelectObjList* select,
                               GfMenuReferenceItem* refItem, mm::mtl::FixedArray<GfMenuIDList*, 7>& partsLists);
    static void refreshPartsList(ui::UIObjectAcc& acc, mm::mtl::FixedArray<GfMenuIDList*, 7>& partsLists);
    static void getEquipItem(unsigned int hana, unsigned int slot, MenuItemInfo& item);
    static void refreshItemInfo(ui::UIObjectAcc& acc, GfMenuItemList* list, unsigned int hana, unsigned int slot);
    static bool isExpandCircuit(unsigned int hana, unsigned int slot, RESULT_HANA& result);
    static void removeParts(unsigned int hana, unsigned int slot);
    static void refreshEquipList(ui::UIObjectAcc& acc, unsigned int hana);
    static void setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* list, ui::UISelectObjList* select);
    static void refreshItemList(GfMenuItemList* list, ui::UISelectObjList* select, unsigned int slot);
    static void equipParts(unsigned int hana, unsigned int slot, unsigned int item, GfItemHandle handle);
    static void setupPlan(ui::UIObjectAcc& acc, GfMenuIDList* list);
    static void setupItemInfo(ui::UIObjectAcc& acc, GfMenuItemList* list);
    static void refreshEquipListSub(ui::UIObjectAcc& acc, unsigned int hana, unsigned int slot, unsigned int type);
    bool seqLineAnime();

    // the names below are not the original's
    GfMenuIDList* m_planList;                          // initialize's (12 columns)
    GfMenuIDList* m_equipList;                         // initialize's (12 columns)
    ui::UISelectObjList* m_select;                     // initialize's
    mm::mtl::ReferenceObject* m_unsetRef0;             // no code sets it (1.0.0's neither); the destructor releases it
    mm::mtl::FixedArray<GfMenuIDList*, 7> m_partsLists;  // initialize's (3 columns each)
    unsigned int m_partsTop;                           // PartsListListener's scroll: added to the plan's slot
    unsigned int pad_84;
    GfMenuItemList* m_itemList;                        // initialize's
    ui::UISelectObjList* m_itemSelect;                 // initialize's
    mm::mtl::ReferenceObject* m_unsetRef1;             // no code sets it (1.0.0's neither); the destructor releases it
    GfMenuCallContext* m_context;                      // initialize's
    GfMenuSequence<GfMenuObjHanaCustom, 8> m_seq;
    int m_lineStep;                                    // seqLineAnime's: 1 while the line animation plays
    unsigned char pad_33C[4];
    GfMenuReferenceItem* m_refItem;                    // initialize's
    int m_partsMode;                                   // PartsListListener sets 0/1
    int pad_34C;
    int m_step;
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_refNumber;  // initialize's (value 0)
};
}  // namespace gf

#endif
