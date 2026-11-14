#ifndef CLASSES_GF_GFCOMEFFECTCASTER_H
#define CLASSES_GF_GFCOMEFFECTCASTER_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
#include "mm/Mat44.h"
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
namespace gf { class EffectCaster; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfComAsm; }
namespace gf { class GfComEvtAnim; }
namespace gf { class CallBackCache; }
namespace effect { class SendParam; }
namespace gf { class MsgFxForceCancel; }
namespace gf { class MsgFxBuff; }
namespace gf { class MsgFxWeapon; }
namespace gf { class GfObj; }
namespace gf { struct EffectMountSetupEv; }

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
        unsigned short pad_68;
        unsigned char pad_6a[0x4];
        // set when the effect took a bone frame from the effect point (cleanup hands pad_34's frame back)
        bool pad_6e;
        unsigned char pad_6f[0x5];
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
        // addMountEffectEv's (built on its stack: empty name, id 0, no frame, zero vector, flags clear)
        EventEfHandleTbl() : m_id(0), pad_30(mm::Vec3::zero), pad_40(false), pad_41(false), pad_42(false) {}

        // the bone whose frame removeMountEffectEv hands back (the name is not the original's)
        mm::mtl::FixStr<32> m_boneName;
        unsigned int m_id;  // removeMountEffectEv's key (the name is not the original's)
        // released by the destructor (reference_object.h's `m_RefCount > 0`); addMountEffectEv stores the bone's
        // frame from the effect point's createFrame or GfComModel::createBoneReferenceFrame when pad_41 is set
        mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> pad_28;
        mm::Vec3 pad_30;  // addMountEffectEv's EffectMountSetupEv::m_pos
        bool pad_40;
        // removeMountEffectEv hands the bone's frame back only when it is set
        bool pad_41;
        bool pad_42;
    };

    // what effectStart starts (0x50 bytes, built on the stack by its callers; the layout is what
    // GfGameObj::setupForLoopEffect fills, the field names are not the original's)
    struct EffectSetUp {
        EffectSetUp()
            : pad_20(nullptr), m_name(nullptr), m_caster(nullptr), m_scale(1.0f), pad_3c(-1.0f), pad_40(1.0f), pad_44(0), pad_46(0), pad_48(0),
              pad_49(0), pad_4a(0), pad_4b(0), pad_4c(0), pad_4d(0), pad_4e(1), pad_4f(0) {
            m_pos = mm::Vec3::zero;
            m_rot = mm::Vec3::zero;
        }

        mm::Vec3 m_pos;
        mm::Vec3 m_rot;
        // the object whose effect caster effectStart uses (the target's when null); procMsgFxBuff hands the message's
        GfObj* pad_20;
        const char* m_name;  // the effect's name
        EffectCaster* m_caster;
        float m_scale;
        float pad_3c;
        float pad_40;
        unsigned short pad_44;
        unsigned short pad_46;
        // procMsgFxBuff and procMsgFxWeapon copy the annotation's bytes into 0x48..0x4d (pad_f5, pad_f4, -, pad_f9,
        // pad_fa, pad_fb); procMsgFxWeapon sets 0x4a
        unsigned char pad_48;
        unsigned char pad_49;
        unsigned char pad_4a;
        unsigned char pad_4b;
        unsigned char pad_4c;
        unsigned char pad_4d;
        unsigned char pad_4e;
        unsigned char pad_4f;
    };

    // what setup and setupEfp read (the layout is what setupEfp shows; the names are not the original's)
    struct SetupInfo {
        unsigned int m_kind;  // setup's pad_117ac (the name is not the original's)
        unsigned char pad_4[0x4];
        GF_ASSET_HANDLE* m_asset;  // the asset setupEfp takes its effect point file from
        // setupEfp hands it to the effect point's EfpInitData (its first field); setup makes it m_layer
        unsigned int pad_10;
        unsigned int m_viewnum;  // setup's m_viewnum (the name is not the original's)
        float pad_18;  // setup's pad_117b8
    };

    GfComEffectCaster();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComEffectCaster();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4

    // ends every running effect an annotation started that has pad_f8 set
    void procMsgFxForceCancel(fw::MessageObject*, MsgFxForceCancel&);
    void cleanup();
    // the packs of the owner's efb and the asset's ".wiefb" files, the effect point and caster, the animation
    // callback, and the effects of the asset's SETUP annotations (type 0)
    void setup(const SetupInfo& info);
    void apply(const fw::UpdateInfo& info);
    void applyEvent(const fw::UpdateInfo& info);
    void asmCallback(GfComAsm* com, const CallBackCache& cache);
    void evtAnimCallback(GfComEvtAnim* com, const CallBackCache& cache);
    void callbackImpl(const CallBackCache& cache);
    // the caster's matrix times the named effect point's transform; false without a caster, its point or a point of
    // that name (the parameter names are not the original's)
    bool getEfpMatrix(const char* name, mm::Mat44& mtx);
    // the effect's matrix and scale for the parameter set (the parameter names are not the original's)
    void calcMtxAndScale(GfComEffectCaster* caster, Param* param, float rate, bool flag, effect::SendParam& sendParam);
    // 0: hand the parameters to the effect, 1: the same without m_flagB, 2: kill the effect (by m_followKind)
    int calcFollowAnnotetionTag(Param* param, effect::SendParam& sendParam);
    // kills the running effect with the handle (its Param's pad_ba set); defined inline in gf_com_effect_caster.cpp
    void effectEnd(unsigned int handle);
    // the handle of the effect started (procMsgFxBuff and procMsgFxWeapon keep it in the annotation's pad_10c)
    unsigned int effectStart(const EffectSetUp& setup, const char*);
    // starts the PROG_BUFF annotations (type 9) of the current animation state
    void procMsgFxBuff(fw::MessageObject*, MsgFxBuff& msg);
    // starts (attach) or ends (detach) the effects of the weapon annotations (type 2)
    void procMsgFxWeapon(fw::MessageObject*, MsgFxWeapon& msg);
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
    // 2.0.0's symbols name it. What it does: hands the matrix to the caster's flushDirectMatrix when there is a caster;
    // gf_game_scene's updaterAfterLayerIraWeaponAttach calls it.
    void applyEffpointByMatrix(const mm::Mat44& mtx);
    // 2.0.0's symbols name it. What it does: clears packs, adds pad_48 when set, then every entry's pack of m_packs
    // when GfGameManager::isGameTypeIra() holds; true if any was added.
    bool getEffectPack(mm::mtl::FixedVector<fw::EffectPack*, 8>& packs);
    // clears packs and adds the pack of every entry of m_packs with that id; true if any was added
    // (the parameter names are not the original's; the second int is unused)
    bool getWeaponEffectPack(mm::mtl::FixedVector<fw::EffectPack*, 8>& packs, int id, int);
    // drops the mounted effect with that id, handing its bone frame back first when it took one; false without one
    // (the parameter name is not the original's)
    bool removeMountEffectEv(unsigned int id);
    // mounts an event's effect (event::AttachUtil::setMount): an m_eventEfHandles entry with the setup's name, id,
    // position and flags, and the bone's frame when pad_41 is set; nothing for id 0
    void addMountEffectEv(const EffectMountSetupEv& setup);
    // the pack holding the named efb: an m_packs entry of the owner's weapon effect type (any entry when
    // GfGameManager::isGameTypeIra() holds), else pad_48, or for pad_117ac kinds 3 and 4 with a parent a pack made
    // from the owner's efb resource; null for "cmn" names (the parameter name is not the original's)
    fw::EffectPack* getWeaponEffectPack(const char* name);
    // an effect of the named file placed at the matrix (GfEffectGround's foot step and splashdown effects)
    void createFromFileName(const mm::Mat44& mtx, const char* fileName) const;

    static mm::mtl::RTTI m_rtti;

    // createFromFileName hands it to EffectManager::setViewnum when not 0 (the name is not the original's)
    unsigned int m_viewnum;
    // the constructor's values; what they hold is unknown
    bool pad_14;
    float pad_18;
    float pad_1c;
    float pad_20;
    // GfEffectGround emits no foot step effect and keeps the water material while the water at the object is at
    // least this deep (the name is not the original's)
    float m_waterDepthLimit;
    // GfComBehaviorPc::setup sets it to the PC property's m_chestHeight (the name is not the original's)
    float m_chestHeight;
    unsigned char pad_2c[0x4];
    // cleared by the constructor; what they hold is unknown
    unsigned long pad_30;
    unsigned long pad_38;
    // the effect annotations (procMsgFxForceCancel ends the effects they started; the name is not the original's)
    fw::EffectResData* m_resData;
    // getEffectPack puts it first in the packs it gathers when it is set; what it holds is unknown
    fw::EffectPack* pad_48;
    mm::mtl::FixedVector<PackEntry, 100> m_packs;  // (the name is not the original's)
    EffectCaster* m_caster;  // setupCaster's (the name is not the original's)
    fw::EffectPoint* m_pPoint;  // getEffectPoint's (the name is not the original's)
    // 16-aligned (its elements hold Vec3s): at 0x6B0, ends at 0xC6C0 (the name is not the original's)
    mm::mtl::FixedVector<Param, 256> m_params;
    // 16-aligned (its elements hold a Vec3): ends at 0x116D0 (the name is not the original's)
    mm::mtl::FixedVector<EventEfHandleTbl, 256> m_eventEfHandles;
    unsigned int m_layer;  // changeLayer's, the caster's layer (the name is not the original's)
    unsigned char pad_116d4[0xC];
    // set to the identity by the constructor; what they hold is unknown
    mm::Mat44 pad_116e0;
    mm::Mat44 pad_11720;
    // effect names the constructor sets ("cmn_001_020" and "cmn_001_000"); what they name is unknown
    mm::mtl::FixStr<16> pad_11760;
    mm::mtl::FixStr<16> pad_11774;
    // cleared by the constructor; EffectCaster::postUpdate hands it to its caster's setStateName (the name is not
    // the original's)
    mm::mtl::FixStr<32> m_stateName;
    unsigned int pad_117ac;  // a kind 0..8: setupEfp picks the effect point file index by it
    float m_motionFrame;  // EffectCaster::postUpdate hands it to setMotionFrame (the name is not the original's)
    unsigned int pad_117b4;  // 1 after the constructor
    float pad_117b8;
    unsigned int m_tailId;  // the tail number setupEfTail loaded last (the name is not the original's)
    unsigned char pad_117c0[0x4];
    unsigned char pad_117c4;  // cleared by the constructor
    // FootStepPlugin::update copies its m_running here (cleared by the constructor; the name is not the original's)
    bool m_running;
};
}  // namespace gf

#endif
