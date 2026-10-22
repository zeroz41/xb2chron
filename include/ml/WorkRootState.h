#ifndef ML_WORKROOTSTATE_H
#define ML_WORKROOTSTATE_H

namespace ml { class WorkObj; }

namespace ml {
// the root of the work objects (ml/_wrootst/WorkRoot.cpp)
class WorkRootState {
public:
    // work entered under parent (the parameter names are not the original's)
    static void entryWork(WorkObj* work, WorkObj* parent, bool flag);
};
}  // namespace ml

#endif
