#ifndef LAYER_LAYERANIMEOBJ_H
#define LAYER_LAYERANIMEOBJ_H

namespace layer {
class LayerAnimeInfo;
class LayerResParmInfo;
// an object's animation (LayerObj holds three; baseRelease deletes them). Its members are LayerSortMan.cpp's; the
// layout is not known yet
class LayerAnimeObj {
public:
    ~LayerAnimeObj();
    void update(LayerResParmInfo& info, float frame);
    void calcParm(LayerResParmInfo& info, const LayerAnimeInfo& anime, float frame);
};
}  // namespace layer

#endif
