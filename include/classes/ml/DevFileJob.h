#ifndef CLASSES_ML_DEVFILEJOB_H
#define CLASSES_ML_DEVFILEJOB_H

#include "mm/mtl/FixedList.h"

namespace ml {
// Only the static member is known (symbol _ZN2ml10DevFileJob6s_jobsE, .bss 0x7100EC54F0): the static initializer of
// th_dev_file_nx builds it and registers FixedList<unsigned int, 512>'s destructor; no code that reads it survives.
// A class (not a namespace) because ml's namespaces are lower-case *_detail; the mangling is the same for both.
class DevFileJob {
public:
    static mm::mtl::FixedList<unsigned int, 512> s_jobs;
};
}  // namespace ml

#endif
