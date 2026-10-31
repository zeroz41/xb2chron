#ifndef ANM_SKELETONIMPORTER_H
#define ANM_SKELETONIMPORTER_H

namespace anm { class Skeleton; }

namespace anm {
// reads a skeleton's binary (a "SKEL" one, version 6)
class SkeletonImporter {
public:
    // the root of a skeleton binary: its version, kind and the skeleton
    struct Root {
        int m_version;          // 6
        char m_magic[4];        // "SKEL"
        Skeleton* m_skeleton;   // in place in the binary: import installs its table
    };

    // the skeleton of `binary`, its pointers resolved, or null when it is not a skeleton binary
    static Skeleton* import(void* binary);
};
}  // namespace anm

#endif
