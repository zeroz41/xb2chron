#ifndef CLASSES_GF_GFCOMSOUND_H
#define CLASSES_GF_GFCOMSOUND_H

#include "mm/mtl/RTTI.h"
namespace gf {
// the event name of the sound annotations GfComSound::setup and GfExtendPacking::registerSoundTrigger register
// (lbl_71009A370D, "sound")
extern const char* SOUND_CALLBACK_EVENT_NAME;

// table 0x7100B69CC0
class GfComSound {
public:
    class SoundInfo;
    class ViewerListener;
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComSound();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual void vf4();  // slot 4
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
