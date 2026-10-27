#ifndef CLASSES_GF_GFMENUOBJBLADESET2_H
#define CLASSES_GF_GFMENUOBJBLADESET2_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuSequence.h"
#include "classes/ui/UIManager.h"
#include "ui/EventData.h"

namespace gf { class GfMenuBladeList; class GfMenuCallContext; class GfMenuDriverList; }
namespace mm { namespace mtl { class ReferenceObject; } }

namespace gf {
// table 0x7100B602E8. Field names are not the original's.
class GfMenuObjBladeSet2 : public ::gf::GfMenuObject {
public:
    class BladeListListener;
    class BladeSlotListener;
    class MainListener;
    GfMenuObjBladeSet2(unsigned int handle);
    virtual ~GfMenuObjBladeSet2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // register how the full-screen layer of menu 0x1E is closed: 1 returns, 2 closes the full screen
    static void setCloseToReturn();
    static void setCloseToFSClose();
    // the file's inline helpers (the shape of GfMenuObjDrKizunaRing's; the names are not the original's): the
    // event fade of MainListener's open (1) and close (2), and an event sent to an object
    static int setFadeIn(unsigned int handle) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    static int setFadeOut(unsigned int handle) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 2;
        int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        ui::EventData event;
        event.m_type = type;
        event.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
    bool seqOpenImage();
    bool seqReturnBlSlot();
    void refreshBladeSlot(GfMenuBladeList* list);
    void refreshBladeList();

    GfMenuBladeList* m_slotList;            // 0x28: initialize's (the destructor releases it)
    mm::mtl::ReferenceObject* pad_30;
    GfMenuBladeList* m_bladeList;           // 0x38: initialize's, the scroll bar's list
    mm::mtl::ReferenceObject* pad_40;
    GfMenuDriverList* m_driverList;         // 0x48: initialize's
    mm::mtl::ReferenceObject* pad_50;
    int pad_58;
    GfMenuCallContext* m_context;           // 0x60: initialize's
    int pad_68;
    unsigned char pad_6C[0xC];
    bool pad_78;
    GfMenuCallContext* m_subContext;        // 0x80: initialize's
    bool pad_88;
    int pad_8C;
    int pad_90;
    int pad_94;
    int m_openType;                         // 0x98: the layer param's menu word (MainListener: 0 char select, 1 main menu)
    int m_faceCount;                        // 0x9C: the constructor leaves it; initialize's count of "LAY_bl_facelayout@%02d"
    GfMenuSequence<GfMenuObjBladeSet2, 8> m_seq;     // 0xA0
    unsigned char pad_330[8];  // the constructor leaves it
    GfMenuSequence<GfMenuObjBladeSet2, 4> m_subSeq;  // 0x338
};
}  // namespace gf

#endif
