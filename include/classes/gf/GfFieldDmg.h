#ifndef CLASSES_GF_GFFIELDDMG_H
#define CLASSES_GF_GFFIELDDMG_H

#include "classes/gf/GfFieldDmgManager.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B514C8: the terrain damage an object standing on a damaging collision takes (GfComBehaviorEnemy keeps
// one; the field names are not the original's)
class GfFieldDmg {
public:
    struct CreateInfo {
        bool m_applyDamage;  // whether update deals the damage itself (applyDamage)
    };
    // what update looks at each frame
    struct UpdateInfo {
        gf::GF_OBJ_HANDLE* m_handle;  // the object
        int m_damageId;               // the damage id of the collision it stands on (negative: none)
        float m_deltaTime;            // the frame's time, in seconds
    };

    GfFieldDmg(const CreateInfo* info);
    // inline: the original's copies follow the unit's last function
    virtual ~GfFieldDmg() {  // slot 0
        dispose();
    }
    void create(const CreateInfo& info);
    void dispose();
    void update(const UpdateInfo& info);
    // deals an object percent of its maximum hit points (never its last one): whether it had an object
    static bool applyDamage(gf::GF_OBJ_HANDLE* handle, unsigned char percent);
    // percent of the hit points, less the given ratio of that
    static unsigned int calculateDamage(unsigned int hp, unsigned char percent, float ratio);

    bool m_applyDamage;  // the create information's
    bool m_active;       // create sets it, dispose clears it
    const GfFieldDmgManager::BdatInfo* m_bdatInfo;  // the row of m_damageId (null: none)
    int m_damageId;      // the damage id m_bdatInfo is for (fw::COLI_INVALID_DAMAGE_ID: none)
    float m_time;        // the time spent on it since the last hit
    bool m_hit;          // update dealt a hit this frame
};
}  // namespace gf

#endif
