#ifndef CLASSES_GF_LOCATORTALK_DUMMYGROUP_H
#define CLASSES_GF_LOCATORTALK_DUMMYGROUP_H

#include "classes/gf/AFieldLocator.h"
#include "mm/mtl/FixedVector.h"

namespace gf {
// table 0x7100B51BC8
class LocatorTalk_DummyGroup : public ::gf::AFieldLocator {
public:
    LocatorTalk_DummyGroup() : m_gmkSetId(0), m_npcId(0), m_groupId(0) {}
    virtual ~LocatorTalk_DummyGroup() {  // slot 0
        dispose();
    }
    virtual unsigned int getPosNum() const {  // slot 3
        return m_posList.size();
    }
    virtual const mm::Vec3* getPos(unsigned int index) const {  // slot 4
        return &m_posList[index];
    }
    virtual void update();  // slot 6
    void create(QuestID questId, unsigned short mapId, unsigned short npcId, unsigned short groupId);
    // the destructor's clearing; 1.0.0's symbols name it dispose() (3.0.1 inlines it)
    void dispose() {
        m_posList.clear();
        m_npcIds.clear();
        m_npcId = 0;
        m_gmkSetId = 0;
    }

    int m_gmkSetId;
    unsigned short m_npcId;
    unsigned short m_groupId;  // the dummy group's row ("NpcID1".."NpcID9")
    mm::mtl::FixedVector<unsigned short, 9> m_npcIds;
    mm::mtl::FixedVector<mm::Vec3, 9> m_posList;
};
}  // namespace gf

#endif
