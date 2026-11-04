#ifndef CLASSES_GF_GFBDATSHOP_H
#define CLASSES_GF_GFBDATSHOP_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatShop; }

namespace gf {
// table 0x7100B47D20; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatShop : public ::mm::mtl::PtrSingleton< ::gf::GfBdatShop>, public ::gf::IDataBdat {
public:
    GfBdatShop();
    virtual ~GfBdatShop();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    void createFP();
    unsigned int getShopListShopType(unsigned int id) const;
    unsigned int getShopListTableID(unsigned int id) const;
    unsigned int getShopListDiscount(unsigned int id, unsigned int slot) const;
    unsigned int getShopNormalPrivilegeFlag(unsigned int id) const;
    unsigned int getShopNormalPrivilegeItem(unsigned int id) const;
    unsigned int getShopNormalDefItem(unsigned int id, unsigned int slot) const;
    unsigned int getShopNormalAddItem(unsigned int id, unsigned int slot) const;
    unsigned int getShopNormalPrivilegeCheck(unsigned int id, unsigned int slot) const;
    unsigned int getShopInnPrice(unsigned int id) const;
    unsigned int getShopChangeLinkQuestTask(unsigned int id) const;
    unsigned int getShopChangeLinkQuestTaskID(unsigned int id) const;
    unsigned int getShopChangeAddTaskSet(unsigned int id, unsigned int slot) const;
    unsigned int getShopChangeAddCondition(unsigned int id, unsigned int slot) const;
    unsigned int getShopChangeTaskStart() const;
    unsigned int getShopChangeTaskEnd() const;
    // 2.0.0's symbols name it. What it does: returns row id's "Name" value (2-byte), 0 when the handle is null or id is
    // out of range.
    unsigned int getShopChangeTaskName(unsigned int id) const;
    unsigned int getShopChangeTaskReward(unsigned int id) const;
    unsigned int getShopChangeTaskAddFlagValue(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns row id's ShopChangeTask "IraCraftIndex" value (2-byte), 0 when the
    // handle is null or id is out of range.
    unsigned int getShopChangeTaskIraCraftIndex(unsigned int id) const;
    unsigned int getShopChangeTaskSetItem(unsigned int id, unsigned int slot) const;
    unsigned int getShopChangeTaskSetNumber(unsigned int id, unsigned int slot) const;
    unsigned int getMNU_EventTheaterStart() const;
    unsigned int getMNU_EventTheaterEnd() const;
    unsigned int getMNU_EventTheaterevent_id(unsigned int id) const;
    unsigned int getMNU_EventTheatercategory(unsigned int id) const;
    unsigned int getMNU_EventTheatermaincast(unsigned int id) const;
    unsigned int getMNU_EventTheaterblade_id(unsigned int id) const;
    unsigned int getMNU_EventTheaterflag_index(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns row id's MNU_DlcGift "getflag" value (2-byte), 0 when the handle
    // is null or id is out of range.
    unsigned int getMNU_DlcGiftgetflag(unsigned int id) const;
    // the tables, by GfDataBdat id (s_aszGfBdatName); names follow 1.0.0's accessors (getShopList.., getMNU_EventTheater..).
    // m_fpShopCategoryName and m_fpMNU_DlcGift have no 1.0.0 accessor: named the same way (the names are not the original's).
    CBdatWrapper* m_fpShopList;  // 0x10, MNU_ShopList
    CBdatWrapper* m_fpShopNormal;  // 0x18, MNU_ShopNormal
    CBdatWrapper* m_fpShopInn;  // 0x20, MNU_ShopInn
    CBdatWrapper* m_fpShopChange;  // 0x28, MNU_ShopChange
    CBdatWrapper* m_fpShopChangeTask;  // 0x30, MNU_ShopChangeTask
    CBdatWrapper* m_fpShopCategoryName;  // 0x38, MNU_ShopCategoryName
    CBdatWrapper* m_fpMNU_EventTheater;  // 0x40, MNU_EventTheater
    CBdatWrapper* m_fpMNU_DlcGift;  // 0x48, MNU_DlcGift
};
}  // namespace gf

#endif
