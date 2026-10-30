#ifndef GF_GFOBJFACTORY_H
#define GF_GFOBJFACTORY_H

class CBdatWrapper;
namespace mm { class Vec3; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfInitParamDriver; class GfInitParamBlade; class GfInitParamEnemy; }
namespace gf { class GfInitParamMapSeamless; class GfInitParamGimmick; class GfInitParamNpc; class GfInitParamMob; }
namespace gf { class GfInitParamFobj; class GfInitParamWeapon; class GfInitParamEnWeapon; class GfInitParamBelonging; }
namespace gf { class GfInitParamExtra; class GfInitParamEventObj; class GfInitParamUiObj; }
namespace gf { class GfAppendHandles; }

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
    // the weapons it made for the driver (GfEvtModelWeapon's constructor copies them into its own GfAppendHandles)
    static GfAppendHandles* createDriverWeapon(GfInitParamWeapon& param);
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

// Placeholder name: 1.0.0 leaves it unnamed too (fn_7100587AF8, a file static there). A free function of the module
// because only GfObjFactory::createNpc and createMob (this unit) call it. What it does: GfAppendUtil::setupBelonging
// (handle, a, b, c, d) when b is not 0; when the object's attach-2 append list is not empty, mounts it
// (GfMountManager::createMount, attach 2, option 2) and creates one belonging per append of that list
// (createBelonging with a GfInitParamBelonging: owner handle, the append's resource id and model, a..d), keeping
// each in the mount's append handles. Callers pass their parameter's four belonging values.
void fn_7100528684(GF_OBJ_HANDLE* handle, unsigned int a, unsigned int b, unsigned int c, unsigned int d);
}  // namespace gf

#endif
