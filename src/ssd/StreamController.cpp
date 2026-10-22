#include "ssd/Mutex.h"
#include "classes/ssd/AudioFileBase.h"
#include "classes/ssd/AudioFileSadf.h"

namespace ssd {

// the lock the debug output stream takes (1.0.0's ssd::InitDebug/QuitDebug set it up and tear it down)
Mutex OutStreamLock;

void AudioFileBase::SetPositionBySample(unsigned long) {}

void AudioFileSadf::SetPositionBySample(unsigned long) {}

}  // namespace ssd
