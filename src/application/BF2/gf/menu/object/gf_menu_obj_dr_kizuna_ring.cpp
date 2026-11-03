#include "classes/gf/GfMenuCharDataAdapter.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfMenuObjDrKizunaRing.h"
#include "classes/gf/GfMenuObjDrKizunaRing/MainListener.h"
#include "classes/gf/GfMenuObjDrKizunaRing/RingListener.h"
#include "classes/gf/GfMenuObjDrKizunaRing/RingPadListener.h"
#include "classes/gf/GfMenuObjDrKizunaRing/SkillDetailListener.h"
#include "classes/gf/GfMenuObjDrKizunaRing/DriverStockSPListener.h"
#include "mm/mtl/FixStr.h"
#include "mm/Pnt.h"
#include "gf/GfDataDriverSkill.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuSkillAdapter.h"
#include "classes/ui/UICtrlFrame.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "ui/EventData.h"
#include "mm/Rect.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/Delegate.h"

namespace gmo_dr_kizuna_ring {
float rateTbl[2] = {1.0f, 0.5f};
}

namespace gf {

GfMenuObjDrKizunaRing::GfMenuObjDrKizunaRing(unsigned int handle)
    : GfMenuObject(handle), m_ringList(nullptr), m_ringFrame(nullptr), m_detailOpen(false), m_unlockLevel(0),
      m_selected(-1), m_subContext(nullptr), m_context(nullptr), m_round(0), m_seq(this), m_step(0),
      m_callContext(nullptr), m_itemList(nullptr), m_voice(nullptr), pad_318(0) {}

GfMenuObjDrKizunaRing::~GfMenuObjDrKizunaRing() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_ringList != nullptr) {
        m_ringList->release();
        m_ringList = nullptr;
    }
    if (m_ringFrame != nullptr) {
        m_ringFrame->release();
        m_ringFrame = nullptr;
    }
    if (m_subContext != nullptr) {
        m_subContext->release();
        m_subContext = nullptr;
    }
    if (m_callContext != nullptr) {
        m_callContext->release();
        m_callContext = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
}

