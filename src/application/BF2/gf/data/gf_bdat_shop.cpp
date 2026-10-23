#include "classes/gf/IDataBdat.h"
#include "classes/gf/GfBdatShop.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {
// the shop tables' column accessors, as 1.0.0's symbols name them: each table member's handle is looked up once
// (init) and a row's value read through it (get)
namespace _gfbsh {
// the column handles the init functions keep (the names are not the original's)
static unsigned char* s_memberShopListName;
static unsigned char* s_memberShopListShopIcon;
static unsigned char* s_memberShopListShopType;
static unsigned char* s_memberShopListTableID;
static unsigned char* s_memberShopListDiscount1;
static unsigned char* s_memberShopListDiscount2;
static unsigned char* s_memberShopListDiscount3;
static unsigned char* s_memberShopListDiscount4;
static unsigned char* s_memberShopListDiscount5;
static unsigned char* s_memberShopNormalDefItem1;
static unsigned char* s_memberShopNormalDefItem2;
static unsigned char* s_memberShopNormalDefItem3;
static unsigned char* s_memberShopNormalDefItem4;
static unsigned char* s_memberShopNormalDefItem5;
static unsigned char* s_memberShopNormalDefItem6;
static unsigned char* s_memberShopNormalDefItem7;
static unsigned char* s_memberShopNormalDefItem8;
static unsigned char* s_memberShopNormalDefItem9;
static unsigned char* s_memberShopNormalDefItem10;
static unsigned char* s_memberShopNormalAddtem1;
static unsigned char* s_memberShopNormalAddCondition1;
static unsigned char* s_memberShopNormalPrivilegeCheck1;
static unsigned char* s_memberShopNormalAddtem2;
static unsigned char* s_memberShopNormalAddCondition2;
static unsigned char* s_memberShopNormalPrivilegeCheck2;
static unsigned char* s_memberShopNormalAddtem3;
static unsigned char* s_memberShopNormalAddCondition3;
static unsigned char* s_memberShopNormalPrivilegeCheck3;
static unsigned char* s_memberShopNormalAddtem4;
static unsigned char* s_memberShopNormalAddCondition4;
static unsigned char* s_memberShopNormalPrivilegeCheck4;
static unsigned char* s_memberShopNormalAddtem5;
static unsigned char* s_memberShopNormalAddCondition5;
static unsigned char* s_memberShopNormalPrivilegeCheck5;
static unsigned char* s_memberShopNormalPrivilegeFlag;
static unsigned char* s_memberShopNormalPrivilegeItem;
static unsigned char* s_memberShopInnPrice;
static unsigned char* s_memberShopChangeDefTaskSet1;
static unsigned char* s_memberShopChangeDefTaskSet2;
static unsigned char* s_memberShopChangeDefTaskSet3;
static unsigned char* s_memberShopChangeDefTaskSet4;
static unsigned char* s_memberShopChangeDefTaskSet5;
static unsigned char* s_memberShopChangeDefTaskSet6;
static unsigned char* s_memberShopChangeDefTaskSet7;
static unsigned char* s_memberShopChangeDefTaskSet8;
static unsigned char* s_memberShopChangeAddTaskSet1;
static unsigned char* s_memberShopChangeAddCondition1;
static unsigned char* s_memberShopChangeAddTaskSet2;
static unsigned char* s_memberShopChangeAddCondition2;
static unsigned char* s_memberShopChangeAddTaskSet3;
static unsigned char* s_memberShopChangeAddCondition3;
static unsigned char* s_memberShopChangeAddTaskSet4;
static unsigned char* s_memberShopChangeAddCondition4;
static unsigned char* s_memberShopChangeAddTaskSet5;
static unsigned char* s_memberShopChangeAddCondition5;
static unsigned char* s_memberShopChangeAddTaskSet6;
static unsigned char* s_memberShopChangeAddCondition6;
static unsigned char* s_memberShopChangeAddTaskSet7;
static unsigned char* s_memberShopChangeAddCondition7;
static unsigned char* s_memberShopChangeAddTaskSet8;
static unsigned char* s_memberShopChangeAddCondition8;
static unsigned char* s_memberShopChangeLinkQuestTask;
static unsigned char* s_memberShopChangeLinkQuestTaskID;
static unsigned char* s_memberShopChangeUnitText;
static unsigned char* s_memberShopChangeTaskName;
static unsigned char* s_memberShopChangeTaskSetItem1;
static unsigned char* s_memberShopChangeTaskSetNumber1;
static unsigned char* s_memberShopChangeTaskSetItem2;
static unsigned char* s_memberShopChangeTaskSetNumber2;
static unsigned char* s_memberShopChangeTaskSetItem3;
static unsigned char* s_memberShopChangeTaskSetNumber3;
static unsigned char* s_memberShopChangeTaskSetItem4;
static unsigned char* s_memberShopChangeTaskSetNumber4;
static unsigned char* s_memberShopChangeTaskSetItem5;
static unsigned char* s_memberShopChangeTaskSetNumber5;
static unsigned char* s_memberShopChangeTaskHideReward;
static unsigned char* s_memberShopChangeTaskReward;
static unsigned char* s_memberShopChangeTaskAddFlagValue;
static unsigned char* s_memberShopChangeTaskIraCraftIndex;
static unsigned char* s_memberMNU_EventTheatertitle;
static unsigned char* s_memberMNU_EventTheaterevent_id;
static unsigned char* s_memberMNU_EventTheatercondition;
static unsigned char* s_memberMNU_EventTheaterthumbnail;
static unsigned char* s_memberMNU_EventTheatercategory;
static unsigned char* s_memberMNU_EventTheaterchapter;
static unsigned char* s_memberMNU_EventTheatermaincast;
static unsigned char* s_memberMNU_EventTheaterblade_id;
static unsigned char* s_memberMNU_EventTheaterflag_index;
static unsigned char* s_memberMNU_DlcGiftreleasecount;
static unsigned char* s_memberMNU_DlcGifttitle;
static unsigned char* s_memberMNU_DlcGiftcondition;
static unsigned char* s_memberMNU_DlcGiftcategory;
static unsigned char* s_memberMNU_DlcGiftitem_id;
static unsigned char* s_memberMNU_DlcGiftvalue;
static unsigned char* s_memberMNU_DlcGiftgetflag;

void initShopListName(const CBdatWrapper& bdat) {
    s_memberShopListName = bdat.getMember("Name");
}

void initShopListShopIcon(const CBdatWrapper& bdat) {
    s_memberShopListShopIcon = bdat.getMember("ShopIcon");
}

void initShopListShopType(const CBdatWrapper& bdat) {
    s_memberShopListShopType = bdat.getMember("ShopType");
}

unsigned int getShopListShopType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopListShopType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberShopListShopType, id, 1);
    }
    return 0;
}

