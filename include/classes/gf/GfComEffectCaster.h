#ifndef CLASSES_GF_GFCOMEFFECTCASTER_H
#define CLASSES_GF_GFCOMEFFECTCASTER_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/gf/GfComponent.h"
namespace fw { class Message; }
namespace fw { class UpdateInfo; }
namespace fw { class MessageObject; }
namespace fw { class EffectPack; }
namespace fw { class EffectPoint; }
namespace fw { class EffectResData; }
namespace anm { class ResASM; }
namespace mm { class Mat44; }
namespace gf { class EffectCaster; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfComAsm; }
namespace gf { class GfComEvtAnim; }
namespace gf { class CallBackCache; }
namespace effect { class SendParam; }
namespace gf { class MsgFxForceCancel; }

namespace gf {
// table 0x7100B65990
class GfComEffectCaster : public ::gf::GfComponent {
public:
    // an effect pack setup created (EffectPack::createFromMemory's) with its id; setup asserts the count < 100
    // (the names are not the original's)
    struct PackEntry {
        fw::EffectPack* m_pack;
        unsigned int m_id;
    };
    // a running effect (findEffectCasterParam looks one up by m_id; setSpeed and startTimer set its fields)
    // The copy constructor and assignment are the implicit ones (out of line in the original): two FixStr<32>s,
    // the runs between them copied as blocks, two Vec3s, 16-byte alignment (0x5C, 0x74 and 0x8C are padding).
    struct Param {
        mm::mtl::FixStr<32> pad_0;
        unsigned int pad_24;
        float m_timer;  // startTimer clears it (the name is not the original's)
        unsigned int pad_2c;
        float m_speed;  // setSpeed's (the name is not the original's)
        mm::mtl::FixStr<32> pad_34;
        unsigned int m_id;  // findEffectCasterParam's key (the name is not the original's)
        // released by the destructor (reference_object.h's `m_RefCount > 0`); what it holds is unknown
        mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> pad_60;
        unsigned int pad_68[3];
        mm::Vec3 pad_80;
        mm::Vec3 pad_90;
        unsigned char pad_a0[0x19];
        // how the effect follows the ground or water (calcFollowAnnotetionTag switches on it, 0..14; the name is not
        // the original's)
        unsigned char m_followKind;
        bool pad_ba;  // set when updateParam kills the effect (one that is set is not killed again)
        unsigned char pad_bb[0x5];
    };
    // an effect an event mounted (removeMountEffectEv looks one up by m_id and hands m_boneName back; the copy
    // assignment is the implicit one, out of line in the original: name, id, pointer, Vec3, three bytes)
    struct EventEfHandleTbl {
        // the bone whose frame removeMountEffectEv hands back (the name is not the original's)
        mm::mtl::FixStr<32> m_boneName;
        unsigned int m_id;  // removeMountEffectEv's key (the name is not the original's)
        // released by the destructor (reference_object.h's `m_RefCount > 0`); what it holds is unknown
        mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> pad_28;
        mm::Vec3 pad_30;
        bool pad_40;
        // removeMountEffectEv hands the bone's frame back only when it is set
        bool pad_41;
        bool pad_42;
    };

    // what setup and setupEfp read (the layout is what setupEfp shows; the names are not the original's)
    struct SetupInfo {
        unsigned char pad_0[0x8];
        GF_ASSET_HANDLE* m_asset;  // the asset setupEfp takes its effect point file from
        unsigned int pad_10;  // setupEfp hands it to the effect point's EfpInitData (its first field)
    };

    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComEffectCaster();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4

