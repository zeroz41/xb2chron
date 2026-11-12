#ifndef CLASSES_GF_GFMENUOBJBALLOON_H
#define CLASSES_GF_GFMENUOBJBALLOON_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceItem.h"
#include "gf/MenuOffset.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/ui/UIObjectListener.h"

namespace gf { class GfMenuCallContext; }
namespace gf { class GF_OBJ_HANDLE; }
namespace ui { class UICtrlCursorSelect; }
namespace ui { class UISelectObjList; }
namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5FBB0
class GfMenuObjBalloon : public ::gf::GfMenuObject {
public:
    class AutoTalkListener;
    class BoxListener;
    class EvSelectListener;
    class EvTalkListener;
    class GetItemListener;
    class SelMoneyListener;
    // nextEvent's: the next text of the talk (the field names are not the original's)
    struct NextParam {
        unsigned char* m_bdat;
        unsigned int m_msgId;
    };
    // openEvent's and openAutoTalk's: the text and the object the balloon shows at (the field names are not the
    // original's)
    struct OpenParam {
        // GfAutoTalk::createMenuObj builds one so (stores 0x10, 0x18, 0x20, 0x30, 0x38, 0x40 in that order), then
        // sets the text and the object
        OpenParam() : pad_10(0.0f, 0.0f, 0.0f), m_object(reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            m_offset.m_offset = mm::Vec3(0.0f, 0.0f, 0.0f);
            m_offset.m_bone = nullptr;
        }
        unsigned char* m_bdat;
        unsigned int m_msgId;
        mm::Vec3 pad_10;  // 0x10: 12 bytes the constructor zeroes (a mm::Vec3 by its size and alignment)
        GF_OBJ_HANDLE* m_object;  // 0x20
        unsigned char pad_28[8];
        MenuOffset m_offset;  // 0x30
    };
    // openEventSelectBox's: a question and the answers to choose from (the field names are not the original's)
    struct OpenSelectBoxParam {
        unsigned char* m_bdat;
        unsigned int m_msgId;
        unsigned char* m_selectBdat;  // 0x10: the answers'
        mm::mtl::FixedVector<unsigned int, 4> m_selectIds;
    };
    // openEventSelectMoney's: listed by the object's money selection (it news a copy for the open event; the
    // field names are not the original's)
    struct OpenSelectMoneyParam {
        OpenSelectMoneyParam() : m_bdat(nullptr), m_msgId(0), pad_C(0) {}
        unsigned char* m_bdat;
        unsigned int m_msgId;
        unsigned short pad_C;
        mm::mtl::FixedVector<unsigned int, 3> m_selectIds;  // 0x10
        mm::mtl::FixedVector<unsigned short, 3> pad_28;
    };
    // openGetItem's: the get-item table's row (BDAT 0xDD: ItemID1-3, ItemNumber1-3; the field name is not the
    // original's)
    struct OpenGetItemParam {
        unsigned int m_id;
    };
    GfMenuObjBalloon(unsigned int handle);
    virtual ~GfMenuObjBalloon();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // ends the balloon a call context shows (GfAutoTalk's disposeMenuObj passes its context and true)
    static void close(GfMenuCallContext* context, bool);
    static void nextEvent(GfMenuCallContext* context, const NextParam& param);
    static void openAutoTalk(GfMenuCallContext* context, const OpenParam& param);
    static void openEventSelectBox(GfMenuCallContext* context, const OpenSelectBoxParam& param);
    static void openEventSelectMoney(GfMenuCallContext* context, const OpenSelectMoneyParam& param);
    // false when the row has no item to show (its context aborted when every item was skipped)
    static bool openGetItem(GfMenuCallContext* context, const OpenGetItemParam& param);
    // 1.0.0's name: shows a talk balloon's text (TXT_ev_talk_msg, the message's ML:Feeling tag); EvTalkListener
    // calls it on open (0x100, the event's text and kind) and on 0x104 (kind -1)
    static void setupEvTalk(unsigned int handle, int msgId, int);
    // 1.0.0's name: fills an event selection (EvSelectListener's): the title (TXT_ev_select_msg_title), the name
    // (TXT_ev_select_name, none for -1) and the two answers from GfMenuCallManager's select strings
    static void setupEvSelect(unsigned int handle, int msgId, int nameId);
    // the save the money selection's listener queues: a save request and the saving display, then waits for it
    bool seqSave();
    bool seqSaveWait();
    // SelMoneyListener's check of the selected reward (inferred, the name is not known): whether the item box can
    // take the items of BDAT 0xDD's row m_moneyType (ItemID1-3, ItemNumber1-3) and m_money more ether stays
    // within 999999999
    bool canGetExpReward();

