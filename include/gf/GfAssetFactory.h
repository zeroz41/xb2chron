#ifndef GF_GFASSETFACTORY_H
#define GF_GFASSETFACTORY_H

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfInitParamDriver; }
namespace gf { class GfInitParamBlade; }
namespace gf { class GfInitParamMapSeamless; }
namespace gf { class GfInitParamEnemy; }
namespace gf { class GfInitParamNpc; }
namespace gf { class GfInitParamMob; }
namespace gf { class GfInitParamGimmick; }
namespace gf { class GfInitParamFobj; }
namespace gf { class GfInitParamWeapon; }
namespace gf { class GfInitParamEnWeapon; }
namespace gf { class GfInitParamBelonging; }
namespace gf { class GfInitParamExtra; }
namespace gf { class GfInitParamEventObj; }
namespace gf { class GfInitParamUiObj; }

namespace gf {
// no table: makes an object's asset handle with the setup its kind (and what it is made for) needs; the setup a
// parameter carries replaces the factory's own
class GfAssetFactory {
public:
    static GF_ASSET_HANDLE* createAssetPackDriver(const GfInitParamDriver& param);
    static GF_ASSET_HANDLE* createAssetPackDriverForEvent(const GfInitParamDriver& param);
    static GF_ASSET_HANDLE* createAssetPackDriverForSalvage(const GfInitParamDriver& param);
    static GF_ASSET_HANDLE* createAssetPackDriverForUi(const GfInitParamDriver& param);
    static GF_ASSET_HANDLE* createAssetPackBlade(const GfInitParamBlade& param);
    static GF_ASSET_HANDLE* createAssetPackBladeForEvent(const GfInitParamBlade& param);
    static GF_ASSET_HANDLE* createAssetPackBladeForUi(const GfInitParamBlade& param);
    static GF_ASSET_HANDLE* createAssetPackMap(const GfInitParamMapSeamless& param);
    static GF_ASSET_HANDLE* createAssetPackEnemy(const GfInitParamEnemy& param);
    static GF_ASSET_HANDLE* createAssetPackEnemyForEvent(const GfInitParamEnemy& param);
    static GF_ASSET_HANDLE* createAssetPackNpc(const GfInitParamNpc& param);
    static GF_ASSET_HANDLE* createAssetPackNpcForEvent(const GfInitParamNpc& param);
    static GF_ASSET_HANDLE* createAssetPackMob(const GfInitParamMob& param);
    static GF_ASSET_HANDLE* createAssetPackMobForEvent(const GfInitParamMob& param);
    static GF_ASSET_HANDLE* createAssetPackGimmick(const GfInitParamGimmick& param);
    static GF_ASSET_HANDLE* createAssetPackFobj(const GfInitParamFobj& param);
    static GF_ASSET_HANDLE* createAssetPackWeapon(const GfInitParamWeapon& param);
    static GF_ASSET_HANDLE* createAssetPackWeaponForEventCS(const GfInitParamWeapon& param);
    static GF_ASSET_HANDLE* createAssetPackEnWeapon(const GfInitParamEnWeapon& param);
    static GF_ASSET_HANDLE* createAssetPackBelonging(const GfInitParamBelonging& param);
    static GF_ASSET_HANDLE* createAssetPackExtra(const GfInitParamExtra& param);
    static GF_ASSET_HANDLE* createAssetPackEventObj(const GfInitParamEventObj& param);
    static GF_ASSET_HANDLE* createAssetPackUiObj(const GfInitParamUiObj& param);
};
}  // namespace gf

#endif
