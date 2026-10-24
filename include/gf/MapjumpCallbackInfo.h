#ifndef GF_MAPJUMPCALLBACKINFO_H
#define GF_MAPJUMPCALLBACKINFO_H

namespace gf {
// what the map jump events (IGfEvent::gevMapjump) pass (the file and field names are not the original's)
class MapjumpCallbackInfo {
public:
    // the map jump (GfFieldManager::gevMapjump hands it to GfDataMap::getMapID, as gevReloadBdat does
    // GfGameManager::getMapJumpID; the name is not the original's)
    unsigned int m_mapJumpId;
    unsigned int m_mapId;  // the map jumped to (GfFieldDmgManager matches its rows' MAPID)
};
}  // namespace gf

#endif
