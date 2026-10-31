#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/gf/GfBladeCreateInfo.h"  // classes/gf/GfBladeCreateInfo.h (new; same folder)

namespace mm { namespace mtl { class ReferenceObject; } }

namespace gf {
class GfMenuCallContext;
class GfMenuModelView;
class GfMenuItemList;
class GfMenuReferenceNumber;
class GfMenuBladeCreateCamera;

// table 0x7100B5FF10
class GfMenuObjBladeCreate : public ::gf::GfMenuObject {
public:
    class BoosterNumListener;
    class BoosterSelectListener;
    class ConfirmListener;
    class CreationListener;
    class CrystalSelectListener;
    class DriverSelectListener;
    class IdeagramListener;
    class MainListener;
    class ResultListener;
    // what registOpenParam keeps for the next open (ScriptPlayText's ui openBladeCreate passes its script
    // argument); the name is not the original's
    struct OpenParam {
        unsigned int m_value;
    };
    // a page sequence's state (the name is 1.0.0's: changePage, nextPage and returnPage take it); the field names
    // are not the original's
    struct PageContext {
        unsigned int m_page;  // the page shown: nextPage and returnPage step from it (0xFF steps on to 0)
        unsigned char pad_04[0x28];
        bool m_skipPage2;     // pages 1 and 3 step over page 2 while it is set
        bool m_confirmed;     // ConfirmListener sets it on a yes (its text's result 1, 1) and clears it on open
        unsigned char pad_2E[0xA];
        GfMenuCallContext* m_callContext;  // the confirmation text's (GfMenuObjCommonText::open)
    };
    GfMenuObjBladeCreate(unsigned int handle);
    static void registOpenParam(const OpenParam& param);
    static void openCreatedBladeName(GfMenuCallContext* context);
    virtual ~GfMenuObjBladeCreate();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // inline helpers (the names are not the original's; their CtrlParams sit above a listener's acc in the frame,
    // as an inlined callee's locals do): IdeagramListener's and ResultListener's fade in (0x21) and out (0x22)
    static void fadeIn(unsigned int handle) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 1;
        param.m_time = 0.5f;
        param.m_eventId = 1;
        GfMenuObjUtil::startCtrl(handle, param, nullptr);
    }
    static void fadeOut(unsigned int handle) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_startFlags = 2;
        param.m_time = 0.25f;
        param.m_eventId = 2;
        GfMenuObjUtil::startCtrl(handle, param, nullptr);
    }

    void changePage(unsigned int handle, PageContext* context, unsigned int page, bool, bool);
    // 1.0.0 has both out of line (0x71003F62E8, 0x71003F6358); 3.0.1 inlines them: the page after and before the
    // context's (changePage, its first flag set; nextPage passes its own, returnPage ignores it)
    void nextPage(unsigned int handle, PageContext* context, bool);
    void returnPage(unsigned int handle, PageContext* context, bool);
    void updateIdea(bool);
    // shows or hides the guide layer (1.0.0 has it out of line, 0x71003F664C; 3.0.1 inlines it)
    void dispGuideText(bool disp);
    void setGuideText(unsigned int);

    // m_seq's jobs
    bool seqStart();
    bool seqWaitLoading();
    bool seqEnd();
    bool seqSave();
    bool seqSaveWait();
    bool seqResultStart();
    bool seqResultConfirm();
    bool seqCreateStartSE();
    bool seqCreateWaitFade();
    bool seqCreatePlayJingle();
    bool seqCreatePlayBgmAfter();

    unsigned char pad_24[4];
    // the page updateIdea compares (> 1) and seqEnd enables the full-screen input of; the name is not the original's
    unsigned int m_page;
    unsigned char pad_2C[4];
    void* pad_30[4];  // the constructor zeroes 0x30..0x50
    unsigned char pad_50[8];
    void* pad_58[2];  // the constructor zeroes 0x58..0x68
    unsigned char pad_68[0x10];
    // the booster list: BoosterNumListener's open caps the number at its selected item's count (the name is not the
    // original's)
    GfMenuItemList* m_boosterList;
    GfBladeCreate m_bladeCreate;  // 0x80 (the name is not the original's)
    mm::mtl::FixedVector<unsigned int, 10> pad_AB8;  // a FixedVector of 0x28 bytes (element type unknown)
    unsigned char pad_AE8[8];
    GfMenuModelView* m_modelView;  // 0xAF0: seqWaitLoading waits for its loading, update updates it
    GfMenuSequence<GfMenuObjBladeCreate, 20> m_seq;  // 0xAF8
    void* pad_1118;
    bool pad_1120;  // cleared by the constructor, seqStart and seqResultStart; nothing in 3.0.1 sets it
    mm::mtl::FixedVector<unsigned int, 4> pad_1128;  // a FixedVector of 0x10 bytes (element type unknown)
    unsigned long pad_1140;  // the constructor sets 4
    unsigned char pad_1148[8];
    // reference-counted objects the destructor releases (in the order 0x1160, 0x1168, 0x1150, 0x1158, 0x11A8)
    mm::mtl::ReferenceObject* pad_1150;
    mm::mtl::ReferenceObject* pad_1158;
    mm::mtl::ReferenceObject* pad_1160;
    mm::mtl::ReferenceObject* pad_1168;
    void* pad_1170;
    void* pad_1178;
    unsigned int pad_1180;
    unsigned char pad_1184[4];
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_number;  // the constructor creates it (the name is not the original's)
    GfMenuBladeCreateCamera* m_camera;  // the constructor creates it (the name is not the original's)
    int pad_1198;  // the constructor sets -1
    unsigned char pad_119C[4];
    unsigned int pad_11A0;
    unsigned char pad_11A4[4];
    mm::mtl::ReferenceObject* pad_11A8;
    // seqSave's GfReqCommand::reqSave handle, -1 once seqSaveWait saw it end; the name is not the original's
    unsigned int m_saveReq;
    bool pad_11B4;
    unsigned int pad_11B8;
    unsigned char pad_11BC[4];
    unsigned int m_bgm;  // the handle seqCreatePlayJingle stops (GfMenuObjUtil::stopBGM); the name is not the original's
    // three sound handles MainListener's event 2 stops in a loop (the name is not the original's): [1] is the one
    // seqCreateStartSE stops first, [2] its "se_fld_allmap_715"
    unsigned int m_se[3];
};
}  // namespace gf

#endif
