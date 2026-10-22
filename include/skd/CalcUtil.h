#ifndef SKD_CALCUTIL_H
#define SKD_CALCUTIL_H

namespace anm { class JobQueue; }

namespace skd {
// skd_calc_util.cpp's: the functions the queue runs each shape's detection jobs with, registered (skd::Packet's
// constructor). registerDetectSphereJobExecuter's address is split into skt/CommandManager.
void registerDetectCapsuleJobExecuter(anm::JobQueue* queue);
void registerDetectPlaneJobExecuter(anm::JobQueue* queue);
void registerDetectSphereJobExecuter(anm::JobQueue* queue);
}  // namespace skd

#endif
