#ifndef CLASSES_GF_GFFIELDMAPGIMMICK_H
#define CLASSES_GF_GFFIELDMAPGIMMICK_H

#include "classes/gf/AFieldSeq.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gmk/BootedGmkCond.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/WeatherCond.h"
#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkCamera.h"
#include "classes/gmk/GmkCtrlVolSe.h"
#include "classes/gmk/GmkMapGimmick.h"
namespace gf { class GF_OBJ_HANDLE; }
class CBdatWrapper;

namespace gf {
// table 0x7100B522A0; the base at 0x28 is mm::mtl::PtrSingleton<gf::GfFieldMapGimmick> (its secondary table at
// 0x7100B52308; the destructor stores PtrSingleton's table and clears the instance). Runs a map gimmick's field
// skill sequence, then its gimmick camera, LOD animation and map object steps.
class GfFieldMapGimmick : public ::gf::AFieldSeq, public ::mm::mtl::PtrSingleton< ::gf::GfFieldMapGimmick> {
public:
    // the gimmick's row (BdatInfo::create reads the columns its fields are named after)
    class BdatInfo {
    public:
        BdatInfo() : m_opCondition(0), m_camGimAtr(0), m_gmkCamPos(false), m_nowaitGmkCam(false), m_bootedGmk(0, 0) {}
        void create(CBdatWrapper bdat, int row);
        bool isCondMatched() const;

        unsigned short m_opCondition;  // OP_Condition (GfGameCond::isGameCond)
        unsigned char m_camGimAtr;     // camGim_ATR
        bool m_gmkCamPos;              // gmkCamPos
        bool m_nowaitGmkCam;           // nowaitGmkCam
        unsigned char pad_5;
        gmk::BootedGmkCond m_bootedGmk;
        gmk::ScenarioFlagCond m_scenarioFlag;
        gmk::QuestFlagCond m_questFlag;
        unsigned char pad_12[0x6];
        gmk::TimeCond m_time;        // OP_Time
        gmk::WeatherCond m_weather;  // OP_weather
    };

    GfFieldMapGimmick(const GfSetupParam& param);
    virtual const char* getIdStr() const {  // slot 0
        static const char s_classId[] = "GfFieldMapGimmick";
        return s_classId;
    }
    virtual void create(gf::GF_OBJ_HANDLE* handle);  // slot 1
    virtual void dispose();  // slot 2
    virtual bool isEnd() const;  // slot 3
    virtual ~GfFieldMapGimmick() {}  // slot 5
    virtual void onFsSucceeded();  // slot 7
    virtual void onFsFailed();  // slot 8
    void update(float dt);
    void clearSe();
    void seqCamera_waitToLoaded(float dt);
    void seqCamera_waitToEnd(float dt);
    void seqLod_init(float dt);
    void seqLod_waitToEndAnim(float dt);
    void seqLod_waitToElapseTime(float dt);
    void seqMapObj_init(float dt);
    void seqMapObj_nextwait(float dt);

    // (the field names below are not the original's)
    BdatInfo m_bdatInfo;
    gmk::GmkAcc m_gmkAcc;
    gmk::GmkCamera m_camera;
    void (GfFieldMapGimmick::*m_seqCamera)(float dt);  // the gimmick camera's step
    void (GfFieldMapGimmick::*m_seqLod)(float dt);     // the LOD animation's step
    unsigned int m_lodStep;  // seqLod_waitToElapseTime runs seqLod_init again until it passes 4
    int m_lodAnim;  // GfFieldLod::isPlayAnimEnd's argument
    void (GfFieldMapGimmick::*m_seqMapObj)(float dt);  // the map object's step
    // a third step (fn_710027AA68 and fn_710027B500 are its; meaning not known)
    void (GfFieldMapGimmick::*m_seqOther)(float dt);
    float m_waitTime;     // the time the waits wait for
    float m_elapsedTime;  // the time waited so far
    gmk::GmkCtrlVolSe m_se[5];
    unsigned int m_seHandle;  // a sound clearSe stops when it loops
    unsigned char m_solveState;  // 2 after SCOM_QUEST_GIMMICK::createMapGimmick and GmkMapGimmick::setSolved
};
}  // namespace gf

#endif
