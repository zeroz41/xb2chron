#ifndef CLASSES_GF_GFGMKLOCATORATLAS_H
#define CLASSES_GF_GFGMKLOCATORATLAS_H

#include "mm/Vec3.h"

namespace gf {
// GfFieldGimmick holds one at 0xF4C0 (its constructor's GfGmkLocatorAtlas(nullptr)); 0x480 bytes, up to
// GfFieldGimmick's next member at 0xF940
class GfGmkLocatorAtlas {
public:
    // what create builds the atlas for: the map and its bounds (create copies it to the atlas's start). Holders
    // construct it with no map and inverted bounds (GfMenuObjWorldMap's constructor); the names are not the original's
    struct CreateInfo {
        CreateInfo() : m_mapId(0), m_param(0), m_min(1e12f, 1e12f, 1e12f), m_max(-1e12f, -1e12f, -1e12f) {}
        int m_mapId;  // create compares it with GfGameManager::getMapID
        int m_param;
        mm::Vec3 m_min;
        mm::Vec3 m_max;
    };

    GfGmkLocatorAtlas(const CreateInfo* info);
    void create(const CreateInfo& info);
    void update(float delta);

    CreateInfo m_info;
    unsigned char pad_30[0x450];
};
}  // namespace gf

#endif
