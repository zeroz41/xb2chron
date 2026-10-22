#ifndef GF_GFUTIL_H
#define GF_GFUTIL_H

namespace mm { class Vec3; }

namespace gf { namespace util {

// a world position's place on the screen; false when it is not in front of the camera
bool getScreenPos(mm::Vec3& screen, const mm::Vec3& world);
// the file name in a path (GfFileSizePool hashes it apart from the whole path)
const char* getFilePtrFromPath(const char* path);

}}  // namespace gf::util

#endif
