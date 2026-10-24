#ifndef CLASSES_EVENT_RESPACKMANAGER_H
#define CLASSES_EVENT_RESPACKMANAGER_H

#include "mm/mtl/FixedVector.h"

namespace event { class ResPack; }

namespace event {
// table 0x7100B3C078
class ResPackManager {
public:
    // inline: CharaObj's ResManager destructor carries it (0x710014C364, 0x710014C384)
    virtual ~ResPackManager() {}  // slot 0

    // the packs: 1.0.0's draw() (0x7100098290) calls ResPack::draw on each of the m_size @0x88 entries @0x8
    mm::mtl::FixedVector<ResPack*, 16> m_packs;  // the name is not the original's
};
}  // namespace event

#endif
