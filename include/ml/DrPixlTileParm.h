#ifndef ML_DRPIXLTILEPARM_H
#define ML_DRPIXLTILEPARM_H

namespace ml {
class DrPixlTileParm {
public:
    // the tile pass begin/end bracket (DrMdoCtlSeamAll::callRenderSeamAll passes 3); no value has a name yet
    enum TileType {};

    void begin(TileType type);
    void end(TileType type);
    DrPixlTileParm();
    ~DrPixlTileParm();
    void update();

    // one pass's tiled cache setting (the field names are not the original's)
    struct TileWork {
        bool m_on;
        unsigned int m_width;
        unsigned int m_height;
    };
    short m_idx;  // 0x0, update: 1 while DrMan::m_qualityMode is 0 (name inferred)
    TileWork m_work[2][9];  // 0x4, by m_idx and TileType
};
}  // namespace ml

#endif
