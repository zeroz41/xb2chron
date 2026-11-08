#include "gf/FileStaticVec3.h"
#include "classes/gf/GfMenuObjNpcTelop.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjHitonowa.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Rect.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"

namespace gf {

// 2.0.0's symbols name it (lbl_7100EAB8D0)
GfMenuObjNpcTelop::OpenParam GfMenuObjNpcTelop::s_OpenParam;
// 2.0.0's symbols name it (lbl_7100EAB928)
bool GfMenuObjNpcTelop::s_Open;

GfMenuObjNpcTelop::GfMenuObjNpcTelop(unsigned int handle)
    : GfMenuObject(handle), m_selectList(nullptr), m_idList(nullptr), m_seq0(this), m_seq1(this) {
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_selectList = ui::UISelectObjList::create(create);
    m_idList = GfMenuIDList::create();
    if (m_idList != nullptr) {
        ui::UIListInfoBase::SetupParam param;
        param.m_pageRowSize = 3;
        m_idList->setup(getAllocator(ALLOCATOR(0)), param);
        m_idList->clear();
    }
}

GfMenuObjNpcTelop::~GfMenuObjNpcTelop() {
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
}

void GfMenuObjNpcTelop::open(GfMenuCallContext* context, const OpenParam& param) {
    if (GfMenuObjUtil::isValidExpansion(3) && GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8C));
        if (acc.m_object != nullptr) {
            s_OpenParam = param;
            ui::UIObjectAcc dummy(acc.searchSibiling("LAY_dummy"));
            GfMenuObject::sendOpenEvent(dummy.m_handle, 0, 0.0f);
            GfMenuObject::startCallContext(context, 0x8C, dummy.m_handle);
        }
    }
}

GfMenuObjNpcTelop::OpenParam* GfMenuObjNpcTelop::getOpenParam() {
    return &s_OpenParam;
}

bool GfMenuObjNpcTelop::isOpen() {
    return s_Open;
}

void GfMenuObjNpcTelop::initialize() {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc acc(m_handle, "LAY_main");
        if (acc.m_object != nullptr) {
            GfMenuObject::attachExternalCall(0x8C, acc.m_handle);
#line 154
            MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
            GfMenuObject::initialize();
            GfMenuAdapterManager::beginAddAfter();
            unsigned int count = acc.countChild("LAY_char@%02d", 1);
            {
                mm::mtl::FixStr<32> name;
                for (unsigned int i = 0; i < count; i++) {
                    name.format("IMG_char_face@%02d", i + 1);
                    GfMenuCharDataAdapter::createFromNpcIDList(acc.searchChild(name.m_str), 0x6C, m_idList, i, false);
                }
            }
            GfMenuAdapterManager::endAddAfter();
            ui::UIObjectAcc dummy(m_handle, "LAY_dummy");
            if (dummy.m_object != nullptr) {
#line 179
                HitonowaListener* dummyListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) HitonowaListener(this);
                dummyListener->m_RefCount = 1;
                ui::UIEventManager::get()->registObjectListener(dummy.m_handle, dummyListener);
                if (dummyListener != nullptr) {
                    dummyListener->release();
                }
            }
        }
    }
}

void GfMenuObjNpcTelop::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjNpcTelop::update() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return;
    }
    m_seq0.update();
    m_seq1.update();
    GfMenuObject::update();
}

bool GfMenuObjNpcTelop::seqWaitStream() {
    if (m_idList != nullptr) {
        ui::UIObjectAcc acc(m_handle, "LAY_main");
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < m_idList->getSize(); i++) {
            name.format("IMG_char_face@%02d", i + 1);
            ui::UIObjectAcc face(acc.m_handle, name.m_str);
            if (face.isStreaming()) {
                return false;
            }
        }
        if (++m_waitCount > 60) {
            return true;
        }
    }
    return true;
}

bool GfMenuObjNpcTelop::seqWaitCloseFullscreen() {
    return !GfMenuManager::isOpenFullScreen();
}

bool GfMenuObjNpcTelop::seqEndHitonowa() {
    ui::UIObjectAcc dummy(m_handle, "LAY_dummy");
    GfMenuObject::sendCloseEvent(dummy.m_handle, 0, 0.0f);
    return true;
}

bool GfMenuObjNpcTelop::seqStart() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    float delay = 0.0f;
    for (unsigned int i = 0; i < m_idList->getSize(); i++) {
        ui::EventData event;
        event.m_type = 0x100;
        event.m_param0 = i;
        if (i != 0) {
            delay = i * 0.1f;
        }
        GfMenuObject::sendEvent(acc.m_handle, event, delay);
    }
    return true;
}

