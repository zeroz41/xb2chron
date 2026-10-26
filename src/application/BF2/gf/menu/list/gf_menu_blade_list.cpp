#include "classes/gf/GfMenuBladeList.h"
#include "gf/GfMenuBdat.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfDataBlade.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/SDataBlade.h"
#include "plugin/Bdat.h"

namespace gf {

GfMenuBladeList::~GfMenuBladeList() {
    ;  // the original stores the table: its body had a statement the build compiles away
}

GfMenuBladeList* GfMenuBladeList::create() {
#line 101
    GfMenuBladeList* list = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuBladeList;
    list->addRef();
    return list;
}

void GfMenuBladeList::getBladeFromDriver(unsigned int driver, mm::mtl::FixedVector<unsigned short, 422>& list,
                                         bool keepInvalid) {
    DataParamAcc acc(3, driver, GimmickType(0));
    if (acc.isValid()) {
        unsigned int blade = acc.getBlade(-1, false);
        unsigned int slotMax = GfMenuObjUtil::getBladeSlotMax();
        if (GfMenuObjUtil::isValidBlade(blade)) {
            list.push_back(blade);
            for (unsigned int slot = 1; slot < slotMax; ++slot) {
                unsigned int id = GfMenuObjUtil::getBladeIDFromDriverSlot(
                    acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0, slot);
                if (keepInvalid || GfMenuObjUtil::isValidBlade(id)) {
                    list.push_back(id);
                }
            }
        }
    }
}

void GfMenuBladeList::sort(unsigned int type, bool descending) {
    if (getSize() == 0) {
        return;
    }
    std::function<bool(const MenuBladeInfo&, const MenuBladeInfo&)> compare;
    switch (type) {
    case 1:
        compare = descending ? sortTimeAscending : sortTimeDescending;
        break;
    case 2:
        compare = descending ? sortNameDescending : sortNameAscending;
        break;
    case 3:
        compare = descending ? sortRarityAscending : sortRarityDescending;
        break;
    case 4:
        compare = descending ? sortWeaponAscending : sortWeaponDescending;
        break;
    case 5:
        compare = descending ? sortAttrAscending : sortAttrDescending;
        break;
    case 6:
        compare = descending ? fn_710036DCE8 : fn_710036DDCC;
        break;
    case 11:
        compare = descending ? sortGenderDescending : sortGenderAscending;
        break;
    case 18:
        compare = fn_710036DF68;
        break;
    case 19:
        compare = fn_710036DFF0;
        break;
    case 22:
        compare = fn_710036E10C;
        break;
    case 23:
        compare = fn_710036E078;
        break;
    default:
        if (type > 100) {
            fn_710036E1A0(type - 100);
        }
        return;
    }
    UIListInfo< ::gf::MenuBladeInfo>::sort(compare);
}

bool GfMenuBladeList::sortTimeAscending(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned int keyA = GfDataBlade::getBornTime(a.m_blade);
    unsigned int keyB = GfDataBlade::getBornTime(b.m_blade);
    if (keyA == keyB) {
        return a.m_blade < b.m_blade;
    }
    return keyA < keyB;
}

bool GfMenuBladeList::sortTimeDescending(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned int keyA = GfDataBlade::getBornTime(a.m_blade);
    unsigned int keyB = GfDataBlade::getBornTime(b.m_blade);
    if (keyA == keyB) {
        return a.m_blade < b.m_blade;
    }
    return keyA > keyB;
}

bool GfMenuBladeList::sortNameDescending(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned int idA;
    unsigned int idB;
    unsigned char* fpA = GfMenuBdat::getBladeDataFP(a.m_blade, idA);
    unsigned char* fpB = GfMenuBdat::getBladeDataFP(b.m_blade, idB);
    const char* key = GfMenuBdat::getSortKeyName();
    unsigned int keyA;
    unsigned int keyB;
    if (idA != 0 && idB != 0 && fpB != nullptr && fpA != nullptr && key != nullptr) {
        keyA = (unsigned int)Bdat::getVal(fpA, key, idA);
        keyB = (unsigned int)Bdat::getVal(fpB, key, idB);
    } else {
        keyA = a.m_blade;
        keyB = b.m_blade;
    }
    if (keyA == keyB) {
        return a.m_blade < b.m_blade;
    }
    return keyA > keyB;
}

bool GfMenuBladeList::sortNameAscending(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned int idA;
    unsigned int idB;
    unsigned char* fpA = GfMenuBdat::getBladeDataFP(a.m_blade, idA);
    unsigned char* fpB = GfMenuBdat::getBladeDataFP(b.m_blade, idB);
    const char* key = GfMenuBdat::getSortKeyName();
    unsigned int keyA;
    unsigned int keyB;
    if (idA != 0 && idB != 0 && fpB != nullptr && fpA != nullptr && key != nullptr) {
        keyA = (unsigned int)Bdat::getVal(fpA, key, idA);
        keyB = (unsigned int)Bdat::getVal(fpB, key, idB);
    } else {
        keyA = a.m_blade;
        keyB = b.m_blade;
    }
    if (keyA == keyB) {
        return a.m_blade < b.m_blade;
    }
    return keyA < keyB;
}

bool GfMenuBladeList::sortRarityAscending(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned int rarityA = GfMenuObjUtil::getBladeRarity(a.m_blade);
    unsigned int rarityB = GfMenuObjUtil::getBladeRarity(b.m_blade);
    if (rarityA == rarityB) {
        unsigned int rankA = GfMenuObjUtil::getBladeRank(a.m_blade);
        unsigned int rankB = GfMenuObjUtil::getBladeRank(b.m_blade);
        if (rankA == rankB) {
            return a.m_blade < b.m_blade;
        }
        return rankA < rankB;
    }
    return rarityA < rarityB;
}

bool GfMenuBladeList::sortRarityDescending(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned int rarityA = GfMenuObjUtil::getBladeRarity(a.m_blade);
    unsigned int rarityB = GfMenuObjUtil::getBladeRarity(b.m_blade);
    if (rarityA == rarityB) {
        unsigned int rankA = GfMenuObjUtil::getBladeRank(a.m_blade);
        unsigned int rankB = GfMenuObjUtil::getBladeRank(b.m_blade);
        if (rankA == rankB) {
            return a.m_blade < b.m_blade;
        }
        return rankA > rankB;
    }
    return rarityA > rarityB;
}

bool GfMenuBladeList::sortWeaponAscending(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned char keyA = GfDataBlade::getSDataBlade(a.m_blade)->m_weaponType;
    unsigned char keyB = GfDataBlade::getSDataBlade(b.m_blade)->m_weaponType;
    if (keyA == keyB) {
        return a.m_blade < b.m_blade;
    }
    return keyA < keyB;
}

bool GfMenuBladeList::sortWeaponDescending(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned char keyA = GfDataBlade::getSDataBlade(a.m_blade)->m_weaponType;
    unsigned char keyB = GfDataBlade::getSDataBlade(b.m_blade)->m_weaponType;
    if (keyA == keyB) {
        return a.m_blade < b.m_blade;
    }
    return keyA > keyB;
}

bool GfMenuBladeList::sortAttrAscending(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned char keyA = GfDataBlade::getAttribute(a.m_blade);
    unsigned char keyB = GfDataBlade::getAttribute(b.m_blade);
    if (keyA == keyB) {
        return a.m_blade < b.m_blade;
    }
    return keyA < keyB;
}

bool GfMenuBladeList::sortAttrDescending(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned char keyA = GfDataBlade::getAttribute(a.m_blade);
    unsigned char keyB = GfDataBlade::getAttribute(b.m_blade);
    if (keyA == keyB) {
        return a.m_blade < b.m_blade;
    }
    return keyA > keyB;
}

// how the creator sorts order a blade's creator (m_creator 1-6; 6 for any other). Inlined in every user (no symbol):
// the name is inferred, not the original's.
static inline unsigned int getCreatorSortOrder(unsigned int creator) {
    switch (creator) {
    case 1:
        return 0;
    case 2:
        return 1;
    case 3:
        return 5;
    case 4:
        return 2;
    case 5:
        return 3;
    case 6:
        return 4;
    default:
        return 6;
    }
}

bool GfMenuBladeList::fn_710036DCE8(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned int orderA = getCreatorSortOrder(a.m_creator);
    unsigned int orderB = getCreatorSortOrder(b.m_creator);
    if (orderA == orderB) {
        unsigned char attrA = GfDataBlade::getAttribute(a.m_blade);
        unsigned char attrB = GfDataBlade::getAttribute(b.m_blade);
        if (attrA == attrB) {
            unsigned int rarityA = GfMenuObjUtil::getBladeRarity(a.m_blade);
            unsigned int rarityB = GfMenuObjUtil::getBladeRarity(b.m_blade);
            if (rarityA == rarityB) {
                unsigned int rankA = GfMenuObjUtil::getBladeRank(a.m_blade);
                unsigned int rankB = GfMenuObjUtil::getBladeRank(b.m_blade);
                if (rankA == rankB) {
                    return a.m_blade < b.m_blade;
                }
                return rankA > rankB;
            }
            return rarityA > rarityB;
        }
        return attrA < attrB;
    }
    return orderA < orderB;
}

bool GfMenuBladeList::fn_710036DDCC(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned int orderA = getCreatorSortOrder(a.m_creator);
    unsigned int orderB = getCreatorSortOrder(b.m_creator);
    if (orderA == orderB) {
        unsigned char attrA = GfDataBlade::getAttribute(a.m_blade);
        unsigned char attrB = GfDataBlade::getAttribute(b.m_blade);
        if (attrA == attrB) {
            unsigned int rarityA = GfMenuObjUtil::getBladeRarity(a.m_blade);
            unsigned int rarityB = GfMenuObjUtil::getBladeRarity(b.m_blade);
            if (rarityA == rarityB) {
                unsigned int rankA = GfMenuObjUtil::getBladeRank(a.m_blade);
                unsigned int rankB = GfMenuObjUtil::getBladeRank(b.m_blade);
                if (rankA == rankB) {
                    return a.m_blade < b.m_blade;
                }
                return rankA > rankB;
            }
            return rarityA > rarityB;
        }
        return attrA < attrB;
    }
    return orderA < orderB;
}


bool GfMenuBladeList::sortGenderDescending(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned char keyA = GfDataBlade::getSDataBlade(a.m_blade)->m_gender;
    unsigned char keyB = GfDataBlade::getSDataBlade(b.m_blade)->m_gender;
    if (keyA == keyB) {
        return a.m_blade < b.m_blade;
    }
    return keyA > keyB;
}

bool GfMenuBladeList::sortGenderAscending(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned char keyA = GfDataBlade::getSDataBlade(a.m_blade)->m_gender;
    unsigned char keyB = GfDataBlade::getSDataBlade(b.m_blade)->m_gender;
    if (keyA == keyB) {
        return a.m_blade < b.m_blade;
    }
    return keyA < keyB;
}



bool GfMenuBladeList::fn_710036DF68(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    bool activeA = GfDataBlade::isActivateMercenaryTeam(a.m_blade);
    bool activeB = GfDataBlade::isActivateMercenaryTeam(b.m_blade);
    if (activeA != activeB) {
        return activeA && !activeB;
    }
    unsigned int timeA = GfDataBlade::getBornTime(a.m_blade);
    unsigned int timeB = GfDataBlade::getBornTime(b.m_blade);
    if (timeA == timeB) {
        return a.m_blade < b.m_blade;
    }
    return timeA > timeB;
}

bool GfMenuBladeList::fn_710036DFF0(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    bool activeA = GfDataBlade::isActivateMercenaryTeam(a.m_blade);
    bool activeB = GfDataBlade::isActivateMercenaryTeam(b.m_blade);
    if (activeA != activeB) {
        return activeB && !activeA;
    }
    unsigned int timeA = GfDataBlade::getBornTime(a.m_blade);
    unsigned int timeB = GfDataBlade::getBornTime(b.m_blade);
    if (timeA == timeB) {
        return a.m_blade < b.m_blade;
    }
    return timeA > timeB;
}

bool GfMenuBladeList::fn_710036E078(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned int trustA = GfDataBlade::getTrustRank(a.m_blade);
    unsigned int trustB = GfDataBlade::getTrustRank(b.m_blade);
    if (trustA == trustB) {
        unsigned int rarityA = GfMenuObjUtil::getBladeRarity(a.m_blade);
        unsigned int rarityB = GfMenuObjUtil::getBladeRarity(b.m_blade);
        if (rarityA == rarityB) {
            unsigned int rankA = GfMenuObjUtil::getBladeRank(a.m_blade);
            unsigned int rankB = GfMenuObjUtil::getBladeRank(b.m_blade);
            if (rankA == rankB) {
                return a.m_blade < b.m_blade;
            }
            return rankA > rankB;
        }
        return rarityA > rarityB;
    }
    return trustA < trustB;
}

bool GfMenuBladeList::fn_710036E10C(const MenuBladeInfo& a, const MenuBladeInfo& b) {
    unsigned int trustA = GfDataBlade::getTrustRank(a.m_blade);
    unsigned int trustB = GfDataBlade::getTrustRank(b.m_blade);
    if (trustA == trustB) {
        unsigned int rarityA = GfMenuObjUtil::getBladeRarity(a.m_blade);
        unsigned int rarityB = GfMenuObjUtil::getBladeRarity(b.m_blade);
        if (rarityA == rarityB) {
            unsigned int rankA = GfMenuObjUtil::getBladeRank(a.m_blade);
            unsigned int rankB = GfMenuObjUtil::getBladeRank(b.m_blade);
            if (rankA == rankB) {
                return a.m_blade < b.m_blade;
            }
            return rankA > rankB;
        }
        return rarityA > rarityB;
    }
    return trustA > trustB;
}

void GfMenuBladeList::fn_710036E1A0(unsigned int skill) {
    unsigned int size = getSize();
    bool* hasSkill = new (getAllocator(ALLOCATOR(0)), nullptr, 0, 8) bool[size];
    for (unsigned int i = 0; i < getSize(); ++i) {
        DataParamAcc acc(4, getContents(i).m_blade, GimmickType(0));
        bool found = false;
        unsigned short level = 0;
        for (unsigned int slot = 0; slot < 3; ++slot) {
            if (acc.getFieldSkill(slot, false) == skill && acc.getFieldSkillLevel(slot, false) != 0) {
                level = acc.getFieldSkillLevel(slot, false);
                found = true;
            }
        }
        hasSkill[i] = found;
        getContents(i).m_index = i;
        getContents(i).m_skillLevel = level;
    }
    UIListInfo< ::gf::MenuBladeInfo>::sort([hasSkill](const MenuBladeInfo& a, const MenuBladeInfo& b) {
        if (hasSkill[a.m_index] != hasSkill[b.m_index]) {
            return hasSkill[a.m_index];
        }
        if (a.m_skillLevel == b.m_skillLevel) {
            unsigned int orderA = getCreatorSortOrder(a.m_creator);
            unsigned int orderB = getCreatorSortOrder(b.m_creator);
            if (orderA == orderB) {
                unsigned int rarityA = GfMenuObjUtil::getBladeRarity(a.m_blade);
                unsigned int rarityB = GfMenuObjUtil::getBladeRarity(b.m_blade);
                if (rarityA == rarityB) {
                    unsigned int rankA = GfMenuObjUtil::getBladeRank(a.m_blade);
                    unsigned int rankB = GfMenuObjUtil::getBladeRank(b.m_blade);
                    if (rankA == rankB) {
                        return a.m_blade < b.m_blade;
                    }
                    return rankA > rankB;
                }
                return rarityA > rarityB;
            }
            return orderA < orderB;
        }
        return a.m_skillLevel > b.m_skillLevel;
    });
    delete[] hasSkill;
}

void GfMenuBladeList::updateOwner() {
    for (unsigned int i = 0; i < getSize(); ++i) {
        MenuBladeInfo& info = getContents(i);
        info.m_creator = GfDataBlade::getCreator(info.m_blade);
    }
}

}  // namespace gf
