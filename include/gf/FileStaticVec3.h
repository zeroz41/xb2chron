#ifndef GF_FILESTATICVEC3_H
#define GF_FILESTATICVEC3_H

#include "mm/Vec3.h"

// Two mm::Vec3 constants a shared gf header defines at file scope: every unit that includes it gets its own
// copies and constructs them in its static initializer, ahead of the unit's own statics. Nothing reads them
// (no code references either copy in any unit), and 1.0.0 has neither, so their name and header are unknown.
static const mm::Vec3 s_unkVec3A(0.038f, 0.085f, 0.046f);
static const mm::Vec3 s_unkVec3B(-1.57079637f, -1.57079637f, 0.0f);

#endif
