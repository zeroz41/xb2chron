#include "classes/gf/GfMenuObjMainMenu2.h"
#include "gf/GfMenuTypes.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/GfMenuObjBlKizunaRing.h"
#include "classes/gf/GfMenuObjBlKizunaRing/MainListener.h"
#include "classes/gf/GfMenuObjBlKizunaRing/RingListener.h"
#include "classes/gf/GfMenuObjBlKizunaRing/RingPadListener.h"
#include "classes/gf/GfMenuObjBlKizunaRing/SkillDetailListener.h"
#include "classes/gf/GfMenuObjBlKizunaRing/BladeSkillInfoListener.h"
#include "mm/mtl/FixStr.h"
#include "gf/GfDataAchievement.h"
#include "mm/Pnt.h"
#include "gf/GfKizunaringBlade.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfMenuAchievementAdapter.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/ui/UICtrlFrame.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "ui/EventData.h"

namespace gmo_bl_kizuna_ring {
float rateTbl[2] = {1.0f, 0.5f};
}

namespace gf {

GfMenuObjBlKizunaRing::GfMenuObjBlKizunaRing(unsigned int handle)
    : GfMenuObject(handle), m_ringList(nullptr), m_ringFrame(nullptr), pad_38(false), m_detailOpen(false),
      m_referenceNumber(0), m_selected(-1), m_subContext(nullptr), m_achieveKind(0), m_context(nullptr),
      m_achievements(), m_achieveIndex(0), m_seq(this), m_achieveStep(0), m_completeStep(0), m_mode(0), m_mercenary(0),
      m_callContext(nullptr), m_itemList(nullptr), pad_450(0), m_achieveFlags(0), m_voice(nullptr), m_voiceBlade(0),
      m_voiceRequest(-1) {
    m_context = GfMenuCallContext::create();
}

GfMenuObjBlKizunaRing::~GfMenuObjBlKizunaRing() {
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

void GfMenuObjBlKizunaRing::initialize() {
    {
        GfMenuTypes::Param param;
        if (GfMenuObject::getFSLayerParam(m_fsLayer, param)) {
            m_mode = param.m_halves.m_type;
            m_mercenary = param.m_value;
            GfMenuObject::removeFSLayerParam(m_fsLayer);
        } else {
            m_mode = 0;
        }
    }
    ui::UIObjectAcc acc(m_handle);
    unsigned int handle = acc.searchChild("LAY_main");
    {
#line 193
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::attachExternalCall(0x6A, handle);
    handle = acc.searchChild("LAY_kizunaring");
    {
#line 199
        RingListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) RingListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_kizunaring_base");
    {
#line 203
        RingPadListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) RingPadListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_skillinfo");
    {
#line 207
        SkillDetailListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SkillDetailListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_skillstock_info");
    {
#line 217
        BladeSkillInfoListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) BladeSkillInfoListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_ringList = ui::UISelectObjList::create(create);
    m_callContext = GfMenuCallContext::create();
    m_itemList = GfMenuItemList::create();
    {
        ui::UIListInfoBase::SetupParam param;
        m_itemList->setup(getAllocator(ALLOCATOR(0)), param);
    }
    m_subContext = GfMenuCallContext::create();
    GfMenuObject::disableInput(acc.searchChild("LAY_kizunaring"));
    GfMenuObject::disableInput(acc.searchChild("LAY_kizunaring_base"));
    if (m_mode == 0) {
        GfMenuObjMainMenu2::setCloseKeyEnable(false);
    }
    GfMenuObject::initialize();
}

void GfMenuObjBlKizunaRing::finalize() {
    if (m_voice != nullptr) {
        GfGameVoice::playStop(m_voice);
        m_voice = nullptr;
    }
    if (m_voiceRequest != -1) {
        GfGameVoice::fn_71002F1F64(m_voiceRequest);
        m_voiceRequest = -1;
    }
    GfMenuObject::finalize();
}

void GfMenuObjBlKizunaRing::update() {
    m_seq.update();
    if (m_voiceRequest != -1 && !GfReqSmallCom::get()->isValid(reinterpret_cast<GF_SCOM_HANDLE*>(m_voiceRequest))) {
        m_voiceRequest = -1;
    }
    GfMenuObject::update();
}

bool GfMenuObjBlKizunaRing::seqWaitVoice() {
    ui::UIObjectAcc acc(m_handle);
    sendEvent(acc.searchChild("LAY_main"), 0x21, 0);
    return true;
}

bool GfMenuObjBlKizunaRing::seqEnd() {
    ui::UIObjectAcc acc(m_handle);
    refreshRing(acc);
    ui::UIObjectAcc cursor(acc.searchChild("IMG_kizunacursor"));
    cursor.setDisp(true);
    cursor.startAnimation("loop", false);
    GfMenuObject::enableInput(acc.searchChild("LAY_kizunaring_base"));
    if (m_mode == 0) {
        GfMenuObjMainMenu2::setCloseKeyEnable(true);
    }
    sendEvent(acc.searchChild("LAY_kizunaring"), 0x21, 0);
    return true;
}

bool GfMenuObjBlKizunaRing::seqWait() {
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc base(acc.searchChild("LAY_kizunaring_base"));
    GfMenuObject::enableInput(base.m_handle);
    return true;
}

void GfMenuObjBlKizunaRing::BladeSkillInfoListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild("TXT_stocknum"), 0x10, 0, 0, 0, true);
        GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild("TXT_stockmax"), 0x11, 0, 0, 0, false);
        acc.setDisp(true);
    } else {
        ui::UIObjectListener::reciveEvent(event, handle);
    }
}