    // the field names are not the original's
    unsigned int pad_24;
    ui::UICtrlCursorSelect* m_selectCursor;  // 0x28: EvSelectListener's, on "LAY_ev_select_cursor"
    ui::UISelectObjList* m_selectList;       // 0x30: EvSelectListener's, on "LAY_ev_select_msg"
    ui::UISelectObjList* m_itemList;         // 0x38: initialize's, on "LAY_sel_item"
    ui::UISelectObjList* m_moneyList;        // 0x40: initialize's, on "LAY_sel_money_item"
    mm::mtl::FixedVector<unsigned int, 4> m_values;  // 0x48
    mm::mtl::FixedArray<mm::mtl::IntrusivePtr<GfMenuReferenceItem>, 3> m_getItems;  // 0x60: the get-item rows' items
    GfMenuSequence<GfMenuObjBalloon, 4> m_seq;  // 0x78
    bool pad_1D8;
    unsigned int m_money;      // 0x1DC: the money selection's
    unsigned int m_moneyType;  // 0x1E0
    unsigned int m_saveRequest;  // 0x1E4: seqSave's request (GfReqManager), -1 without one
};

// table 0x7100B5FBF8: initialize registers it (0x28 bytes; initialize zeroes 0xC-0x1B)
class GfMenuObjBalloon::BoxListener : public ::ui::UIObjectListener {
public:
    BoxListener(GfMenuObjBalloon* owner) : pad_0C(), m_owner(owner) {}
    virtual ~BoxListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(const ::ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x14];
    GfMenuObjBalloon* m_owner;  // 0x20
};

// table 0x7100B5FC20: initialize registers it (0x28 bytes; initialize zeroes 0xC-0x1B)
class GfMenuObjBalloon::SelMoneyListener : public ::ui::UIObjectListener {
public:
    SelMoneyListener(GfMenuObjBalloon* owner) : pad_0C(), m_owner(owner) {}
    virtual ~SelMoneyListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(const ::ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x14];
    GfMenuObjBalloon* m_owner;  // 0x20
};

// table 0x7100B5FC48: initialize registers it (0x28 bytes; initialize zeroes 0xC-0x1B)
class GfMenuObjBalloon::GetItemListener : public ::ui::UIObjectListener {
public:
    GetItemListener(GfMenuObjBalloon* owner) : pad_0C(), m_owner(owner) {}
    virtual ~GetItemListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(const ::ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x14];
    GfMenuObjBalloon* m_owner;  // 0x20
};

// table 0x7100B5FC70: initialize registers it on "LAY_ev_talk_root" (0x28 bytes; initialize zeroes 0xC-0x1B)
class GfMenuObjBalloon::EvTalkListener : public ::ui::UIObjectListener {
public:
    EvTalkListener(GfMenuObjBalloon* owner) : pad_0C(), m_owner(owner) {}
    virtual ~EvTalkListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(const ::ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x14];
    GfMenuObjBalloon* m_owner;  // 0x20
};

// table 0x7100B5FC98: initialize registers it on "LAY_auto_talk_root" (0x28 bytes; initialize zeroes 0xC-0x1B)
class GfMenuObjBalloon::AutoTalkListener : public ::ui::UIObjectListener {
public:
    AutoTalkListener(GfMenuObjBalloon* owner) : pad_0C(), m_owner(owner) {}
    virtual ~AutoTalkListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(const ::ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x14];
    GfMenuObjBalloon* m_owner;  // 0x20
};

// table 0x7100B5FCC0: initialize registers it on "LAY_ev_select_root" (0x28 bytes; initialize zeroes 0xC-0x1B)
class GfMenuObjBalloon::EvSelectListener : public ::ui::UIObjectListener {
public:
    EvSelectListener(GfMenuObjBalloon* owner) : pad_0C(), m_owner(owner) {}
    virtual ~EvSelectListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(const ::ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x14];
    GfMenuObjBalloon* m_owner;  // 0x20
};
}  // namespace gf

#endif
