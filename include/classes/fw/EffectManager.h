#ifndef CLASSES_FW_EFFECTMANAGER_H
#define CLASSES_FW_EFFECTMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"
#include "mm/Col3.h"
#include "mm/Col4.h"
#include "classes/ml/IScnRender.h"
#include "classes/ml/IDrDrawCallback.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/VolumeFadeParams.h"
#include "mtl/AllocHandle.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/EffectCasterSend.h"
#include "classes/fw/RimBloomCalc.h"
#include "ml/StlCustomAllocator.h"
#include <string>
#include <unordered_map>

namespace ml { struct MdlVtxParticle; }
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
namespace ml { class DrMdlBase; }
namespace ml { class Scn; }
namespace mm { namespace mtl { class IAllocator; } }
namespace grlib { class CGLibTextureBuffer; }

namespace fw {
// effect categories (setCategory hands one to effect::SystemManager::es_set_category)
enum EF_CATEGORY : int;

// table 0x7100B41428; the base at 0x18 is ml::IDrDrawCallback (the destructor hands it to
// ScnRenderDrSys::releaseCallBack; its secondary table's slots are IDrDrawCallback's begin..finalRender)
class EffectManager : public ::mm::mtl::PtrSingleton< ::fw::EffectManager>, public ::fw::ManagerObject, public ::ml::IDrDrawCallback, public ::ml::IScnRender {
public:
    // 2.0.0's symbols name it. What it does: stores its bool at 0x2FD8
    void setIra(bool flag);
    // 2.0.0's symbols name it. What it does: hands the flag to setDisableCollision on effect::SystemManager::getPtr()'s
    // system; GfMapManager passes false before building a map's data, true before destroying it (then waits a frame).
    void setDisableCollision(bool flag);
    // the casters' sends of one layer
    class CasterGroup : public ::mm::mtl::IntrusiveList<EffectCasterSend> {};
    virtual ~EffectManager();  // slot 0
    virtual bool initialize();  // slot 2
    bool isCommonLoaded();
    bool commonLoaded();
    // slot 3 (a primary slot of its own: it overrides a secondary base's, ManagerObject's); it hands on to
    // commonDestryed, whose body the -8 thunk reaches directly once finalize is inlined into it
    virtual bool finalize();  // slot 3
    // 2.0.0's symbols name it. What it does: sets m_inactive, clears the effect system (es_clearall), the caster
    // groups, the texture buffers and the common packs; true once done.
    bool commonDestryed();
    // 2.0.0's symbols name it. What it does: sets path to the common effect folder, "effect/common" with "_dlc"
    // appended while m_gfManagerFlag is set, then "/"; true.
    bool getCommonFilePath(mm::mtl::FixStr<32>& path);
    // 2.0.0's symbols name it: getCommonFilePath's folder ("effect/common").
    static const char* s_commonFilePath;
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
    // 2.0.0's symbols name them. What they do: requestDestroy sets pad_2fdb and pad_2fd7 to 1 and pad_2fda to 0;
    // isDestryed is true while pad_2fdb is 0; requestLoad sets pad_2fdc to 1; isLoaded is true while pad_2fdc is 0.
    void requestDestroy();
    bool isDestryed();
    void requestLoad();
    bool isLoaded();
    // the pack map's: files a pack under its name, takes it out, the one filed under a name (null for none)
    void addPack(EffectPack* pack);
    void removePack(EffectPack* pack);
    EffectPack* findPack(const char* name);
    // the data map's, filed under getName()
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
    // the record the effect library hands setLgtParam (as void*): the struct, its name and its field names are
    // inferred from what setLgtParam copies where
    struct LgtParam {
        float m_lightParam;  // 0x0, kept unless above -1 (point 0xA4, spot 0xC8)
        float m_size;  // 0x4, kept unless above -1
        mm::Col3 m_color;  // 0x8
        float m_angle;  // 0x14, spot only
        float m_param18;  // 0x18, spot 0xE0
        float m_lightParam2;  // 0x1C (point 0xB4, spot 0xDC)
        float m_subtract;  // 0x20, above 0 turns setSubtractOn on
    };
    // a light's parameters from a LgtParam (the parameter names are not the original's)
    static void setLgtParam(unsigned int type, void* lgt, void* param);
    static void debugRenderer(void* data);
    // hands the effect library these callbacks and creates its effect::SystemManager (once: not while pad_2fda is
    // set or a manager exists); apply calls it
    void efSystemStart(const ml::IDrDrawWorkInfo* info);
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
    // the ring at pos turned by angle about y, scaled in x; flag picks the colour (the names of the parameters
    // are not the original's)
    bool updateHateRing(unsigned int handle, const mm::Vec3& pos, const float& angle, bool flag, const float& scale);
    // as updateHateRing with the colour given (id 4 like the ring)
    bool updateHateRingVec(unsigned int handle, const mm::Vec3& pos, const float& angle, const float& scale,
                           const mm::Col4& color);
    // as updateHateRingVec, the id left at its default
    bool updateHateArrow(unsigned int handle, const mm::Vec3& pos, const float& angle, const float& scale,
                         const mm::Col4& color);
    void destroyHateRing(unsigned int handle);
    void destroyHateRingVec(unsigned int handle);
    void destroyHateArrow(unsigned int handle);
    // the ball at pos, scale in x (the names of the parameters are not the original's)
    bool updateComboBall(unsigned int handle, const mm::Vec3& pos, const float& scale);
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
    // the effect's matrix and scale; value goes to SendParam::m_flagF (the names of the parameters are not the
    // original's)
    void setParam(unsigned int handle, const mm::Mat44& mtx, const mm::Vec3& scale, unsigned char value);
    // GfComEffectCaster::setCaster passes its caster and 1.0f (the names of the parameters are not the original's)
    void setParam(unsigned int handle, EffectCasterBase* caster, float rate);
    // BladeChangeManager::UpdateProc passes the blade's position and mm::Vec3::unit (the names of the parameters are
    // not the original's)
    void setParam(unsigned int handle, const mm::Vec3& pos, const mm::Vec3& scale);
    // the effect at pos, turned by rot (euler angles) and scaled (the names of the parameters are not the original's)
    void setParam(unsigned int handle, const mm::Vec3& pos, const mm::Vec3& rot, const mm::Vec3& scale);
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

