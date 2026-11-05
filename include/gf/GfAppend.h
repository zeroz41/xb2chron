#ifndef GF_GFAPPEND_H
#define GF_GFAPPEND_H

#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

namespace gf { enum OPTMNT : int; }

namespace gf {
// no table: a model attached to an object (a weapon, a belonging): its model and motion files and where it mounts
class GfAppend {
public:
    // a bone the model mounts on (FixedVector<MOUNT_INFO, 4>::assign copies the name as a FixStr, then the mount)
    struct MOUNT_INFO {
        mm::mtl::FixStr<16> m_name;
        OPTMNT m_mount;
    };

    GfAppend();
    // inline: 3.0.1 keeps no copy (session 19 notes put an out-of-line one in 1.0.0); setupExtraModel,
    // setupBelongingForDriver and fn_71004A2030 inline it
    GfAppend(const char* modelName, const char* motionName, unsigned short mountIndex, unsigned short rscID, float scale,
             bool secondList)
        : m_modelName(modelName), m_motionName(motionName), m_mountIndex(mountIndex), m_rscID(rscID), m_scale(scale),
          m_secondList(secondList) {}
    // the name of the bone the mount is on, "" when none is
    const char* getBone(OPTMNT mount) const;
    // inline: 3.0.1 keeps no copy (session 19 notes put an out-of-line one in 1.0.0)
    void addMount(MOUNT_INFO& info) { m_mounts.push_back(info); }
    const char* getModelName() const;
    const char* getMotionName() const;
    const char* getResourceName() const;
    const char* getAsmFileName() const;
    unsigned short getMountIndex() const;
    unsigned short getRscID() const;

    mm::mtl::FixedVector<MOUNT_INFO, 4> m_mounts;
    const char* m_modelName;      // getModelName
    const char* m_motionName;     // getMotionName
    unsigned short m_mountIndex;  // getMountIndex
    unsigned short m_rscID;       // getRscID
    float m_scale;                // the constructor's scale (1 by default): GfGameMount::detach scales the model by it
    // the constructor's bool: setupBelonging's appends set it when added to the second list (the name is not the
    // original's)
    bool m_secondList;
    // (0x81..0x87: alignment only: GfObjSetupWeapon's copy of its parameter copies 0x68..0x80 as one block)
};

// no table: an object's appends, in two lists (GfAppendUtil::setupWeapon adds to the one m_list names, then sets it
// back to 0); the appends are its own, deleted when it is cleared
class GfAppendInfo {
public:
    GfAppendInfo() : m_list(0) {}
    ~GfAppendInfo() { clear(); }
    // inline: 1.0.0's GfAppendUtil::setupWeapon inlines it (the name is not the original's)
    void clear() {
        for (int i = 0; i < 2; i++) {
            for (GfAppend **it = m_appends[i].begin(), **end = m_appends[i].end(); it != end; ++it) {
                if (*it != nullptr) {
                    delete *it;
                    *it = nullptr;
                }
            }
            m_appends[i].clear();
            m_list = 0;
        }
    }

    mm::mtl::FixedVector<GfAppend*, 10> m_appends[2];
    int m_list;  // the list appends are added to (the name is not the original's)
};
}  // namespace gf

#endif