bool GfMenuObjBlKizunaRing::procAchieve(unsigned int handle, GfMenuObjBlKizunaRing* ring) {
    unsigned int blade = GfMenuReference::getReferenceBladeID(0);
    if (fn_71002EE72C(blade)) {
        fn_71002EE640(blade);
        ring->m_achieveKind = 0;
        ring->m_achieveFlags = 0;
    } else {
        ring->m_achieveKind = 0;
        ring->m_achieveFlags = 0;
        if (getAchievementList(ring->m_achievements, ring->m_achieveKind, ring->m_achieveFlags) == 0) {
            return false;
        }
    }
    ring->m_achieveStep = 1;
    ring->m_completeStep = 0;
    ring->m_seq.clear();
    ring->m_seq.addJob(&GfMenuObjBlKizunaRing::seqAchieve);
    if (ring->m_mode == 0) {
        GfMenuObjMainMenu2::disableCharChange();
    }
    ui::UIObjectAcc cursor(handle, "IMG_kizunacursor");
    cursor.setDisp(false);
    {
        ui::UIObjectAcc acc(handle);
        GfMenuObject::disableInput(acc.searchChild("LAY_kizunaring_base"));
    }
    if (ring->m_mode == 0) {
        GfMenuObjMainMenu2::setCloseKeyEnable(false);
    }
    return true;
}

unsigned int GfMenuObjBlKizunaRing::getAchievementList(mm::mtl::FixedVector<Achievement, 50>& list, unsigned int& kind,
                                                       unsigned int& flags) {
    unsigned int blade = GfMenuReference::getReferenceBladeID(0);
    list.clear();
    for (int level = 4; level >= 0; level--) {
        for (int line = 9; line >= 0; line--) {
            if (GfKizunaringBlade::getReleaseAchievement(blade, line, level + 1) == 3) {
                if (line == 9) {
                    for (int i = 8; i >= 0; i--) {
                        if (GfKizunaringBlade::getReleaseAchievement(blade, i, level + 1) == 1) {
                            list.push_back(Achievement(i, level + 1, 1));
                        }
                    }
                    if (level < 4) {
                        list.push_back(Achievement(9, level + 2, 1));
                    }
                    kind = 1;
                    flags |= 1;
                } else {
                    kind = 2;
                    flags |= 2;
                }
                list.push_back(Achievement(line, level + 1, 3));
            }
        }
    }
    return list.size();
}

void GfMenuObjBlKizunaRing::dispDetail(ui::UIObjectAcc& acc, unsigned int blade) {
    int line = GfMenuReference::getReferenceNumber(0);
    int level = GfMenuReference::getReferenceNumber(1);
    unsigned short type = GfKizunaringBlade::getReleaseAchievement(blade, GfMenuReference::getReferenceNumber(0),
                                                                   GfMenuReference::getReferenceNumber(1)) == 0
                              ? 0x22
                              : 0x21;
    ACHIEVEMENT_TYPE achievement;
    unsigned int index;
    if (GfDataAchievement::getAchievementType(achievement, index, GfMenuReference::getReferenceNumber(0))) {
        if (achievement == 3 && line == 9 && level == 1) {
            type = 0x22;
        }
    }
    unsigned int handle = acc.searchChild("LAY_skillinfo");
    ui::EventData event;
    event.m_type = type;
    ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

void GfMenuObjBlKizunaRing::movePointer(unsigned int handle, int index, ui::UISelectObjList* list) {
    GfMenuObject::setupInputSelection(handle, index, list->getSize());
    mm::Pnt<short> pos;
    {
        ui::UIObjectAcc acc(list->getContents(index));
        acc.getPosCenter(pos);
    }
    GfMenuObject::changePointerPos(handle, pos);
}

void GfMenuObjBlKizunaRing::openForMercenary(unsigned int handle, unsigned int value, unsigned short group) {
    OpenParam param;
    param.m_mode = 1;
    param.m_value = value;
    registOpenParam(param);
    GfMenuObject::changeFSSubLayer(handle, group, GfMenuObject::getMenuLayerID(0x22), true);
}

bool GfMenuObjBlKizunaRing::attach(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x6A));
    bool attached = false;
    if (acc.m_object != nullptr) {
        GfMenuObject::startCallContext(context, 0x6A, acc.m_handle);
        attached = true;
    }
    return attached;
}

}  // namespace gf
