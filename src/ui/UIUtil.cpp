#include "ui/UIUtil.h"
#include "ui/UIUtil.h"
#include "classes/ui/UICtrlCurve.h"
#include <math.h>
#include "classes/fw/PadManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIPadRead.h"
#include <string.h>
#include "classes/fw/BdatManager.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIInputManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectList.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "layer/LayerAccManager.h"
#include "classes/fw/MemHandlebaseAllocator.h"
#include "classes/fw/PointerMap.h"
#include "classes/ui/UIImageObject.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UIObject.h"

namespace ui { namespace UIUtil {


fw::PointerMap s_ObjPtrMap;
unsigned int s_ObjPtrMax;
fw::MemHandlebaseAllocator s_ProgAllocator;
fw::MemHandlebaseAllocator s_ResAllocator;
unsigned char* s_BdatFPs[17];
unsigned int s_SafeMarginW;
unsigned int s_SafeMarginH;
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EC5458)
unsigned int s_uioReplaceNo;
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B75878)
unsigned int s_layerMask = 1;
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B75880)
const char* s_menuDir = "menu";

void initLayerLib() {
    layer::LayerAccManager manager;
    manager.setCoordinate(layer::LayerCoordinate(0));
}

void termLayerLib() {}

void initObjectMap(unsigned int count) {
    s_ObjPtrMap.reserve(&s_ProgAllocator, count);
    s_ObjPtrMax = count;
}

mm::mtl::IAllocator* getProgAllocator() {
    return &s_ProgAllocator;
}

void termObjectMap() {
    s_ObjPtrMap.destroy();
    s_ObjPtrMax = 0;
}

unsigned int registObject(UIObject* object) {
    return s_ObjPtrMap.regist(object);
}

void releaseObject(unsigned int handle) {
    UIObjectAcc acc(handle);
    if (acc.m_object != nullptr) {
        if (UIInputManager::sys() != nullptr && acc.isDuplicate()) {
            unsigned int input = UIInputManager::sys()->searchInputHandle(acc.m_handle);
            if (input != 0) {
                UIInputManager::sys()->migrateInput(input, 0);
            }
        }
        if (UIEventManager::sys() != nullptr) {
            UIEventManager::sys()->removeObjectListener(handle);
        }
        s_ObjPtrMap.remove(handle);
    }
}

UIObject* getObject(unsigned int handle) {
    return static_cast<UIObject*>(s_ObjPtrMap.getPtr(handle));
}

UILayoutObject* getLayoutObject(unsigned int handle) {
    UIObject* object = getObject(handle);
    if (object == nullptr) {
        return nullptr;
    }
    return object->getRTTI()->isKindOf(&UILayoutObject::m_rtti) ? static_cast<UILayoutObject*>(object) : nullptr;
}

UIImageObject* getImageObject(unsigned int handle) {
    UIObject* object = getObject(handle);
    if (object == nullptr) {
        return nullptr;
    }
    return object->getRTTI()->isKindOf(&UIImageObject::m_rtti) ? static_cast<UIImageObject*>(object) : nullptr;
}

unsigned int searchChild(unsigned int handle, const char* name) {
    UILayoutObject* layout = getLayoutObject(handle);
    if (layout == nullptr) {
        return 0;
    }
    return layout->searchChild(name);
}

void setDispChild(unsigned int handle, bool disp, const char* child) {
    UILayoutObject* layout = getLayoutObject(handle);
    if (layout == nullptr) {
        return;
    }
    unsigned int found = layout->searchChild(child);
    if (!isValid(found)) {
        return;
    }
    UIObject* object = getObject(found);
    if (object == nullptr) {
        return;
    }
    object->m_displayInfo.setDisp(disp);
}

bool isValid(unsigned int handle) {
    return s_ObjPtrMap.isValid(handle);
}

bool isTerm(unsigned int handle) {
    if (!isValid(handle)) {
        return false;
    }
    return getObject(handle)->m_flags.test(3);
}

void initBdatFP() {
    s_BdatFPs[0] = fw::BdatManager::getFp("MNU_ResImage");
    s_BdatFPs[1] = fw::BdatManager::getFp("MNU_ResLayout");
    s_BdatFPs[2] = fw::BdatManager::getFp("MNU_ResFont");
    s_BdatFPs[3] = fw::BdatManager::getFp("MNU_ResFontStyle");
    s_BdatFPs[4] = fw::BdatManager::getFp("MNU_ResMSProj");
    s_BdatFPs[5] = fw::BdatManager::getFp("menu_ms");
    s_BdatFPs[6] = fw::BdatManager::getFp("MNU_Layer");
    s_BdatFPs[7] = fw::BdatManager::getFp("MNU_InputPad");
    s_BdatFPs[8] = fw::BdatManager::getFp("MNU_InputWheel");
    s_BdatFPs[9] = fw::BdatManager::getFp("MNU_InputPointer");
    s_BdatFPs[10] = fw::BdatManager::getFp("MNU_InputAct");
    s_BdatFPs[11] = fw::BdatManager::getFp("MNU_TextProperty");
    s_BdatFPs[12] = fw::BdatManager::getFp("MNU_ColorList");
    s_BdatFPs[13] = fw::BdatManager::getFp("MNU_FacePatternList");
    s_BdatFPs[14] = fw::BdatManager::getFp("MNU_ResMotion");
    s_BdatFPs[15] = fw::BdatManager::getFp("MNU_ResUio");
    s_BdatFPs[16] = fw::BdatManager::getFp("MNU_UioReplace");
}

