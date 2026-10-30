#ifndef CLASSES_GF_GFMENUOBJSAVELOAD2_H
#define CLASSES_GF_GFMENUOBJSAVELOAD2_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/ui/UIManager.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"
#include "ui/EventData.h"

namespace ui {
class UIObjectAcc;
class UIObjectNumberPlugin;
class UIObjectTextPlugin;
class UIObjectTimePlugin;
class UISelectObjList;
}  // namespace ui

namespace gf {
class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuDriverList;

// table 0x7100B646C8
class GfMenuObjSaveLoad2 : public ::gf::GfMenuObject {
public:
    class MainListener;
    // what GfMenuManager::openSave passes registOpenParam (the field name is not the original's)
    struct OpenParam {
        unsigned short m_mode;  // 1 from openSave
    };
    GfMenuObjSaveLoad2(unsigned int handle);
    static void registOpenParam(const OpenParam& param);
    virtual ~GfMenuObjSaveLoad2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // the three party drivers' names and levels, the clock, progress, play time and area texts on "LAY_main"
    void setupSave(ui::UIObjectAcc& acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber>* numbers);
    void refreshSave(ui::UIObjectAcc& acc, unsigned int);
    // the save sequence's jobs: request the save (slot 22) and wait for it, then refresh and either reopen the
    // input or close the menu
    bool seqSave();
    bool seqSaveWait();
    bool seqSaveWaitToClose();

    // 1.0.0's setFadeIn/setFadeOut (0x71004C9858, 0x71004C9BC0) and sendEvent (0x71004C9964), out of line there;
    // 3.0.1 inlines them: the common fade of that type (0 the preset, 1 from the left, 2 from the right), heard by
    // the handle's object, and an event of that type and first parameter to the handle's object
    static int setFadeIn(unsigned int handle, unsigned int type) {
        int ctrl = -1;
        switch (type) {
        case 0: {
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 6;
            param.m_out = 0;
            param.m_eventId = 1;
            ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
            break;
        }
        case 1: {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l_early";
            param.m_eventId = 1;
            param.m_setDefault = true;
            ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
            break;
        }
        case 2: {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_r_early";
            param.m_eventId = 1;
            param.m_setDefault = true;
            ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
            break;
        }
        }
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    static int setFadeOut(unsigned int handle, unsigned int type) {
        int ctrl = -1;
        switch (type) {
        case 0: {
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 6;
            param.m_out = 1;
            param.m_eventId = 2;
            ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
            break;
        }
        case 1: {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_l_early";
            param.m_startFlags = 10;
            param.m_eventId = 2;
            param.m_setDefault = true;
            ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
            break;
        }
        case 2: {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_r_early";
            param.m_startFlags = 10;
            param.m_eventId = 2;
            param.m_setDefault = true;
            ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
            break;
        }
        }
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        ui::EventData event;
        event.m_type = type;
        event.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }

    GfMenuCallContext* m_context;  // 0x28: initialize creates it (the confirmation texts run on it)
    GfMenuSequence<GfMenuObjSaveLoad2, 8> m_seq;  // 0x30: update runs it (the name is not the original's)
    unsigned int m_saveReq;  // 0x2C0: seqSave's GfReqCommand::reqSave handle, -1 for none (the name is not the original's)
    unsigned short m_mode;  // 0x2C4: the OpenParam's (registOpenParam's layer parameter); 0 from the main menu
    ui::UISelectObjList* m_selectList;  // 0x2C8: initialize creates it (the names below are not the original's)
    ui::UIObjectTimePlugin* m_yearPlugin;  // 0x2D0: setupSave's, on "TXT_year_num"
    ui::UIObjectTimePlugin* m_timePlugin;  // 0x2D8: on "TXT_time_num"
    ui::UIObjectNumberPlugin* m_progressPlugin;  // 0x2E0: on "TXT_progress"
    ui::UIObjectTimePlugin* m_gameTimePlugin;  // 0x2E8: on "TXT_game_time"
    ui::UIObjectTextPlugin* m_areaPlugin;  // 0x2F0: on "TXT_area"
    GfMenuDriverList* m_drivers;  // 0x2F8: initialize creates it (the party's drivers)
    GfMenuBladeList* m_blades;  // 0x300: initialize creates it (a team's blades)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_numbers[3];  // 0x308: the drivers' levels (setupSave)
    // 0x320: which confirmation the common text asked: 0 save (text 0x9D), 1 close (text 0xE3); the name is not the
    // original's
    int m_confirm;
};
}  // namespace gf

#endif
