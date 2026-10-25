#ifndef GF_GFGAMEUTILCLOUDSEA_H
#define GF_GFGAMEUTILCLOUDSEA_H

namespace gf { enum CLOUD_SEA : int; }

namespace gf {
// the cloud sea's helpers (functions, by its symbols)
class GfGameUtilCloudSea {
public:
    static bool isEnableChangeInn();  // the current map has an inn condition and it holds
    static int getCloudSea();
    static void setInnCloudSea(CLOUD_SEA cloudSea);  // the inn's cloud sea, for the current map  // the cloud sea's level: GfMenuGameAdapter::update_CloudIcon shows whether it is 0
};
}  // namespace gf

#endif
