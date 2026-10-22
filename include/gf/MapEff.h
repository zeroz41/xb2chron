#ifndef GF_MAPEFF_H
#define GF_MAPEFF_H

namespace fw { class ColiObject; }
namespace fw { class EffectPack; }
namespace fw { class ModelObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_ASSET_HANDLE; }
namespace ml { class ScnObj; }
namespace ml { class ScnObjIBL; }
namespace mm { class Vec3; }

namespace gf {
// the parts of a map made from its asset's files (no tables; the field names are not the original's)

// its effects (file 6): an effect pack, and the effect LOD manager set up for the map's model
class MapEff {
public:
    ~MapEff();
    void create(GF_ASSET_HANDLE* handle, fw::ModelObject* model);
    void destroy();
    void destroyEffefct();
    void update(const fw::UpdateInfo& info);

    bool m_lodInit;          // create set up the effect LOD manager; destroyEffefct terms it
    fw::EffectPack* m_pack;  // file 6's pack, counted
};

// its navigation mesh (file 2), handed to the navigation manager
class MapNavi {
public:
    ~MapNavi();
    void create(GF_ASSET_HANDLE* handle);
    void destroy();

    bool m_created;  // fw::NaviManager::createNaviMesh's answer
};

// its ground collision (file 1)
class MapColi {
public:
    ~MapColi();
    void create(GF_ASSET_HANDLE* handle);
    void destroy();

    fw::ColiObject* m_coli;  // counted
};

// its global image-based light (file 7), in the setup parameters' scene
class MapGIBL {
public:
    ~MapGIBL();
    void create(GF_ASSET_HANDLE* handle);
    void destroy();
    void setReferencePos(const mm::Vec3& pos);

    ml::ScnObjIBL* m_ibl;
};

// its local lights (file 8), in the setup parameters' scene
class MapLIBL {
public:
    ~MapLIBL();
    void create(GF_ASSET_HANDLE* handle);
    void destroy();

    ml::ScnObj* m_lgt;
};
}  // namespace gf

#endif