void GfMenuObjNpcTelop::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        acc.setSuspend(true);
        break;
    case 8:
        if (event.m_param1 == 1) {
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::close();
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
        }
        break;
    case 0xC: {
        unsigned int index = event.m_param0;
        if (m_state == 1) {
            if (s_OpenParam.m_flag == 0) {
                SCOM_FIELD_VOICE::createHitonowaGet();
            }
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjOperationInfo::open(acc.m_handle, 0, 0, 0);
            GfMenuObjOperationInfo::setGuideDisp(false);
        } else {
            mm::mtl::FixStr<32> name;
            for (unsigned int i = 0; i < m_owner->m_idList->getSize(); i++) {
                name.format("IMG_char_face@%02d", i + 1);
                ui::UIObjectAcc face(acc.m_handle, name.m_str);
                face.setImageIndex(0);
            }
            m_owner->m_idList->clear();
            GfMenuObject::termCallContext(acc.m_handle);
            acc.setDisp(false);
            acc.setSuspend(true);
        }
        mm::mtl::FixStr<32> name;
        name.format("IMG_char_get_eff@%02d", index + 1);
        ui::UIObjectAcc eff(acc.m_handle, name.m_str);
        GfMenuObject::hookAnimationEvent(0, eff.m_handle, 0);
        break;
    }
    case 0x21:
        if (s_OpenParam.m_entries.size() != 0 && m_owner->m_selectList != nullptr) {
            m_owner->m_selectList->clear();
            m_owner->m_idList->clear();
            mm::mtl::FixStr<32> name;
            {
                ui::UIObjectAcc base(acc.m_handle, "IMG_telop_base");
                base.startAnimation(s_OpenParam.m_flag == 0 ? "start_success" : "start_failed", false);
                acc.setDispChild(s_OpenParam.m_flag == 0, "LAY_telop_success");
                acc.setDispChild(s_OpenParam.m_flag == 1, "LAY_telop_lost");
                acc.setDispChild(true, "LAY_telop");
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_motion = "fade_in_l";
                param.m_setDefault = true;
                param.m_startFlags = 8;
                GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_telop");
            }
            for (unsigned int i = 0; i < 3; i++) {
                name.format("LAY_char@%02d", i + 1);
                ui::UIObjectAcc chara(acc.m_handle, name.m_str);
                chara.setDisp(false);
                if (i < s_OpenParam.m_entries.size()) {
                    OpenParam::Entry& entry = s_OpenParam.m_entries[i];
                    name.format("TXT_char_name@%02d", i + 1);
                    if (entry.m_bdat == nullptr) {
                        acc.setDispChild(false, name.m_str);
                    } else {
                        bool disp = entry.m_name != 0;
                        acc.setDispChild(disp, name.m_str);
                        if (disp) {
                            // a temporary object (the original gives it a stack slot of its own)
                            ui::UIObjectAcc(acc.m_handle, name.m_str).setText(ui::UIStr(entry.m_bdat, entry.m_name));
                        }
                    }
                    // the original passes a copy of the handle
                    m_owner->m_selectList->addContents(static_cast<unsigned int>(chara.m_handle));
                    {  // the original stores the second id first, in a slot it shares with the face object
                        MenuID id;
                        id.m_subId = 0;
                        id.m_id = entry.m_id;
                        m_owner->m_idList->addContents(id);
                    }
                    name.format("IMG_char_face@%02d", i + 1);
                    ui::UIObjectAcc face(acc.m_handle, name.m_str);
                    GfMenuObjHitonowa::setFaceStream(face, entry.m_id);
                }
            }
            mm::Rect<short> center;
            mm::Rect<short> range;
            acc.getLayoutRect("get_anim_center", center);
            acc.getLayoutRect("get_anim_range", range);
            GfMenuObjUtil::placeObjectH(m_owner->m_selectList,
                                        mm::Pnt<short>(center.x + center.w / 2, center.y + center.h / 2),
                                        range.x - center.x);
            acc.setDisp(true);
            acc.setSuspend(false);
            m_owner->m_waitCount = 0;
            m_owner->m_seq0.addJob(&GfMenuObjNpcTelop::seqWaitStream);
            m_owner->m_seq0.addJob(&GfMenuObjNpcTelop::seqStart);
            m_state = 1;
        } else {
            GfMenuObject::termCallContext(acc.m_handle);
        }
        break;
    case 0x22:
        if (m_state == 0) {
            break;
        }
        if (s_OpenParam.m_entries.size() != 0 && m_owner->m_selectList != nullptr) {
            mm::mtl::FixStr<32> name;
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 2;
            param.m_time = 0.16666667f;
            param.m_startFlags = 10;
            {
                ui::UIObjectAcc base(acc.m_handle, "IMG_telop_base");
                base.startAnimation(s_OpenParam.m_flag == 0 ? "end_success" : "end_filed", false);
                GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_telop");
            }
            GfMenuObjUtil::playSE(0x2B);
            for (unsigned int i = 0; i < s_OpenParam.m_entries.size(); i++) {
                name.format("IMG_char_get_eff@%02d", i + 1);
                ui::UIObjectAcc eff(acc.m_handle, name.m_str);
                if (s_OpenParam.m_flag != 0) {
                    eff.startAnimation("end_failed", false);
                } else {
                    eff.startAnimation("end_success", false);
                }
                if (i == m_owner->m_selectList->getSize() - 1) {
                    GfMenuObject::hookAnimationEvent(acc.m_handle, eff.m_handle, i);
                }
                name.format("LAY_char_face@%02d", i + 1);
                GfMenuObjUtil::startCtrl(acc.m_handle, param, name.m_str);
                name.format("LAY_char_name@%02d", i + 1);
                GfMenuObjUtil::startCtrl(acc.m_handle, param, name.m_str);
            }
            GfMenuObjNpcTelop* owner = m_owner;
            m_state = 0;
            owner->m_seq0.clear();
        } else {
            GfMenuObject::termCallContext(acc.m_handle);
        }
        break;
    case 0x100: {
        unsigned int index = event.m_param0;
        mm::mtl::FixStr<32> name;
        name.format("LAY_char@%02d", index + 1);
        acc.setDispChild(true, name.m_str);
        name.format("LAY_char_face@%02d", index + 1);
        acc.setDispChild(s_OpenParam.m_flag == 1, name.m_str);
        name.format("LAY_char_name@%02d", index + 1);
        acc.setDispChild(s_OpenParam.m_flag == 1, name.m_str);
        name.format("IMG_char_get_eff@%02d", index + 1);
        ui::UIObjectAcc eff(acc.m_handle, name.m_str);
        if (s_OpenParam.m_flag == 0) {
            eff.startAnimation("start_success", false);
            ui::EventData next;
            next.m_type = 0x101;
            next.m_param0 = index;
            GfMenuObject::sendEvent(acc.m_handle, next, 1.0f);
        } else {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l";
            param.m_setDefault = true;
            param.m_startFlags = 8;
            name.format("LAY_char_face@%02d", index + 1);
            acc.setDispChild(true, name.m_str);
            GfMenuObjUtil::startCtrl(acc.m_handle, param, name.m_str);
            name.format("LAY_char_name@%02d", index + 1);
            acc.setDispChild(true, name.m_str);
            GfMenuObjUtil::startCtrl(acc.m_handle, param, name.m_str);
            eff.startAnimation("start_failed", false);
            ui::EventData next;
            next.m_type = 0x102;
            GfMenuObject::sendEvent(acc.m_handle, next, 0.83333337f);
        }
        if (index == m_owner->m_selectList->getSize() - 1) {
            GfMenuObject::hookAnimationEvent(acc.m_handle, eff.m_handle, index);
        }
        break;
    }
    case 0x101: {
        unsigned int index = event.m_param0;
        mm::mtl::FixStr<32> name;
        name.format("LAY_char_face@%02d", index + 1);
        acc.setDispChild(true, name.m_str);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_setDefault = true;
        param.m_startFlags = 8;
        name.format("LAY_char_name@%02d", index + 1);
        acc.setDispChild(true, name.m_str);
        GfMenuObjUtil::startCtrl(acc.m_handle, param, name.m_str);
        GfMenuObjUtil::playSE(0x2A);
        break;
    }
    case 0x102:
        GfMenuObjUtil::playSE(0x32);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjNpcTelop::HitonowaListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 0x21:
        if (m_state == 0) {
            GfMenuObjHitonowa::setBootFromEvent();
            GfMenuManager::setMainmenuOpenHitonowa();
            GfMenuManager::openFullScreen(1, true, true);
            m_owner->m_seq1.addJob(&GfMenuObjNpcTelop::seqWaitCloseFullscreen);
            m_owner->m_seq1.addJob(&GfMenuObjNpcTelop::seqEndHitonowa);
            m_state = 1;
            s_Open = true;
        }
        break;
    case 0x22:
        if (m_state == 1) {
            GfMenuObject::termCallContext(acc.m_handle);
            m_state = 0;
            s_Open = false;
        }
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf
