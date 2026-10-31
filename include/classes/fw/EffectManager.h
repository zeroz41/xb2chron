#ifndef CLASSES_FW_EFFECTMANAGER_H
#define CLASSES_FW_EFFECTMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"
#include "mm/Col3.h"
#include "classes/ml/IScnRender.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/VolumeFadeParams.h"
#include "mtl/AllocHandle.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/EffectCasterSend.h"
#include "classes/fw/RimBloomCalc.h"

namespace effect { class SendParam; }
namespace fw { class EffectData; }
namespace fw { class EffectPack; }
namespace fw { class RenderResource; }
namespace fw { class EffectCasterBase; }
namespace fw { class EffectManager; }
namespace mm { class Mat44; }
namespace fw { class UpdateInfo; }
namespace ml { class IDrDrawWorkInfo; }
namespace ml { struct VolumeFadeParams; }
namespace ml { struct DrMdlAfterImageParams; }

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
    // slot 3 (a primary slot of its own: it overrides a secondary base's, ManagerObject's); it hands on to
    // fn_71001765E8, whose body the -8 thunk reaches directly once finalize is inlined into it
    virtual bool finalize();  // slot 3
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's finalize, slot 3, held this body
    // itself). A member: finalize and update call it on this. What it does: sets m_inactive, clears the effect
    // system (es_clearall), the caster groups, the texture buffers and the common packs; true once done.
    bool fn_71001765E8();
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
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (1.0.0 has commonLoaded then finalize there)
    // and nothing calls them. Members because they sit among EffectManager's functions and read only its flag bytes.
    // What they do: fn_710017658C sets pad_2fdb and pad_2fd7 to 1 and pad_2fda to 0; fn_71001765AC is true while
    // pad_2fdb is 0; fn_71001765C0 sets pad_2fdc to 1; fn_71001765D0 is true while pad_2fdc is 0.
    void fn_710017658C();
    bool fn_71001765AC();
    void fn_71001765C0();
    bool fn_71001765D0();
    void addData(EffectData* data);
    // EffectCasterBase's setters hand their values on to these
    void addCaster(EffectCasterBase* caster);
    void changeLayerCaster(EffectCasterBase* caster, unsigned int index, unsigned int layer);
    void sendCaster(EffectCasterBase* caster, mm::Mat44& mtx, const char* name, int index);
    void sendCaster(EffectCasterBase* caster, float scl);
    void sendCasterFrame(EffectCasterBase* caster, float frame);
    void sendCasterStateName(EffectCasterBase* caster, const char* name);
    void removeData(EffectData* data);
    void destroyKizunaLine(unsigned int handle);  // the symbols' name (BattleCharacter's kizuna link effect)
    // an effect by name, its handle (0 for none)
    unsigned int create(const char* name, EffectPack* pack, const effect::SendParam* param, bool flag);
    unsigned int create(const char* name, EffectPack* pack, bool flag);
    // an effect from an effect resource (efb) while there is an effect::SystemManager, its handle (0 for none)
    unsigned int create(void* efb, bool flag);
    // the effect library's callbacks: memory from the system and resource allocators ("no name", line 0), the
    // model and debug hooks
    static void* effectAllocSys(void* user, unsigned int size, unsigned int alignment, const char* name, unsigned int line);
    static void effectFreeSys(void* user, void* p);
    static void* effectAllocRes(void* user, unsigned int size, unsigned int alignment, const char* name, unsigned int line);
    static void effectFreeRes(void* user, void* p);
    static mtl::ALLOC_HANDLE effectSysHandle();
    static mtl::ALLOC_HANDLE effectResHandle();
    // the effect library's debug file hook: reads path with the resource allocator (0x1000 aligned), its size into size
    static void* debugReadFile(const char* path, int& size);
    static void debugReadFileEnd(void* data);
    static void debugOutputString(const char* text);
    static void warnOutputString(const char* text);
    static void setMdlPos(void* mdl, void* pos);
    static void setMdlMatrix(void* mdl, void* matrix);
    static void setMdlAlpha(void* mdl, float alpha);
    // what the effect library hands setMdlColor for a model (the names are not the original's): the ace colour and
    // values 0..2 go to the model's setAceColor/setAceVal, m_viewNum is stored as the model's view number and the model
    // is shown while m_dispThreshold is above 0.01
    struct MdlColorParam {
        mm::Col3 m_color;
        float m_aceVal[3];
        float m_viewNum;
        float m_dispThreshold;
    };
    static void setMdlColor(void* mdl, void* param);
    static void setMdlSpeed(void* mdl, void* speed);
    // the effect library's model hooks: a model group (an ml::DrMdoGrpObj) while there is a Framework, a model of a
    // group shown with the identity matrix, each deleted with the frame's stock index (the parameter names are not the
    // original's)
    static void* createGroup(int arg, int viewNum);
    static void destroyGroup(void* grp);
    static void* createMdl(const void* res, const char* name, int index, const void* grp, int option);
    static void deleteMdl(void* mdl);
    // the effect library's light hooks: an instant point (type 1) or spot (type 2) light of a view's DrLightMan while
    // there is a Framework, released, placed or turned through DrMan's light manager (the parameter names are not the
    // original's)
    static void* createLgt(unsigned int type, int viewNum);
    static void deleteLgt(unsigned int type, void* lgt);
    static void setLgtPos(unsigned int type, void* lgt, void* pos);
    static void setLgtMatrix(unsigned int type, void* lgt, void* matrix);
    // an effect resource (efb) by name: from pack first, else from the common packs (null for none)
    void* search(const char* name, EffectPack* pack);
    // the common packs' battle effects, by their efb names (cmn_000_000, cmn_000_001, cmn_000_002); 0 for none
    unsigned int createHateRing();
    unsigned int createHateRingVec();
    unsigned int createHateArrow();
    // combo ball type (1 on) from the common packs' cmn_010_<type - 1>; 0 for type 0 or none
    unsigned int createComboBall(unsigned int type);
    // a bond line's ends and count (1..6, 0 counts as 1) by its handle (1..7); other handles do nothing
    // the handle (1..7) of a free bond line work, initialised; 0 when all are taken
    unsigned int createKizunaLine();
    void updateKizunaLine(unsigned int handle, const mm::Vec3& start, const mm::Vec3& end, unsigned int count);
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
    // copies the volume fade parameters of type into params; false when there are none
    bool getVolumeFadeParam(unsigned int type, ml::VolumeFadeParams& params);
    // rim bloom src's colour and floats into the first after image, dst's into the second (parameter names inferred)
    bool getAfterImageParams(unsigned int src, unsigned int dst, ml::DrMdlAfterImageParams& params);
    void fadeOutDead(unsigned int handle);
    void fadeOutDead(unsigned int handle, unsigned int frames);
    void setDisp(unsigned int handle, bool disp);
    void setCategory(unsigned int handle, EF_CATEGORY category);
    void setViewnum(unsigned int handle, unsigned int viewnum);
    void setParamPosOnly(unsigned int handle, const effect::SendParam* param);
    void setParamPosOnly2(unsigned int handle, const effect::SendParam* param);
    void setParam(unsigned int handle, const effect::SendParam* param);
    // the effect's matrix alone (es_set_param_pos_only with the default parameters)
    void setMatrix(unsigned int handle, const mm::Mat44& mtx);
    // GfComEffectCaster::setCaster passes its caster and 1.0f (the names of the parameters are not the original's)
    void setParam(unsigned int handle, EffectCasterBase* caster, float rate);
    // BladeChangeManager::UpdateProc passes the blade's position and mm::Vec3::unit (the names of the parameters are
    // not the original's)
    void setParam(unsigned int handle, const mm::Vec3& pos, const mm::Vec3& scale);
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
    unsigned char pad_348[0x418];
    // gf::EffectCaster::postUpdate copies the party leader's caster matrix in (the name is not the original's)
    mm::Mat44 m_leaderMtx;
    unsigned char pad_7a0[0x1818];
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
    unsigned char pad_2fd7;  // fn_710017658C sets it (byte loads: not a bool)
    // stored by fn_710017CB08 (GfManager::fn_710032A1FC hands it on), cleared by the constructor; nothing in this
    // unit reads it (the name is not the original's)
    bool m_gfManagerFlag;
    unsigned char m_tailFlip;  // tail flips it between 0 and 1 every frame (the name is not the original's)
    unsigned char pad_2fda;  // fn_710017658C clears it
    unsigned char pad_2fdb;  // fn_710017658C sets it, fn_71001765AC tests it
    unsigned char pad_2fdc;  // fn_71001765C0 sets it, fn_71001765D0 tests it
    unsigned char pad_2fdd[0x3];
    // the volume fade (vanish) parameters by gf::VFEFF, each from its effect/common/vanish/<VolumeName>.dprm
    // (BTL_VolumeFade's rows; gf::GfVolumeFade reads them)
    VolumeFadeParams* m_volumeFadeParams[32];
    RimBloomCalc m_rimBlooms[64];  // 0x30E0, the constructor clears them (the name is not the original's)
    unsigned char pad_352e0[0x100];
    // one bond (kizuna) line effect: createKizunaLine takes the first of works 1..7 whose byte at 0x459 is clear (work
    // 0 stays unused: handle 0 is none); updateKizunaLine sets its two ends and its count (the names are not the
    // original's)
    struct KizunaWork {
        void init();
        void term();
        void update();

        unsigned char pad_0[0x4];
        unsigned int m_count;  // updateKizunaLine keeps it within 1..6
        unsigned char pad_8[0x8];
        mm::Vec3 m_start;
        mm::Vec3 m_end;
        // init sets the first two to (0, 0, i * 0.05) and clears the third, 20 points each
        mm::Vec3 pad_30[20];
        mm::Vec3 pad_170[20];
        mm::Vec3 pad_2b0[20];
        unsigned char pad_3f0[0x20];
        mm::Vec3 pad_410;  // init copies pad_440 in
        mm::Vec3 pad_420;  // init copies the last of pad_30 in
        unsigned char pad_430[0x10];
        mm::Vec3 pad_440;
        float pad_450;  // init: the distance between pad_30's first two points
        float pad_454;  // init: ml::mtRandf1() times pi
        bool pad_458;   // init clears it
        bool m_inUse;  // createKizunaLine takes a work whose flag is clear and sets it (the name is not the original's)
        bool pad_45a;   // init sets it
        bool pad_45b;   // init sets it
        unsigned char pad_45c[0x14];
    };
    KizunaWork m_kizunaWorks[8];  // 0x353E0, by handle (the name is not the original's)
    unsigned char pad_37760[0x1F8];
    // an effect speed per category: apply hands each to effect::SystemManager::setCategorySpd, gf::MapEff::update
    // sets category 1's from the frame's update speed (the name is not the original's)
    float m_categorySpeed[8];
};
}  // namespace fw

#endif
