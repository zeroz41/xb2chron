#ifndef ML_DRGLOBALIBLMAN_H
#define ML_DRGLOBALIBLMAN_H
#include "classes/ml/DrGlobalIBLPack.h"
namespace ml {
class DrMan;
// a view's global IBL manager (DrMan::m_iblMan): ScnObjIBLDr and DrMdoCtlSeamAll make their packs with it
class DrGlobalIBLMan {
public:
    // a list of packs linked through m_prev/m_next (the names are not the original's)
    struct List {
        DrGlobalIBLPack* m_head;
        DrGlobalIBLPack* m_tail;
        // deletes every pack
        void clear() {
            for (DrGlobalIBLPack* pack = m_head; pack;) {
                DrGlobalIBLPack* next = pack->m_next;
                delete pack;
                pack = next;
            }
            m_head = nullptr;
            m_tail = nullptr;
        }
        // pack linked last
        void push_back(DrGlobalIBLPack* pack) {
            if (m_tail) {
                m_tail->m_next = pack;
                pack->m_prev = m_tail;
                m_tail = pack;
            } else {
                m_head = pack;
                m_tail = pack;
                pack->m_prev = nullptr;
            }
            pack->m_next = nullptr;
        }
        // pack unlinked
        void remove(DrGlobalIBLPack* pack) {
            if (pack->m_prev && pack->m_next) {
                pack->m_prev->m_next = pack->m_next;
                pack->m_next->m_prev = pack->m_prev;
            } else if (pack->m_prev) {
                m_tail = pack->m_prev;
                m_tail->m_next = nullptr;
            } else if (pack->m_next) {
                m_head = pack->m_next;
                m_head->m_prev = nullptr;
            } else {
                m_head = nullptr;
                m_tail = nullptr;
            }
            pack->m_prev = nullptr;
            pack->m_next = nullptr;
        }
    };

    DrGlobalIBLMan(DrMan* drMan, int view);
    ~DrGlobalIBLMan();
    void update();
    DrGlobalIBLPack* createObj(const void* resource);
    // marks the pack for release (DrGlobalIBLPack::FLAG_RELEASE shifted by DrMan::s_nDblStockIdx)
    void releaseObj(DrGlobalIBLPack* pack);

    // the field names are not the original's
    DrMan* m_drMan;         // 0x0
    int m_view;             // 0x8
    List m_stock[2];        // 0x10, by DrMan::s_nDblStockIdx
    List m_list;            // 0x30
    List m_release;         // 0x40
};
}  // namespace ml
#endif
