#ifndef CLASSES_GF_SCOM_ACHIEV_INC_H
#define CLASSES_GF_SCOM_ACHIEV_INC_H

#include "classes/gf/SCOM.h"
#include "mm/mtl/FixedVector.h"

namespace fw { class UpdateInfo; }

namespace gf {
class GF_OBJ_HANDLE;
// table 0x7100B6AA60
class SCOM_ACHIEV_INC : public ::gf::SCOM {
public:
    // inline: every create function builds its request in place; each type-0x22 request counts once more
    SCOM_ACHIEV_INC(unsigned int type, int value) : SCOM(SCOM_TYPE(0x37)), m_value(type), m_value2(value) {
        if (type == 0x22) {
            ++s_countSalvageShop;
        }
    }
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // queues a request that adds value to achievement counter type (type 0x22 also counts salvage-shop requests)
    static unsigned long create(unsigned int type, int value, unsigned int);
    // the same for every blade in the party (GfDataBlade::getListPartyAll)
    static unsigned long createParty(unsigned int type, int value);
    static void addTotalCount(unsigned int type, unsigned int value);
    static void createCrystal();
    // placeholders (callers: one dispatch at 0x710000FDEC): fn_7100564360 counts type-1 once, then type for every
    // blade fn_7100563BB4 lists for the handle; the wrappers pass a fixed type and value 1
    static void fn_7100563BB4(mm::mtl::FixedVector<unsigned short, 422>&, GF_OBJ_HANDLE*, bool);
    static void fn_7100564354(GF_OBJ_HANDLE*);
    static void fn_7100564360(GF_OBJ_HANDLE*, unsigned int, unsigned int);
    static void fn_71005645DC(GF_OBJ_HANDLE*);
    static void fn_71005645E8(GF_OBJ_HANDLE*);
    static void fn_71005645F0(GF_OBJ_HANDLE*, unsigned int);
    static void fn_7100564920(GF_OBJ_HANDLE*);
    static void fn_7100564ACC();
    static void fn_7100564AE8(GF_OBJ_HANDLE*);
    static void fn_7100564AF4();
    static void fn_7100564B10(GF_OBJ_HANDLE*);
    static void fn_7100564B1C(GF_OBJ_HANDLE*);
    static void fn_7100564C9C(GF_OBJ_HANDLE*, unsigned int);

    // type-0x22 requests not yet counted: exec adds them as one (GfAchievManager::incAchiev(0x22, 1))
    static unsigned int s_countSalvageShop;

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_value;
    int m_value2;
    unsigned char pad_24[0x4];
    // the blades the count applies to (exec passes them to GfAchievManager::incAchievWithBlade when there are any)
    mm::mtl::FixedVector<unsigned short, 422> m_blades;
};
}  // namespace gf

#endif
