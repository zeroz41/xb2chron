#ifndef CLASSES_GF_VOICEINFO_PJOB_WAIT_STOP_H
#define CLASSES_GF_VOICEINFO_PJOB_WAIT_STOP_H

#include "classes/gf/VoiceInfo/PJOB.h"

namespace gf { namespace VoiceInfo {
// table 0x7100B56BD0
class PJOB_WAIT_STOP : public ::gf::VoiceInfo::PJOB {
public:
    virtual ~PJOB_WAIT_STOP();  // slot 0
    virtual void exec();  // slot 2
};
}}  // namespace gf::VoiceInfo

#endif
