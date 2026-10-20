#ifndef CLASSES_GF_VOICEINFO_PJOB_PLAY_H
#define CLASSES_GF_VOICEINFO_PJOB_PLAY_H

namespace gf { namespace VoiceInfo {
// table 0x7100B56B60
class PJOB_PLAY {
public:
    virtual ~PJOB_PLAY();  // slot 0
    virtual void vf2();  // slot 2
    virtual void getName();  // slot 3
    virtual void getVoiceHandle() const;  // slot 4
};
}}  // namespace gf::VoiceInfo

#endif
