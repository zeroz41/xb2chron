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
class GfMenuDriverList;
class GfSequentialPlaySignal;

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
    // a page sequence's state (the name is 1.0.0's: changePage, nextPage and returnPage take it); the field names
    // are not the original's. It runs from 0x28 to the model view (0xAF0): changePage reads the model view through
    // the context (context + 0xAC8). The constructor zeroes its 0x08..0x28 and 0x30..0x40.
    struct PageContext {
        // GfMenuObjBladeCreate's constructor zeroes these (0x30..0x50, 0x58, 0x60) and the FixedVector's size
        PageContext() : pad_08(), pad_30(nullptr), m_callContext(nullptr), pad_A90() {}
        unsigned int m_page;      // the page shown: nextPage and returnPage step from it (0xFF steps on to 0)
        unsigned int m_prevPage;  // changePage keeps the page it leaves here
        unsigned char pad_08[0x20];
        // the blade being created (seqCreateStartEvent's GfDataBlade::getCreateEvent and createBlEvent get it,
        // seqResultEnd deletes its model, delGfObj type 4)
        unsigned int m_blade;
        bool m_skipPage2;     // pages 1 and 3 step over page 2 while it is set
        bool m_confirmed;     // ConfirmListener sets it on a yes (its text's result 1, 1) and clears it on open
        unsigned char pad_2E[2];
        mm::mtl::ReferenceObject* pad_30;  // 0x58: finalize releases it
        // the confirmation text's (GfMenuObjCommonText::open); finalize releases it
        GfMenuCallContext* m_callContext;
        // 0x68: the driver list (seqCreateStartDriver and seqCreateWaitDriver find the selected driver's model by
        // its id)
        GfMenuDriverList* m_driverList;
        mm::mtl::ReferenceObject* pad_48;  // 0x70: finalize releases it
        // 0x78: the booster list: BoosterNumListener's open caps the number at its selected item's count
        GfMenuItemList* m_boosterList;
        GfBladeCreate m_bladeCreate;  // 0x80
        mm::mtl::FixedVector<unsigned int, 10> pad_A90;  // 0xAB8: a FixedVector of 0x28 bytes (element type unknown)
        unsigned char pad_AC0[8];
        // 0xAF0: seqWaitLoading waits for its loading, update updates it, changePage moves its camera
        GfMenuModelView* m_modelView;
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

    // the page's UI object (a child of the handle's, or its sibling), 0 without a handle or for page 6 on. 1.0.0 has
    // it out of line (0x71003F60BC); 3.0.1 inlines it into changePage (defined inline in the unit)
    unsigned int getPageObject(unsigned int handle, unsigned int page, bool sibling);
    void changePage(unsigned int handle, PageContext* context, unsigned int page, bool sibling, bool popCamera);
    // 1.0.0 has both out of line (0x71003F62E8, 0x71003F6358); 3.0.1 inlines them: the page after and before the
    // context's (changePage, its first flag set; nextPage passes its own, returnPage ignores it)
    void nextPage(unsigned int handle, PageContext* context, bool sibling) {
        unsigned int page = 0;
        switch (context->m_page) {
        case 0:
            page = 1;
            break;
        case 1:
            page = context->m_skipPage2 ? 3 : 2;
            break;
        case 2:
            page = 3;
            break;
        case 3:
            page = 4;
            break;
        case 4:
            page = 5;
            break;
        case 5:
            break;
        case 0xFF:
            break;
        default:
            return;
        }
        changePage(handle, context, page, sibling, false);
    }
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
    bool seqSetupDriverObj();
    bool seqSetupCrystal();
    void refreshCrystalList();
    bool seqCreateStart();
    bool seqCreateSetup();
    // 2.0.0's symbols name it (not in 1.0.0; between seqCreateSetup and seqCreateStartDriver): once no fade runs, steps
    // the page sequence on
    bool seqCreateSkipToReslt();
    // 2.0.0's symbols name it (not in 1.0.0, whose seqCreateStart is followed by ResultListener::reciveEvent);
    // CreationListener queues it: once no fade runs, idles the driver, hides the drivers and the crystals and
    // queues seqCreateSkipToReslt
    bool seqCreateSkip();
    bool seqCreateStartDriver();
    bool seqCreateWaitDriver();
    bool seqCreateBuildBlade();
    bool seqCreateCtrlBlade();
    bool seqCreateWaitBlade();
    bool seqCreateStartEvent();
    bool seqCreateWaitEvent();
    bool seqResultEnd();

    unsigned char pad_24[4];
    // 0x28: the main page sequence's (changePage, nextPage and returnPage get it; its m_page is the page updateIdea
    // compares (> 1) and seqEnd enables the full-screen input of); the name is not the original's
    PageContext m_pageContext;
    GfMenuSequence<GfMenuObjBladeCreate, 20> m_seq;  // 0xAF8
    // seqCreateStartEvent's (handed to GfPlayFactory::createBlEvent); seqCreateWaitEvent waits for it to clear and
    // deletes it. The name is not the original's
    GfSequentialPlaySignal* m_eventSignal;
    // seqResultConfirm sets it once it opened its common window (7); cleared by the constructor, seqStart,
    // seqResultStart and seqResultConfirm once the window is answered
    bool pad_1120;
    mm::mtl::FixedVector<unsigned int, 4> pad_1128;  // a FixedVector of 0x10 bytes (element type unknown)
    unsigned int pad_1140;  // the constructor sets 4
    // the step seqCreateCtrlBlade runs on the first blade of pad_1128 (0, 1, 2; seqCreateWaitBlade steps it on and
    // seqCreateBuildBlade clears it)
    unsigned int pad_1144;
    // seqCreateSetup clears it; seqCreateStartEvent stops the model view's effect one past it; seqCreateCtrlBlade
    // plays its effect in that slot and counts it up
    unsigned int pad_1148;
    unsigned int pad_114C;  // seqCreateCtrlBlade's step 0 sets 15
    // reference-counted objects the destructor releases (in the order 0x1160, 0x1168, 0x1150, 0x1158, 0x11A8)
    mm::mtl::ReferenceObject* pad_1150;
    mm::mtl::ReferenceObject* pad_1158;
    mm::mtl::ReferenceObject* pad_1160;
    mm::mtl::ReferenceObject* pad_1168;
    unsigned int pad_1170;
    // the number updateIdea keeps for a booster when asked (by the booster list's selected index; BoosterNumListener
    // asks on a decide). Name and size inferred: 0x1174..0x1180
    unsigned int m_boosterNumbers[3];
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
    bool pad_11BC;  // seqResultConfirm adds the blade to the party straight away while it and pad_11B4 are set
    unsigned char pad_11BD[3];
    unsigned int m_bgm;  // the handle seqCreatePlayJingle stops (GfMenuObjUtil::stopBGM); the name is not the original's
    // three sound handles MainListener's event 2 stops in a loop (the name is not the original's): [1] is the one
    // seqCreateStartSE stops first, [2] its "se_fld_allmap_715"
    unsigned int m_se[3];
};
}  // namespace gf

#endif
