#ifndef ML_DRPIXLTILEPARM_H
#define ML_DRPIXLTILEPARM_H

namespace ml {
class DrPixlTileParm {
public:
    // the tile pass begin/end bracket (DrMdoCtlSeamAll::callRenderSeamAll passes 3); no value has a name yet
    enum TileType {};

    void begin(TileType type);
    void end(TileType type);
    ~DrPixlTileParm();
};
}  // namespace ml

#endif
