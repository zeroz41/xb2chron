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
#include "gf/GfDataBlade.h"
#include "gf/GfItemUtil.h"
#include "gf/GfKizunaringUtil.h"
#include "gf/GfQuestReward.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjPopup.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfMenuAchievementAdapter.h"
#include "classes/gf/GfMenuAdapterManager.h"
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
#include "ui/UIStr.h"
#include "mm/Rect.h"

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
        GfGameVoice::playStop(reinterpret_cast<GF_SCOM_HANDLE*>(m_voiceRequest));
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

bool GfMenuObjBlKizunaRing::seqComplete() {
    unsigned int blade = GfMenuReference::getReferenceBladeID(0);
    if (GfDataBlade::isKizunaringComplete(blade)) {
        return true;
    }
    unsigned int max = GfDataBlade::getKizunaringMax(blade);
    if (max > GfDataBlade::getKizunaringCompleteNum(blade)) {
        return true;
    }
    ui::UIObjectAcc root(m_handle);
    ui::UIObjectAcc complete(root.searchChild("LAY_complete"));
    switch (m_completeStep) {
    case 0: {
        complete.setDisp(true);
        ui::UIObjectAcc image(complete.searchChild("IMG_complete"));
        image.startAnimation("fade_in", false);
        ui::UIObjectAcc text(complete.searchChild("TXT_complete"));
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "mnu89_complete_telop";
        param.m_motion = "fade_in";
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(text.m_handle, param, nullptr);
        GfMenuObjUtil::playJingle(0x10);
        m_voiceRequest = SCOM_FIELD_VOICE::createAchievementAll(blade);
        m_completeStep++;
        break;
    }
    case 1: {
        ui::UIObjectAcc image(complete.searchChild("IMG_complete"));
        if (!image.isPlayingAnimation()) {
            complete.setDisp(false);
            m_itemList->clear();
            GfQuestReward reward;
            if (!GfKizunaringUtil::getCompleteKizunaringReward(reward, blade)) {
                return true;
            }
            for (int i = 8; i < 12; i++) {
                unsigned short id = reward.m_items[i].m_low;
                if (id != 0) {
                    MenuItemInfo info;
                    info.m_type = GfItemUtil::getType(id);
                    info.m_id = id;
                    info.m_count = reward.m_items[i].m_high;
                    m_itemList->addContents(info);
                }
            }
            m_callContext->reset();
            GfMenuObjCommonText::openGetItem(m_callContext, m_itemList);
            m_completeStep++;
        }
        break;
    }
    case 2:
        if (m_callContext->isTerm()) {
            GfDataBlade::setKizunaringComplete(blade);
            m_completeStep = 0;
            return true;
        }
        break;
    }
    return false;
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

void GfMenuObjBlKizunaRing::SkillDetailListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        setupSkillDetail(acc);
        acc.setDisp(false);
        break;
    case 0x21: {
        unsigned int blade = GfMenuReference::getReferenceBladeID(0);
        unsigned int line = GfMenuReference::getReferenceNumber(0);
        unsigned int level = GfMenuReference::getReferenceNumber(1);
        const char* layout = line < 4 || line == 9 ? "blskillinfo2_2" : "blskillinfo2_1";
        mm::Rect<short> rect;
        ui::UIObjectAcc main(owner.searchChild("LAY_main"));
        main.getLayoutRect(layout, rect);
        mm::Pnt<short> pos;
        pos.x = rect.x;
        pos.y = rect.y;
        acc.setPos(pos);
        ui::UIObjectAcc title(acc.searchChild("LAY_questtitle"));
        ui::UIObjectAcc title2(acc.searchChild("LAY_questtitle2"));
        ui::UIObjectAcc clear(acc.searchChild("LAY_clear"));
        ui::UIObjectAcc normal(acc.searchChild("LAY_normal"));
        ui::UIObjectAcc small(acc.searchChild("LAY_small"));
        unsigned char* bdat;
        unsigned int id;
        ui::UIObjectAcc icon(acc.searchChild("IMG_skill_icon@01"));
        ui::UIObjectAcc base(acc.searchChild("IMG_skill_base@01"));
        unsigned int state = GfKizunaringBlade::getReleaseAchievement(blade, line, level);
        if (state == 4 || state == 5 || (GfMenuObjUtil::isValidExpansion(3) && state == 3)) {
            title.setDisp(false);
            bool text = false;
            if (GfDataBlade::getTaskResultMessage(bdat, id, blade, line, level)) {
                ui::UIStr str(bdat, id);
                text = str.size() != 0;
            }
            title2.setDisp(text);
            clear.setDisp(false);
            if (text) {
                normal.setDisp(true);
                small.setDisp(false);
            } else {
                normal.setDisp(false);
                small.setDisp(true);
            }
            icon.setMulColor("white");
            base.setMulColor("white");
        } else {
            bool text = false;
            if (GfDataBlade::getTaskTitleMessage(bdat, id, blade, line, level)) {
                ui::UIStr str(bdat, id);
                text = str.size() != 0;
            }
            title.setDisp(text);
            title2.setDisp(false);
            clear.setDisp(true);
            if (text) {
                normal.setDisp(true);
                small.setDisp(false);
            } else {
                normal.setDisp(false);
                small.setDisp(true);
            }
            if (line == 9 || state == 0 || state == 1) {
                icon.setMulColor("white");
            } else {
                icon.setMulColor("black");
            }
            base.setMulColor("gray");
        }
        if (!m_owner->m_detailOpen) {
            m_owner->m_detailOpen = true;
            GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeIn(handle, 1, 0));
        }
        break;
    }
    case 0x22:
        if (m_owner->m_detailOpen) {
            m_owner->m_detailOpen = false;
            GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeOut(handle, 2, 0));
        }
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
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

