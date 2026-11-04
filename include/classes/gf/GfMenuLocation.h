#ifndef CLASSES_GF_GFMENULOCATION_H
#define CLASSES_GF_GFMENULOCATION_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfFieldLocator.h"
#include "classes/gf/GfFieldNpcLocator.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Vector.h"
#include "mm/Vec3.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfMenuLocation; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B5E910
// the menus' locators: five lists of field locators (0 and 1: the current quests' tasks, 3: the orderable quests,
// 4: m_locator's), each with its positions ordered by distance from the party leader
class GfMenuLocation : public ::mm::mtl::PtrSingleton< ::gf::GfMenuLocation> {
public:
    // one position of a list's locators and its distance (-1 on another map), what CompareOrder sorts by
    // (the field names are not the original's)
    struct OrderInfo {
        unsigned int m_index;     // the position's number over the list's locators
        unsigned int m_distance;  // whole units minus one, at least 0; -1 (last) on another map
    };
    struct CompareOrder {
        bool operator()(const OrderInfo& a, const OrderInfo& b) const {
            return a.m_distance < b.m_distance;
        }
    };
    // what getLocatorData fills (the field names are not the original's)
    struct LocatorData {
        mm::Vec3 m_pos;
        int m_id;          // 0x10: the GfFieldLocator's CreateInfoByQuest id
        int m_iconId;      // 0x14
        bool m_isOtherMap; // 0x18
        int m_mapId;       // 0x1C
        int m_distance;    // 0x20
    };
    // one of the five lists (0x438 bytes; the name and field names are not the original's)
    struct LocatorList {
        mm::mtl::Vector<GfFieldLocator> m_locators;
        unsigned int m_dataNum;   // 0x28: getLocatorDataNum: the positions updateDataNum counted
        unsigned int m_addedNum;  // 0x2C: how many of them updateLocator gave GfMenuObjCompass
        mm::mtl::FixedVector<OrderInfo, 128> m_orders;
    };

    // 3.0.1 has no out-of-line copy: build inlines it
    GfMenuLocation(const GfSetupParam&) : m_requestId(0), m_locator(nullptr), m_lists(), pad_1560(0) {}
    virtual ~GfMenuLocation();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    static bool isInitialized();
    static void postUpdate(const fw::UpdateInfo& info);
    // updates the menus' locators (GfMenuObjWorldMap::update calls it each frame)
    static void updateLocator();
    void updateDataNum(unsigned int kind);
    // GfMenuManager's quest events refresh locators 0, 1 and 3
    static void refreshLocator(unsigned int kind);
    void refreshLocatorFromQuest(unsigned int kind, unsigned int type);
    static unsigned int getLocatorDataNum(unsigned int kind);
    static bool getLocatorData(unsigned int kind, unsigned int index, LocatorData& data, unsigned int mapId, bool curMap);
    // 2.0.0's symbols name it. What it does: when the instance exists, stores value in m_requestId (GfMenuObjHitonowa's
    // setupGame, initialize and seqWaitNavi pass it).
    static void startNpcNavigate(unsigned int value);
    // 2.0.0's symbols name it. What it does: m_requestId, 0 without the instance (callers: fn_71003601DC,
    // GfMenuObjHitonowa's initialize, MainListener::reciveEvent and seqWaitNavi).
    static unsigned int getNpcNavigateID();
    // 2.0.0's symbols name it. What it does: when the instance exists, empties every list (locators, orders, both
    // counts). Caller: GfMenuManager::setupGame.
    static void reset();

    unsigned int m_requestId;  // 0x8: startNpcNavigate's value; postUpdate makes m_locator for it (the name is not the original's)
    GfFieldNpcLocator m_locator;     // 0x10: list 4's locator (the name is not the original's)
    bool m_initialized;        // 0x40: isInitialized; build sets it
    LocatorList m_lists[5];    // 0x48
    unsigned int pad_1560;     // 0x1560: the constructor and build zero it
};
}  // namespace gf

#endif