void GfMenuObjDrKizunaRing::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int handle = acc.searchChild("LAY_main");
    {
#line 155
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::attachExternalCall(0x66, handle);
    handle = acc.searchChild("LAY_dr_main");
    {
#line 161
        RingListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) RingListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_scale");
    {
#line 165
        RingPadListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) RingPadListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_skill_info");
    {
#line 169
        SkillDetailListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SkillDetailListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_dr_stocksp");
    {
#line 177
        DriverStockSPListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) DriverStockSPListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_ringList = ui::UISelectObjList::create(create);
    m_subContext = GfMenuCallContext::create();
    m_context = GfMenuCallContext::create();
    m_callContext = GfMenuCallContext::create();
    m_itemList = GfMenuItemList::create();
    {
        ui::UIListInfoBase::SetupParam param;
        m_itemList->setup(getAllocator(ALLOCATOR(0)), param);
    }
    GfMenuObject::disableInput(acc.searchChild("LAY_dr_main"));
    GfMenuObject::disableInput(acc.searchChild("LAY_scale"));
    GfMenuObject::initialize();
}

void GfMenuObjDrKizunaRing::finalize() {
    if (m_voice != nullptr) {
        GfGameVoice::playStop(m_voice);
        m_voice = nullptr;
    }
    GfMenuObject::finalize();
}

void GfMenuObjDrKizunaRing::update() {
    m_seq.update();
    if (m_voice != nullptr && GfGameVoice::getResult(m_voice) >= 3) {
        m_voice = nullptr;
    }
    GfMenuObject::update();
}

void GfMenuObjDrKizunaRing::setupRingList(ui::UIObjectAcc& acc, ui::UISelectObjList* list) {
    mm::mtl::FixStr<32> name;
    list->clear();
    for (int level = 1; level <= 3; level++) {
        name.format("LAY_lock@%02d", level);
        unsigned int lock = acc.searchChild(name.m_str);
        if (lock != 0) {
            list->addObject(lock);
            for (int line = 0; line < 5; line++) {
                name.format("LAY_skillspot_RL@%02d", level + line * 3);
                unsigned int spot = acc.searchChild(name.m_str);
                if (spot != 0) {
                    list->addObject(spot);
                }
            }
        }
    }
}

void GfMenuObjDrKizunaRing::refreshRing(ui::UIObjectAcc& acc) {
    unsigned int driver = GfMenuReference::getReferenceDriverID(0);
    bool round = GfMenuReference::getReferenceNumber(2) != 0;
    mm::mtl::FixStr<32> name;
    for (int level = 0; level < 3; level++) {
        for (int line = 0; line < 5; line++) {
            name.format("IMG_node_icon@%02d", level + 1 + line * 3);
            ui::UIObjectAcc icon(acc.searchChild(name.m_str));
            if (icon.m_object != nullptr) {
                name.format("IMG_node_base@%02d", level + 1 + line * 3);
                ui::UIObjectAcc base(acc.searchChild(name.m_str));
                if (base.m_object != nullptr) {
                    if (!GfDataDriverSkill::isSkillUnlock(driver, line, level + 1, round)) {
                        icon.setMulColor("white");
                        base.setMulColor("gray");
                    } else if (GfDataDriverSkill::getSkill(driver, line, level + 1, round) == 0) {
                        icon.setMulColor("black");
                        base.setMulColor("gray");
                    } else {
                        icon.setMulColor("white");
                        base.setMulColor("white");
                    }
                }
            }
        }
    }
}

void GfMenuObjDrKizunaRing::movePointer(unsigned int handle, int index, ui::UISelectObjList* list) {
    GfMenuObject::setupInputSelection(handle, index, list->getSize());
    mm::Pnt<short> pos;
    {
        ui::UIObjectAcc acc(list->getContents(index));
        acc.getPosCenter(pos);
    }
    GfMenuObject::changePointerPos(handle, pos);
}

bool GfMenuObjDrKizunaRing::seqWait() {
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc scale(acc.searchChild("LAY_scale"));
    GfMenuObject::enableInput(scale.m_handle);
    return true;
}

void GfMenuObjDrKizunaRing::setupSkillDetail(ui::UIObjectAcc& acc) {
    GfMenuAdapterManager::beginAddAfter();
    GfMenuSkillAdapter::createFromReferenceDriverLineLevel(acc.searchChild("TXT_skif_skillname_S24_L1C12"), 0, 0, 0, 1, 2, true);
    GfMenuSkillAdapter::createFromReferenceDriverLineLevel(acc.searchChild("TXT_skif_infotxt_S24_L3C20"), 1, 0, 0, 1, 2, true);
    GfMenuSkillAdapter::createFromReferenceDriverLineLevel(acc.searchChild("TXT_skif_spnum_S20_L1C10"), 2, 0, 0, 1, 2, true);
    mm::mtl::FixStr<32> name;
    name.format("IMG_skif_icon@%02d", 1);
    GfMenuSkillAdapter::createFromReferenceDriverLineLevel(acc.searchChild(name.m_str), 3, 0, 0, 1, 2, true);
    name.format("IMG_skif_icon_base@%02d", 1);
    GfMenuSkillAdapter::createFromReferenceDriverLineLevel(acc.searchChild(name.m_str), 5, 0, 0, 1, 2, true);
    GfMenuSkillAdapter* lock =
        GfMenuSkillAdapter::createFromReferenceDriverLineLevel(acc.searchChild("TXT_skif_skillname_lock"), 10, 0, 0, 1, 2, true);
    lock->m_rowHandle = acc.searchChild("LAY_skif_lock");
    GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjDrKizunaRing::DriverStockSPListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 8:
    case 0x105:
    case 0x106:
        break;
    case 1:
        setupDriverSkillInfo(owner);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjDrKizunaRing::seqUnlockAnime() {
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc main(acc.searchChild("LAY_dr_main"));
    ui::UIObjectAcc open(main.searchChild("IMG_lock_open"));
    if (m_step == 0) {
        const char* lock = getSkillUnlockLevel(GfMenuReference::getReferenceDriverID(0)) == 1 ? "lock2" : "lock3";
        open.startAnimation("skill_open", false);
        open.setDisp(true);
        mm::Rect<short> rect;
        main.getLayoutRect(lock, rect);
        mm::Pnt<short> pos;
        pos.x = rect.x + rect.w / 2;
        pos.y = rect.y + rect.h / 2;
        open.setPosCenter(pos);
        GfMenuObjUtil::playSE(0xF);
        m_step++;
        return false;
    }
    if (!open.isPlayingAnimation()) {
        m_step = 0;
        return true;
    }
    return false;
}

bool GfMenuObjDrKizunaRing::seqCircleAnime() {
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc main(acc.searchChild("LAY_dr_main"));
    unsigned int level = getSkillUnlockLevel(GfMenuReference::getReferenceDriverID(0));
    ui::UIObjectAcc eff(main.searchChild("IMG_ring_eff"));
    if (m_step == 0) {
        eff.startAnimation(level == 1 ? "lineb" : "linec", false);
        GfMenuObjUtil::playSE(0x10);
        m_step++;
        return false;
    }
    if (!eff.isPlayingAnimation()) {
        m_step = 0;
        return true;
    }
    return false;
}

bool GfMenuObjDrKizunaRing::seqOpenAnime() {
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc main(acc.searchChild("LAY_dr_main"));
    int node = getSkillUnlockLevel(GfMenuReference::getReferenceDriverID(0)) == 1 ? 2 : 3;
    mm::mtl::FixStr<32> name;
    if (m_step == 0) {
        int index = node;
        for (int line = 0; line < 5; line++) {
            name.format("IMG_node_eff@%02d", index);
            ui::UIObjectAcc eff(main.searchChild(name.m_str));
            eff.startAnimation("skill_open", false);
            index += 3;
        }
        GfMenuObjUtil::playSE(0xF);
        m_step++;
    } else {
        name.format("IMG_node_eff@%02d", node);
        ui::UIObjectAcc eff(main.searchChild(name.m_str));
        if (!eff.isPlayingAnimation()) {
            m_step = 0;
            return true;
        }
    }
    return false;
}

bool GfMenuObjDrKizunaRing::seqEndAnime() {
    getSkillUnlockLevel(GfMenuReference::getReferenceDriverID(0));
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc main(acc.searchChild("LAY_dr_main"));
    sendEvent(acc.searchChild("LAY_dr_main"), 0x102, 0);
    sendEvent(acc.searchChild("LAY_skill_info"), 0x21, 0);
    ui::UIObjectAcc cursor(acc.searchChild("IMG_pointcursor"));
    cursor.setDisp(true);
    cursor.startAnimation("loop", false);
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
    ui::UIObjectAcc ring(m_handle, "LAY_dr_main");
    GfMenuObjMainMenu2::openCharChange(ring.m_handle, 0, false);
    return true;
}
}  // namespace gf

template bool gf::GfMenuSequence<gf::GfMenuObjDrKizunaRing, 8>::wait();

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjDrKizunaRing, 8>>(const mm::mtl::Delegate<bool()>*);

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjDrKizunaRing>(const mm::mtl::Delegate<bool()>*);

namespace gf {

void GfMenuObjDrKizunaRing::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        setupMain(acc);
        setupCircle(acc, getSkillUnlockLevel(GfMenuReference::getReferenceDriverID(0)));
        GfMenuReference::setReferenceNumber(0, 0);
        GfMenuReference::setReferenceNumber(1, 1);
        GfMenuReference::setReferenceNumber(2, 0);
        GfMenuObjOperationInfo::add(acc.searchChild("LAY_scale"), acc.searchChild("LAY_dr_main"), 0, 0);
        GfMenuObjOperationInfo::setGuideText(0x10, 0);
        GfMenuObjMainMenu2::setSubIndexText(7);
        setFadeIn(handle);
        GfMenuObjUtil::setPointSpeedRate(ui::UIObjectAcc(acc.searchChild("LAY_dr_main")), gmo_dr_kizuna_ring::rateTbl[0]);
        break;
    case 3:
        if (event.m_param0 == 1) {
            sendEvent(acc.searchChild("LAY_dr_main"), 0x102, 0);
            ui::UIObjectAcc cursor(acc.searchChild("IMG_pointcursor"));
            cursor.startAnimation("loop", false);
            cursor.setDisp(true);
        } else if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setTerm();
            GfMenuObjUtil::setPointSpeedRate(ui::UIObjectAcc(acc.searchChild("LAY_dr_main")), 1.0f);
            GfMenuObjOperationInfo::remove(acc.searchChild("LAY_scale"), acc.searchChild("LAY_dr_main"), 0, 0);
            GfMenuObjCharSelect::returnSubMenu();
            GfMenuObject::returnFSSubLayer(m_owner);
        }
        break;
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        setFadeOut(handle);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjDrKizunaRing::seqExecSkill() {
    GfGameUtil::execDriverSkillLevelUp(GfMenuReference::getReferenceDriverID(0), GfMenuReference::getReferenceNumber(0),
                                       GfMenuReference::getReferenceNumber(1), GfMenuReference::getReferenceNumber(2) != 0);
    return true;
}

void GfMenuObjDrKizunaRing::SkillDetailListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        setupSkillDetail(acc);
        m_owner->m_detailOpen = false;
        acc.setDisp(false);
        break;
    case 0x21: {
        ui::UIObjectAcc caption(acc.searchChild("LAY_caption"));
        caption.setDisp(true);
        const char* name = isScreenLR(m_owner->m_selected % 6) ? "drskillinfo2_2" : "drskillinfo2_1";
        mm::Rect<short> rect;
        ui::UIObjectAcc main(owner.searchChild("LAY_dr_main"));
        main.getLayoutRect(name, rect);
        mm::Pnt<short> pos;
        pos.x = rect.x;
        pos.y = rect.y;
        acc.setPos(pos);
        if (m_owner->m_unlockLevel == 0) {
            ui::UIObjectAcc skill(acc.searchChild("LAY_skif_skill"));
            skill.setDisp(true);
            ui::UIObjectAcc lock(acc.searchChild("LAY_skif_lock"));
            lock.setDisp(false);
        } else {
            ui::UIObjectAcc skill(acc.searchChild("LAY_skif_skill"));
            skill.setDisp(false);
            ui::UIObjectAcc lock(acc.searchChild("LAY_skif_lock"));
            lock.setDisp(true);
        }
        if (!m_owner->m_detailOpen) {
            setFadeIn(handle);
            m_owner->m_detailOpen = true;
        }
        unsigned int driver = GfMenuReference::getReferenceDriverID(0);
        unsigned int line = GfMenuReference::getReferenceNumber(0);
        unsigned int level = GfMenuReference::getReferenceNumber(1);
        int round = GfMenuReference::getReferenceNumber(2);
        ui::UIObjectAcc icon(acc.searchChild("IMG_skif_icon@01"));
        ui::UIObjectAcc base(acc.searchChild("IMG_skif_icon_base@01"));
        if (!GfDataDriverSkill::isSkillUnlock(driver, line, level, round != 0)) {
            icon.setMulColor("white");
            base.setMulColor("gray");
        } else if (GfDataDriverSkill::getSkill(driver, line, level, round != 0) == 0) {
            icon.setMulColor("black");
            base.setMulColor("gray");
        } else {
            icon.setMulColor("white");
            base.setMulColor("white");
        }
        break;
    }
    case 0x22:
        if (m_owner->m_detailOpen) {
            m_owner->m_detailOpen = false;
            setFadeOut(handle);
        }
        break;
    case 0x101:
        if (!m_owner->m_detailOpen) {
            setFadeIn(handle);
            m_owner->m_detailOpen = true;
        }
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}
}  // namespace gf
