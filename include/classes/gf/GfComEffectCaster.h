#ifndef CLASSES_GF_GFCOMEFFECTCASTER_H
#define CLASSES_GF_GFCOMEFFECTCASTER_H

#include "mm/mtl/RTTI.h"
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
namespace gf { class GfComAsm; }
namespace gf { class GfComEvtAnim; }
namespace gf { class CallBackCache; }

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
    struct Param {
        unsigned char pad_0[0x28];
        float m_timer;  // startTimer clears it (the name is not the original's)
        unsigned char pad_2c[0x4];
        float m_speed;  // setSpeed's (the name is not the original's)
        unsigned char pad_34[0x24];
        unsigned int m_id;  // findEffectCasterParam's key (the name is not the original's)
        unsigned char pad_5c[0x4];
        // released by the destructor (reference_object.h's `m_RefCount > 0`); what it holds is unknown
        mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> pad_60;
        unsigned char pad_68[0x58];
    };
    struct EventEfHandleTbl {
        unsigned char pad_0[0x28];
        // released by the destructor (reference_object.h's `m_RefCount > 0`); what it holds is unknown
        mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> pad_28;
        unsigned char pad_30[0x20];
    };

    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComEffectCaster();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4

    void cleanup();
    void apply(const fw::UpdateInfo& info);
    void applyEvent(const fw::UpdateInfo& info);
    void asmCallback(GfComAsm* com, const CallBackCache& cache);
    void evtAnimCallback(GfComEvtAnim* com, const CallBackCache& cache);
    void callbackImpl(const CallBackCache& cache);
    fw::EffectPoint* getEffectPoint();
    static void registerAsmCallbackEffect(GF_OBJ_HANDLE* handle, anm::ResASM* asmRes, fw::EffectResData* resData);
    void setupCaster(const fw::EffectPoint* point);
    Param* findEffectCasterParam(unsigned int id);
    const char* getEfpData(const char* name, mm::Mat44& mtx);
    void setCaster(unsigned int handle);
    bool setSpeed(unsigned int id, float speed);
    bool startTimer(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits in this class's
    // code and reads m_caster from `this`. What it does: hands the matrix to the caster's fn_71004B3B78 when there
    // is a caster; gf_game_scene's fn_71002C7DC0 calls it.
    void fn_71004B3B68(const mm::Mat44& mtx);

    static mm::mtl::RTTI m_rtti;

    unsigned char pad_10[0x40];
    mm::mtl::FixedVector<PackEntry, 100> m_packs;  // (the name is not the original's)
    EffectCaster* m_caster;  // setupCaster's (the name is not the original's)
    fw::EffectPoint* m_pPoint;  // getEffectPoint's (the name is not the original's)
    unsigned char pad_6a8[0x8];
    mm::mtl::FixedVector<Param, 256> m_params;  // findEffectCasterParam's (the name is not the original's)
    unsigned char pad_c6b8[0x8];
    mm::mtl::FixedVector<EventEfHandleTbl, 256> m_eventEfHandles;  // (the name is not the original's)
    unsigned char pad_116c8[0x8];
    unsigned int m_layer;  // changeLayer's, the caster's layer (the name is not the original's)
    unsigned char pad_116d4[0xB4];
    // cleared by the constructor; EffectCaster::postUpdate hands it to its caster's setStateName (the name is not
    // the original's)
    mm::mtl::FixStr<32> m_stateName;
    unsigned char pad_117ac[0x4];
    float m_motionFrame;  // EffectCaster::postUpdate hands it to setMotionFrame (the name is not the original's)
    unsigned char pad_117b4[0x1C];
};
}  // namespace gf

#endif
