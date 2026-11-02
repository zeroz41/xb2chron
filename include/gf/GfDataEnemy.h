#ifndef GF_GFDATAENEMY_H
#define GF_GFDATAENEMY_H

namespace gf { class SDataEnemy; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}
namespace mm { namespace mtl { template <int> class FixStr; }}

namespace gf {
// the enemies' data, by their row ids (functions, by its symbols)
class GfDataEnemy {
public:
    static const char* getName(unsigned int arrange);
    // the message table and row of the enemy's name
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int arrange);
    static const char* getVoiceStr(unsigned int arrange);
    static const char* getResourceNameModel(unsigned int arrange);  // its resource row's model name, nullptr for none
    static unsigned int getEquipBlade(unsigned int arrange);  // the enemy's blade, 0 for none
    static unsigned int getWeaponType(unsigned int arrange);  // its blade's weapon type, 0 for none
    // the driver enemy's added animation "<model>_<index>" (two digits); false when the enemy has no data
    static bool getDriverAddAnim(mm::mtl::FixStr<128>& name, unsigned int arrange, unsigned int index);
    // the same name in name and the model's in model
    static bool getDriverEffect(mm::mtl::FixStr<128>& model, mm::mtl::FixStr<128>& name, unsigned int arrange,
                                unsigned int index);
    static bool getExtraParts(unsigned int rsc, unsigned int part);
    static void setupSDataEnemy(SDataEnemy& data, unsigned int arrange, unsigned int arg);
    // the enemy's game parameters set up again for another level (GfGameUtil::levelupForEnemy)
    static void setupGameParamForLevel(SDataEnemy& data, unsigned int level);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies among
    // GfDataEnemy's functions and, like getExtraParts, it takes an enemy's GfBdatRsc row. What it does: true when
    // GfBdatRsc::getRscEnExtraParts(rsc, part) is 2. DataObjEnemy's new table slot 42 returns it for its part.
    static bool fn_7100235424(unsigned int rsc, unsigned int part);
    static const char* getSePack(unsigned int arrange);
    // the BTL_Enhance rows of the enemy's blade's valid enhances (DataObjEnemy's stat helper reads them)
    static void getValidEnhance(mm::mtl::FixedVector<unsigned short, 64>& enhances, unsigned int arrange);
    static unsigned int getBladeID(unsigned int arrange);
    static unsigned int getEquipBladeEnArrangeID(unsigned int arrange);
    static bool isNamed(unsigned int arrange);
    static bool isBoss(unsigned int arrange);
    static unsigned int getSavedHpType(unsigned int arrange);
    static const char* getAddMotionName(unsigned int rsc);  // null for none or empty
    static unsigned int getSavedHp(unsigned int type);  // SDataGame::m_enemySavedHp[type - 4]
    static void setSavedHp(unsigned int type, unsigned int hp);  // SDataGame::m_enemySavedHp[type - 1]
    static const char* getLoopEffect(unsigned int rsc);  // null for none or empty
    static unsigned int getRscIdByArrangeId(unsigned int arrange);  // the arrangement's param's GfBdatRsc row, 0 for none
};
}  // namespace gf

#endif
