#ifndef CLASSES_GF_VOICEINFO_PJOB_H
#define CLASSES_GF_VOICEINFO_PJOB_H

namespace gf { namespace VoiceInfo {
// table none (its derived classes')
class PJOB {
public:
    virtual ~PJOB() {}  // slot 0
    virtual bool exec() = 0;  // slot 2
    virtual void getName();  // slot 3
    virtual void getVoiceHandle() const;  // slot 4
};
}}  // namespace gf::VoiceInfo

#endif
