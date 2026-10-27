#include "classes/gf/GfMenuObjTargetCursor.h"
#include "classes/gf/GfMenuObjTargetCursor/MainListener.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfObjAcc.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuPosAdapter.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/MenuOffset.h"
#include "mm/mtl/FixStr.h"
#include "mm/Pnt.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjTargetCursor::GfMenuObjTargetCursor(unsigned int handle)
    : GfMenuObject(handle), m_cursor(0), m_target(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_cameraType(0),
      m_posAdapter(nullptr), m_seq(this), m_lockSeq(this), m_stepStarted(false), pad_564(0), m_mini(false) {}

GfMenuObjTargetCursor::~GfMenuObjTargetCursor() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjTargetCursor::initialize() {
    ui::UIObjectAcc acc(m_handle);
    GfMenuObject::attachExternalCall(0x12, m_handle);
    unsigned int main = acc.searchChild("LAY_main");
    if (ui::UIObjectAcc(main).m_object != nullptr) {
#line 107
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(main, listener);
        if (listener != nullptr) {
            listener->release();
        }
        m_cursor = main;
        // (GF_OBJ_HANDLE*)-1: no object yet, as GfMenuManager::getAccessObjHandle says it
        m_posAdapter = GfMenuPosAdapter::create(acc.searchChild("LAY_en_cursor"), reinterpret_cast<GF_OBJ_HANDLE*>(-1), nullptr);
        m_posAdapter->setPosAdjustScreen(true);
        m_posAdapter->setPosOffsMode(1);
        m_posAdapter->m_screenOffset = mm::Pnt<short>(0, -5);
        GfMenuObject::addPosEventCondition(main, "LAY_en_cursor", 0, 0);
        GfMenuObjUtil::createSyncPlugin(acc.searchChild("IMG_en_cursor_arrow"), acc.searchChild("IMG_en_cursor"), 0x20);
        GfMenuObjUtil::createSyncPlugin(acc.searchChild("IMG_en_cursor_btl_arrow"), acc.searchChild("IMG_en_cursor_btl"), 0x20);
    }
    GfMenuObject::initialize();
}

void GfMenuObjTargetCursor::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjTargetCursor::update() {
    GfMenuObject::update();
    ui::UIObjectAcc acc(m_cursor);
    if (acc.m_object == nullptr) {
        return;
    }
    m_seq.update();
    m_lockSeq.update();
    if (acc.isTerm()) {
        return;
    }
    if (m_target == GfMenuManager::getTargetObjHandle()) {
        GfObjAcc obj(GfMenuManager::getTargetObjHandle());
        if (obj.m_obj != nullptr) {
            bool battle = GfMenuObjUtil::isInBattle(obj.getHandle());
            if (m_dispType != battle) {
                ui::EventData event;
                event.m_type = 0x120;
                event.m_param0 = battle;
                ui::UIManager::get()->requestObjectEvent(m_cursor, event, 0.0f);
                m_dispType = battle;
            }
        }
        if (m_cameraType != GfMenuManager::getCurCameraType()) {
            ui::EventData event;
            event.m_type = 0x102;
            event.m_param0 = GfMenuManager::getCurCameraType();
            ui::UIManager::get()->requestObjectEvent(m_cursor, event, 0.0f);
            m_cameraType = GfMenuManager::getCurCameraType();
        }
        return;
    }
    GfObjAcc obj(GfMenuManager::getTargetObjHandle());
    ui::EventData event(0);
    if (obj.m_obj == nullptr || obj.getType() != 5) {
        event.m_type = 0x101;
    } else {
        event.m_type = 0x100;
        int band;
        {
            DataParamAcc param(obj.getHandle());
            int level = param.getLevel(false);
            int leader = GfGameParty::getLeaderLevel();
            // the colour band of the level difference (tgt_cursor_lv%02d): 3 the same or within 2, 2/1 higher by
            // 3-5/6 or more, 4/5 lower by 3-5/6 or more (the name of the variable is not the original's)
            if (level == leader) {
                band = 3;
            } else if (level > leader) {
                int diff = level - leader;
                band = diff < 3 ? 3 : diff < 6 ? 2 : 1;
            } else if (level < leader) {
                int diff = leader - level;
                band = diff < 3 ? 3 : diff < 6 ? 4 : 5;
            } else {
                band = 0;
            }
        }
        event.m_param1 = band;
        m_dispType = 0;
    }
    event.m_param0 = m_cameraType;
    ui::UIManager::get()->requestObjectEvent(m_cursor, event, 0.0f);
    m_target = GfMenuManager::getTargetObjHandle();
    if (event.m_type == 0x100) {
        MenuOffset offset;
        offset.m_offset = mm::Vec3(0.0f, 0.0f, 0.0f);
        offset.m_bone = nullptr;
        GfMenuBdat::getMenuOffset(GfGameUtil::getUiOffsetId(m_target), offset);
        m_posAdapter->changeReference(m_target, &offset);
    }
}

bool GfMenuObjTargetCursor::seqEnCursorOpen() {
    ui::UIObjectAcc cursor(m_handle, "IMG_en_cursor");
    ui::UIObjectAcc arrow(m_handle, "IMG_en_cursor_arrow");
    if (!m_stepStarted) {
        refreshDisp(0);
        cursor.startAnimation("fadein", false);
        arrow.startAnimation("fadein", false);
        m_stepStarted = true;
        return false;
    }
    if (cursor.isPlayingAnimation()) {
        return false;
    }
    m_stepStarted = false;
    if (GfMenuManager::isBattleState(0) && m_cameraType == 1) {
        m_seq.addJob(&GfMenuObjTargetCursor::seqEnCursorLock);
    } else {
        cursor.startAnimation("idol", false);
        arrow.startAnimation("idol", false);
    }
    return true;
}

bool GfMenuObjTargetCursor::seqEnCursorLock() {
    ui::UIObjectAcc sub(m_handle, "IMG_en_cursor_sub");
    if (!m_stepStarted) {
        sub.startAnimation("lock", false);
        sub.setDisp(true);
        m_stepStarted = true;
        return false;
    }
    if (sub.isPlayingAnimation()) {
        return false;
    }
    m_stepStarted = false;
    sub.startAnimation("idol", false);
    return true;
}

bool GfMenuObjTargetCursor::seqCursorClose() {
    ui::UIObjectAcc cursor(m_handle, "IMG_en_cursor");
    ui::UIObjectAcc btl(m_handle, "IMG_en_cursor_btl");
    ui::UIObjectAcc sub(m_handle, "IMG_en_cursor_sub");
    if (!m_stepStarted) {
        if (cursor.isDisp()) {
            if (m_mini) {
                startCursorAnimation("mini_fadeout");
            } else {
                startCursorAnimation("fadeout");
            }
            sub.startAnimation("fadeout", false);
        } else {
            ui::UIObjectAcc other(m_handle, "IMG_other_cursor");
            other.setDisp(false);
        }
        m_stepStarted = true;
        return false;
    }
    if (cursor.isDisp() && cursor.isPlayingAnimation()) {
        return false;
    }
    if (btl.isDisp() && btl.isPlayingAnimation()) {
        return false;
    }
    cursor.setDisp(false);
    btl.setDisp(false);
    sub.setDisp(false);
    m_stepStarted = false;
    return true;
}

bool GfMenuObjTargetCursor::seqEnCursorOutScreen() {
    ui::UIObjectAcc cursor(m_handle, "IMG_en_cursor");
    ui::UIObjectAcc btl(m_handle, "IMG_en_cursor_btl");
    if (!m_stepStarted) {
        startCursorAnimation("cursor_in");
        m_stepStarted = true;
        m_mini = true;
        return false;
    }
    if (cursor.isPlayingAnimation() || btl.isPlayingAnimation()) {
        return false;
    }
    startCursorAnimation("mini_idol");
    m_stepStarted = false;
    return true;
}

bool GfMenuObjTargetCursor::seqEnCursorInScreen() {
    ui::UIObjectAcc cursor(m_handle, "IMG_en_cursor");
    ui::UIObjectAcc btl(m_handle, "IMG_en_cursor_btl");
    if (!m_stepStarted) {
        startCursorAnimation("cursor_out");
        m_mini = false;
        m_stepStarted = true;
        return false;
    }
    if (cursor.isPlayingAnimation() || btl.isPlayingAnimation()) {
        return false;
    }
    startCursorAnimation("idol");
    m_stepStarted = false;
    return true;
}

bool GfMenuObjTargetCursor::seqEnCursorInTarget() {
    ui::UIObjectAcc cursor(m_handle, "IMG_en_cursor");
    if (!m_stepStarted) {
        startCursorAnimation("fadein");
        m_stepStarted = true;
        return false;
    }
    if (cursor.isPlayingAnimation()) {
        return false;
    }
    startCursorAnimation("idol");
    m_stepStarted = false;
    return true;
}

bool GfMenuObjTargetCursor::seqEnCursorInBattle() {
    ui::UIObjectAcc btl(m_handle, "IMG_en_cursor_btl");
    if (!m_stepStarted) {
        startCursorAnimation("fadein");
        m_stepStarted = true;
        return false;
    }
    if (btl.isPlayingAnimation()) {
        return false;
    }
    startCursorAnimation("idol");
    m_stepStarted = false;
    return true;
}

void GfMenuObjTargetCursor::disp(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x12));
    if (acc.m_object != nullptr) {
        acc.setDisp(disp);
    }
}

void GfMenuObjTargetCursor::refreshDisp(unsigned int type) {
    ui::UIObjectAcc cursor(m_handle, "IMG_en_cursor");
    ui::UIObjectAcc arrow(m_handle, "IMG_en_cursor_arrow");
    ui::UIObjectAcc btl(m_handle, "IMG_en_cursor_btl");
    ui::UIObjectAcc btlArrow(m_handle, "IMG_en_cursor_btl_arrow");
    cursor.setDisp(type == 0);
    arrow.setDisp(type == 0);
    btl.setDisp(type == 1);
    btlArrow.setDisp(type == 1);
}

}  // namespace gf
