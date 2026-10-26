#ifndef GF_GFUTIL_H
#define GF_GFUTIL_H

#include "mm/mtl/FixStr.h"

namespace mm { class Vec3; }

namespace gf { namespace util {

// a world position's place on the screen; false when it is not in front of the camera
bool getScreenPos(mm::Vec3& screen, const mm::Vec3& world);
// the file name in a path (GfFileSizePool hashes it apart from the whole path)
const char* getFilePtrFromPath(const char* path);
// a path's file name without its extension (forwards to ml::PathUtil::getNoPathExtName; SCOM_SCRIPT::create names
// its script with it)
mm::mtl::FixStr<64> getNoPathExtName(const char* path);
// a collision hit on the segment from `from` to `to`, written to `hit`; false when nothing is hit
// (GfAppendWire::checkAndSetupSalvagePoint drops a salvage point with it)
bool getHitCollision(mm::Vec3& hit, const mm::Vec3& from, const mm::Vec3& to);

}}  // namespace gf::util

#endif