void initShopListTableID(const CBdatWrapper& bdat) {
    s_memberShopListTableID = bdat.getMember("TableID");
}

unsigned int getShopListTableID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopListTableID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopListTableID, id, 2);
    }
    return 0;
}

void initShopListDiscount1(const CBdatWrapper& bdat) {
    s_memberShopListDiscount1 = bdat.getMember("Discount1");
}

unsigned int getShopListDiscount1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopListDiscount1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberShopListDiscount1, id, 1);
    }
    return 0;
}

void initShopListDiscount2(const CBdatWrapper& bdat) {
    s_memberShopListDiscount2 = bdat.getMember("Discount2");
}

unsigned int getShopListDiscount2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopListDiscount2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberShopListDiscount2, id, 1);
    }
    return 0;
}

void initShopListDiscount3(const CBdatWrapper& bdat) {
    s_memberShopListDiscount3 = bdat.getMember("Discount3");
}

unsigned int getShopListDiscount3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopListDiscount3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberShopListDiscount3, id, 1);
    }
    return 0;
}

void initShopListDiscount4(const CBdatWrapper& bdat) {
    s_memberShopListDiscount4 = bdat.getMember("Discount4");
}

unsigned int getShopListDiscount4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopListDiscount4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberShopListDiscount4, id, 1);
    }
    return 0;
}

void initShopListDiscount5(const CBdatWrapper& bdat) {
    s_memberShopListDiscount5 = bdat.getMember("Discount5");
}

unsigned int getShopListDiscount5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopListDiscount5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberShopListDiscount5, id, 1);
    }
    return 0;
}

void initShopNormalDefItem1(const CBdatWrapper& bdat) {
    s_memberShopNormalDefItem1 = bdat.getMember("DefItem1");
}

unsigned int getShopNormalDefItem1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalDefItem1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalDefItem1, id, 2);
    }
    return 0;
}

void initShopNormalDefItem2(const CBdatWrapper& bdat) {
    s_memberShopNormalDefItem2 = bdat.getMember("DefItem2");
}

unsigned int getShopNormalDefItem2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalDefItem2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalDefItem2, id, 2);
    }
    return 0;
}

void initShopNormalDefItem3(const CBdatWrapper& bdat) {
    s_memberShopNormalDefItem3 = bdat.getMember("DefItem3");
}

unsigned int getShopNormalDefItem3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalDefItem3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalDefItem3, id, 2);
    }
    return 0;
}

void initShopNormalDefItem4(const CBdatWrapper& bdat) {
    s_memberShopNormalDefItem4 = bdat.getMember("DefItem4");
}

unsigned int getShopNormalDefItem4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalDefItem4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalDefItem4, id, 2);
    }
    return 0;
}

void initShopNormalDefItem5(const CBdatWrapper& bdat) {
    s_memberShopNormalDefItem5 = bdat.getMember("DefItem5");
}

unsigned int getShopNormalDefItem5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalDefItem5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalDefItem5, id, 2);
    }
    return 0;
}

void initShopNormalDefItem6(const CBdatWrapper& bdat) {
    s_memberShopNormalDefItem6 = bdat.getMember("DefItem6");
}

unsigned int getShopNormalDefItem6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalDefItem6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalDefItem6, id, 2);
    }
    return 0;
}

void initShopNormalDefItem7(const CBdatWrapper& bdat) {
    s_memberShopNormalDefItem7 = bdat.getMember("DefItem7");
}

unsigned int getShopNormalDefItem7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalDefItem7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalDefItem7, id, 2);
    }
    return 0;
}

void initShopNormalDefItem8(const CBdatWrapper& bdat) {
    s_memberShopNormalDefItem8 = bdat.getMember("DefItem8");
}

unsigned int getShopNormalDefItem8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalDefItem8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalDefItem8, id, 2);
    }
    return 0;
}

void initShopNormalDefItem9(const CBdatWrapper& bdat) {
    s_memberShopNormalDefItem9 = bdat.getMember("DefItem9");
}

unsigned int getShopNormalDefItem9(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalDefItem9 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalDefItem9, id, 2);
    }
    return 0;
}

void initShopNormalDefItem10(const CBdatWrapper& bdat) {
    s_memberShopNormalDefItem10 = bdat.getMember("DefItem10");
}

unsigned int getShopNormalDefItem10(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalDefItem10 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalDefItem10, id, 2);
    }
    return 0;
}

void initShopNormalAddtem1(const CBdatWrapper& bdat) {
    s_memberShopNormalAddtem1 = bdat.getMember("Addtem1");
}

unsigned int getShopNormalAddtem1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalAddtem1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalAddtem1, id, 2);
    }
    return 0;
}

void initShopNormalAddCondition1(const CBdatWrapper& bdat) {
    s_memberShopNormalAddCondition1 = bdat.getMember("AddCondition1");
}

void initShopNormalPrivilegeCheck1(const CBdatWrapper& bdat) {
    s_memberShopNormalPrivilegeCheck1 = bdat.getMember("PrivilegeCheck1");
}

unsigned int getShopNormalPrivilegeCheck1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalPrivilegeCheck1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberShopNormalPrivilegeCheck1, id, 1);
    }
    return 0;
}

void initShopNormalAddtem2(const CBdatWrapper& bdat) {
    s_memberShopNormalAddtem2 = bdat.getMember("Addtem2");
}

unsigned int getShopNormalAddtem2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalAddtem2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalAddtem2, id, 2);
    }
    return 0;
}

void initShopNormalAddCondition2(const CBdatWrapper& bdat) {
    s_memberShopNormalAddCondition2 = bdat.getMember("AddCondition2");
}

