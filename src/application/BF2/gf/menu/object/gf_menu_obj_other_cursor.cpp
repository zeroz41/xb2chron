#include "classes/gf/GfMenuObjOtherCursor.h"
#include "classes/gf/GfMenuObjOtherCursor/MainListener.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuManager.h"
#include "gf/GfObjAcc.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuPosAdapter.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/MenuOffset.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjOtherCursor::GfMenuObjOtherCursor(unsigned int handle)
    : GfMenuObject(handle), m_cursor(0), m_posAdapter(nullptr) {}

GfMenuObjOtherCursor::~GfMenuObjOtherCursor() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjOtherCursor::initialize() {
    ui::UIObjectAcc acc(m_handle);
    GfMenuObject::attachExternalCall(0x13, m_handle);
    unsigned int main = acc.searchChild("LAY_main");
    if (ui::UIObjectAcc(main).m_object != nullptr) {
#line 86
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(main, listener);
        if (listener != nullptr) {
            listener->release();
        }
        m_cursor = main;
        // (GF_OBJ_HANDLE*)-1: no object yet, as GfMenuManager::getAccessObjHandle says it
        m_posAdapter = GfMenuPosAdapter::create(acc.searchChild("LAY_main"), reinterpret_cast<GF_OBJ_HANDLE*>(-1), nullptr);
        m_posAdapter->setPosOffsMode(1);
    }
    GfMenuObject::initialize();
}

void GfMenuObjOtherCursor::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjOtherCursor::update() {
    GfMenuObject::update();
    ui::UIObjectAcc acc(m_cursor);
    if (acc.m_object != nullptr && !acc.isTerm()) {
        if (m_target != GfMenuManager::getAccessObjHandle()) {
            GfObjAcc obj(GfMenuManager::getAccessObjHandle());
            ui::EventData event(0);
            if (obj.m_obj == nullptr || obj.getType() == 5) {
                event.m_type = 0x101;
            } else {
                event.m_type = 0x100;
                gmk::AGmkBase* gmk = gmk::getBindedGmkInst(obj.getHandle());
                if (gmk != nullptr) {
                    int type = gmk->getGmkType();
                    switch (type) {
                    case 28:
                    case 31:
                    case 36:
                        event.m_param0 = 1;
                        break;
                    default:
                        if (GfMenuObjUtil::isValidExpansion(3) && type == 62) {
                            event.m_param0 = 1;
                        } else {
                            event.m_param0 = 0;
                        }
                        break;
                    }
                }
            }
            ui::UIManager::get()->requestObjectEvent(m_cursor, event, 0.0f);
            m_target = GfMenuManager::getAccessObjHandle();
            if (event.m_type == 0x100) {
                MenuOffset offset;
                offset.m_offset = mm::Vec3(0.0f, 0.0f, 0.0f);
                offset.m_bone = nullptr;
                GfMenuBdat::getMenuOffset(GfGameUtil::getUiOffsetId(m_target), offset);
                m_posAdapter->changeReference(m_target, &offset);
            }
        }
    }
}

void GfMenuObjOtherCursor::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
    case 0x101:
        acc.setDisp(false);
        break;
    case 0x100: {
        int kind = event.m_param0;
        if (kind == 0) {
            ui::UIObjectAcc cursor(acc.m_handle, "IMG_other_cursor");
            cursor.startAnimation("focus_s", false);
        } else if (kind == 1) {
            ui::UIObjectAcc cursor(acc.m_handle, "IMG_symbol_cursor");
            cursor.startAnimation("focus_l", false);
        }
        GfMenuObjUtil::playSE(0x1C);
        acc.setDispChild(kind == 0, "LAY_other_cursor");
        acc.setDispChild(kind == 1, "LAY_symbol_cursor");
        acc.setDisp(true);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjOtherCursor::disp(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x13));
    if (acc.m_object != nullptr) {
        acc.setDisp(disp);
    }
}

}  // namespace gf
