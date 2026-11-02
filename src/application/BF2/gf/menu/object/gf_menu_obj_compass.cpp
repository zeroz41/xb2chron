#include "gf/FileStaticVec3.h"
#include "classes/gf/GfMenuObjCompass.h"
#include "classes/gf/GfMenuObjCompass/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "ui/EventData.h"
#include "classes/ui/UIObjectTextPlugin.h"
#include "classes/ui/UIObjectNumberPlugin.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuFlag.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Col3.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfMenuLocation.h"
#include "classes/ui/UIObject.h"
#include "gf/GfObjAcc.h"
#include "fw/Transform.h"
#include "plugin/Bdat.h"
#include "ui/UIUtil.h"
#include "ui/UIStr.h"
#include "mm/Rect.h"
#include "mm/Pnt.h"
#include "mm/mtl/FixStr.h"

namespace gf {

GfMenuObjCompass::GfMenuObjCompass(unsigned int handle) : GfMenuObject(handle) {
    m_IconObjList.clear();
}

GfMenuObjCompass::~GfMenuObjCompass() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjCompass::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x42, acc.m_handle);
    GfMenuObject::attachExternalCall(0x43, acc.m_handle);
#line 83
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::initialize();
}

void GfMenuObjCompass::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjCompass::update() {
    mm::Rect<short> rect;
    GfObjAcc leader(GfGameManager::getPartyLeaderDriver());
    if (leader.m_obj == nullptr) {
        return;
    }
    float height = leader.getWorldTransform().position.y;
    GfMenuLocation::LocatorData data;
    ui::UIObjectAcc center(m_handle, "IMG_center");
    if (center.m_object == nullptr) {
        return;
    }
    {
        mm::mtl::FixStr<32> name;
        name.format("LAY_outside@%02d", 1);
        GfMenuObjUtil::setChildDisp(m_handle, name.m_str, false);
    }
    int outside = 0;
    for (IconObj* obj = m_IconObjList.begin(); obj != m_IconObjList.end(); ++obj) {
        ui::UIObjectAcc icon(obj->m_handle);
        if (!GfMenuLocation::getLocatorData(obj->m_param.m_id, obj->m_param.m_type, data, 0, false)) {
            if (obj->m_lostFrames != 0) {
                obj->m_lostFrames--;
                continue;
            }
        } else {
            obj->m_lostFrames = 2;
            if (data.m_isOtherMap) {
                mm::mtl::FixStr<32> name;
                if (!outside) {
                    ui::UIObjectAcc outsides(m_handle, "LAY_outsides");
                    name.format("LAY_outside@%02d", 1);
                    GfMenuObjUtil::setChildDisp(outsides.m_handle, name.m_str, true);
                    unsigned char* maps = GfDataBdat::getFP(0x5D);
                    unsigned char* texts = GfDataBdat::getFP(0x1B4);
                    mm::mtl::FixStr<32> child;
                    child.format("TXT_area@%02d", 1);
                    ui::UIObjectAcc area(outsides.searchChild(child.m_str));
                    ui::UIObject* object = ui::UIUtil::getObject(area.m_handle);
                    if (object != nullptr) {
                        ui::UIObjectPlugin* plugin = object->m_plugins;
                        if (plugin != nullptr && plugin->getRTTI()->isKindOf(&ui::UIObjectTextPlugin::m_rtti)) {
                            if (data.m_mapId >= Bdat::getIdTop(maps) && data.m_mapId <= Bdat::getIdEnd(maps)) {
                                unsigned int nameId = (unsigned short)Bdat::getVal(maps, "nameID", data.m_mapId);
                                if (nameId >= (unsigned int)Bdat::getIdTop(texts) &&
                                    nameId <= (unsigned int)Bdat::getIdEnd(texts)) {
                                    ui::UIStr text(texts, nameId);
                                    static_cast<ui::UIObjectTextPlugin*>(plugin)->setText(text);
                                }
                            }
                        }
                    }
                    unsigned int index = GfMenuBdat::getIconImageIndex(data.m_iconId);
                    if (index < 3) {
                        child.format("IMG_icon_outside@%02d", 1);
                        ui::UIObjectAcc image(outsides.searchChild(child.m_str));
                        image.setImageIndex(index);
                    }
                    outside = 1;
                }
            } else {
                mm::Vec3 dir;
                GfMenuObjUtil::convViewSpace(dir, data.m_pos);
                dir.y = 0.0f;
                float length = dir.length();
                if (length <= 1e-6f) {
                    dir = mm::Vec3::zero;
                } else {
                    float scale = 1.0f / length;
                    dir.x = scale * dir.x;
                    dir.y = scale * dir.y;
                    dir.z = scale * dir.z;
                }
                mm::Vec3 front = GfInfo::m_camTgt;
                GfMenuObjUtil::convViewSpace(front, GfInfo::m_camPos + (front - GfInfo::m_camPos));
                if (front.isZero()) {
                    continue;
                }
                float frontLength = front.length();
                if (frontLength <= 1e-6f) {
                    front = mm::Vec3::zero;
                } else {
                    float scale = 1.0f / frontLength;
                    front.x = scale * front.x;
                    front.y = scale * front.y;
                    front.z = scale * front.z;
                }
                float dot = front.dot(dir);
                if (dot < 0.0f) {
                    dot = 0.0f;
                    if (obj->m_param.m_id >= 2) {
                        icon.setDisp(false);
                        continue;
                    }
                }
                icon.setDisp(true);
                float rate = dot * 0.5f;
                if (dir.x > 0.0f) {
                    rate = 0.5f - rate + 0.5f;
                }
                unsigned int pos = 2;
                if (::fabsf(height - data.m_pos.y) > 5.0f) {
                    pos = data.m_pos.y > height ? 0 : 1;
                }
                int distance = data.m_distance;
                if (obj->m_param.m_count == 0 || distance <= obj->m_param.m_count) {
                    ui::UIObjectAcc frame(center.m_handle);
                    mm::Pnt<short> point;
                    short width;
                    short heightPx;
                    icon.getSize(true, width, heightPx);
                    frame.getRect(rect, 2);
                    rect.w -= width;
                    rect.h -= heightPx;
                    point.x = rect.x + width / 2 + (int)(rate * rect.w);
                    point.y = heightPx / 2 + rect.y;
                    icon.setPosCenter(point);
                    {
                        ui::UIObjectAcc image(icon.searchChild("IMG_icon"));
                        image.setImageIndex(GfMenuBdat::getIconImageIndex(data.m_iconId));
                        ui::UIObjectAcc arrow(icon.searchChild("IMG_icon_pos"));
                        arrow.setImageIndex(pos);
                        if (GfMenuObjUtil::fn_710048FD30(3)) {
                            ui::UIObjectAcc npc(icon.searchChild("IMG_icon_npc"));
                            bool isNpc = obj->m_param.m_id == 4;
                            image.setAlpha(isNpc ? 0.0f : 1.0f);
                            npc.setDisp(isNpc);
                        }
                    }
                    ui::UIObjectAcc len(icon.searchChild("TXT_len"));
                    if (distance != 0) {
                        len.setAlpha(1.0f);
                    } else {
                        len.setAlpha(0.0f);
                    }
                    ui::UIObjectNumberPlugin* number = ui::UIObjectNumberPlugin::getPlugin(len.m_handle);
                    if (number != nullptr) {
                        number->setNumber(distance);
                    }
                    continue;
                }
            }
        }
        icon.setDisp(false);
    }
    GfMenuObject::update();
}

