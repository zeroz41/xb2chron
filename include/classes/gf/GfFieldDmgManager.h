#ifndef CLASSES_GF_GFFIELDDMGMANAGER_H
#define CLASSES_GF_GFFIELDDMGMANAGER_H

#include <string.h>
#include "classes/gf/GfEvent.h"
#include "classes/gf/IGfEvent.h"
#include "plugin/Bdat.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Vector.h"

class CBdatWrapper;
namespace gf { class GfFieldDmgManager; }
namespace gf { class GfSetupParam; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }

namespace gf {
// table 0x7100B514E8: the terrain damages of the current map (FLD_DmgFloor's rows, read as a map jump ends)
class GfFieldDmgManager : public ::mm::mtl::PtrSingleton< ::gf::GfFieldDmgManager>, public ::gf::IGfEvent {
public:
    // one terrain damage's row (12 bytes, found by id); the columns: Condition, attributeID, DMG_interval, Pc_dmg,
    // EN_dmg
    struct BdatInfo {
        BdatInfo() : m_condition(0), m_id(0), m_interval(0.0f), m_damage(0), m_enemyDamage(0) {}
        // reads row id of the table (inline here: 3.0.1 has no copy of it, 1.0.0 one out of line)
        void create(const CBdatWrapper& bdat, int id) {
            m_id = 0;
            m_condition = (unsigned short)(unsigned long)Bdat::getValCheck(bdat.m_fp, "Condition", id, 2);
            m_id = (unsigned short)(unsigned long)Bdat::getValCheck(bdat.m_fp, "attributeID", id, 2);
            unsigned int interval = (unsigned int)(unsigned long)Bdat::getValCheck(bdat.m_fp, "DMG_interval", id, 8);
            memcpy(&m_interval, &interval, sizeof(m_interval));  // a float column's bits
            m_damage = (unsigned char)(unsigned long)Bdat::getValCheck(bdat.m_fp, "Pc_dmg", id, 1);
            m_enemyDamage = (unsigned char)(unsigned long)Bdat::getValCheck(bdat.m_fp, "EN_dmg", id, 1);
        }

        unsigned short m_condition;
        unsigned short m_id;       // findBdatInfo's key
        float m_interval;          // how long between hits, in seconds
        unsigned char m_damage;    // what each hit deals a party member
        unsigned char m_enemyDamage;  // what each hit deals an enemy (GfFieldDmg::update's percent)
        unsigned char pad_a[0x2];
    };

    // inline here: 3.0.1 has no copy of it (build inlines it), 1.0.0 one out of line
    GfFieldDmgManager(const GfSetupParam* param) {
        GfEvent::addEventCallback(this);
        create(*param);
    }
    virtual ~GfFieldDmgManager();  // slot 0
    virtual void gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const& info);  // slot 2
    void create(const GfSetupParam& param);
    // inline here: 3.0.1 has no copy of it, 1.0.0 one out of line
    void dispose() {
        if (m_bdatInfos.size() != 0) {
            m_bdatInfos.destroy();
        }
    }
    static void build(const GfSetupParam& param);
    static void destroy();

    const BdatInfo* findBdatInfo(unsigned short id) const;

    mm::mtl::Vector<BdatInfo> m_bdatInfos;  // the current map's rows (the name is not the original's)
};
}  // namespace gf

#endif
