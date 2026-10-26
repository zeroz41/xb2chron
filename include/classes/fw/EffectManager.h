// not proven yet: its table differs from the original's (word 18: _ZN2fw13EffectManager8finalizeEv where the original has =-8)
#ifndef CLASSES_FW_EFFECTMANAGER_H
#define CLASSES_FW_EFFECTMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/ml/IScnRender.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/VolumeFadeParams.h"
#include "mtl/AllocHandle.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/EffectCasterSend.h"

namespace effect { class SendParam; }
namespace fw { class EffectData; }
namespace fw { class EffectPack; }
namespace fw { class RenderResource; }
namespace fw { class EffectCasterBase; }
namespace fw { class EffectManager; }
namespace mm { class Mat44; }
namespace fw { class UpdateInfo; }
namespace ml { class IDrDrawWorkInfo; }

namespace fw {
// effect categories (setCategory hands one to effect::SystemManager::es_set_category)
enum EF_CATEGORY : int;

// a base of fw::EffectManager no evidence names yet
class TUnk_B41508 {
public:
    virtual ~TUnk_B41508();
    virtual void begin() = 0;
    virtual void end() = 0;
    virtual void apply(ml::IDrDrawWorkInfo const*) = 0;
    virtual void opacityRender(ml::IDrDrawWorkInfo const*) = 0;
    virtual void alphaRender(ml::IDrDrawWorkInfo const*) = 0;
    virtual void lastRender(ml::IDrDrawWorkInfo const*) = 0;
    virtual void blurRender(ml::IDrDrawWorkInfo const*) = 0;
    virtual void finalRender(ml::IDrDrawWorkInfo const*) = 0;
};
// table 0x7100B41428; base at 0x18 unknown (TUnk_B41508)
class EffectManager : public ::mm::mtl::PtrSingleton< ::fw::EffectManager>, public ::fw::ManagerObject, public TUnk_B41508, public ::ml::IScnRender {
public:
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in effect_manager's unit and
    // GfManager::fn_710032A1FC calls it on PtrSingleton<fw::EffectManager>'s instance. What it does: stores its bool at 0x2FD8
    void fn_710017CB08(bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's GfMapManager::buildMapData and
    // destroyMapData have no call there). A member: its code is in effect_manager's unit and GfMapManager calls it on
    // PtrSingleton<fw::EffectManager>'s instance. What it does: hands the flag to fn_710083FF24 on
    // effect::SystemManager::getPtr()'s system; GfMapManager passes false before building a map's data, true before
    // destroying it (then waits a frame).
    void fn_7100179D30(bool flag);
    // the casters' sends of one layer
    class CasterGroup : public ::mm::mtl::IntrusiveList<EffectCasterSend> {};
    virtual ~EffectManager();  // slot 0
    virtual bool initialize();  // slot 2
    bool isCommonLoaded();
    bool commonLoaded();
    virtual void vf3();  // slot 3
    virtual void update(fw::UpdateInfo const&);  // slot 4
    virtual void updateLayer(fw::UpdateInfo const&, unsigned int);  // slot 5
    virtual void updateLayerPost(fw::UpdateInfo const&, unsigned int);  // slot 6
    virtual void tail(fw::UpdateInfo const&, bool);  // slot 7
    virtual void begin();  // slot 8
    virtual void end();  // slot 9
    virtual void apply(ml::IDrDrawWorkInfo const*);  // slot 10
    virtual void opacityRender(ml::IDrDrawWorkInfo const*);  // slot 11
    virtual void alphaRender(ml::IDrDrawWorkInfo const*);  // slot 12
    virtual void lastRender(ml::IDrDrawWorkInfo const*);  // slot 13
    virtual void blurRender(ml::IDrDrawWorkInfo const*);  // slot 14
    virtual void finalRender(ml::IDrDrawWorkInfo const*);  // slot 15
    virtual bool finalize();  // overrides a secondary base's (ManagerObject's)
    void addData(EffectData* data);
    // EffectCasterBase's setters hand their values on to these
    void addCaster(EffectCasterBase* caster);
    void changeLayerCaster(EffectCasterBase* caster, unsigned int index, unsigned int layer);
    void sendCaster(EffectCasterBase* caster, mm::Mat44& mtx, const char* name, int index);
    void sendCaster(EffectCasterBase* caster, float scl);
    void sendCasterFrame(EffectCasterBase* caster, float frame);
    void sendCasterStateName(EffectCasterBase* caster, const char* name);
    void removeData(EffectData* data);
    // an effect by name, its handle (0 for none)
    unsigned int create(const char* name, EffectPack* pack, const effect::SendParam* param, bool flag);
    // the effect library's callbacks: memory from the system and resource allocators ("no name", line 0), the
    // model and debug hooks
    static void* effectAllocSys(void* user, unsigned int size, unsigned int alignment, const char* name, unsigned int line);
    static void effectFreeSys(void* user, void* p);
    static void* effectAllocRes(void* user, unsigned int size, unsigned int alignment, const char* name, unsigned int line);
    static void effectFreeRes(void* user, void* p);
    static mtl::ALLOC_HANDLE effectSysHandle();
    static mtl::ALLOC_HANDLE effectResHandle();
    static void debugReadFileEnd(void* data);
    static void debugOutputString(const char* text);
    static void warnOutputString(const char* text);
    static void setMdlPos(void* mdl, void* pos);
    static void setMdlMatrix(void* mdl, void* matrix);
    static void setMdlAlpha(void* mdl, float alpha);
    static void setMdlSpeed(void* mdl, void* speed);
    // the effect library's model hooks: a model group (an ml::DrMdoGrpObj) while there is a Framework, a model of a
    // group shown with the identity matrix, each deleted with the frame's stock index (the parameter names are not the
    // original's)
    static void* createGroup(int arg, int viewNum);
    static void destroyGroup(void* grp);
    static void* createMdl(const void* res, const char* name, int index, const void* grp, int option);
    static void deleteMdl(void* mdl);
    // an effect resource (efb) by name: from pack first, else from the common packs (null for none)
    void* search(const char* name, EffectPack* pack);
    // the common packs' battle effects, by their efb names (cmn_000_000, cmn_000_001, cmn_000_002); 0 for none
    unsigned int createHateRing();
    unsigned int createHateRingVec();
    unsigned int createHateArrow();
    // combo ball type (1 on) from the common packs' cmn_010_<type - 1>; 0 for type 0 or none
    unsigned int createComboBall(unsigned int type);
    void destroyHateRing(unsigned int handle);
    void destroyHateRingVec(unsigned int handle);
    void destroyHateArrow(unsigned int handle);
    void destroyComboBall(unsigned int handle);
    void setMasterPause(bool pause);
    void kill(unsigned int handle);
    void remove(unsigned int handle);
    // EffectCasterBase's destructor drops the caster with these
    void remove(EffectCasterBase* caster);
    void removeCaster(EffectCasterBase* caster);
    void dead(unsigned int handle);
    void fadeOutDead(unsigned int handle);
    void fadeOutDead(unsigned int handle, unsigned int frames);
    void setDisp(unsigned int handle, bool disp);
    void setCategory(unsigned int handle, EF_CATEGORY category);
    void setViewnum(unsigned int handle, unsigned int viewnum);
    void setParamPosOnly(unsigned int handle, const effect::SendParam* param);
    void setParamPosOnly2(unsigned int handle, const effect::SendParam* param);
    void setParam(unsigned int handle, const effect::SendParam* param);
    int getDeadFlag(unsigned int handle);
    bool isLoop(void* data) const;
    bool containsCamAxis(void* data) const;
    void setAlpha(unsigned int handle, float alpha);
    void setSpeed(unsigned int handle, float speed);
    bool isExist(unsigned int handle);
    // a volume fade effect's parameters, none past the 32 (inline: the name is not the original's)
    const VolumeFadeParams* getVolumeFadeParams(unsigned int type) const {
        if (type >= 32) {
            return nullptr;
        }
        return m_volumeFadeParams[type];
    }

    unsigned char pad_28[0x4];
    // the allocators effectAllocSys and effectAllocRes take from (effectSysHandle and effectResHandle hand them out;
    // the names are not the original's)
    mtl::ALLOC_HANDLE m_sysHandle;
    mtl::ALLOC_HANDLE m_resHandle;
    unsigned char pad_34[0x14];
    mm::mtl::FixedArray<CasterGroup, 32> m_casterGroups;  // by layer (changeLayerCaster moves a send between them)
    unsigned char pad_348[0x1c70];
    // one of the common effect packs commonLoaded requests: its resource and, once loaded, its pack (the names are not
    // the original's)
    struct CommonPack {
        RenderResource* m_resource;
        mm::mtl::IntrusivePtr<EffectPack> m_pack;
    };
    mm::mtl::FixedVector<CommonPack, 128> m_commonPacks;  // 0x1FB8 (the name is not the original's)
    unsigned char pad_27c0[0x815];
    bool m_masterPause;  // what setMasterPause last handed effect::SystemManager::es_pause (the name is not the original's)
    // set when finalize starts, cleared once update's pending commonLoaded succeeds; update and the renders skip
    // while it is set (the name is not the original's)
    bool m_inactive;
    unsigned char pad_2fd7[0x1];
    // stored by fn_710017CB08 (GfManager::fn_710032A1FC hands it on), cleared by the constructor; nothing in this
    // unit reads it (the name is not the original's)
    bool m_gfManagerFlag;
    unsigned char pad_2fd9[0x7];
    // the volume fade (vanish) parameters by gf::VFEFF, each from its effect/common/vanish/<VolumeName>.dprm
    // (BTL_VolumeFade's rows; gf::GfVolumeFade reads them)
    VolumeFadeParams* m_volumeFadeParams[32];
    unsigned char pad_30e0[0x34878];
    // an effect speed per category: apply hands each to effect::SystemManager::setCategorySpd, gf::MapEff::update
    // sets category 1's from the frame's update speed (the name is not the original's)
    float m_categorySpeed[8];
};
}  // namespace fw

#endif