void GfMenuObjCompass::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        acc.setDisp(false);
        m_ctrl = -1;
        State state = {-1, 0};
        m_state = state;
        mm::mtl::FixStr<32> name;
        name.format("TXT_area@%02d", 1);
        ui::UIObjectAcc text(acc.searchChild(name.m_str));
        ui::UIObjectPlugin* plugin = ui::UIObjectTextPlugin::create(text.m_handle);
        if (plugin != nullptr) {
            plugin->release();
        }
        break;
    }
    case 0x21:
        if (GfMenuFlag::get1(0x1F) == 0 && m_state.m_open == 0) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 1;
            param.m_time = 0.25f;
            int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_state.m_open = 1;
            m_ctrl = ctrl;
        }
        break;
    case 0x22:
        if (m_state.m_open == 1) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 2;
            param.m_time = 0.25f;
            int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_state.m_open = 0;
            m_ctrl = ctrl;
        }
        break;
    case 0x101:
        if (event.m_param0 == 0) {
            if (m_state.m_frameCtrl != -1) {
                GfMenuObjUtil::stopCtrl(m_state.m_frameCtrl);
                m_state.m_frameCtrl = -1;
            }
        } else if (m_state.m_frameCtrl == -1) {
            ui::UIObjectAcc frame(acc.m_handle, "LAY_frame");
            if (frame.m_object != nullptr) {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x2000000;
                param.m_color = mm::Col3(0.8f, 0.0f, 0.0f);
                param.m_reserve = true;
                param.m_curve = 3;
                param.m_startFlags = 8;
                param.m_time = 1.0f;
                m_state.m_frameCtrl = GfMenuObjUtil::startCtrl(frame.m_handle, param, nullptr);
            }
        }
        break;
    case 0x102: {
        unsigned short icon = event.m_paramShort[1];
        ui::UIObjectAcc image(acc.searchDuplicatedChild("IMG_icon", event.m_paramShort[0]));
        if (image.m_object != nullptr) {
            image.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
            image.setDisp(true);
        }
        break;
    }
    case 0x103: {
        ui::UIObjectAcc image(acc.searchDuplicatedChild("IMG_icon", event.m_paramShort[0]));
        if (image.m_object != nullptr) {
            image.setTerm();
            GfMenuObject::termCallContext(image.m_handle);
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjCompass::open() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x42);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x21;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjCompass::close() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x42);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjCompass::addLocator(const LocatorParam& param) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x43);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::UIObjectAcc compass(handle);
            ui::UIObjectAcc icon(compass.duplicateChild("LAY_icon"));
            if (icon.m_object != nullptr) {
                icon.setDispPriority(icon.getDispPriority() + 5 - param.m_id);
                {
                    ui::UIObjectAcc len(icon.searchChild("TXT_len"));
                    if (len.m_object != nullptr) {
                        ui::UIObjectPlugin* plugin = ui::UIObjectNumberPlugin::create(len.m_handle);
                        if (plugin != nullptr) {
                            plugin->release();
                        }
                    }
                }
                IconObj obj = {icon.m_handle, param, 2};
                m_IconObjList.push_back(obj);
            }
        }
    }
}

mm::mtl::FixedVector<GfMenuObjCompass::IconObj, 32> GfMenuObjCompass::m_IconObjList;

}  // namespace gf
