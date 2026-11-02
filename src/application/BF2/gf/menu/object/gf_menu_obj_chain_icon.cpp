#include "classes/gf/GfMenuObjChainIcon.h"
#include "classes/gf/GfMenuObjChainIcon/ChainIconInfo.h"
#include "classes/gf/GfMenuObjChainIcon/ListListener.h"
#include "classes/gf/GfMenuManyObjects.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuFieldPosAdapter.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfMenuBdat.h"
#include "gf/MenuOffset.h"
#include "gf/GfObjAcc.h"
#include "fw/Transform.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

namespace {
// a closed icon off the queue and terminated (the name is not the original's)
void termIcon(ui::UIObjectAcc icon) {
    GfMenuManyObjects::remove<GfMenuObjChainIcon::ChainIconInfo>(2, icon.m_handle);
    icon.setDisp(false);
    icon.setTerm();
}

}  // namespace

GfMenuObjChainIcon::GfMenuObjChainIcon(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjChainIcon::~GfMenuObjChainIcon() {
    GfMenuManyObjects::destroy<ChainIconInfo>(2);
}

void GfMenuObjChainIcon::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int list = acc.searchChild("LAY_main");
    if (ui::UIObjectAcc(list).m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x41, list);
#line 78
        ListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(list, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    ui::UIObjectAcc(m_handle).setTerm();
    GfMenuObject::initialize();
    GfMenuManyObjects::createQueue<ChainIconInfo>(2, 32);
}

void GfMenuObjChainIcon::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjChainIcon::update() {
    GfMenuObject::update();
}

void GfMenuObjChainIcon::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 0x21: {
        ui::UIObjectAcc icon(acc.searchDuplicatedChild("LAY_chain_icon_root", event.m_param0Short));
        if (icon.m_object != nullptr) {
            acc.setDisp(true);
            icon.setDisp(true);
            GfMenuObjUtil::setChildDisp(icon.m_handle, "LAY_main", true);
            GfMenuObjUtil::CtrlParam param;
            param.m_time = 1.0f;
            param.m_methods = 0x20;
            param.m_distance = 60;
            param.m_eventId = (event.m_param0Short << 8) | 1;
            int ctrl = GfMenuObjUtil::startCtrl(icon.m_handle, param, nullptr);
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            ui::UIObjectAcc image(icon.m_handle, "IMG_icon");
            image.startAnimation("fadein", false);
        }
        break;
    }
    case 0x22: {
        ui::UIObjectAcc icon(acc.searchDuplicatedChild("LAY_chain_icon_root", event.m_param0Short));
        if (icon.m_object != nullptr) {
            termIcon(icon);
        }
        break;
    }
    case 3: {
        // the control's end: the icon's index << 8, 1 for its fade-in, 2 for its fade-out
        unsigned int id = event.m_param0;
        if (id == 0) {
            break;
        }
        ui::UIObjectAcc icon(acc.searchDuplicatedChild("LAY_chain_icon_root", id >> 8));
        if (icon.m_object != nullptr) {
            if ((id & 0xff) == 1) {
                GfMenuObjUtil::CtrlParam param;
                param.m_time = 0.25f;
                param.m_methods = 0x22;
                param.m_distance = 15;
                param.m_eventId = (id & 0xffff00) | 2;
                int ctrl = GfMenuObjUtil::startCtrl(icon.m_handle, param, nullptr);
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            } else if ((id & 0xff) == 2) {
                termIcon(icon);
            }
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

// the object's block ends before the event: its GfObjAcc shares a stack slot with add's dequeued info, the
// MenuOffset with the event (the original's frame)
unsigned int GfMenuObjChainIcon::open(const OpenParam& param) {
    if (GfMenuObjUtil::isMenuObjectFull()) {
        return 0;
    }
    unsigned int root = GfMenuObject::getAttachedObject(0x41);
    if (ui::UIObjectAcc(root).m_object == nullptr) {
        return 0;
    }
    if (ui::UIObjectAcc(root).isTerm()) {
        return 0;
    }
    unsigned int screen = ui::UIObjectAcc(root).duplicateChild("LAY_chain_icon_root");
    if (ui::UIObjectAcc(screen).m_object == nullptr) {
        return 0;
    }
    {
        GfObjAcc obj(param.m_obj);
        if (obj.m_obj == nullptr || obj.getType() != 3) {
            return 0;
        }
        unsigned short id = Bdat::getVal(GfDataBdat::getFP(0x88), "OffsetID", obj.getBdatId());
        int offsetId = id == 0 ? 1 : id;
        MenuOffset offset;
        offset.m_offset = mm::Vec3(0.0f, 0.0f, 0.0f);
        offset.m_bone = nullptr;
        GfMenuBdat::getMenuOffset(offsetId, offset);
        const fw::Transform& transform = obj.getWorldTransform();
        mm::Vec3 pos = transform.position;
        pos.y += offset.m_offset.y + -1.0f;
        GfMenuFieldPosAdapter::create(ui::UIObjectAcc(screen).searchChild("LAY_chain_icon"), pos);
    }
    ui::EventData event;
    event.m_type = 0x21;
    event.m_param0Short = ui::UIObjectAcc(screen).getDuplicateIndex();
    GfMenuObject::sendEvent(root, event, 0.0f);
    GfMenuManyObjects::add<ChainIconInfo>(2, ChainIconInfo(screen), close);
    return screen;
}

void GfMenuObjChainIcon::close(unsigned int handle) {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x41));
    if (root.m_object != nullptr && !root.isTerm()) {
        ui::UIObjectAcc icon(handle);
        if (icon.m_object != nullptr && icon.isDuplicate()) {
            ui::EventData event;
            event.m_type = 0x22;
            event.m_param0Short = ui::UIObjectAcc(handle).getDuplicateIndex();
            GfMenuObject::sendEvent(root.m_handle, event, 0.0f);
        }
    }
}

}  // namespace gf