    // ends every running effect an annotation started that has pad_f8 set
    void procMsgFxForceCancel(fw::MessageObject*, MsgFxForceCancel&);
    void cleanup();
    void apply(const fw::UpdateInfo& info);
    void applyEvent(const fw::UpdateInfo& info);
    void asmCallback(GfComAsm* com, const CallBackCache& cache);
    void evtAnimCallback(GfComEvtAnim* com, const CallBackCache& cache);
    void callbackImpl(const CallBackCache& cache);
    // the effect's matrix and scale for the parameter set (the parameter names are not the original's)
    void calcMtxAndScale(GfComEffectCaster* caster, Param* param, float rate, bool flag, effect::SendParam& sendParam);
    // 0: hand the parameters to the effect, 1: the same without m_flagB, 2: kill the effect (by m_followKind)
    int calcFollowAnnotetionTag(Param* param, effect::SendParam& sendParam);
    // kills the running effect with the handle (its Param's pad_ba set); defined inline in gf_com_effect_caster.cpp
    void effectEnd(unsigned int handle);
    // hands the effect its parameters, or kills it (the parameter names are not the original's)
    void updateParam(GfComEffectCaster* caster, Param* param, float rate, bool flag);
    fw::EffectPoint* getEffectPoint();
    static void registerAsmCallbackEffect(GF_OBJ_HANDLE* handle, anm::ResASM* asmRes, fw::EffectResData* resData);
    void setupCaster(const fw::EffectPoint* point);
    // creates m_pPoint from the asset's effect point file (one file index per pad_117ac kind) with the model
    // component's bone frames; nothing for a kind above 8
    void setupEfp(const SetupInfo& info);
    // hands the caster the asset's ".wiswt" tail numbered id (its name's two digits after '_'; the first one for a
    // pad_117ac kind other than 0), unless it is the one loaded last (the parameter name is not the original's)
    void setupEfTail(unsigned int id);
    Param* findEffectCasterParam(unsigned int id);
    const char* getEfpData(const char* name, mm::Mat44& mtx);
    void setCaster(unsigned int handle);
    bool setSpeed(unsigned int id, float speed);
    bool startTimer(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits in this class's
    // code and reads m_caster from `this`. What it does: hands the matrix to the caster's fn_71004B3B78 when there
    // is a caster; gf_game_scene's fn_71002C7DC0 calls it.
    void fn_71004B3B68(const mm::Mat44& mtx);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads pad_48 and m_packs
    // from `this` (btl::EffectManager::CreateBullet calls it on a component). What it does: clears packs, adds pad_48
    // when set, then every entry's pack of m_packs when GfGameManager::fn_71002A9E68() holds; true if any was added.
    bool fn_71004B39DC(mm::mtl::FixedVector<fw::EffectPack*, 8>& packs);
    // clears packs and adds the pack of every entry of m_packs with that id; true if any was added
    // (the parameter names are not the original's; the second int is unused)
    bool getWeaponEffectPack(mm::mtl::FixedVector<fw::EffectPack*, 8>& packs, int id, int);
    // drops the mounted effect with that id, handing its bone frame back first when it took one; false without one
    // (the parameter name is not the original's)
    bool removeMountEffectEv(unsigned int id);
    // the pack holding the named efb: an m_packs entry of the owner's weapon effect type (any entry when
    // GfGameManager::fn_71002A9E68() holds), else pad_48, or for pad_117ac kinds 3 and 4 with a parent a pack made
    // from the owner's efb resource; null for "cmn" names (the parameter name is not the original's)
    fw::EffectPack* getWeaponEffectPack(const char* name);
    // an effect of the named file placed at the matrix (GfEffectGround's foot step and splashdown effects)
    void createFromFileName(const mm::Mat44& mtx, const char* fileName) const;

    static mm::mtl::RTTI m_rtti;

    // createFromFileName hands it to EffectManager::setViewnum when not 0 (the name is not the original's)
    unsigned int m_viewnum;
    unsigned char pad_14[0x10];
    // GfEffectGround emits no foot step effect and keeps the water material while the water at the object is at
    // least this deep (the name is not the original's)
    float m_waterDepthLimit;
    // GfComBehaviorPc::setup sets it to the PC property's m_chestHeight (the name is not the original's)
    float m_chestHeight;
    unsigned char pad_2c[0x14];
    // the effect annotations (procMsgFxForceCancel ends the effects they started; the name is not the original's)
    fw::EffectResData* m_resData;
    // fn_71004B39DC puts it first in the packs it gathers when it is set; what it holds is unknown
    fw::EffectPack* pad_48;
    mm::mtl::FixedVector<PackEntry, 100> m_packs;  // (the name is not the original's)
    EffectCaster* m_caster;  // setupCaster's (the name is not the original's)
    fw::EffectPoint* m_pPoint;  // getEffectPoint's (the name is not the original's)
    // 16-aligned (its elements hold Vec3s): at 0x6B0, ends at 0xC6C0 (the name is not the original's)
    mm::mtl::FixedVector<Param, 256> m_params;
    // 16-aligned (its elements hold a Vec3): ends at 0x116D0 (the name is not the original's)
    mm::mtl::FixedVector<EventEfHandleTbl, 256> m_eventEfHandles;
    unsigned int m_layer;  // changeLayer's, the caster's layer (the name is not the original's)
    unsigned char pad_116d4[0xB4];
    // cleared by the constructor; EffectCaster::postUpdate hands it to its caster's setStateName (the name is not
    // the original's)
    mm::mtl::FixStr<32> m_stateName;
    unsigned int pad_117ac;  // a kind 0..8: setupEfp picks the effect point file index by it
    float m_motionFrame;  // EffectCaster::postUpdate hands it to setMotionFrame (the name is not the original's)
    unsigned char pad_117b4[0x8];
    unsigned int m_tailId;  // the tail number setupEfTail loaded last (the name is not the original's)
    unsigned char pad_117c0[0x10];
};
}  // namespace gf

#endif
