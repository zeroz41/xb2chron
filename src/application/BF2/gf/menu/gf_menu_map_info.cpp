#include "classes/gf/GfMenuMapInfo.h"
#include "classes/gf/GfAllocator.h"
#include "classes/fw/CommonResource.h"
#include "gf/GfMenuObjUtil.h"
#include <string.h>

namespace gf {

GfMenuMapInfo::GfMenuMapInfo(const GfSetupParam& param)
    : m_initialized(false), m_curMapIndex(-1), m_curAreaIndex(-1), m_segOffsX(0), m_segOffsY(0), m_segImageOffsX(0),
      m_segImageOffsY(0), pad_2e8(false), pad_2f0(nullptr), pad_2f8(0), pad_300(nullptr), pad_308(0),
      pad_310(nullptr) {
    initialize(param);
}

GfMenuMapInfo::~GfMenuMapInfo() {}

void GfMenuMapInfo::build(const GfSetupParam& param) {
#line 117
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuMapInfo(param);
}

void GfMenuMapInfo::destroy() {
    GfMenuMapInfo* info = get();
    info->finalize();
    delete info;
}

void GfMenuMapInfo::initialize(const GfSetupParam& param) {
    m_segInfos.setAllocator(getAllocator(ALLOCATOR(0)));
    for (int i = 0; i < 15; i++) {
        m_miniIcons[i].setAllocator(getAllocator(ALLOCATOR(0)));
        m_miniIcons[i].reserve(64);
    }
    m_initialized = true;
}

void GfMenuMapInfo::finalize() {
    if (m_mapResources.capacity() != 0) {
        for (unsigned int i = 0; i < m_mapResources.size(); i++) {
            if (m_mapResources[i] != nullptr) {
                m_mapResources[i]->release();
                m_mapResources[i] = nullptr;
            }
        }
        m_mapResources.destroy();
    }
    if (m_segInfos.capacity() != 0) {
        for (unsigned int i = 0; i < m_segInfos.size(); i++) {
            if (m_segInfos[i].m_resource != nullptr) {
                m_segInfos[i].m_resource->release();
                m_segInfos[i].m_resource = nullptr;
            }
        }
        m_segInfos.destroy();
    }
    for (int i = 0; i < 15; i++) {
        m_miniIcons[i].destroy();
    }
    m_initialized = false;
}

bool GfMenuMapInfo::isInitialized() {
    GfMenuMapInfo* info = get();
    if (info != nullptr && info->m_initialized) {
        return !isLoading();
    }
    return false;
}

bool GfMenuMapInfo::isLoading() {
    GfMenuMapInfo* info = get();
    if (info != nullptr) {
        if (info->m_mapResources.capacity() != 0) {
            for (unsigned int i = 0; i < info->m_mapResources.size(); i++) {
                if (!info->m_mapResources[i]->valid()) {
                    return true;
                }
            }
        }
        if (info->m_segInfos.capacity() != 0) {
            for (unsigned int i = 0; i < info->m_segInfos.size(); i++) {
                if (!info->m_segInfos[i].m_resource->valid()) {
                    return true;
                }
            }
        }
    }
    return false;
}

int GfMenuMapInfo::getMapAreaCount(int index) {
    GfMenuMapInfo* info = get();
    if (info == nullptr) {
        return -1;
    }
    if (index < info->m_mapResources.size() && info->m_mapResources[index]->valid()) {
        if (info->m_mapResources[index]->getAssetName() == nullptr) {
            return 0;
        }
        return static_cast<MapData*>(info->m_mapResources[index]->getAssetData())->m_areaCount;
    }
    return 0;
}

bool GfMenuMapInfo::getMapArea(int index, unsigned int area, MapAreaInfo& out) {
    GfMenuMapInfo* info = get();
    if (info != nullptr && index < info->m_mapResources.size() && info->m_mapResources[index]->valid()) {
        if (info->m_mapResources[index]->getAssetName() == nullptr) {
            return false;
        }
        MapData* data = static_cast<MapData*>(info->m_mapResources[index]->getAssetData());
        if (area < data->m_areaCount) {
            out = data->m_areas[area];
            return true;
        }
    }
    return false;
}

const GfMenuMapInfo::MapAreaInfo* GfMenuMapInfo::getMapArea(int index, unsigned int area) {
    GfMenuMapInfo* info = get();
    if (info != nullptr && index < info->m_mapResources.size() && info->m_mapResources[index]->valid()) {
        if (info->m_mapResources[index]->getAssetName() == nullptr) {
            return nullptr;
        }
        MapData* data = static_cast<MapData*>(info->m_mapResources[index]->getAssetData());
        if (area < data->m_areaCount) {
            return &data->m_areas[area];
        }
        return nullptr;
    }
    return nullptr;
}

bool GfMenuMapInfo::getMapAreaFromName(int index, const char* name, MapAreaInfo& out) {
    GfMenuMapInfo* info = get();
    if (info != nullptr && index < info->m_mapResources.size() && info->m_mapResources[index]->valid()) {
        if (info->m_mapResources[index]->getAssetName() == nullptr) {
            return false;
        }
        MapData* data = static_cast<MapData*>(info->m_mapResources[index]->getAssetData());
        for (unsigned int i = 0; i < data->m_areaCount; i++) {
            if (strcmp(data->m_areas[i].m_name, name) == 0) {
                out = data->m_areas[i];
                return true;
            }
        }
    }
    return false;
}

const GfMenuMapInfo::MapAreaInfo* GfMenuMapInfo::getMapAreaFromName(int index, const char* name) {
    GfMenuMapInfo* info = get();
    if (info != nullptr && index < info->m_mapResources.size() && info->m_mapResources[index]->valid()) {
        if (info->m_mapResources[index]->getAssetName() == nullptr) {
            return nullptr;
        }
        MapData* data = static_cast<MapData*>(info->m_mapResources[index]->getAssetData());
        for (unsigned int i = 0; i < data->m_areaCount; i++) {
            if (strcmp(data->m_areas[i].m_name, name) == 0) {
                return &data->m_areas[i];
            }
        }
    }
    return nullptr;
}

unsigned int GfMenuMapInfo::getCurMapInfoID() {
    GfMenuMapInfo* info = get();
    if (info != nullptr) {
        int area = info->m_curAreaIndex;
        if (area < info->m_segInfos.size()) {
            return info->m_segInfos[area].m_floorId;
        }
    }
    return 0;
}

bool GfMenuMapInfo::isIraSpecialAreaCheckForGimmick(const mm::Vec3& pos, const char* mapName, const char* otherName) {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    if (strcmp(mapName, "dlc3_ma40a_f01") == 0 && strcmp(otherName, "dlc3_ma40a_f03") == 0) {
        if (pos.y > -47.0f) {
            return true;
        }
        if (pos.x < -350.0f || pos.x > -250.0f) {
            if (pos.y > -54.0f) {
                return true;
            }
        } else {
            unsigned char outside = pos.z < 150.0f || pos.z > 360.0f;
            if (pos.y > -54.0f && outside) {
                return true;
            }
        }
    }
    if (strcmp(mapName, "dlc3_ma40a_f03") == 0 && strcmp(otherName, "dlc3_ma40a_f01") == 0) {
        if (pos.y > -47.0f) {
            return true;
        }
        if (pos.x < -350.0f || pos.x > -250.0f) {
            if (pos.y > -54.0f) {
                return true;
            }
        } else {
            unsigned char outside = pos.z < 150.0f || pos.z > 360.0f;
            if (pos.y > -54.0f && outside) {
                return true;
            }
        }
    }
    return false;
}

bool GfMenuMapInfo::getMiniIconList(unsigned int kind, const mm::mtl::Vector<MiniIcon>** list) {
    GfMenuMapInfo* info = get();
    if (kind < 15 && info != nullptr) {
        *list = &info->m_miniIcons[kind];
        return true;
    }
    return false;
}

bool GfMenuMapInfo::getMapRatio(float& x, float& y) {
    GfMenuMapInfo* info = get();
    if (info == nullptr) {
        return false;
    }
    x = info->m_mapRatioX;
    y = info->m_mapRatioY;
    return true;
}

bool GfMenuMapInfo::getMapSize(short& x, short& y, short& width, short& height) {
    GfMenuMapInfo* info = get();
    if (info == nullptr) {
        return false;
    }
    x = info->m_mapX;
    y = info->m_mapY;
    width = info->m_mapWidth;
    height = info->m_mapHeight;
    return true;
}

bool GfMenuMapInfo::getCurMapAreaInfo(MapAreaInfo& out) {
    GfMenuMapInfo* info = get();
    if (info == nullptr) {
        return false;
    }
    getMapArea(info->m_curMapIndex, info->m_curAreaIndex, out);
    return true;
}

bool GfMenuMapInfo::getCurMapRegionInfo(RegionInfo& region) {
    GfMenuMapInfo* info = get();
    if (info != nullptr) {
        SegData* data = static_cast<SegData*>(info->m_segInfos[info->m_curAreaIndex].m_resource->getAssetData());
        if (data != nullptr) {
            region.m_offsX = info->m_segOffsX;
            region.m_offsY = info->m_segOffsY;
            region.m_width = data->m_width;
            region.m_height = data->m_height;
        }
    }
    return false;
}

}  // namespace gf

// the segment vector's growth (its user is not written yet)
template void mm::mtl::Vector<gf::GfMenuMapInfo::SegInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfMenuMapInfo::MiniIcon>::push_back(const gf::GfMenuMapInfo::MiniIcon&);