unsigned char* getBdatFP(unsigned char index) {
    if (index < 17) {
        return s_BdatFPs[index];
    }
    return nullptr;
}

void fn_7100696920(unsigned int no) {
    s_uioReplaceNo = no;
}

void fn_7100696930(const char* dir) {
    s_menuDir = dir;
}

const char* fn_7100696940() {
    return s_menuDir;
}

void fn_7100696950(unsigned int bit) {
    s_layerMask |= 1 << bit;
}

bool fn_7100696970(unsigned int bit) {
    return (s_layerMask & (1 << bit)) != 0;
}

bool fn_7100696990(const char* file) {
    unsigned char* fp = s_BdatFPs[16];
    if (fp != nullptr) {
        for (int i = 0; i < Bdat::getIdCount(fp); i++) {
            int id = Bdat::getIdTop(fp) + i;
            if (strcmp(file, reinterpret_cast<const char*>(Bdat::getVal(fp, "file", id))) == 0) {
                return true;
            }
        }
    }
    return false;
}

unsigned char* fn_7100696A28(unsigned int dlc) {
    if (dlc == 0) {
        return s_BdatFPs[6];
    }
    if (fn_7100696970(dlc)) {
        mm::mtl::FixStr<32> name;
        name.format("MNU_Layer_Dlc%02d", dlc);
        return Bdat::getFP(name.m_str);
    }
    return nullptr;
}

mm::mtl::IAllocator* getResourceAllocator() {
    return &s_ResAllocator;
}

unsigned int getGroupPriority(unsigned int group) {
    return (group << 5) | 1;
}

void setSafeMergin(unsigned int width, unsigned int height) {
    s_SafeMarginW = width;
    s_SafeMarginH = height;
}

unsigned long timeSecToUITime(float sec) {
    return sec * 1000.0f;
}

unsigned int getScreenWidth() {
    layer::LayerAccManager manager;
    return manager.getScreenWidth();
}

unsigned int getScreenHeight() {
    layer::LayerAccManager manager;
    return manager.getScreenHeight();
}

namespace {
UICtrlCurveLinear s_curveLinear;
UICtrlCurveLinearLoop s_curveLinearLoop;
UICtrlCurveSin90 s_curveSin90;
UICtrlCurveSin180 s_curveSin180;
UICtrlCurveSin90Rev s_curveSin90Rev;
UICtrlCurveSin180Rev s_curveSin180Rev;
}  // namespace

const UICtrlCurve* getCurve(CURVE_TYPE type) {
    switch (type) {
    case CURVE_LINEAR:
        return &s_curveLinear;
    case CURVE_LINEAR_LOOP:
        return &s_curveLinearLoop;
    case CURVE_SIN90:
        return &s_curveSin90;
    case CURVE_SIN180:
        return &s_curveSin180;
    case CURVE_SIN90_REV:
        return &s_curveSin90Rev;
    case CURVE_SIN180_REV:
        return &s_curveSin180Rev;
    }
    return nullptr;
}

const fw::PadData* getPadData() {
    if (UIManager::sys() != nullptr && UIManager::sys()->m_padRead != nullptr) {
        return &UIManager::sys()->m_padRead->uiGetControlPad();
    }
    return &fw::PadManager::getControlPadData(0);
}

}}  // namespace ui::UIUtil

namespace ui {

float UICtrlCurveLinear::calc(float time, float from, float to, float duration) const {
    return time / duration;
}

float UICtrlCurveLinearLoop::calc(float time, float from, float to, float duration) const {
    float t = time / (duration * 0.5f);
    return t < 1.0f ? t : 2.0f - t;
}

float UICtrlCurveSin90::calc(float time, float from, float to, float duration) const {
    return (to - from) * sinf(time / duration * 90.0f * 0.017453292f) + from;
}

float UICtrlCurveSin180::calc(float time, float from, float to, float duration) const {
    return (to - from) * sinf(time / duration * 180.0f * 0.017453292f) + from;
}

float UICtrlCurveSin90Rev::calc(float time, float from, float to, float duration) const {
    return (to - from) * (1.0f - sinf((time / duration * 90.0f + 90.0f) * 0.017453292f)) + from;
}

float UICtrlCurveSin180Rev::calc(float time, float from, float to, float duration) const {
    return (to - from) * (1.0f - fabsf(sinf((time / duration * 180.0f + 90.0f) * 0.017453292f))) + from;
}

}  // namespace ui
