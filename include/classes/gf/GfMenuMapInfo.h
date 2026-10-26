#ifndef CLASSES_GF_GFMENUMAPINFO_H
#define CLASSES_GF_GFMENUMAPINFO_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Vector.h"

namespace gf { class GfMenuMapInfo; }
namespace gf { class GfSetupParam; }
namespace fw { class CommonResource; }
namespace fw { struct UpdateInfo; }

namespace gf {
// table 0x7100B5EDC0
class GfMenuMapInfo : public ::mm::mtl::PtrSingleton< ::gf::GfMenuMapInfo> {
public:
    // an area of a map: its name and bounds (getMapAreaFromName fills it; GfMenuObjWorldMap::getFloorAABB clears it
    // first); the names are not the original's
    struct MapAreaInfo {
        // GfMenuObjWorldMap::getFloorAABB's clears the name's first byte and the rest
        MapAreaInfo() : m_minX(0.0f), m_minY(0.0f), m_minZ(0.0f), m_maxX(0.0f), m_maxY(0.0f), m_maxZ(0.0f), pad_38() {
            m_name[0] = '\0';
        }
        char m_name[0x20];
        float m_minX, m_minY, m_minZ;
        float m_maxX, m_maxY, m_maxZ;
        unsigned char pad_38[0x10];
    };
    // a map info resource's asset: its areas (getMapAreaCount, getMapArea read it); the names are not the original's
    struct MapData {
        unsigned char pad_0[4];
        unsigned int m_areaCount;
        MapAreaInfo m_areas[1];
    };
    // an icon of the mini map (0x30 bytes; initialize reserves 64 per list)
    struct MiniIcon {
        unsigned int pad_0;
        unsigned int pad_4;
        mm::Vec3 m_pos;
        unsigned int pad_20;
        unsigned int pad_24;
        unsigned int pad_28;
    };
    // a map segment image resource (0x18 bytes)
    struct SegInfo {
        fw::CommonResource* m_resource;
        unsigned char pad_8[2];
        bool m_useOtherArea;          // getMapSegImageName then reads m_otherArea's segment image instead
        unsigned char pad_b[5];
        int m_otherArea;
        unsigned int m_floorId;       // fn_7100361DC0 returns the current area's (GfMenuObjWorldMap reads it)
    };
    // a segment image resource's asset: the segment grid (getMapSegImageName, fn_71003620FC read it); the names are
    // not the original's
    struct SegData {
        int m_width;
        int m_height;
        int m_columns;
        int m_rows;
        unsigned char pad_10[0x10];
        unsigned char m_cells[1];     // per segment, row-major from the far corner: whether it has an image
    };

    GfMenuMapInfo(const GfSetupParam& param);
    virtual ~GfMenuMapInfo();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    void initialize(const GfSetupParam& param);
    void finalize();
    static bool isInitialized();
    static bool isLoading();
    static void postUpdate(const fw::UpdateInfo& info);
    // the number of areas of that map info; -1 without the menu
    static int getMapAreaCount(int index);
    static bool getMapArea(int index, unsigned int area, MapAreaInfo& info);
    static const MapAreaInfo* getMapArea(int index, unsigned int area);
    static void setCurrentMap(unsigned int mapId);
    static bool getMapAreaFromName(int index, const char* name, MapAreaInfo& info);
    static const MapAreaInfo* getMapAreaFromName(int index, const char* name);
    static bool getMiniIconList(unsigned int kind, const mm::mtl::Vector<MiniIcon>** list);
    static bool getMapRatio(float& x, float& y);
    static bool getMapSize(short& x, short& y, short& width, short& height);
    static bool getCurMapAreaInfo(MapAreaInfo& info);
    // the current map's segment image offset (GfMenuObjMinimap2::refreshMapPosition centers its map image by it);
    // false when there is none
    static bool getMapSegImageOffs(mm::Pnt<short>& offs);
    // the file name of the current map's segment image at that column and row (GfMenuObjMinimap2's map listener
    // streams the 3x3 segments by it); false when there is none
    static bool getMapSegImageName(unsigned int column, unsigned int row, mm::mtl::FixStr<64>& name);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads the menu's
    // singleton's segment infos. What it does: the current area's segment info's value at 0x14, 0 when the area
    // has none; GfMenuObjWorldMap::initialize, setupZoneList and its zone list listener call it.
    static unsigned int fn_7100361DC0();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads the menu's
    // singleton. What it does: when the current area's segment image has loaded, fills rect with the segment
    // offset (0x6c, 0x70) and the image's first two values; returns false either way (GfMenuObjMinimap2::update).
    static bool fn_71003620FC(mm::Rect<int>& rect);

    bool m_initialized;                                    // set by initialize
    mm::mtl::Vector<fw::CommonResource*> m_mapResources;   // per map info: its resource
    mm::mtl::Vector<SegInfo> m_segInfos;                   // the current map's segment images
    int m_curMapIndex;                                     // -1: none
    int m_curAreaIndex;                                    // -1: none
    unsigned char pad_68[4];
    int m_segOffsX;  // the segment grid's offset (getMapSegImageName adds the column and row to it)
    int m_segOffsY;
    int m_segImageOffsX;
    int m_segImageOffsY;
    unsigned char pad_7c[4];
    mm::mtl::Vector<MiniIcon> m_miniIcons[15];             // per icon kind
    float m_mapRatioX;
    float m_mapRatioY;
    short m_mapX;
    short m_mapY;
    short m_mapWidth;
    short m_mapHeight;
    bool pad_2e8;
    void* pad_2f0;
    int pad_2f8;
    void* pad_300;
    int pad_308;
    void* pad_310;
    unsigned char pad_318[8];
};
}  // namespace gf

#endif
