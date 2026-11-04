#ifndef CLASSES_GF_GFBDATRSC_H
#define CLASSES_GF_GFBDATRSC_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatRsc; }

namespace gf {
// table 0x7100B47288; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatRsc : public ::mm::mtl::PtrSingleton< ::gf::GfBdatRsc>, public ::gf::IDataBdat {
public:
    GfBdatRsc();
    virtual ~GfBdatRsc();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    void createFP();
    unsigned int getRscEnTypeFamily(unsigned int id) const;
    unsigned int getRscEnTypeGenus(unsigned int id) const;
    unsigned int getRscEnActType(unsigned int id) const;
    int getRscEnFlyHeight(unsigned int id) const;
    unsigned int getRscEnFldMoveType(unsigned int id) const;
    unsigned int getRscEnMaterial(unsigned int id) const;
    unsigned int getRscEnEnRadius(unsigned int id) const;
    unsigned int getRscEnEnRadius2(unsigned int id) const;
    unsigned int getRscEnChestHeight(unsigned int id) const;
    unsigned int getRscEnChestHeight2(unsigned int id) const;
    float getRscEnBallRadius(unsigned int id) const;
    float getRscEnBallHeight(unsigned int id) const;
    float getRscEnCharColli(unsigned int id) const;
    unsigned int getRscEnoffsetID(unsigned int id) const;
    unsigned int getRscEnEyeRot(unsigned int id) const;
    const char* getRscEnSearchBaseBone(unsigned int id) const;
    const char* getRscEnCenterBone(unsigned int id) const;
    const char* getRscEnCamBone(unsigned int id) const;
    unsigned int getRscEnFrontAngle(unsigned int id) const;
    const char* getRscEnModel(unsigned int id) const;
    const char* getRscEnMotion(unsigned int id) const;
    const char* getRscEnRefMotion(unsigned int id) const;
    const char* getRscEnEffectPack(unsigned int id) const;
    const char* getRscEnLoopEffect(unsigned int id) const;
    const char* getRscEnSePack(unsigned int id) const;
    const char* getRscEnVoice(unsigned int id) const;
    unsigned int getRscEnVoiceEx(unsigned int id) const;
    const char* getRscEnComp_Eff(unsigned int id) const;
    bool isRscEnFlagBait(unsigned int id) const;
    bool isRscEnFlagNoVanish(unsigned int id) const;
    bool isRscEnFlagNoCamera(unsigned int id) const;
    bool isRscEnFlagWeaponDrawDisp(unsigned int id) const;
    bool isRscEnFlagJoinAll(unsigned int id) const;
    bool isRscEnFlagDeathMotion(unsigned int id) const;
    unsigned int getRscEnMemorySlot(unsigned int id) const;
    unsigned int getRscEnRace(unsigned int id) const;
    unsigned int getRscEnDrType(unsigned int id) const;
    int getRscEnGoldDivideRev(unsigned int id) const;
    unsigned int getRscEnFootStep(unsigned int id) const;
    unsigned int getRscEnFootStepEffect(unsigned int id) const;
    int getRscEnRotateX(unsigned int id) const;
    int getRscEnRotateY(unsigned int id) const;
    int getRscEnRotateZ(unsigned int id) const;
    int getRscEnRotateDeg(unsigned int id) const;
    unsigned int getRscEnRotEffScale(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns _gfbrs::getRscEnExtraParts5(*m_fpRscEn, id).
    unsigned int getRscEnExtraParts5(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns _gfbrs::getRscEnExtraParts6(*m_fpRscEn, id).
    unsigned int getRscEnExtraParts6(unsigned int id) const;
    unsigned int getRscEnDeadSeNum(unsigned int id) const;
    unsigned int getRscEnWeaponNum(unsigned int id, unsigned int slot) const;
    unsigned int getRscEnExtraParts(unsigned int id, unsigned int slot) const;
    const char* getRscEnRotateBone(unsigned int id) const;
    unsigned int getRscEnGenusNAME(unsigned int id) const;
    bool isRscEnGenusFlaggimmicktype(unsigned int id) const;
    unsigned int getRscNpcListStart() const;
    unsigned int getRscNpcListEnd() const;
    const char* getRscNpcListModel(unsigned int id) const;
    const char* getRscNpcListMotion(unsigned int id) const;
    const char* getRscNpcListAddMotion(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns getRscNpcListEvtRetarget(*m_fpRscNpcList, id).
    unsigned int getRscNpcListEvtRetarget(unsigned int id) const;
    const char* getRscNpcListComp_Eff(unsigned int id) const;
    unsigned int getRscNpcListCollisionId(unsigned int id) const;
    unsigned int getRscNpcListRace(unsigned int id) const;
    unsigned int getRscNpcListFootStep(unsigned int id) const;
    unsigned int getRscNpcListFootStepEffect(unsigned int id) const;
    unsigned int getRscNpcListRoots(unsigned int id) const;
    unsigned int getRscNpcListGender(unsigned int id) const;
    unsigned int getRscNpcListName(unsigned int id) const;
    unsigned int getRscNpcListOffsetID(unsigned int id) const;
    unsigned int getRscNpcListEyeRot(unsigned int id) const;
    unsigned int getRscNpcListScale(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns getRscNpcListJob(*m_fpRscNpcList, id).
    unsigned int getRscNpcListJob(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns getRscNpcListHitonowaFlag(*m_fpRscNpcList, id).
    unsigned int getRscNpcListHitonowaFlag(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns getRscNpcListNpcMeetFlag(*m_fpRscNpcList, id).
    unsigned int getRscNpcListNpcMeetFlag(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns getRscNpcListMSGID(*m_fpRscNpcList, id).
    unsigned int getRscNpcListMSGID(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns getRscNpcListCondition1(*m_fpRscNpcList, id).
    unsigned int getRscNpcListCondition1(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns getRscNpcListMSGID2(*m_fpRscNpcList, id).
    unsigned int getRscNpcListMSGID2(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns getRscNpcListCondition2(*m_fpRscNpcList, id).
    unsigned int getRscNpcListCondition2(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns getRscNpcListMSGID3(*m_fpRscNpcList, id).
    unsigned int getRscNpcListMSGID3(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns getRscNpcListresult(*m_fpRscNpcList, id).
    unsigned int getRscNpcListresult(unsigned int id) const;
    unsigned int getRscNpcListExtraParts(unsigned int id, unsigned int slot) const;
    const char* getRscMobListModel(unsigned int id) const;
    const char* getRscMobListMotion(unsigned int id) const;
    const char* getRscMobListAddMotion(unsigned int id) const;
    const char* getRscMobListComp_Eff(unsigned int id) const;
    unsigned int getRscMobListRace(unsigned int id) const;
    unsigned int getRscMobListFootStep(unsigned int id) const;
    unsigned int getRscMobListFootStepEffect(unsigned int id) const;
    unsigned int getRscMobListOffsetID(unsigned int id) const;
    unsigned int getRscMobListExtraParts(unsigned int id, unsigned int slot) const;
    const char* getRSC_MapObjListModel(unsigned int id) const;
    const char* getRSC_MapObjListMotion(unsigned int id) const;
    unsigned int getRSC_MapObjListExtraParts1(unsigned int id) const;
    const char* getRSC_TboxListModel(unsigned int id) const;
    const char* getRSC_TboxListMotion(unsigned int id) const;
    const char* getRSC_PcWpnModel(unsigned int id) const;
    const char* getRSC_PcWpnMotion(unsigned int id) const;
    int getRSC_PcWpnMenuImageID(unsigned int id) const;
    const char* getRSC_PcWpnMountWpnInR(unsigned int id, unsigned int slot) const;
    const char* getRSC_PcWpnMountWpnInL(unsigned int id, unsigned int slot) const;
    const char* getRSC_PcWpnMountWpnOutR(unsigned int id, unsigned int slot) const;
    const char* getRSC_PcWpnMountWpnOutL(unsigned int id, unsigned int slot) const;
    const char* getRscEnWpnModel(unsigned int id) const;
    unsigned int getRscEnWpnScale(unsigned int id) const;
    const char* getRscEnWpnMotion(unsigned int id) const;
    const char* getRscEnWpnMtpInChara(unsigned int id) const;
    const char* getRscEnWpnMtpOutChara(unsigned int id) const;
    const char* getRscNpcWpnModel(unsigned int id) const;
    const char* getRscNpcWpnMotion(unsigned int id) const;
    unsigned int getDriverParamExtMountNpc(unsigned int id) const;
    const char* getDriverParamExtMountBone(unsigned int id) const;
    unsigned int getDriverParamExtMountCond(unsigned int id) const;
    const char* getVoiceTableDriver(unsigned int id, unsigned int slot) const;
    // 2.0.0's symbols name it. What it does: calls the slot's getter from its table of getVoiceTableIra1... column
    // getters ("" for an empty slot).
    const char* getVoiceTableIra(unsigned int id, unsigned int slot) const;
    const char* getVoiceTableBladeBlade(unsigned int id, unsigned int slot) const;
    const char* getVoiceTableRareBlade(unsigned int id, unsigned int slot) const;
    const char* getVoiceTableCommonCommonBlade(unsigned int id, unsigned int slot) const;
    unsigned int getFLD_actorSEStart() const;
    unsigned int getFLD_actorSEEnd() const;
    const char* getFLD_actorSELOD(unsigned int id) const;
    unsigned int getFLD_actorSEse_type(unsigned int id) const;
    unsigned int getFLD_actorSEseName(unsigned int id) const;
    float getFLD_actorSEmax_volume_Dist(unsigned int id) const;
    float getFLD_actorSEmin_volume_Dist(unsigned int id) const;
    unsigned int getFLD_actorSEvolumeMAX(unsigned int id) const;
    unsigned int getFLD_actorSEvolumeMIN(unsigned int id) const;
    float getFLD_actorSEoffsetX(unsigned int id) const;
    float getFLD_actorSEoffsetY(unsigned int id) const;
    float getFLD_actorSEoffsetZ(unsigned int id) const;
    // the tables, made by createFP in this order of GfDataBdat::getFP ids; names follow their accessors
    CBdatWrapper* m_fpRscEn;  // 0x10
    CBdatWrapper* m_fpRscEnGenus;  // 0x18
    CBdatWrapper* m_fpRscEnUnd;  // 0x20
    CBdatWrapper* m_fpRscNpcList;  // 0x28
    CBdatWrapper* m_fpRscNpcWpn;  // 0x30
    CBdatWrapper* m_fpRscMobList;  // 0x38
    CBdatWrapper* m_fpRSC_PcWpn;  // 0x40
    CBdatWrapper* m_fpRSC_PcWpnMount;  // 0x48
    CBdatWrapper* m_fpRscEnWpn;  // 0x50
    CBdatWrapper* m_fpRSC_TboxList;  // 0x58
    CBdatWrapper* m_fpRSC_MapObjList;  // 0x60
    CBdatWrapper* m_fpDriverParam;  // 0x68
    CBdatWrapper* m_fpVoiceTable;  // 0x70
    CBdatWrapper* m_fpVoiceTableBlade;  // 0x78
    CBdatWrapper* m_fpVoiceTableRare;  // 0x80
    CBdatWrapper* m_fpVoiceTableCommon;  // 0x88
    CBdatWrapper* m_fpFLD_actorSE;  // 0x90
    CBdatWrapper* m_fpNoRetargetA;  // 0x98  (the name is not the original's: only its noRetarget column is read)
    CBdatWrapper* m_fpNoRetargetB;  // 0xA0  (the name is not the original's: only its noRetarget column is read)
};
}  // namespace gf

#endif
