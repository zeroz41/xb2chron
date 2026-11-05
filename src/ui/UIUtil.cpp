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
#include "mtl/MemManager.h"
#include "classes/ml/DevGraph.h"

namespace ui { namespace UIUtil {


fw::PointerMap s_ObjPtrMap;
unsigned int s_ObjPtrMax;
fw::MemHandlebaseAllocator s_ProgAllocator;
fw::MemHandlebaseAllocator s_ResAllocator;
unsigned char* s_BdatFPs[17];
unsigned int s_SafeMarginW;
unsigned int s_SafeMarginH;
// 2.0.0's symbols name it
unsigned int s_ResourceReplaceID;
// 2.0.0's symbols name it
unsigned int s_EnableExpFlag = 1;
// 2.0.0's symbols name it
const char* s_pRootFolder = "menu";

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

void setResourceReplaceID(unsigned int no) {
    s_ResourceReplaceID = no;
}

void changeRootFolder(const char* dir) {
    s_pRootFolder = dir;
}

const char* getRootFolder() {
    return s_pRootFolder;
}

void registEnableExpType(unsigned int bit) {
    s_EnableExpFlag |= 1 << bit;
}

bool isEnableExpType(unsigned int bit) {
    return (s_EnableExpFlag & (1 << bit)) != 0;
}

bool canUIOReplace(const char* file) {
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

unsigned char* getLayerBdat(unsigned int dlc) {
    if (dlc == 0) {
        return s_BdatFPs[6];
    }
    if (isEnableExpType(dlc)) {
        mm::mtl::FixStr<32> name;
        name.format("MNU_Layer_Dlc%02d", dlc);
        return Bdat::getFP(name.m_str);
    }
    return nullptr;
}

// the file name of path (after its last '/' or '\\') in lower case, unless it holds a character past 0x80 (every
// makeMenu*FileName inlines it; the name is not the original's)
static inline void lowerFileName(mm::mtl::FixStr<128>& path) {
    int pos = path.findLast('/');
    if (pos == -1) {
        pos = path.findLast('\\');
    }
    int start = pos == -1 ? 0 : pos;
    for (int i = start; i < path.m_nLen; i++) {
        if (static_cast<unsigned char>(path.m_str[i]) > 0x80) {
            return;
        }
    }
    for (int i = start; i < path.m_nLen; i++) {
        if (path.m_str[i] >= 'A' && path.m_str[i] <= 'Z') {
            path.m_str[i] += 0x20;
        }
    }
}

void makeMenuFontDataFileName(mm::mtl::FixStr<128>& path, const char* name) {
    path.format("/%s/font/%s", s_pRootFolder, name);
    if (strstr(name, ".wifnt") == nullptr) {
        path += ".wifnt";
    }
    lowerFileName(path);
}

void makeMenuFontStyleFileName(mm::mtl::FixStr<128>& path, const char* name) {
    path.format("/%s/font/%s", s_pRootFolder, name);
    if (strstr(name, ".wisty") == nullptr) {
        path += ".wisty";
    }
    lowerFileName(path);
}

void makeMSProjFileName(mm::mtl::FixStr<128>& path, const char* name) {
    path.format("/%s/msproj/%s", s_pRootFolder, name);
    if (strstr(name, ".msbp") == nullptr) {
        path += ".msbp";
    }
    lowerFileName(path);
}

void makeMenuImageFileName(mm::mtl::FixStr<128>& path, const char* name) {
    path.format("/%s/image/%s", s_pRootFolder, name);
    if (strstr(name, ".wilay") == nullptr) {
        path += ".wilay";
    }
    lowerFileName(path);
}

void makeMenuLayoutFileName(mm::mtl::FixStr<128>& path, const char* name) {
    path.format("/%s/layout/%s", s_pRootFolder, name);
    if (strstr(name, ".wilay") == nullptr) {
        path += ".wilay";
    }
    lowerFileName(path);
}

void makeMenuUIOFileName(mm::mtl::FixStr<128>& path, const char* name) {
    if (s_ResourceReplaceID != 0) {
        unsigned char* fp = s_BdatFPs[16];
        if (fp != nullptr) {
            mm::mtl::FixStr<32> column;
            column.format("replace%02d", s_ResourceReplaceID);
            if (Bdat::getMember(fp, column.m_str) != nullptr) {
                for (int i = 0; i < Bdat::getIdCount(fp); i++) {
                    int id = Bdat::getIdTop(fp) + i;
                    if (strcmp(name, reinterpret_cast<const char*>(Bdat::getVal(fp, "file", id))) == 0) {
                        name = reinterpret_cast<const char*>(Bdat::getVal(fp, column.m_str, id));
                    }
                }
            }
        }
    }
    path.format("/%s/object/%s", s_pRootFolder, name);
    if (strstr(name, ".uio") == nullptr) {
        path += ".uio";
    }
    lowerFileName(path);
}

void makeMenuUIMFileName(mm::mtl::FixStr<128>& path, const char* name) {
    path.format("/%s/motion/%s", s_pRootFolder, name);
    if (strstr(name, ".uim") == nullptr) {
        path += ".uim";
    }
    lowerFileName(path);
}

void makeMenuUIPFileName(mm::mtl::FixStr<128>& path, const char* name) {
    path.format("/%s/particle/%s", s_pRootFolder, name);
    if (strstr(name, ".uip") == nullptr) {
        path += ".uip";
    }
    lowerFileName(path);
}

void makeMenuEnvFileName(mm::mtl::FixStr<128>& path, const char* name) {
    path.format("/map/%s", name);
    if (strstr(name, ".wismhd") == nullptr) {
        path += ".wismhd";
    }
    lowerFileName(path);
}

void setupAllocator(mtl::ALLOC_HANDLE handle) {
    mtl::ALLOC_HANDLE prog =
        mtl::MemManager::create(handle, 0x500000, "MenuProgram", false, mtl::AllocatorType(1), 0x10, "no name", 0);
    mtl::ALLOC_HANDLE res =
        mtl::MemManager::create(handle, 0x5500000, "MenuResource", false, mtl::AllocatorType(2), 0x1000, "no name", 0);
    ml::DevGraph::setMemPoolMemHandle(res);
    s_ProgAllocator.m_name = "MenuProgram";
    s_ProgAllocator.setMemHandle(prog);
    s_ResAllocator.m_name = "MenuResource";
    s_ResAllocator.setMemHandle(res);
}

void destoryAllocator() {
    mtl::ALLOC_HANDLE handle;
    handle = s_ProgAllocator.getMemHandle();
    if (handle.m_handle != 0) {
        mtl::MemManager::erase(handle);
        s_ProgAllocator.setMemHandle(mtl::ALLOC_HANDLE());
    }
    handle = s_ResAllocator.getMemHandle();
    if (handle.m_handle != 0) {
        ml::DevGraph::releaseMemPoolMemHandle(handle);
        mtl::MemManager::erase(handle);
        s_ResAllocator.setMemHandle(mtl::ALLOC_HANDLE());
    }
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

bool adjustScreen(mm::Rect<short>& rect) {
    auto right = [](const mm::Rect<short>& r) -> short { return r.x + r.w; };
    auto bottom = [](const mm::Rect<short>& r) -> short { return r.y + r.h; };
    layer::LayerAccManager manager;
    mm::Rect<short> r;
    r = rect;
    mm::Rect<short> screen;
    screen.x = s_SafeMarginW;
    screen.w = (int)manager.getScreenWidth() - s_SafeMarginW * 2;
    screen.y = s_SafeMarginH;
    screen.h = (int)manager.getScreenHeight() - s_SafeMarginH * 2;
    if (screen.x <= rect.x && right(screen) > right(rect) && screen.y <= rect.y && bottom(screen) > bottom(rect)) {
        return false;
    }
    if (r.x < screen.x) {
        r.x = screen.x;
    }
    if (r.y < screen.y) {
        r.y = screen.y;
    }
    if (r.x + r.w > screen.x + screen.w) {
        r.x = screen.x + screen.w - r.w;
    }
    if (r.y + r.h > screen.y + screen.h) {
        r.y = screen.y + screen.h - r.h;
    }
    rect = r;
    return true;
}

bool adjustRect(mm::Rect<short>& rect, mm::Rect<short>& area) {
    auto right = [](const mm::Rect<short>& r) -> short { return r.x + r.w; };
    auto bottom = [](const mm::Rect<short>& r) -> short { return r.y + r.h; };
    if (area.x <= rect.x && right(area) > right(rect) && area.y <= rect.y && bottom(area) > bottom(rect)) {
        return false;
    }
    if (rect.x < area.x) {
        rect.x = area.x;
    }
    if (rect.y < area.y) {
        rect.y = area.y;
    }
    if (rect.x + rect.w > area.x + area.w) {
        rect.x = area.x + area.w - rect.w;
    }
    if (rect.y + rect.h > area.y + area.h) {
        rect.y = area.y + area.h - rect.h;
    }
    return true;
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

void setDockPos(unsigned int handle, unsigned int target, unsigned char side, bool outer) {
    UIObjectAcc acc(handle);
    UIObjectAcc targetAcc(target);
    unsigned short mode = outer ? 3 : 2;
    if (acc.m_object != nullptr && targetAcc.m_object != nullptr) {
        short width;
        mm::Pnt<short> pos;
        short height;
        acc.getSize(true, width, height);
        width /= 2;
        height /= 2;
        mm::Rect<short> rect;
        targetAcc.getRect(rect, mode);
        pos.x = rect.x + rect.w / 2;
        pos.y = rect.y + rect.h / 2;
        switch (side) {
        case 0:
            break;
        case 1:
            pos.x -= rect.w / 2 + width;
            break;
        case 2:
            pos.x += rect.w / 2 + width;
            break;
        case 3:
            pos.y = pos.y - height - rect.h / 2;
            break;
        case 4:
            pos.y = height + pos.y + rect.h / 2;
            break;
        default:
            return;
        }
        acc.setPosCenter(pos);
    }
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
