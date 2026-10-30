#include "classes/gf/GfMenuObjDamageBuff.h"
#include "classes/gf/GfMenuObjDamageBuff/DamageInfo.h"
#include "classes/gf/GfMenuObjDamageBuff/ListListener.h"
#include "classes/gf/GfMenuManyObjects.h"
#include "classes/gf/GfMenuCallManager.h"
#include "classes/gf/GfMenuFieldPosAdapter.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "ui/UIUtil.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

namespace {
// the background colour of each name type (the name is not the original's)
const char* s_colors[] = {"dmg_buff", "dmg_debuff", "dmg_combo"};

// a name type's colour, white past the table (the name is not the original's): the table is handed over, so it
// stays writable data as the original's
template <unsigned long N>
inline const char* getColor(const char* (&colors)[N], int type) {
    return static_cast<unsigned int>(type) < N ? colors[type] : "white";
}
}  // namespace

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAA440)
mm::mtl::FixedQueue<GfMenuObjDamageBuff::OpenParam, 32> GfMenuObjDamageBuff::s_openRequests;

GfMenuObjDamageBuff::GfMenuObjDamageBuff(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjDamageBuff::~GfMenuObjDamageBuff() {
    GfMenuManyObjects::destroy<DamageInfo>(1);
}

void GfMenuObjDamageBuff::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int list = acc.searchChild("LAY_main");
    if (ui::UIObjectAcc(list).m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x2d, list);
#line 103
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
    GfMenuManyObjects::createQueue<DamageInfo>(1, 32);
    s_openRequests.clear();
}

void GfMenuObjDamageBuff::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjDamageBuff::update() {
    const mm::mtl::FixedQueue<OpenParam, 32>& requests = s_openRequests;
    for (mm::mtl::FixedQueue<OpenParam, 32>::const_iterator it = requests.begin(); it != requests.end(); ++it) {
        open(*it);
    }
    s_openRequests.clear();
    GfMenuObject::update();
}

inline void GfMenuObjDamageBuff::setupPlugin(unsigned int handle) {
    unsigned int item = ui::UIUtil::searchChild(handle, "LAY_buff_item");
    if (ui::UIUtil::isValid(item)) {
        unsigned int bg = ui::UIUtil::searchChild(handle, "IMG_bg");
        if (ui::UIUtil::isValid(bg)) {
            GfMenuObjUtil::createFitPlugin(bg, item, 0x18, 8, GfMenuObjUtil::FitOption());
        }
    }
}

unsigned int GfMenuObjDamageBuff::open(const OpenParam& param) {
    if (GfMenuObjUtil::isMenuObjectFull() || GfMenuCallManager::get()->m_strLinker.m_freeIndices.empty()) {
        return 0;
    }
    unsigned int root = GfMenuObject::getAttachedObject(0x2d);
    if (ui::UIObjectAcc(root).m_object == nullptr) {
        return 0;
    }
    if (ui::UIObjectAcc(root).isTerm()) {
        return 0;
    }
    unsigned int screen = ui::UIObjectAcc(root).duplicateChild("LAY_buff_root");
    if (ui::UIObjectAcc(screen).m_object == nullptr) {
        return 0;
    }
    setupPlugin(screen);
    GfMenuFieldPosAdapter::create(ui::UIObjectAcc(screen).searchChild("LAY_buff"), param.m_pos);
    unsigned short text;
    if (param.m_bdat != nullptr && param.m_nameId != 0) {
        text = GfMenuObject::registString(ui::UIStr(param.m_bdat, param.m_nameId));
    } else {
        if (param.m_text == nullptr) {
            return 0;
        }
        text = GfMenuObject::registString(ui::UIStr(param.m_text, true));
    }
    ui::EventData event;
    event.m_type = 0x21;
    event.m_param0 = param.m_type;
    event.m_paramShort[2] = param.m_resist2 ? 2 : param.m_resist;
    event.m_paramShort[3] = ui::UIObjectAcc(screen).getDuplicateIndex();
    event.m_param2 = text;
    event.m_param3 = param.m_icon;
    GfMenuObject::sendEvent(root, event, 0.0f);
    DamageInfo info(screen);
    mm::mtl::Queue<DamageInfo>* queue = GfMenuManyObjects::getQueue<DamageInfo>(1);
    if (queue != nullptr) {
        if (queue->full()) {
            close(queue->dequeue().m_handle);
        }
        queue->push_back(info);
    }
    return screen;
}

