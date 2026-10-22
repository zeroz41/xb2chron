#ifndef SKD_SOLVER_H
#define SKD_SOLVER_H

namespace anm { class JobQueue; }

namespace skd {
// skd_solver.cpp's: the function the queue runs its apply-detect jobs with, registered (skd::Packet's constructor)
void registerApplyDetectJobExecuter(anm::JobQueue* queue);
}  // namespace skd

#endif