void initShopNormalPrivilegeCheck2(const CBdatWrapper& bdat) {
    s_memberShopNormalPrivilegeCheck2 = bdat.getMember("PrivilegeCheck2");
}

unsigned int getShopNormalPrivilegeCheck2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalPrivilegeCheck2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberShopNormalPrivilegeCheck2, id, 1);
    }
    return 0;
}

void initShopNormalAddtem3(const CBdatWrapper& bdat) {
    s_memberShopNormalAddtem3 = bdat.getMember("Addtem3");
}

unsigned int getShopNormalAddtem3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalAddtem3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalAddtem3, id, 2);
    }
    return 0;
}

void initShopNormalAddCondition3(const CBdatWrapper& bdat) {
    s_memberShopNormalAddCondition3 = bdat.getMember("AddCondition3");
}

void initShopNormalPrivilegeCheck3(const CBdatWrapper& bdat) {
    s_memberShopNormalPrivilegeCheck3 = bdat.getMember("PrivilegeCheck3");
}

unsigned int getShopNormalPrivilegeCheck3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalPrivilegeCheck3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberShopNormalPrivilegeCheck3, id, 1);
    }
    return 0;
}

void initShopNormalAddtem4(const CBdatWrapper& bdat) {
    s_memberShopNormalAddtem4 = bdat.getMember("Addtem4");
}

unsigned int getShopNormalAddtem4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalAddtem4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalAddtem4, id, 2);
    }
    return 0;
}

void initShopNormalAddCondition4(const CBdatWrapper& bdat) {
    s_memberShopNormalAddCondition4 = bdat.getMember("AddCondition4");
}

void initShopNormalPrivilegeCheck4(const CBdatWrapper& bdat) {
    s_memberShopNormalPrivilegeCheck4 = bdat.getMember("PrivilegeCheck4");
}

unsigned int getShopNormalPrivilegeCheck4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalPrivilegeCheck4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberShopNormalPrivilegeCheck4, id, 1);
    }
    return 0;
}

void initShopNormalAddtem5(const CBdatWrapper& bdat) {
    s_memberShopNormalAddtem5 = bdat.getMember("Addtem5");
}

unsigned int getShopNormalAddtem5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalAddtem5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalAddtem5, id, 2);
    }
    return 0;
}

void initShopNormalAddCondition5(const CBdatWrapper& bdat) {
    s_memberShopNormalAddCondition5 = bdat.getMember("AddCondition5");
}

void initShopNormalPrivilegeCheck5(const CBdatWrapper& bdat) {
    s_memberShopNormalPrivilegeCheck5 = bdat.getMember("PrivilegeCheck5");
}

unsigned int getShopNormalPrivilegeCheck5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalPrivilegeCheck5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberShopNormalPrivilegeCheck5, id, 1);
    }
    return 0;
}

void initShopNormalPrivilegeFlag(const CBdatWrapper& bdat) {
    s_memberShopNormalPrivilegeFlag = bdat.getMember("PrivilegeFlag");
}

unsigned int getShopNormalPrivilegeFlag(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalPrivilegeFlag != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalPrivilegeFlag, id, 2);
    }
    return 0;
}

void initShopNormalPrivilegeItem(const CBdatWrapper& bdat) {
    s_memberShopNormalPrivilegeItem = bdat.getMember("PrivilegeItem");
}

unsigned int getShopNormalPrivilegeItem(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopNormalPrivilegeItem != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopNormalPrivilegeItem, id, 2);
    }
    return 0;
}

void initShopInnPrice(const CBdatWrapper& bdat) {
    s_memberShopInnPrice = bdat.getMember("Price");
}

unsigned int getShopInnPrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopInnPrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopInnPrice, id, 2);
    }
    return 0;
}

void initShopChangeDefTaskSet1(const CBdatWrapper& bdat) {
    s_memberShopChangeDefTaskSet1 = bdat.getMember("DefTaskSet1");
}

void initShopChangeDefTaskSet2(const CBdatWrapper& bdat) {
    s_memberShopChangeDefTaskSet2 = bdat.getMember("DefTaskSet2");
}

void initShopChangeDefTaskSet3(const CBdatWrapper& bdat) {
    s_memberShopChangeDefTaskSet3 = bdat.getMember("DefTaskSet3");
}

void initShopChangeDefTaskSet4(const CBdatWrapper& bdat) {
    s_memberShopChangeDefTaskSet4 = bdat.getMember("DefTaskSet4");
}

void initShopChangeDefTaskSet5(const CBdatWrapper& bdat) {
    s_memberShopChangeDefTaskSet5 = bdat.getMember("DefTaskSet5");
}

void initShopChangeDefTaskSet6(const CBdatWrapper& bdat) {
    s_memberShopChangeDefTaskSet6 = bdat.getMember("DefTaskSet6");
}

void initShopChangeDefTaskSet7(const CBdatWrapper& bdat) {
    s_memberShopChangeDefTaskSet7 = bdat.getMember("DefTaskSet7");
}

void initShopChangeDefTaskSet8(const CBdatWrapper& bdat) {
    s_memberShopChangeDefTaskSet8 = bdat.getMember("DefTaskSet8");
}

void initShopChangeAddTaskSet1(const CBdatWrapper& bdat) {
    s_memberShopChangeAddTaskSet1 = bdat.getMember("AddTaskSet1");
}

unsigned int getShopChangeAddTaskSet1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddTaskSet1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddTaskSet1, id, 2);
    }
    return 0;
}

void initShopChangeAddCondition1(const CBdatWrapper& bdat) {
    s_memberShopChangeAddCondition1 = bdat.getMember("AddCondition1");
}

unsigned int getShopChangeAddCondition1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddCondition1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddCondition1, id, 2);
    }
    return 0;
}

void initShopChangeAddTaskSet2(const CBdatWrapper& bdat) {
    s_memberShopChangeAddTaskSet2 = bdat.getMember("AddTaskSet2");
}

unsigned int getShopChangeAddTaskSet2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddTaskSet2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddTaskSet2, id, 2);
    }
    return 0;
}

