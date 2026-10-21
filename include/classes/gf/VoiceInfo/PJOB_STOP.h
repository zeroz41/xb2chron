#ifndef CLASSES_GF_VOICEINFO_PJOB_STOP_H
#define CLASSES_GF_VOICEINFO_PJOB_STOP_H

#include "classes/gf/VoiceInfo/PJOB.h"

namespace gf { namespace VoiceInfo {
// table 0x7100B56B98
class PJOB_STOP : public ::gf::VoiceInfo::PJOB {
public:
    virtual ~PJOB_STOP();  // slot 0
    virtual bool exec();  // slot 2
};
}}  // namespace gf::VoiceInfo

#endif