inline void GfMenuObjDamageBuff::removeObject(ui::UIObjectAcc screen) {
    GfMenuManyObjects::remove<DamageInfo>(1, screen.m_handle);
    screen.setDisp(false);
    screen.setTerm();
}

void GfMenuObjDamageBuff::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 3: {
        // the control's end: the screen's index << 16, its root << 12, the control << 8 and its kind
        unsigned int id = event.m_param0;
        if (id == 0) {
            break;
        }
        unsigned int unite = (id >> 12) & 0xf;
        ui::UIObjectAcc screen(unite == 0 ? acc.searchDuplicatedChild("LAY_buff_root", id >> 16)
                                          : acc.searchDuplicatedChild("LAY_unite_root", id >> 16));
        if (screen.m_object != nullptr) {
            switch ((id >> 8) & 0xf) {
            case 1: {
                GfMenuObjUtil::CtrlParam param;
                param.m_time = 0.25f;
                param.m_eventId = (id & 0xff) | ((id >> 16) << 16) | (unite << 12) | 0x200;
                param.m_methods = (id & 0xff) != 0 ? 0x42 : 0x22;
                param.m_distance = 15;
                int ctrl = GfMenuObjUtil::startCtrl(screen.m_handle, param, nullptr);
                if (ctrl == -1) {
                    removeObject(screen);
                } else {
                    GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
                }
                break;
            }
            case 2:
                removeObject(screen);
                break;
            }
        }
        break;
    }
    case 0x21: {
        ui::UIObjectAcc screen(acc.searchDuplicatedChild("LAY_buff_root", event.m_paramShort[3]));
        if (screen.m_object != nullptr) {
            acc.setDisp(true);
            screen.setDisp(true);
            int unused;
            setupScreen(screen.m_handle, event.m_param0, event.m_paramShort[2], event.m_param2, unused);
            int type = event.m_param0;
            // the screen's index (the event's fourth short) << 16
            unsigned int index = event.m_param1 & 0xffff0000;
            GfMenuObjUtil::CtrlParam param;
            param.m_time = 1.0f;
            // 1 << 8 for its fade in, and whether it is not a buff
            param.m_eventId = index | 0x100 | (type != 0);
            param.m_methods = type != 0 ? 0x40 : 0x20;
            param.m_distance = 60;
            int ctrl = GfMenuObjUtil::startCtrl(screen.m_handle, param, nullptr);
            if (ctrl == -1) {
                removeObject(screen);
            } else {
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            }
        }
        break;
    }
    case 0x22: {
        ui::UIObjectAcc screen(acc.searchDuplicatedChild("LAY_buff_root", event.m_param0Short));
        if (screen.m_object != nullptr) {
            removeObject(screen);
        }
        break;
    }
    case 0x100: {
        ui::UIObjectAcc screen(acc.searchDuplicatedChild("LAY_unite_root", event.m_paramShort[3]));
        if (screen.m_object != nullptr) {
            acc.setDisp(true);
            screen.setDisp(true);
            {
                int combo = event.m_param2;
                ui::UIObjectAcc text(screen.m_handle, "TXT_dr_combo_name");
                unsigned int msg = GfMenuObjUtil::getMsgIDFromList(0x13f, combo);
                ui::UIStr str(GfDataBdat::getFP(0x120), msg);
                text.setText(str);
            }
            {
                int combo = event.m_param3;
                ui::UIObjectAcc text(screen.m_handle, "TXT_bl_combo_name");
                ui::UIStr str = GfMenuObjUtil::getElementComboName(combo);
                text.setText(str);
            }
            GfMenuObjUtil::CtrlParam param;
            param.m_time = 1.0f;
            param.m_eventId = (event.m_paramShort[3] << 16) | 0x1100;
            param.m_methods = 0x20;
            param.m_distance = 60;
            int ctrl = GfMenuObjUtil::startCtrl(screen.m_handle, param, nullptr);
            if (ctrl == -1) {
                removeObject(screen);
            } else {
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            }
        }
        break;
    }
    case 0x101: {
        ui::UIObjectAcc screen(acc.searchDuplicatedChild("LAY_unite_root", event.m_param0Short));
        if (screen.m_object != nullptr) {
            removeObject(screen);
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjDamageBuff::setupScreen(unsigned int handle, int type, int resist, int text, int unused) {
    GfMenuObjUtil::setChildText(handle, "TXT_name", text);
    if (resist != 0) {
        const int names[] = {1, 2};
        unsigned char* data = GfDataBdat::getFP(0x161);
        int id = names[resist - 1];
        unsigned char* msg = GfDataBdat::getFP(0xf5);
        unsigned int name = static_cast<unsigned short>(Bdat::getVal(data, "name", id));
        ui::UIObjectAcc(handle, "TXT_resist").setText(ui::UIStr(msg, name));
    }
    GfMenuObjUtil::setChildDisp(handle, "TXT_resist", resist != 0);
    GfMenuObjUtil::setChildAddColor(handle, "IMG_bg", getColor(s_colors, type));
}

unsigned int GfMenuObjDamageBuff::fn_71003E537C(const OpenParam& param) {
    if (s_openRequests.full()) {
        s_openRequests.pop();
    }
    s_openRequests.push_back(param);
    return 0;
}

void GfMenuObjDamageBuff::close(unsigned int handle) {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x2d));
    if (root.m_object != nullptr && !root.isTerm()) {
        ui::UIObjectAcc screen(handle);
        if (screen.m_object != nullptr && screen.isDuplicate()) {
            ui::EventData event;
            event.m_type = 0x22;
            event.m_paramShort[0] = ui::UIObjectAcc(handle).getDuplicateIndex();
            GfMenuObject::sendEvent(root.m_handle, event, 0.0f);
        }
    }
}

