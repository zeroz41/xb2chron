#ifndef CLASSES_GF_GFCOMSOUND_H
#define CLASSES_GF_GFCOMSOUND_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/mm/mtl/List.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/SoundResSourceManager.h"
#include "classes/fw/SoundUpdater.h"
#include "classes/gf/GfComponent.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GfComAsm; }
namespace gf { class GfComEvtAnim; }
namespace gf { class CallBackCache; }

namespace gf {
// the event name of the sound annotations GfComSound::setup and GfExtendPacking::registerSoundTrigger register
// (lbl_71009A370D, "sound")
extern const char* SOUND_CALLBACK_EVENT_NAME;

// table 0x7100B69CC0: an object's sounds; the sounds it plays stay in m_cache until they end (the field names are
// not the original's)
class GfComSound : public ::gf::GfComponent {
public:
    // a sound it plays (playSe, playSeBone, playSe2D store them; flush follows m_frame while m_follow is set)
    struct SoundInfo {
        SoundInfo() : m_handle(0), m_type(0), m_offset(mm::Vec3::zero), m_follow(true) {}
        unsigned int m_handle;  // SoundResSourceManager::playSe's: eraseCache stops it
        mm::mtl::FixStr<32> m_name;  // the source's name: stopSe finds the entry by it
        mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_frame;  // the frame flush places the sound at
        int m_type;  // 1: m_frame is m_boneName's (eraseCache destroys that bone frame)
        mm::mtl::FixStr<32> m_boneName;
        mm::Vec3 m_offset;  // flush rotates it by the frame and adds the frame's position
        bool m_follow;  // flush moves the sound while set; a sound that does not loop clears it
    };
    // table 0x7100B69CF8
    class ViewerListener {
    public:
        explicit ViewerListener(GfComSound* owner) : m_pOwner(owner) {}
        // slot 0 (inline: emitted after the class's own functions)
        virtual void onWkStandbyLogout() {
            if (m_pOwner != nullptr) {
                m_pOwner->m_pViewer = nullptr;
            }
        }
        GfComSound* m_pOwner;  // (the name is not the original's)
    };
    typedef mm::mtl::_reslist_iterator<SoundInfo, SoundInfo&, SoundInfo*> CacheIterator;

    GfComSound();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComSound();  // slot 1
    virtual void changeLayer(unsigned int prevLayer, unsigned int layer);  // slot 3
    virtual bool recieveMessage(fw::MessageObject* sender, fw::Message& msg);  // slot 4
    void setup();
    void callbackAnim(GfComAsm* asmCom, const CallBackCache& cache);
    void callbackAnimForEvent(GfComEvtAnim* evtAnim, const CallBackCache& cache);
    unsigned int flush();
    void cleanup();
    void playSe(const char* name, float volume, const mm::Vec3& offset, bool follow);
    void playSeBone(const char* name, const char* bone, float volume, const mm::Vec3& offset, bool follow);
    void playSe2D(const char* name, float volume, bool, bool);  // not written yet: what the two flags do is not read
    bool stopSe(const char* name);
    CacheIterator eraseCache(CacheIterator it);
    void setAttributeVariable(int value);
    int getAttributeVariable() const;
    void flushVariables();
    void callbackAnimImpl(const CallBackCache& cache);
    static mm::mtl::RTTI m_rtti;

    fw::SoundVariableTable m_variables;  // what the sounds it plays pick by (setup sets them)
    mm::mtl::List<SoundInfo> m_cache;  // the sounds playing (cleanup erases them all); 16-aligned, to 0xF0
    // linked into SoundLayerManager's list of its layer; its delegate is setup's: flush (the name is not the
    // original's)
    fw::SoundUpdater m_soundUpdater;
    void* pad_128;  // the constructor clears it
    // what the sound resources call back with for a resource's custom info (GfComBehaviorPc::setup sets
    // callbackSound; the name is not the original's)
    mm::mtl::Delegate<void(const fw::ResSoundData&, fw::SoundResSourceManager::CustomInfo*)> m_customInfoCallback;
    bool m_isSetup;  // setup sets it, cleanup clears it
    ViewerListener m_viewerListener;
    void* m_pViewer;  // the viewer listener's onWkStandbyLogout clears it
};
}  // namespace gf

#endif
