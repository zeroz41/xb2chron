#include "classes/ssd/SoundCore.h"
#include "classes/ssd/SystemCorePlatform.h"
#include "classes/ssd/BehaviorInstance.h"
#include "classes/ssd/XorShift128Random.h"
#include "classes/ssd/SystemCore.h"
#include "classes/ssd/SoundHandle.h"
#include "classes/ssd/SoundEntry.h"

namespace ssd {

void SoundHandle::UpdateAudioFrame(float frameTime) {
    pitch_.Update(frameTime);
    volume_.Update(frameTime);
}

}  // namespace ssd
