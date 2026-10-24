#include "classes/ml/ScnDebug.h"
#include "classes/ml/ScnDebugManipu.h"
#include "classes/ml/ScnObj.h"
#include "classes/ml/ScnObjClip.h"
#include "classes/ml/ScnObjEnvColi.h"
#include "classes/ml/ScnObjLight.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/ScnObjIBLDr.h"
#include "classes/ml/ScnRender.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnPoolObj.h"
#include "classes/ml/ScnCamMan.h"
#include "nn/os.h"
#include "ml/CriticalSection.h"
#include "classes/ml/Thread.h"
#include "classes/ml/ThreadNx.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/threadval.h"
#include "classes/ml/ScnDebugManipuObj.h"
#include "classes/ml/ScnObjIBL.h"
#include "classes/ml/ScnDebugManipuRot.h"
#include "classes/ml/ScnDebugManipuTrans.h"
#include "classes/ml/DevClock.h"
#include "ml/EdianUtil.h"
#include "ml/TimeCount.h"
#include "ml/WorkUtil.h"
#include "mtl/MemManager.h"
#include "mm/mtl/FixStr.h"
#include <string.h>

namespace ml {

unsigned int EdianUtil::read(const unsigned int& value) {
    return __builtin_bswap32(value);
}

short EdianUtil::read(const short& value) {
    return __builtin_bswap16(value);
}

void TimeCount::reset() {
    DevClock::getClockNow(pad_0);
}

void TimeCount::start() {
    DevClock::getClockNow(pad_0);
}

void TimeCount::getClockLap(long& lap) const {
    long now;
    DevClock::getClockNow(now);
    lap = now - pad_0;
}

float TimeCount::getSecLap() const {
    float sec;
    DevClock::getTimeNow(sec, pad_0);
    return sec;
}

}  // namespace ml