bool GfMenuObjBlKizunaRing::seqAchieve() {
    ui::UIObjectAcc root(m_handle);
    mm::mtl::FixStr<32> name;
    unsigned int blade = GfMenuReference::getReferenceBladeID(0);
    switch (m_achieveStep) {
    case 1:
        if (m_achievements.empty()) {
            if (getAchievementList(m_achievements, m_achieveKind, m_achieveFlags) == 0) {
                m_achieveStep = 0;
                sendEvent(root.searchChild("LAY_main"), 0x21, 0);
                return true;
            }
            m_achieveStep = 1;
        } else {
            const Achievement& achievement = m_achievements.back();
            short state = achievement.m_state;
            unsigned short line = achievement.m_line;
            unsigned int index = line * 5 + (achievement.m_level - 1);
            if (state != 1 || index < 45) {
                m_achieveIndex = index;
                if (index <= 44) {
                    name.format("IMG_node_eff@%02d", index + 6);
                } else {
                    name.format("IMG_lock_eff@%02d", index - 44);
                }
                ui::UIObjectAcc eff(root.searchChild(name.m_str));
                eff.startAnimation(state == 1 ? "skill_open" : "skill_learn", false);
                if (state == 3) {
                    GfMenuObjUtil::playSE(0xF);
                    if (line != 9) {
                        m_voiceBlade = line;
                    }
                }
            }
            m_achieveStep = 2;
        }
        return false;
    case 2: {
        unsigned int index = m_achieveIndex;
        if (index <= 44) {
            name.format("IMG_node_eff@%02d", index + 6);
        } else {
            name.format("IMG_lock_eff@%02d", index - 44);
        }
        ui::UIObjectAcc eff(root.searchChild(name.m_str));
        if (m_achievements.size() != 1 || !eff.isPlayingAnimation()) {
            const Achievement& achievement = m_achievements.back();
            unsigned short line = achievement.m_line;
            unsigned short level = achievement.m_level;
            short state = achievement.m_state;
            m_achievements.pop_back();
            if (m_achieveIndex > 44 && state == 3) {
                const char* anims[] = {"linea", "lineb", "linec", "lined", "linee"};
                unsigned int ring = m_achieveIndex - 45;
                if (ring < 5) {
                    ui::UIObjectAcc bg(root.searchChild("IMG_kizunabg_eff"));
                    bg.startAnimation(anims[ring], false);
                }
                GfMenuObjUtil::playSE(0x10);
            }
            if (state == 3) {
                GfKizunaringBlade::releaseAchievement(blade, line, level);
                GfMenuObjPopup::OpenParam param;
                param.m_type = 4;
                param.m_value0 = blade;
                param.m_value1 = line;
                param.m_value2 = level;
                GfMenuObjPopup::remove(param);
            } else {
                GfKizunaringBlade::orderAchievement(blade, line, level);
            }
            refreshRing(root);
            m_achieveStep = 1;
        }
        return false;
    }
    default:
        return true;
    }
}