    // a third allocator the destructor erases (the name is not the original's)
    mtl::ALLOC_HANDLE m_heapHandle;
    // the allocators effectAllocSys and effectAllocRes take from (effectSysHandle and effectResHandle hand them out;
    // the names are not the original's)
    mtl::ALLOC_HANDLE m_sysHandle;
    mtl::ALLOC_HANDLE m_resHandle;
    unsigned char pad_34[0x4];
    // what the constructor is handed: its allocator and the scene (the destructor releases the draw callback from the
    // scene's ScnRenderDrSys; the names are not the original's)
    mm::mtl::IAllocator* m_allocator;
    ml::Scn* m_scn;
    mm::mtl::FixedArray<CasterGroup, 32> m_casterGroups;  // by layer (changeLayerCaster moves a send between them)
    // packs and data by name, each in an allocator-backed std::unordered_map (the names are not the original's)
    typedef std::unordered_map<std::string, EffectPack*, std::hash<std::string>, std::equal_to<std::string>,
                               ml::StlCustomAllocator<std::pair<const std::string, EffectPack*> > >
        PackMap;
    typedef std::unordered_map<std::string, EffectData*, std::hash<std::string>, std::equal_to<std::string>,
                               ml::StlCustomAllocator<std::pair<const std::string, EffectData*> > >
        DataMap;
    PackMap* m_packMap;
    DataMap* m_dataMap;
    unsigned char pad_358[0x408];
    // gf::EffectCaster::postUpdate copies the party leader's caster matrix in (the name is not the original's)
    mm::Mat44 m_leaderMtx;
    // a resource commonLoaded requests (RenderResource::request) and a counted object pushed as null with it; the
    // destructor releases both, the second first (the names are not the original's)
    struct ResourceEntry {
        RenderResource* m_resource;
        mm::mtl::ReferenceObject* m_object;
    };
    // the resources commonLoaded requests for BTL_VolumeFade's rows (their data goes to m_volumeFadeParams),
    // BTL_HitEffectRim's (rim blooms) and BTL_VtxParticle's (the names are not the original's)
    mm::mtl::FixedVector<ResourceEntry, 128> m_volumeFadeResources;  // 0x7A0
    mm::mtl::FixedVector<ResourceEntry, 128> m_rimBloomResources;  // 0xFA8
    mm::mtl::FixedVector<ResourceEntry, 128> m_vtxParticleResources;  // 0x17B0
    // one of the common effect packs commonLoaded requests: its resource and, once loaded, its pack (the names are not
    // the original's). The destructor releases both by hand and its FixedVector clears destroy nothing, so the
    // original's element is trivially destructible (a raw pointer here loses search/createHateRing* by 2 words of
    // latch order)
    struct CommonPack {
        RenderResource* m_resource;
        mm::mtl::IntrusivePtr<EffectPack> m_pack;
    };
    mm::mtl::FixedVector<CommonPack, 128> m_commonPacks;  // 0x1FB8 (the name is not the original's)
    int m_loadState;  // commonLoaded's step (it switches on it; the name is not the original's)
    unsigned char pad_27c4[0x4];
    // the resources commonLoaded requests for EFF_KizunaLink's rows, step by step (the names are not the original's)
    mm::mtl::FixedVector<ResourceEntry, 128> m_kizunaLinkResources;  // 0x27C8
    int m_kizunaLoadState;
    unsigned char pad_2fd4;  // the constructor clears it
    bool m_masterPause;  // what setMasterPause last handed effect::SystemManager::es_pause (the name is not the original's)
    // set when finalize starts, cleared once update's pending commonLoaded succeeds; update and the renders skip
    // while it is set (the name is not the original's)
    bool m_inactive;
    unsigned char pad_2fd7;  // requestDestroy sets it (byte loads: not a bool)
    // stored by setIra (GfManager::resetGameType hands it on), cleared by the constructor; nothing in this
    // unit reads it (the name is not the original's)
    bool m_gfManagerFlag;
    unsigned char m_tailFlip;  // tail flips it between 0 and 1 every frame (the name is not the original's)
    unsigned char pad_2fda;  // requestDestroy clears it
    unsigned char pad_2fdb;  // requestDestroy sets it, isDestryed tests it
    unsigned char pad_2fdc;  // requestLoad sets it, isLoaded tests it
    unsigned char pad_2fdd[0x3];
    // the volume fade (vanish) parameters by gf::VFEFF, each from its effect/common/vanish/<VolumeName>.dprm
    // (BTL_VolumeFade's rows; gf::GfVolumeFade reads them)
    VolumeFadeParams* m_volumeFadeParams[32];
    RimBloomCalc m_rimBlooms[64];  // 0x30E0, the constructor clears them (the name is not the original's)
    // vertex particle parameters by index (GfObjUtil::setDeadParticle copies the first 0x30 bytes of one; the name
    // is not the original's)
    ml::MdlVtxParticle* m_particleParams[32];
    // one bond (kizuna) line effect: createKizunaLine takes the first of works 1..7 whose byte at 0x459 is clear (work
    // 0 stays unused: handle 0 is none); updateKizunaLine sets its two ends and its count (the names are not the
    // original's)
    struct KizunaWork {
        // EffectManager's destructor inlines it: term, then m_object's release
        ~KizunaWork() { term(); }
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
        // the line's effect handles: term fades each still set out (es_fade_core -1, as EffectManager::remove) and
        // clears it (the name is not the original's)
        unsigned int m_effects[8];
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
        unsigned char pad_45c[0x4];
        // a counted object the work's destructor releases, null from the constructor (the name is not the original's)
        mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> m_object;
        // a model term hides and hands to setDeleteCall (DrMdlBase slots 15/16, as deleteMdl) and clears (the name is
        // not the original's)
        ml::DrMdlBase* m_model;
    };
    KizunaWork m_kizunaWorks[8];  // 0x353E0, by handle (the name is not the original's)
    // the texture buffers apply makes from the kizuna link resources; the destructor deletes them (the name is not the
    // original's)
    mm::mtl::FixedVector<grlib::CGLibTextureBuffer*, 32> m_textureBuffers;  // 0x37760
    unsigned char pad_37868[0xF0];
    // an effect speed per category: apply hands each to effect::SystemManager::setCategorySpd, gf::MapEff::update
    // sets category 1's from the frame's update speed (the name is not the original's)
    float m_categorySpeed[8];
};
}  // namespace fw

#endif
