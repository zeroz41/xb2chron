#ifndef GF_MAPJUMPCALLBACKINFO_H
#define GF_MAPJUMPCALLBACKINFO_H

namespace gf {
// what the map jump events (IGfEvent::gevMapjump) pass (the file and field names are not the original's)
class MapjumpCallbackInfo {
public:
    // every field zeroed (GfFieldWeather's constructor, inlined in its build, zeroes its copy so)
    MapjumpCallbackInfo() : m_mapJumpId(0), m_mapId(0), pad_8(0), m_withSaveData(false), m_jumpKind(0) {}

    // the map jump (GfFieldManager::gevMapjump hands it to GfDataMap::getMapID, as gevReloadBdat does
    // GfGameManager::getMapJumpID; the name is not the original's)
    unsigned int m_mapJumpId;
    unsigned int m_mapId;  // the map jumped to (GfFieldDmgManager matches its rows' MAPID)
    unsigned int pad_8;
    // whether the jump loads save data (GfGameEnv::gevMapjump keeps it for isMapjumpWithSaveData; the name is not
    // the original's)
    bool m_withSaveData;
    unsigned char pad_D[0x3];
    // the kind of jump (GfFieldBgm::gevMapjump sets and clears its dead-sequence flag for kind 2; the name is not
    // the original's)
    int m_jumpKind;
};
}  // namespace gf

#endif
