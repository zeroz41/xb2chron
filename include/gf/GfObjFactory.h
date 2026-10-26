#ifndef GF_GFOBJFACTORY_H
#define GF_GFOBJFACTORY_H

class CBdatWrapper;
namespace mm { class Vec3; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfInitParamDriver; class GfInitParamBlade; class GfInitParamEnemy; }
namespace gf { class GfInitParamMapSeamless; class GfInitParamGimmick; class GfInitParamNpc; class GfInitParamMob; }
namespace gf { class GfInitParamFobj; class GfInitParamWeapon; class GfInitParamEnWeapon; class GfInitParamBelonging; }
namespace gf { class GfInitParamExtra; class GfInitParamEventObj; class GfInitParamUiObj; }

namespace gf {
// makes the game's objects (functions, by its symbols)
class GfObjFactory {
public:
    // the driver object param describes, -1 when none is made
    static GF_OBJ_HANDLE* createDriver(GfInitParamDriver& param);
    static GF_OBJ_HANDLE* createUiWeapon(GF_OBJ_HANDLE* handle, unsigned int id);
    static GF_OBJ_HANDLE* createBlade(GfInitParamBlade& param);
    static GF_OBJ_HANDLE* createMap(const GfInitParamMapSeamless& param);
    static GF_OBJ_HANDLE* createMapLodAnim();
    static GF_OBJ_HANDLE* createGmkMapObj(const CBdatWrapper& bdat, int row);
    static GF_OBJ_HANDLE* createMapObj(const GfInitParamGimmick& param);
    static GF_OBJ_HANDLE* createGmkTbox(const CBdatWrapper& bdat, int row);
    static GF_OBJ_HANDLE* createGmkNpc(const CBdatWrapper& bdat, int row);
    static GF_OBJ_HANDLE* createNpc(const GfInitParamNpc& param);
    static GF_OBJ_HANDLE* createGmkMob(int id, unsigned short a, unsigned short b, unsigned short c, unsigned short d);
    static GF_OBJ_HANDLE* createMob(const GfInitParamMob& param);
    static GF_OBJ_HANDLE* createMobNull();
    static GF_OBJ_HANDLE* createGmkEnemy(int id, signed char a, unsigned short b, const mm::Vec3& pos,
                                         const mm::Vec3& rot, bool flag);
    static GF_OBJ_HANDLE* createEnemy(GfInitParamEnemy& param);
    static GF_OBJ_HANDLE* createSmnEnemy(int id, const mm::Vec3& pos, const mm::Vec3& rot, bool flag);
    static GF_OBJ_HANDLE* createGmkEvent(const CBdatWrapper& bdat, int row);
    static GF_OBJ_HANDLE* createGmkCollection(const CBdatWrapper& bdat, int row);
    static GF_OBJ_HANDLE* createGmkMapGimmick(const CBdatWrapper& bdat, int row);
    static GF_OBJ_HANDLE* createGmkBlade(const CBdatWrapper& bdat, int row, int index);
    static GF_OBJ_HANDLE* createFieldObj(const GfInitParamFobj& param);
    static GF_OBJ_HANDLE* createDriverWeapon(GfInitParamWeapon& param);
    static GF_OBJ_HANDLE* createEnemyBladeWeapon(GfInitParamWeapon& param, unsigned int id, GF_OBJ_HANDLE* owner,
                                                 GF_OBJ_HANDLE* blade);
    static GF_OBJ_HANDLE* createEnWeapon(GfInitParamEnWeapon& param);
    static GF_OBJ_HANDLE* createBelonging(GfInitParamBelonging& param);
    static GF_OBJ_HANDLE* createExtraModel(GfInitParamExtra& param);
    static GF_OBJ_HANDLE* createEventObj(const GfInitParamEventObj& param);
    static GF_OBJ_HANDLE* createUiObj(const GfInitParamUiObj& param);
    static void loadedAsset(GF_OBJ_HANDLE* handle);
    static void createComponent(GF_OBJ_HANDLE* handle);
    static void destroyComponent(GF_OBJ_HANDLE* handle);
    static bool destroyObjHandle(GF_OBJ_HANDLE* handle);
    static void rebuildAssetHandle(GF_OBJ_HANDLE* handle);
    static void destroyObj(GF_OBJ_HANDLE* handle);
};
}  // namespace gf

#endif