void initShopChangeAddCondition2(const CBdatWrapper& bdat) {
    s_memberShopChangeAddCondition2 = bdat.getMember("AddCondition2");
}

unsigned int getShopChangeAddCondition2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddCondition2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddCondition2, id, 2);
    }
    return 0;
}

void initShopChangeAddTaskSet3(const CBdatWrapper& bdat) {
    s_memberShopChangeAddTaskSet3 = bdat.getMember("AddTaskSet3");
}

unsigned int getShopChangeAddTaskSet3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddTaskSet3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddTaskSet3, id, 2);
    }
    return 0;
}

void initShopChangeAddCondition3(const CBdatWrapper& bdat) {
    s_memberShopChangeAddCondition3 = bdat.getMember("AddCondition3");
}

unsigned int getShopChangeAddCondition3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddCondition3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddCondition3, id, 2);
    }
    return 0;
}

void initShopChangeAddTaskSet4(const CBdatWrapper& bdat) {
    s_memberShopChangeAddTaskSet4 = bdat.getMember("AddTaskSet4");
}

unsigned int getShopChangeAddTaskSet4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddTaskSet4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddTaskSet4, id, 2);
    }
    return 0;
}

void initShopChangeAddCondition4(const CBdatWrapper& bdat) {
    s_memberShopChangeAddCondition4 = bdat.getMember("AddCondition4");
}

unsigned int getShopChangeAddCondition4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddCondition4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddCondition4, id, 2);
    }
    return 0;
}

void initShopChangeAddTaskSet5(const CBdatWrapper& bdat) {
    s_memberShopChangeAddTaskSet5 = bdat.getMember("AddTaskSet5");
}

unsigned int getShopChangeAddTaskSet5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddTaskSet5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddTaskSet5, id, 2);
    }
    return 0;
}

void initShopChangeAddCondition5(const CBdatWrapper& bdat) {
    s_memberShopChangeAddCondition5 = bdat.getMember("AddCondition5");
}

unsigned int getShopChangeAddCondition5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddCondition5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddCondition5, id, 2);
    }
    return 0;
}

void initShopChangeAddTaskSet6(const CBdatWrapper& bdat) {
    s_memberShopChangeAddTaskSet6 = bdat.getMember("AddTaskSet6");
}

unsigned int getShopChangeAddTaskSet6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddTaskSet6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddTaskSet6, id, 2);
    }
    return 0;
}

void initShopChangeAddCondition6(const CBdatWrapper& bdat) {
    s_memberShopChangeAddCondition6 = bdat.getMember("AddCondition6");
}

unsigned int getShopChangeAddCondition6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddCondition6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddCondition6, id, 2);
    }
    return 0;
}

void initShopChangeAddTaskSet7(const CBdatWrapper& bdat) {
    s_memberShopChangeAddTaskSet7 = bdat.getMember("AddTaskSet7");
}

unsigned int getShopChangeAddTaskSet7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddTaskSet7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddTaskSet7, id, 2);
    }
    return 0;
}

void initShopChangeAddCondition7(const CBdatWrapper& bdat) {
    s_memberShopChangeAddCondition7 = bdat.getMember("AddCondition7");
}

unsigned int getShopChangeAddCondition7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddCondition7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddCondition7, id, 2);
    }
    return 0;
}

void initShopChangeAddTaskSet8(const CBdatWrapper& bdat) {
    s_memberShopChangeAddTaskSet8 = bdat.getMember("AddTaskSet8");
}

unsigned int getShopChangeAddTaskSet8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddTaskSet8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddTaskSet8, id, 2);
    }
    return 0;
}

void initShopChangeAddCondition8(const CBdatWrapper& bdat) {
    s_memberShopChangeAddCondition8 = bdat.getMember("AddCondition8");
}

unsigned int getShopChangeAddCondition8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeAddCondition8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeAddCondition8, id, 2);
    }
    return 0;
}

void initShopChangeLinkQuestTask(const CBdatWrapper& bdat) {
    s_memberShopChangeLinkQuestTask = bdat.getMember("LinkQuestTask");
}

unsigned int getShopChangeLinkQuestTask(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeLinkQuestTask != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeLinkQuestTask, id, 2);
    }
    return 0;
}

void initShopChangeLinkQuestTaskID(const CBdatWrapper& bdat) {
    s_memberShopChangeLinkQuestTaskID = bdat.getMember("LinkQuestTaskID");
}

unsigned int getShopChangeLinkQuestTaskID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeLinkQuestTaskID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeLinkQuestTaskID, id, 2);
    }
    return 0;
}

void initShopChangeUnitText(const CBdatWrapper& bdat) {
    s_memberShopChangeUnitText = bdat.getMember("UnitText");
}

// 3.0.1's column: 1.0.0 has no ShopChangeTaskName accessors (the name is not the original's)
void initShopChangeTaskName(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskName = bdat.getMember("Name");
}

unsigned int getShopChangeTaskName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeTaskName, id, 2);
    }
    return 0;
}

void initShopChangeTaskSetItem1(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskSetItem1 = bdat.getMember("SetItem1");
}

unsigned int getShopChangeTaskSetItem1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskSetItem1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeTaskSetItem1, id, 2);
    }
    return 0;
}

void initShopChangeTaskSetNumber1(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskSetNumber1 = bdat.getMember("SetNumber1");
}

unsigned int getShopChangeTaskSetNumber1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskSetNumber1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeTaskSetNumber1, id, 2);
    }
    return 0;
}

void initShopChangeTaskSetItem2(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskSetItem2 = bdat.getMember("SetItem2");
}

unsigned int getShopChangeTaskSetItem2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskSetItem2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeTaskSetItem2, id, 2);
    }
    return 0;
}

void initShopChangeTaskSetNumber2(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskSetNumber2 = bdat.getMember("SetNumber2");
}

unsigned int getShopChangeTaskSetNumber2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskSetNumber2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeTaskSetNumber2, id, 2);
    }
    return 0;
}

void initShopChangeTaskSetItem3(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskSetItem3 = bdat.getMember("SetItem3");
}

unsigned int getShopChangeTaskSetItem3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskSetItem3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeTaskSetItem3, id, 2);
    }
    return 0;
}

