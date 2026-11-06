#ifndef CLASSES_EVENT_RESPACKMANAGER_H
#define CLASSES_EVENT_RESPACKMANAGER_H

#include "mm/mtl/FixedVector.h"

#include "classes/event/ResPack.h"

namespace event {
// table 0x7100B3C078
class ResPackManager {
public:
    // inline: CharaObj's ResManager destructor carries it (0x710014C364, 0x710014C384)
    virtual ~ResPackManager() {}  // slot 0

    // the packs: 1.0.0's draw() (0x7100098290) calls ResPack::draw on each of the m_size @0x88 entries @0x8
    // 1.0.0's clear, update and isLoading (0x71000980DC, 0x71000981C8, 0x7100098440; 3.0.1 inlines them:
    // ResManager::clear, ResManager::update)
    void clear() {
        for (ResPack** it = m_packs.begin(); it != m_packs.end(); ++it) {
            ResPack* pack = *it;
            pack->clear();
            delete pack;
        }
        m_packs.clear();
    }
    void update() {
        for (unsigned long i = 0; i < m_packs.size(); i++) {
            (*m_packs.at(i))->update();
        }
    }
    // 1.0.0's draw (0x7100098290; 3.0.1 inlines it: ResManager::render)
    void draw() {
        for (unsigned long i = 0; i < m_packs.size(); i++) {
            (*m_packs.at(i))->draw();
        }
    }
    bool isLoading() const {
        for (unsigned long i = 0; i < m_packs.size(); i++) {
            if ((*m_packs.at(i))->m_func) {
                return true;
            }
        }
        return false;
    }
    // out of line (ResManager::loadPack calls it)
    void load(mtl::ALLOC_HANDLE handle, const char* name, IResPackEvent* event);
    mm::mtl::FixedVector<ResPack*, 16> m_packs;  // the name is not the original's
};
}  // namespace event

#endif