unsigned int GfMenuObjDamageBuff::openUniteCombo(const OpenUniteParam& param) {
    if (GfMenuObjUtil::isMenuObjectFull()) {
        return 0;
    }
    unsigned int root = GfMenuObject::getAttachedObject(0x2d);
    if (ui::UIObjectAcc(root).m_object == nullptr) {
        return 0;
    }
    if (ui::UIObjectAcc(root).isTerm()) {
        return 0;
    }
    unsigned int screen = ui::UIObjectAcc(root).duplicateChild("LAY_unite_root");
    ui::UIObjectAcc acc(screen);
    if (acc.m_object == nullptr) {
        return 0;
    }
    GfMenuObjUtil::createFitPlugin(acc.searchChild("IMG_dr_combo_bg"), acc.searchChild("TXT_dr_combo_name"), 0x18, 8,
                                   GfMenuObjUtil::FitOption());
    GfMenuObjUtil::createFitPlugin(acc.searchChild("IMG_bl_combo_bg"), acc.searchChild("TXT_bl_combo_name"), 0x18, 8,
                                   GfMenuObjUtil::FitOption());
    GfMenuFieldPosAdapter::create(acc.searchChild("LAY_unite_combo"), param.m_pos);
    ui::EventData event;
    event.m_type = 0x100;
    event.m_paramShort[3] = ui::UIObjectAcc(screen).getDuplicateIndex();
    event.m_param2 = param.m_eventParam0;
    event.m_param3 = param.m_eventParam1;
    GfMenuObject::sendEvent(root, event, 0.0f);
    DamageInfo info(screen);
    mm::mtl::Queue<DamageInfo>* queue = GfMenuManyObjects::getQueue<DamageInfo>(1);
    if (queue != nullptr) {
        if (queue->full()) {
            closeUniteCombo(queue->dequeue().m_handle);
        }
        queue->push_back(info);
    }
    return screen;
}

void GfMenuObjDamageBuff::closeUniteCombo(unsigned int handle) {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x2d));
    if (root.m_object != nullptr && !root.isTerm()) {
        ui::UIObjectAcc screen(handle);
        if (screen.m_object != nullptr && screen.isDuplicate()) {
            ui::EventData event;
            event.m_type = 0x101;
            event.m_paramShort[0] = ui::UIObjectAcc(handle).getDuplicateIndex();
            GfMenuObject::sendEvent(root.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjDamageBuff::closeAll() {
    unsigned int root = GfMenuObject::getAttachedObject(0x2d);
    if (ui::UIObjectAcc(root).m_object == nullptr) {
        return;
    }
    if (!ui::UIObjectAcc(root).isTerm()) {
        GfMenuManyObjects::closeAll<DamageInfo>(1, &close);
        s_openRequests.clear();
    }
}

}  // namespace gf