void initShopChangeTaskSetNumber3(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskSetNumber3 = bdat.getMember("SetNumber3");
}

unsigned int getShopChangeTaskSetNumber3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskSetNumber3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeTaskSetNumber3, id, 2);
    }
    return 0;
}

void initShopChangeTaskSetItem4(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskSetItem4 = bdat.getMember("SetItem4");
}

unsigned int getShopChangeTaskSetItem4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskSetItem4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeTaskSetItem4, id, 2);
    }
    return 0;
}

void initShopChangeTaskSetNumber4(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskSetNumber4 = bdat.getMember("SetNumber4");
}

unsigned int getShopChangeTaskSetNumber4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskSetNumber4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeTaskSetNumber4, id, 2);
    }
    return 0;
}

void initShopChangeTaskSetItem5(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskSetItem5 = bdat.getMember("SetItem5");
}

unsigned int getShopChangeTaskSetItem5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskSetItem5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeTaskSetItem5, id, 2);
    }
    return 0;
}

void initShopChangeTaskSetNumber5(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskSetNumber5 = bdat.getMember("SetNumber5");
}

unsigned int getShopChangeTaskSetNumber5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskSetNumber5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeTaskSetNumber5, id, 2);
    }
    return 0;
}

void initShopChangeTaskHideReward(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskHideReward = bdat.getMember("HideReward");
}

void initShopChangeTaskReward(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskReward = bdat.getMember("Reward");
}

unsigned int getShopChangeTaskReward(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskReward != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeTaskReward, id, 2);
    }
    return 0;
}

void initShopChangeTaskAddFlagValue(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskAddFlagValue = bdat.getMember("AddFlagValue");
}

unsigned int getShopChangeTaskAddFlagValue(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskAddFlagValue != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberShopChangeTaskAddFlagValue, id, 1);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no ShopChangeTaskIraCraftIndex accessors (the name is not the original's)
void initShopChangeTaskIraCraftIndex(const CBdatWrapper& bdat) {
    s_memberShopChangeTaskIraCraftIndex = bdat.getMember("IraCraftIndex");
}

unsigned int getShopChangeTaskIraCraftIndex(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberShopChangeTaskIraCraftIndex != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberShopChangeTaskIraCraftIndex, id, 2);
    }
    return 0;
}

void initMNU_EventTheatertitle(const CBdatWrapper& bdat) {
    s_memberMNU_EventTheatertitle = bdat.getMember("title");
}

void initMNU_EventTheaterevent_id(const CBdatWrapper& bdat) {
    s_memberMNU_EventTheaterevent_id = bdat.getMember("event_id");
}

unsigned int getMNU_EventTheaterevent_id(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMNU_EventTheaterevent_id != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMNU_EventTheaterevent_id, id, 2);
    }
    return 0;
}

void initMNU_EventTheatercondition(const CBdatWrapper& bdat) {
    s_memberMNU_EventTheatercondition = bdat.getMember("condition");
}

void initMNU_EventTheaterthumbnail(const CBdatWrapper& bdat) {
    s_memberMNU_EventTheaterthumbnail = bdat.getMember("thumbnail");
}

void initMNU_EventTheatercategory(const CBdatWrapper& bdat) {
    s_memberMNU_EventTheatercategory = bdat.getMember("category");
}

unsigned int getMNU_EventTheatercategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMNU_EventTheatercategory != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMNU_EventTheatercategory, id, 1);
    }
    return 0;
}

void initMNU_EventTheaterchapter(const CBdatWrapper& bdat) {
    s_memberMNU_EventTheaterchapter = bdat.getMember("chapter");
}

void initMNU_EventTheatermaincast(const CBdatWrapper& bdat) {
    s_memberMNU_EventTheatermaincast = bdat.getMember("maincast");
}

unsigned int getMNU_EventTheatermaincast(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMNU_EventTheatermaincast != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberMNU_EventTheatermaincast, id, 1);
    }
    return 0;
}

void initMNU_EventTheaterblade_id(const CBdatWrapper& bdat) {
    s_memberMNU_EventTheaterblade_id = bdat.getMember("blade_id");
}

unsigned int getMNU_EventTheaterblade_id(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMNU_EventTheaterblade_id != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMNU_EventTheaterblade_id, id, 2);
    }
    return 0;
}

void initMNU_EventTheaterflag_index(const CBdatWrapper& bdat) {
    s_memberMNU_EventTheaterflag_index = bdat.getMember("flag_index");
}

unsigned int getMNU_EventTheaterflag_index(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMNU_EventTheaterflag_index != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMNU_EventTheaterflag_index, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no MNU_DlcGiftreleasecount accessors (the name is not the original's)
void initMNU_DlcGiftreleasecount(const CBdatWrapper& bdat) {
    s_memberMNU_DlcGiftreleasecount = bdat.getMember("releasecount");
}

// 3.0.1's column: 1.0.0 has no MNU_DlcGifttitle accessors (the name is not the original's)
void initMNU_DlcGifttitle(const CBdatWrapper& bdat) {
    s_memberMNU_DlcGifttitle = bdat.getMember("title");
}

// 3.0.1's column: 1.0.0 has no MNU_DlcGiftcondition accessors (the name is not the original's)
void initMNU_DlcGiftcondition(const CBdatWrapper& bdat) {
    s_memberMNU_DlcGiftcondition = bdat.getMember("condition");
}

// 3.0.1's column: 1.0.0 has no MNU_DlcGiftcategory accessors (the name is not the original's)
void initMNU_DlcGiftcategory(const CBdatWrapper& bdat) {
    s_memberMNU_DlcGiftcategory = bdat.getMember("category");
}

// 3.0.1's column: 1.0.0 has no MNU_DlcGiftitem_id accessors (the name is not the original's)
void initMNU_DlcGiftitem_id(const CBdatWrapper& bdat) {
    s_memberMNU_DlcGiftitem_id = bdat.getMember("item_id");
}

// 3.0.1's column: 1.0.0 has no MNU_DlcGiftvalue accessors (the name is not the original's)
void initMNU_DlcGiftvalue(const CBdatWrapper& bdat) {
    s_memberMNU_DlcGiftvalue = bdat.getMember("value");
}

// 3.0.1's column: 1.0.0 has no MNU_DlcGiftgetflag accessors (the name is not the original's)
void initMNU_DlcGiftgetflag(const CBdatWrapper& bdat) {
    s_memberMNU_DlcGiftgetflag = bdat.getMember("getflag");
}

unsigned int getMNU_DlcGiftgetflag(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMNU_DlcGiftgetflag != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMNU_DlcGiftgetflag, id, 2);
    }
    return 0;
}

