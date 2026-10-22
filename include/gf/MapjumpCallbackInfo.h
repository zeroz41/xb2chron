#ifndef GF_MAPJUMPCALLBACKINFO_H
#define GF_MAPJUMPCALLBACKINFO_H

namespace gf {
// what the map jump events (IGfEvent::gevMapjump) pass (the file and field names are not the original's)
class MapjumpCallbackInfo {
public:
    unsigned char pad_0[0x4];
    unsigned int m_mapId;  // the map jumped to (GfFieldDmgManager matches its rows' MAPID)
};
}  // namespace gf

#endif
