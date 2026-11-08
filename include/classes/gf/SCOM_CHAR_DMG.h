#ifndef CLASSES_GF_SCOM_CHAR_DMG_H
#define CLASSES_GF_SCOM_CHAR_DMG_H

namespace gf {
class GF_OBJ_HANDLE;
class MsgObjectNotifyDamage;
// only the static create is known (no table in the symbols): it queues no request but hands an object's damage to
// the scene, the achievement stats and the ordered quests that reduce the object's HP
class SCOM_CHAR_DMG {
public:
    static void create(GF_OBJ_HANDLE* handle, const MsgObjectNotifyDamage& msg);
};
}  // namespace gf

#endif