// a slot table's getter for a slot (the name is not the original's). The original's slot tables are writable data
// (.data, null checks kept): clang 3.9 makes a static table constant unless its address is passed on before inlining,
// so its slot getters handed the table to an inline helper like this one.
template <class Getter, unsigned long N>
inline Getter getSlot(Getter (&table)[N], unsigned int slot) {
    return table[slot];
}

}  // namespace _gfbsh

GfBdatShop::GfBdatShop() {
    m_fpShopList = nullptr;
    m_fpShopNormal = nullptr;
    m_fpShopInn = nullptr;
    m_fpShopChange = nullptr;
    m_fpShopChangeTask = nullptr;
    m_fpShopCategoryName = nullptr;
    m_fpMNU_EventTheater = nullptr;
    m_fpMNU_DlcGift = nullptr;
    bdatRefresh();
}

GfBdatShop::~GfBdatShop() {
    destroyFP();
}

void GfBdatShop::destroyFP() {
    if (m_fpShopList != nullptr) {
        delete m_fpShopList;
        m_fpShopList = nullptr;
    }
    if (m_fpShopNormal != nullptr) {
        delete m_fpShopNormal;
        m_fpShopNormal = nullptr;
    }
    if (m_fpShopInn != nullptr) {
        delete m_fpShopInn;
        m_fpShopInn = nullptr;
    }
    if (m_fpShopChange != nullptr) {
        delete m_fpShopChange;
        m_fpShopChange = nullptr;
    }
    if (m_fpShopChangeTask != nullptr) {
        delete m_fpShopChangeTask;
        m_fpShopChangeTask = nullptr;
    }
    if (m_fpShopCategoryName != nullptr) {
        delete m_fpShopCategoryName;
        m_fpShopCategoryName = nullptr;
    }
    if (m_fpMNU_EventTheater != nullptr) {
        delete m_fpMNU_EventTheater;
        m_fpMNU_EventTheater = nullptr;
    }
    if (m_fpMNU_DlcGift != nullptr) {
        delete m_fpMNU_DlcGift;
        m_fpMNU_DlcGift = nullptr;
    }
}

void GfBdatShop::createFP() {
#line 179
    m_fpShopList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xED));
    m_fpShopNormal = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xEE));
    m_fpShopInn = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xEF));
    m_fpShopChange = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xF0));
    m_fpShopChangeTask = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xF2));
    m_fpShopCategoryName = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xF3));
    m_fpMNU_EventTheater = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xFD));
    m_fpMNU_DlcGift = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x10A));
}

