#include "classes/gf/GfMenuObjGiftBox.h"
#include "classes/gf/GfMenuObjGiftBox/MainListener.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuMsgList.h"
#include "classes/gf/GfMenuReferenceItem.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "gf/gf_data_aoc.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjGiftBox::GfMenuObjGiftBox(unsigned int handle)
    : GfMenuObject(handle), m_topList(nullptr), m_subList(nullptr), m_numbers(), m_seq(this), pad_378(0),
      m_refItem(), m_ids(), m_counts(), m_menuId(0), m_hasMenuId(false), m_noMenuId(false) {
    m_topList = GfMenuMsgList::create();
    m_subList = GfMenuIDList::create();
    m_refItem = GfMenuReferenceItem::create();
    for (int i = 0; i < 22; i++) {
        m_numbers[i] = GfMenuReferenceNumber::create();
    }
}

GfMenuObjGiftBox::~GfMenuObjGiftBox() {
    m_refItem = nullptr;
    for (int i = 0; i < 22; i++) {
        m_numbers[i] = nullptr;
    }
    if (m_counts.capacity() != 0) {
        m_counts.destroy();
    }
    if (m_subList != nullptr) {
        m_subList->release();
        m_subList = nullptr;
    }
    if (m_topList != nullptr) {
        m_topList->release();
        m_topList = nullptr;
    }
}

bool GfMenuObjGiftBox::canGetItem(unsigned int row, unsigned int arg) {
    if (GfGameFlag::getLocal(1, static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x10A), "getflag", row))) == 0 &&
        GfGameCond::isGameCond(static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x10A), "condition", row)))) {
        return !isGetItemFull(row, arg);
    }
    return false;
}

bool GfMenuObjGiftBox::hasFreeGift() {
    unsigned char* fp = GfDataBdat::getFP(0x10A);
    if (GfDataAoc::fn_71002229C0(5) >= 0) {
        for (int i = 0; i < Bdat::getIdCount(fp); i++) {
            if (Bdat::getVal(fp, "releasecount", Bdat::getIdTop(fp) + i) & 0x80) {
                return true;
            }
        }
    }
    return false;
}

void GfMenuObjGiftBox::setCloseToAnnounce() {
    GfMenuTypes::Param param;
    param.m_menuId = 1;
    GfMenuFullScreen::registLayerParam(0x46, param);
}

void GfMenuObjGiftBox::setCloseToAnnounceEx() {
    GfMenuTypes::Param param;
    param.m_menuId = 2;
    GfMenuFullScreen::registLayerParam(0x46, param);
}

void GfMenuObjGiftBox::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjGiftBox::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjGiftBox::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 1, 0);
    } else if (event.m_type == 2) {
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
    } else if (event.m_type == 3) {
        if (event.m_param0 == 1) {
            GfMenuObject::sendOpenEvent(acc.searchChild("LAY_top_list"), 0, 0.0f);
        } else if (event.m_param0 == 2) {
            acc.setTerm();
        }
    } else {
        ui::UIObjectListener::reciveEvent(event, handle);
    }
}

bool GfMenuObjGiftBox::seqWaitCommonDialog() {
    return !GfMenuManager::isOpenCommonWindow();
}

bool GfMenuObjGiftBox::seqReturnTop() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    ui::EventData event;
    event.m_type = 0x100;
    event.m_param0 = 1;
    GfMenuObject::sendEvent(acc.searchSibiling("LAY_top_list"), event, 0.0f);
    return true;
}

bool GfMenuObjGiftBox::seqGetItem() {
    execGetItem(m_subList->getContents(m_subList->getIndex(false)).m_id);
    refreshTopList(true);
    refreshSubList();
    GfMenuManager::openCommonWindow(0xE8);
    return true;
}

bool GfMenuObjGiftBox::seqReturnSub() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    ui::EventData event;
    event.m_type = 0x100;
    GfMenuObject::sendEvent(acc.searchSibiling("LAY_sub_list"), event, 0.0f);
    return true;
}

}  // namespace gf