void GfMenuObjBlKizunaRing::RingListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        setupRing(acc);
        setupRingList(acc, m_owner->m_ringList);
        refreshRing(acc);
        {
            ui::UIInputPointer::SelectionSetup setup;
            setup.m_list = m_owner->m_ringList;
            setup.m_sizeW = 0x10;
            setup.m_sizeH = 0x10;
            ui::UIObjectAcc(owner.searchChild("IMG_cursorarea")).getRect(setup.m_rect, 2);
            GfMenuObject::setupPointerSelection(handle, setup);
        }
        mm::Pnt<short> pos;
        ui::UIObjectAcc(m_owner->m_ringList->getContents(0)).getPosCenter(pos);
        GfMenuObject::changePointerPos(handle, pos);
        m_firstSelect = 1;
        {
            ui::UICtrlFrame::Setting setting;
            setting.m_contentName = "LAY_kizunabg";
            setting.m_viewName = "IMG_maskbg";
            setting.m_centerName = "IMG_kizunacursor";
            setting.m_distance = 0xC;
            setting.m_list = m_owner->m_ringList;
            m_owner->m_ringFrame = ui::UICtrlFrame::create(handle, setting);
        }
        if (m_owner->m_ringFrame != nullptr) {
            m_owner->m_ringFrame->setupEventHanding(handle, 3);
        }
        ui::UIObjectAcc cursor(acc.searchChild("IMG_kizunacursor"));
        cursor.setDisp(false);
        GfMenuObject::setupInputSelection(handle, -1, m_owner->m_ringList->getSize());
        GfMenuObject::disableInput(handle);
        break;
    }
    case 6: {
        int index = event.m_param0;
        unsigned int blade = GfMenuReference::getReferenceBladeID(0);
        if (index >= 1) {
            unsigned int column = index % 10U;
            int level = index / 10U + 1;
            if (column == 0) {
                m_owner->m_referenceNumber = level;
                GfMenuReference::setReferenceNumber(0, 9);
                GfMenuReference::setReferenceNumber(1, m_owner->m_referenceNumber);
            } else {
                GfMenuReference::setReferenceNumber(0, column - 1);
                GfMenuReference::setReferenceNumber(1, level);
                m_owner->m_referenceNumber = 0;
            }
            dispDetail(owner, blade);
            unsigned int base = owner.searchChild("LAY_kizunaring_base");
            if (column < 5) {
                GfMenuObjOperationInfo::changeText(base, 9, false);
                GfMenuObjOperationInfo::changeText(base, 10, false);
            } else {
                GfMenuObjOperationInfo::changeText(base, 9, true);
                GfMenuObjOperationInfo::changeText(base, 10, true);
            }
        } else {
            GfMenuReference::setReferenceNumber(0, 9);
            GfMenuReference::setReferenceNumber(1, 1);
            sendEvent(owner.searchChild("LAY_skillinfo"), 0x22, 0);
            if (index < 0) {
                break;
            }
        }
        m_owner->m_selected = index;
        if (m_firstSelect == 1) {
            m_firstSelect = 0;
        } else {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 10: {
        ui::UIObjectAcc cursor(acc.m_handle, "IMG_kizunacursor");
        short x = event.m_paramShort[0];
        if (m_owner->m_ringFrame != nullptr) {
            bool select = event.m_paramShort[2] == 1;
            m_owner->m_ringFrame->movePoint(mm::Pnt<short>(x, event.m_paramShort[1]), select);
        } else {
            mm::Pnt<short> pos(x, event.m_paramShort[1]);
            cursor.setPosCenter(pos);
        }
        break;
    }
    case 0x21:
        GfMenuObject::enableInput(handle);
        GfMenuObject::enableInput(owner.searchChild("LAY_kizunaring_base"));
        GfMenuObjOperationInfo::add(acc.searchChild("LAY_kizunaring_base"), handle, 0, 0);
        if (m_owner->m_mode == 0 && GfMenuObjMainMenu2::isOpenCharMenu()) {
            GfMenuObjMainMenu2::openCharChange(acc.m_handle, 1, false);
        }
        break;
    case 0x22:
        GfMenuObject::disableInput(handle);
        GfMenuObject::disableInput(owner.searchChild("LAY_kizunaring_base"));
        GfMenuObjOperationInfo::remove(acc.searchChild("LAY_kizunaring_base"), handle, 0, 0);
        break;
    case 0x140: {
        unsigned int blade = event.m_param0;
        GfMenuReference::setReferenceBladeID(0, blade);
        refreshRing(acc);
        if (m_owner->m_voice != nullptr) {
            GfGameVoice::playStop(m_owner->m_voice);
            m_owner->m_voice = nullptr;
        }
        if (m_owner->m_voiceRequest != -1) {
            GfGameVoice::playStop(reinterpret_cast<GF_SCOM_HANDLE*>(m_owner->m_voiceRequest));
            m_owner->m_voiceRequest = -1;
        }
        if (procAchieve(owner.searchChild("LAY_main"), m_owner) && m_owner->m_mode == 0) {
            GfMenuObjOperationInfo::remove(acc.searchChild("LAY_kizunaring_base"), handle, 0, 0);
        }
        dispDetail(owner, blade);
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjBlKizunaRing::setupRing(ui::UIObjectAcc& acc) {
    mm::mtl::FixStr<32> name;
    GfMenuAdapterManager::beginAddAfter();
    for (int level = 0; level < 5; level++) {
        for (int line = 0; line < 10; line++) {
            int node = level + line * 5 + 1;
            name.format("IMG_node_icon@%02d", node);
            if (acc.searchChild(name.m_str) != 0) {
                unsigned int handle = acc.searchChild(name.m_str);
                unsigned short kizunaLine = line == 0 ? 9 : line - 1;
                GfMenuAchievementAdapter::createFromReferenceBlade(handle, 0xB, 0, kizunaLine, level + 1, true);
                name.format("IMG_node_base@%02d", node);
                if (acc.searchChild(name.m_str) != 0) {
                    GfMenuAchievementAdapter* adapter = GfMenuAchievementAdapter::createFromReferenceBlade(
                        acc.searchChild(name.m_str), 0xC, 0, kizunaLine, level + 1, true);
                    name.format("IMG_node_frame@%02d", node);
                    adapter->m_rowHandle = acc.searchChild(name.m_str);
                }
            }
        }
    }
    for (int level = 1; level <= 5; level++) {
        name.format("IMG_lock_icon@%02d", level);
        GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild(name.m_str), 0x18, 0, 9, level, true);
    }
    GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjBlKizunaRing::setupRingList(ui::UIObjectAcc& acc, ui::UISelectObjList* list) {
    mm::mtl::FixStr<32> name;
    list->clear();
    for (int level = 0; level < 5; level++) {
        for (int line = 0; line < 10; line++) {
            name.format("LAY_spot@%02d", level + line * 5 + 1);
            unsigned int handle = acc.searchChild(name.m_str);
            if (handle != 0) {
                list->addObject(handle);
            }
        }
    }
}

void GfMenuObjBlKizunaRing::refreshRing(ui::UIObjectAcc& acc) {
    unsigned int blade = GfMenuReference::getReferenceBladeID(0);
    mm::mtl::FixStr<32> name;
    for (int level = 0; level < 5; level++) {
        for (int line = 0; line < 10; line++) {
            int node = level + line * 5 + 1;
            name.format("IMG_node_icon@%02d", node);
            ui::UIObjectAcc icon(acc.searchChild(name.m_str));
            if (icon.m_object != nullptr) {
                name.format("IMG_node_base@%02d", node);
                ui::UIObjectAcc base(acc.searchChild(name.m_str));
                if (base.m_object != nullptr) {
                    unsigned int state =
                        GfKizunaringBlade::getReleaseAchievement(blade, line == 0 ? 9 : line - 1, level + 1);
                    if (state == 0 || state == 1) {
                        icon.setMulColor("white");
                        base.setMulColor("gray");
                    } else if (state == 4 || state == 5) {
                        icon.setMulColor("white");
                        base.setMulColor("white");
                    } else {
                        icon.setMulColor("black");
                        base.setMulColor("gray");
                    }
                }
            }
        }
    }
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

void GfMenuObjBlKizunaRing::RingPadListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::setupInputSelection(handle, 0, 10);
        GfMenuObject::disableInput(handle);
        break;
    case 6:
        break;
    case 8: {
        int next;
        int index;
        switch (event.m_param1) {
        case 2: {
            unsigned int main = owner.searchChild("LAY_main");
            ui::EventData close;
            close.m_type = 0x22;
            ui::UIManager::get()->requestObjectEvent(main, close, 0.0f);
            GfMenuObject::disableInput(handle);
            if (m_owner->m_mode == 0) {
                GfMenuObjMainMenu2::disableCharChange();
            }
            GfMenuObjUtil::playSECommonCancel();
            return;
        }
        // case 10 before case 9 and index at the outer scope: the original's branch layout (case 9's tail merge) and its
        // case 0xB test (one `||` without a scope-exit selector) need both
        case 10: {
            index = m_owner->m_selected;
            if (index < 0) {
                return;
            }
            unsigned int row = index / 10U;
            unsigned int column = index % 10U;
            if (column < 5) {
                if (index < 10U) {
                    return;
                }
                next = (row - 1) * 10 + column;
            } else {
                if (row + 1 > 4) {
                    return;
                }
                next = (row + 1) * 10 + column;
            }
            break;
        }
        case 9: {
            index = m_owner->m_selected;
            if (index < 0) {
                return;
            }
            unsigned int row = index / 10U;
            unsigned int column = index % 10U;
            if (!(column >= 5)) {
                if (row + 1 > 4) {
                    return;
                }
                next = (row + 1) * 10 + column;
            } else {
                if (index < 10U) {
                    return;
                }
                next = (row - 1) * 10 + column;
            }
            break;
        }
        case 0xB: {
            index = m_owner->m_selected;
            if (index < 0) {
                return;
            }
            if (index % 10U < 9) {
                next = index + 1;
            } else {
                return;
            }
            break;
        }
        case 0xC: {
            index = m_owner->m_selected;
            if (index < 0 || index % 10U == 0) {
                return;
            }
            next = index - 1;
            break;
        }
        default:
            return;
        }
        GfMenuObject::changePointerPos(owner.searchChild("LAY_kizunaring"), mm::Pnt<short>(0, 0));
        movePointer(owner.searchChild("LAY_kizunaring"), next, m_owner->m_ringList);
        GfMenuObjUtil::playSECommonTab();
        sendEvent(handle, 0x101, 0);
        break;
    }
    case 0x101:
        m_owner->m_seq.clear();
        m_owner->m_seq.addWait(1);
        m_owner->m_seq.addJob(&GfMenuObjBlKizunaRing::seqWait);
        GfMenuObject::disableInput(handle);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjBlKizunaRing::setupSkillDetail(ui::UIObjectAcc& acc) {
    GfMenuAdapterManager::beginAddAfter();
    GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_questtitle"), 0x16, 0, 0, 1, false);
    GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_questtitle2"), 0x17, 0, 0, 1, false);
    GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_achinum"), 0x12, 0, 0, 1, false);
    GfMenuAchievementAdapter* count =
        GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_achimax"), 0x13, 0, 0, 1, false);
    if (count != nullptr) {
        count->m_rowHandle = acc.searchChild("LAY_count");
    }
    GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("LAY_neta"), 0x19, 0, 0, 1, false);
    mm::mtl::FixStr<32> name;
    for (int i = 1; i < 3; i++) {
        name.format("TXT_questinfo2@%02d", i);
        GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.m_str), 3, 0, 0, 1, false);
        name.format("TXT_skillname@%02d", i);
        GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.m_str), 2, 0, 0, 1, false);
        name.format("IMG_skill_icon@%02d", i);
        GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.m_str), 0xB, 0, 0, 1, false);
        name.format("IMG_skill_base@%02d", i);
        GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.m_str), 0xC, 0, 0, 1, false);
        name.format("IMG_idea_icon@%02d", i);
        GfMenuAchievementAdapter* idea = GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(
            acc.searchChild(name.m_str), 0x15, 0, 0, 1, false);
        if (idea != nullptr) {
            name.format("LAY_idea@%02d", i);
            idea->m_rowHandle = acc.searchChild(name.m_str);
        }
    }
    GfMenuAdapterManager::endAddAfter();
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