void GfBdatShop::bdatRefresh() {
    destroyFP();
    createFP();
    _gfbsh::initShopListName(*m_fpShopList);
    _gfbsh::initShopListShopIcon(*m_fpShopList);
    _gfbsh::initShopListShopType(*m_fpShopList);
    _gfbsh::initShopListTableID(*m_fpShopList);
    _gfbsh::initShopListDiscount1(*m_fpShopList);
    _gfbsh::initShopListDiscount2(*m_fpShopList);
    _gfbsh::initShopListDiscount3(*m_fpShopList);
    _gfbsh::initShopListDiscount4(*m_fpShopList);
    _gfbsh::initShopListDiscount5(*m_fpShopList);
    _gfbsh::initShopNormalDefItem1(*m_fpShopNormal);
    _gfbsh::initShopNormalDefItem2(*m_fpShopNormal);
    _gfbsh::initShopNormalDefItem3(*m_fpShopNormal);
    _gfbsh::initShopNormalDefItem4(*m_fpShopNormal);
    _gfbsh::initShopNormalDefItem5(*m_fpShopNormal);
    _gfbsh::initShopNormalDefItem6(*m_fpShopNormal);
    _gfbsh::initShopNormalDefItem7(*m_fpShopNormal);
    _gfbsh::initShopNormalDefItem8(*m_fpShopNormal);
    _gfbsh::initShopNormalDefItem9(*m_fpShopNormal);
    _gfbsh::initShopNormalDefItem10(*m_fpShopNormal);
    _gfbsh::initShopNormalAddtem1(*m_fpShopNormal);
    _gfbsh::initShopNormalAddCondition1(*m_fpShopNormal);
    _gfbsh::initShopNormalPrivilegeCheck1(*m_fpShopNormal);
    _gfbsh::initShopNormalAddtem2(*m_fpShopNormal);
    _gfbsh::initShopNormalAddCondition2(*m_fpShopNormal);
    _gfbsh::initShopNormalPrivilegeCheck2(*m_fpShopNormal);
    _gfbsh::initShopNormalAddtem3(*m_fpShopNormal);
    _gfbsh::initShopNormalAddCondition3(*m_fpShopNormal);
    _gfbsh::initShopNormalPrivilegeCheck3(*m_fpShopNormal);
    _gfbsh::initShopNormalAddtem4(*m_fpShopNormal);
    _gfbsh::initShopNormalAddCondition4(*m_fpShopNormal);
    _gfbsh::initShopNormalPrivilegeCheck4(*m_fpShopNormal);
    _gfbsh::initShopNormalAddtem5(*m_fpShopNormal);
    _gfbsh::initShopNormalAddCondition5(*m_fpShopNormal);
    _gfbsh::initShopNormalPrivilegeCheck5(*m_fpShopNormal);
    _gfbsh::initShopNormalPrivilegeFlag(*m_fpShopNormal);
    _gfbsh::initShopNormalPrivilegeItem(*m_fpShopNormal);
    _gfbsh::initShopInnPrice(*m_fpShopInn);
    _gfbsh::initShopChangeDefTaskSet1(*m_fpShopChange);
    _gfbsh::initShopChangeDefTaskSet2(*m_fpShopChange);
    _gfbsh::initShopChangeDefTaskSet3(*m_fpShopChange);
    _gfbsh::initShopChangeDefTaskSet4(*m_fpShopChange);
    _gfbsh::initShopChangeDefTaskSet5(*m_fpShopChange);
    _gfbsh::initShopChangeDefTaskSet6(*m_fpShopChange);
    _gfbsh::initShopChangeDefTaskSet7(*m_fpShopChange);
    _gfbsh::initShopChangeDefTaskSet8(*m_fpShopChange);
    _gfbsh::initShopChangeAddTaskSet1(*m_fpShopChange);
    _gfbsh::initShopChangeAddCondition1(*m_fpShopChange);
    _gfbsh::initShopChangeAddTaskSet2(*m_fpShopChange);
    _gfbsh::initShopChangeAddCondition2(*m_fpShopChange);
    _gfbsh::initShopChangeAddTaskSet3(*m_fpShopChange);
    _gfbsh::initShopChangeAddCondition3(*m_fpShopChange);
    _gfbsh::initShopChangeAddTaskSet4(*m_fpShopChange);
    _gfbsh::initShopChangeAddCondition4(*m_fpShopChange);
    _gfbsh::initShopChangeAddTaskSet5(*m_fpShopChange);
    _gfbsh::initShopChangeAddCondition5(*m_fpShopChange);
    _gfbsh::initShopChangeAddTaskSet6(*m_fpShopChange);
    _gfbsh::initShopChangeAddCondition6(*m_fpShopChange);
    _gfbsh::initShopChangeAddTaskSet7(*m_fpShopChange);
    _gfbsh::initShopChangeAddCondition7(*m_fpShopChange);
    _gfbsh::initShopChangeAddTaskSet8(*m_fpShopChange);
    _gfbsh::initShopChangeAddCondition8(*m_fpShopChange);
    _gfbsh::initShopChangeLinkQuestTask(*m_fpShopChange);
    _gfbsh::initShopChangeLinkQuestTaskID(*m_fpShopChange);
    _gfbsh::initShopChangeUnitText(*m_fpShopChange);
    _gfbsh::initShopChangeTaskName(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskSetItem1(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskSetNumber1(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskSetItem2(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskSetNumber2(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskSetItem3(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskSetNumber3(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskSetItem4(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskSetNumber4(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskSetItem5(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskSetNumber5(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskHideReward(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskReward(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskAddFlagValue(*m_fpShopChangeTask);
    _gfbsh::initShopChangeTaskIraCraftIndex(*m_fpShopChangeTask);
    _gfbsh::initMNU_EventTheatertitle(*m_fpMNU_EventTheater);
    _gfbsh::initMNU_EventTheaterevent_id(*m_fpMNU_EventTheater);
    _gfbsh::initMNU_EventTheatercondition(*m_fpMNU_EventTheater);
    _gfbsh::initMNU_EventTheaterthumbnail(*m_fpMNU_EventTheater);
    _gfbsh::initMNU_EventTheatercategory(*m_fpMNU_EventTheater);
    _gfbsh::initMNU_EventTheaterchapter(*m_fpMNU_EventTheater);
    _gfbsh::initMNU_EventTheatermaincast(*m_fpMNU_EventTheater);
    _gfbsh::initMNU_EventTheaterblade_id(*m_fpMNU_EventTheater);
    _gfbsh::initMNU_EventTheaterflag_index(*m_fpMNU_EventTheater);
    _gfbsh::initMNU_DlcGiftreleasecount(*m_fpMNU_DlcGift);
    _gfbsh::initMNU_DlcGifttitle(*m_fpMNU_DlcGift);
    _gfbsh::initMNU_DlcGiftcondition(*m_fpMNU_DlcGift);
    _gfbsh::initMNU_DlcGiftcategory(*m_fpMNU_DlcGift);
    _gfbsh::initMNU_DlcGiftitem_id(*m_fpMNU_DlcGift);
    _gfbsh::initMNU_DlcGiftvalue(*m_fpMNU_DlcGift);
    _gfbsh::initMNU_DlcGiftgetflag(*m_fpMNU_DlcGift);
}

unsigned int GfBdatShop::getShopListShopType(unsigned int id) const {
    return _gfbsh::getShopListShopType(*m_fpShopList, id);
}

unsigned int GfBdatShop::getShopListTableID(unsigned int id) const {
    return _gfbsh::getShopListTableID(*m_fpShopList, id);
}

unsigned int GfBdatShop::getShopListDiscount(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbsh::getShopListDiscount1,
        _gfbsh::getShopListDiscount2,
        _gfbsh::getShopListDiscount3,
        _gfbsh::getShopListDiscount4,
        _gfbsh::getShopListDiscount5,
    };
    return _gfbsh::getSlot(s_getters, slot)(*m_fpShopList, id);
}

unsigned int GfBdatShop::getShopNormalPrivilegeFlag(unsigned int id) const {
    return _gfbsh::getShopNormalPrivilegeFlag(*m_fpShopNormal, id);
}

unsigned int GfBdatShop::getShopNormalPrivilegeItem(unsigned int id) const {
    return _gfbsh::getShopNormalPrivilegeItem(*m_fpShopNormal, id);
}

unsigned int GfBdatShop::getShopNormalDefItem(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbsh::getShopNormalDefItem1,
        _gfbsh::getShopNormalDefItem2,
        _gfbsh::getShopNormalDefItem3,
        _gfbsh::getShopNormalDefItem4,
        _gfbsh::getShopNormalDefItem5,
        _gfbsh::getShopNormalDefItem6,
        _gfbsh::getShopNormalDefItem7,
        _gfbsh::getShopNormalDefItem8,
        _gfbsh::getShopNormalDefItem9,
        _gfbsh::getShopNormalDefItem10,
    };
    return _gfbsh::getSlot(s_getters, slot)(*m_fpShopNormal, id);
}

unsigned int GfBdatShop::getShopNormalAddItem(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbsh::getShopNormalAddtem1,
        _gfbsh::getShopNormalAddtem2,
        _gfbsh::getShopNormalAddtem3,
        _gfbsh::getShopNormalAddtem4,
        _gfbsh::getShopNormalAddtem5,
    };
    return _gfbsh::getSlot(s_getters, slot)(*m_fpShopNormal, id);
}

unsigned int GfBdatShop::getShopNormalPrivilegeCheck(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbsh::getShopNormalPrivilegeCheck1,
        _gfbsh::getShopNormalPrivilegeCheck2,
        _gfbsh::getShopNormalPrivilegeCheck3,
        _gfbsh::getShopNormalPrivilegeCheck4,
        _gfbsh::getShopNormalPrivilegeCheck5,
    };
    return _gfbsh::getSlot(s_getters, slot)(*m_fpShopNormal, id);
}

unsigned int GfBdatShop::getShopInnPrice(unsigned int id) const {
    return _gfbsh::getShopInnPrice(*m_fpShopInn, id);
}

unsigned int GfBdatShop::getShopChangeLinkQuestTask(unsigned int id) const {
    return _gfbsh::getShopChangeLinkQuestTask(*m_fpShopChange, id);
}

unsigned int GfBdatShop::getShopChangeLinkQuestTaskID(unsigned int id) const {
    return _gfbsh::getShopChangeLinkQuestTaskID(*m_fpShopChange, id);
}

unsigned int GfBdatShop::getShopChangeAddTaskSet(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbsh::getShopChangeAddTaskSet1,
        _gfbsh::getShopChangeAddTaskSet2,
        _gfbsh::getShopChangeAddTaskSet3,
        _gfbsh::getShopChangeAddTaskSet4,
        _gfbsh::getShopChangeAddTaskSet5,
        _gfbsh::getShopChangeAddTaskSet6,
        _gfbsh::getShopChangeAddTaskSet7,
        _gfbsh::getShopChangeAddTaskSet8,
    };
    return _gfbsh::getSlot(s_getters, slot)(*m_fpShopChange, id);
}

unsigned int GfBdatShop::getShopChangeAddCondition(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbsh::getShopChangeAddCondition1,
        _gfbsh::getShopChangeAddCondition2,
        _gfbsh::getShopChangeAddCondition3,
        _gfbsh::getShopChangeAddCondition4,
        _gfbsh::getShopChangeAddCondition5,
        _gfbsh::getShopChangeAddCondition6,
        _gfbsh::getShopChangeAddCondition7,
        _gfbsh::getShopChangeAddCondition8,
    };
    return _gfbsh::getSlot(s_getters, slot)(*m_fpShopChange, id);
}

unsigned int GfBdatShop::getShopChangeTaskStart() const {
    return Bdat::getIdTop(m_fpShopChangeTask->m_fp);
}

unsigned int GfBdatShop::getShopChangeTaskEnd() const {
    return Bdat::getIdTop(m_fpShopChangeTask->m_fp) + Bdat::getIdCount(m_fpShopChangeTask->m_fp);
}

unsigned int GfBdatShop::fn_710021E294(unsigned int id) const {
    return _gfbsh::getShopChangeTaskName(*m_fpShopChangeTask, id);
}

unsigned int GfBdatShop::getShopChangeTaskReward(unsigned int id) const {
    return _gfbsh::getShopChangeTaskReward(*m_fpShopChangeTask, id);
}

unsigned int GfBdatShop::getShopChangeTaskAddFlagValue(unsigned int id) const {
    return _gfbsh::getShopChangeTaskAddFlagValue(*m_fpShopChangeTask, id);
}

unsigned int GfBdatShop::fn_710021E42C(unsigned int id) const {
    return _gfbsh::getShopChangeTaskIraCraftIndex(*m_fpShopChangeTask, id);
}

unsigned int GfBdatShop::getShopChangeTaskSetItem(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbsh::getShopChangeTaskSetItem1,
        _gfbsh::getShopChangeTaskSetItem2,
        _gfbsh::getShopChangeTaskSetItem3,
        _gfbsh::getShopChangeTaskSetItem4,
        _gfbsh::getShopChangeTaskSetItem5,
    };
    return _gfbsh::getSlot(s_getters, slot)(*m_fpShopChangeTask, id);
}

unsigned int GfBdatShop::getShopChangeTaskSetNumber(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbsh::getShopChangeTaskSetNumber1,
        _gfbsh::getShopChangeTaskSetNumber2,
        _gfbsh::getShopChangeTaskSetNumber3,
        _gfbsh::getShopChangeTaskSetNumber4,
        _gfbsh::getShopChangeTaskSetNumber5,
    };
    return _gfbsh::getSlot(s_getters, slot)(*m_fpShopChangeTask, id);
}

unsigned int GfBdatShop::getMNU_EventTheaterStart() const {
    return Bdat::getIdTop(m_fpMNU_EventTheater->m_fp);
}

unsigned int GfBdatShop::getMNU_EventTheaterEnd() const {
    return Bdat::getIdTop(m_fpMNU_EventTheater->m_fp) + Bdat::getIdCount(m_fpMNU_EventTheater->m_fp);
}

unsigned int GfBdatShop::getMNU_EventTheaterevent_id(unsigned int id) const {
    return _gfbsh::getMNU_EventTheaterevent_id(*m_fpMNU_EventTheater, id);
}

unsigned int GfBdatShop::getMNU_EventTheatercategory(unsigned int id) const {
    return _gfbsh::getMNU_EventTheatercategory(*m_fpMNU_EventTheater, id);
}

unsigned int GfBdatShop::getMNU_EventTheatermaincast(unsigned int id) const {
    return _gfbsh::getMNU_EventTheatermaincast(*m_fpMNU_EventTheater, id);
}

unsigned int GfBdatShop::getMNU_EventTheaterblade_id(unsigned int id) const {
    return _gfbsh::getMNU_EventTheaterblade_id(*m_fpMNU_EventTheater, id);
}

unsigned int GfBdatShop::getMNU_EventTheaterflag_index(unsigned int id) const {
    return _gfbsh::getMNU_EventTheaterflag_index(*m_fpMNU_EventTheater, id);
}

unsigned int GfBdatShop::fn_710021E7CC(unsigned int id) const {
    return _gfbsh::getMNU_DlcGiftgetflag(*m_fpMNU_DlcGift, id);
}

}  // namespace gf
