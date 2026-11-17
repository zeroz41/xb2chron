#ifndef GF_GFOBJFACTORY_H
#define GF_GFOBJFACTORY_H

class CBdatWrapper;
namespace mm { class Vec3; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfInitParamDriver; class GfInitParamBlade; class GfInitParamEnemy; }
namespace gf { class GfInitParamMapSeamless; class GfInitParamGimmick; class GfInitParamNpc; class GfInitParamMob; }
namespace gf { class GfInitParamFobj; class GfInitParamWeapon; class GfInitParamEnWeapon; class GfInitParamBelonging; }
namespace gf { class GfInitParamExtra; class GfInitParamEventObj; class GfInitParamUiObj; }
namespace gf { class GfAppendHandles; class GfAppendInfo; }
namespace gf { class GfComSound; class GfExtendPacking; class GfObj; class GF_ASSET_HANDLE; }
namespace fw { struct ResSoundTriggerInfo; }
namespace gf { enum GfFileIdx : int; }
namespace anm { class Skeleton; }
namespace fw { class ForceCalculator; }
namespace mm { namespace mtl { template <typename T> class IntrusivePtr; } }

namespace gf {
// makes the game's objects (functions, by its symbols)
class GfObjFactory {
public:
    // the driver object param describes, -1 when none is made
    static GF_OBJ_HANDLE* createDriver(GfInitParamDriver& param);
    // the driver's weapon remade for the UI (false when handle is not a driver with appends)
    static bool createUiWeapon(GF_OBJ_HANDLE* handle, unsigned int id);
    static GF_OBJ_HANDLE* createBlade(GfInitParamBlade& param);
    static GF_OBJ_HANDLE* createMap(const GfInitParamMapSeamless& param);
    static GF_OBJ_HANDLE* createMapLodAnim();
    static GF_OBJ_HANDLE* createGmkMapObj(const CBdatWrapper& bdat, int row);
    static GF_OBJ_HANDLE* createMapObj(const GfInitParamGimmick& param);
    static GF_OBJ_HANDLE* createGmkTbox(const CBdatWrapper& bdat, int row);
    static GF_OBJ_HANDLE* createGmkTboxBattleChallenge(const CBdatWrapper& bdat, int row, int id);
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
    // the enemy blade's weapons (the parameter's own GfAppendHandles when the mount has none)
    static GfAppendHandles* createEnemyBladeWeapon(GfInitParamWeapon& param, unsigned int id, GF_OBJ_HANDLE* owner,
                                                   GF_OBJ_HANDLE* blade);
    static GF_OBJ_HANDLE* createEnWeapon(GfInitParamEnWeapon& param);
    static GF_OBJ_HANDLE* createBelonging(GfInitParamBelonging& param);
    static GF_OBJ_HANDLE* createExtraModel(GfInitParamExtra& param);
    static GF_OBJ_HANDLE* createEventObj(const GfInitParamEventObj& param);
    static GF_OBJ_HANDLE* createUiObj(const GfInitParamUiObj& param);
    static GF_OBJ_HANDLE* createDummyMover();
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
// Placeholder name (no symbol names it). Called by GfObjFactory::createDriver and rebuildAssetHandle (this unit)
// on the driver's init param before GfAssetFactory::createAssetPackDriver; it reads the driver's blades and their
// weapons (GfDataDriver::getIraBlade, DataParamAcc::getWeaponType, GfDataBlade::getAttribute).
void fn_7100525A2C(GfInitParamDriver& param);
// Placeholder name (no symbol names it). Called twice by GfObjFactory::createDriverWeapon (this unit), once per set of
// handles (m_useSecond and the append info's list set to 1, then 0): makes the weapons of info's current list into
// handles' current set.
void fn_710052A760(GfAppendHandles& handles, GfInitParamWeapon& param, GfAppendInfo& info);
// Placeholder name (no symbol names it). Called by GfObjFactory::createEnemyBladeWeapon (this unit) once per append,
// after it copied the append into param.pad_98: makes that weapon object and returns its handle.
GF_OBJ_HANDLE* fn_710052AD9C(GfInitParamWeapon& param, GF_OBJ_HANDLE* owner, GF_OBJ_HANDLE* blade);
// a GfComSound's trigger filter (its m_triggerFilter's signature): the jump states' sound triggers ("S_jump_02",
// "S_jumpdmg") play only while the ground under the object is above the water it is in (when it is in water
// and on ground); every other trigger plays
bool checkSoundTriggerPlayer(GfComSound* sound, const fw::ResSoundTriggerInfo& info);
// queues the sound triggers of every file of the asset's archive file into the packing's queue
void addExtendPackingSoundTrigger(GF_ASSET_HANDLE* asset, GfFileIdx file, GfExtendPacking* packing);
// a driver's or a blade's slope IK limits (pitch, roll) in radians from its character data; false for other objects
bool getSlopeIKLimit(GfObj* obj, float* pitch, float* roll);
// Placeholder name (no symbol names it). Called by GfObjFactory::createDriver and createUiWeapon (this unit) with the
// driver's init param and handle: the party blade's appends (GfAppendUtil::setupPartyBlade) in the Ira game or for
// creation types 1 and 7, the act viewer's (setupActViewer, the weapon found from the blade's weapon type) for an
// all-weapon param, then the extra model for types 1, 2, 3, 7 and 11 unless pad_1a2 is set.
void fn_71005260B8(GfInitParamDriver& param, GF_OBJ_HANDLE* handle);
// Placeholder name (no symbol names it). Called by GfObjFactory::createDriver (this unit): when the driver's data
// has a blade, mounts it (attach 0, option 1) if it has no mount and makes its equipped weapon (creation type 7,
// pad_40 12) through createDriverWeapon.
void fn_7100526BD8(GF_OBJ_HANDLE* handle);
// Placeholder name (no symbol names it). Called by GfObjFactory::createDriver (this unit): mounts the driver
// (attach 0, option 2) if it has no mount and, when its blade (m_bladeId, else the driver's data's) has an equipped
// weapon, makes it through createDriverWeapon.
void fn_7100527120(GfInitParamDriver& driver, GF_OBJ_HANDLE* handle);
// Placeholder name (no symbol names it). Called by GfObjFactory::loadedAsset (this unit): the skeleton of the
// asset's file 0x44 archive, read from its "<asset name without path and extension>.skl" file; none when the asset
// has no such resource or pack.
anm::Skeleton* fn_7100540BB4(GF_ASSET_HANDLE* asset);
// Placeholder name (no symbol names it). Called by fn_7100540CC4 and fn_71005418C4 (this unit): the skeleton of the
// asset's file resource, the named file of its archive when name is given and the data is an archive, else the
// resource's data itself; none when there is no resource or no such file.
anm::Skeleton* fn_710054113C(GF_ASSET_HANDLE* asset, GfFileIdx file, const char* name);
// Placeholder name (no symbol names it). Called by GfObjFactory::loadedAsset (this unit): the skeleton read from the
// "<pack's pad_258>.skl" file of the asset's file archive; none when there is no resource.
anm::Skeleton* fn_7100541780(GF_ASSET_HANDLE* asset, GfFileIdx file);
// Placeholder name (no symbol names it). Called by GfObjFactory::createComponent and fn_710053B178 (this unit): sets
// up the object's effect caster (component slot 7) with the object's asset and view, its layer, kind and value.
void fn_7100543DC8(GfObj* obj, unsigned int kind, float value);
// Placeholder name (no symbol names it). Called by GfObjFactory::createComponent and fn_710053B178 (this unit): sets
// up the object's transform (component slot 0) at pos, rotated by the half-angle quaternion of the angles rot.
void fn_7100541A00(GfObj* obj, const mm::Vec3& pos, const mm::Vec3& rot);
// Placeholder name (no symbol names it). Called by GfObjFactory::createComponent (this unit): sets up the object's
// dynamics (component slot 8) from the dynamics resource of the asset's file (the named file of its archive when
// name is given), level 6, or 30 when high is set.
void fn_7100543E68(GfObj* obj, GfFileIdx file, const char* name, bool high);
// Placeholder name (no symbol names it). Called by GfObjFactory::createComponent (this unit): for an object of type 3
// shows or hides its scenario parts by bdat id (Rex's crystal, Metsu's crystal, Laura's medal, fn_71005442A4).
void fn_7100543F98(GF_OBJ_HANDLE* handle);
// Placeholder name (no symbol names it). Called by fn_7100543F98 (this unit) for bdat id 0x14: sets up the object's
// extra parts (GfObjAcc::setupExtraParts), then shows or hides Metsu's crystal on an "np100201" model and the sin
// mask on an "np100101" or "pc700401" model.
void fn_71005442A4(GF_OBJ_HANDLE* handle);
// Placeholder name (no symbol names it). Called by GfObjFactory::createComponent: sets up the object's transform
// (component slot 0) at pos, rotated by the half-angle quaternion of the angles rot, with two frames per list and a
// child frame (fn_7100541A00's with other settings).
void fn_7100544354(GfObj* obj, const mm::Vec3& pos, const mm::Vec3& rot);
// Placeholder name (no symbol names it). Called by GfObjFactory::createComponent: sets up the object's dynamics
// (component slot 8) from the dynamics resource of the asset's file 0x3B (the named file of its archive when name is
// given), level 6, driven by force.
void fn_71005444A0(GfObj* obj, const char* name, mm::mtl::IntrusivePtr<fw::ForceCalculator> force);
// Placeholder name (no symbol names it). Called by GfObjFactory::createComponent: gives the object's collider
// (component slot 4) its character collision 0, a kind 3 shape of height and radius, at collision priority.
void fn_710054461C(GfObj* obj, unsigned int priority, float height, float radius);
// Placeholder name (no symbol names it). Called by GfObjFactory::createComponent: when the object's model component
// (slot 1) has a model, gives its IK component (slot 3) a blow-rotate solver on the object data's rotate bone.
void fn_710054473C(GfObj* obj);
// Placeholder name (no symbol names it). Called by GfObjFactory::loadedAsset (this unit): gives the asset a new
// GfExtendPacking (extend resource 0) and, when the skeleton of skeletonFile (fn_710054113C) and the first of the
// count archives of files exist, fills its state machine resource from the name file of that archive (resolved
// against the archives, bound to the skeleton and srcSkeleton); the packing, none when no state machine was made.
GfExtendPacking* fn_7100540CC4(GF_ASSET_HANDLE* asset, const char* name, GfFileIdx skeletonFile,
                               const char* skeletonName, unsigned int count, const GfFileIdx* files,
                               const anm::Skeleton* srcSkeleton);
// Placeholder name (no symbol names it). Called by GfObjFactory::createComponent and fn_710053B178 (this unit): sets
// up the object's model component (slot 1) from the asset's file, with the skeleton of skeletonFile (fn_710054113C)
// when it is not negative, the object's asset and view, flag (SetupInfo::pad_20) and scale; then the camera fade
// and the collide model clip of the object's flags 0x16 and 0x17.
void fn_71005418C4(GF_OBJ_HANDLE* handle, GfFileIdx file, GfFileIdx skeletonFile, const char* name, float scale,
                   bool flag);
// Placeholder name (no symbol names it). Called by GfObjFactory::destroyComponent (this unit): unmounts the object
// from its bone, cleans up its sound, effect caster, asm, model and transform components, then deletes its sound,
// property, model, transform, asm, effect caster and weapon behavior components (each only when its slot holds that
// kind).
void fn_710054056C(GF_OBJ_HANDLE* handle);
}  // namespace gf

#endif
