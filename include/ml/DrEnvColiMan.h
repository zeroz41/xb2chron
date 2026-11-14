#ifndef ML_DRENVCOLIMAN_H
#define ML_DRENVCOLIMAN_H

#include "ml/DrEnvColiObj.h"

namespace ml {
class DrMan;

// the environment collision of one view (DrEnvironmentMan's); ScnRenderDrEnvColi reads what a test hit
class DrEnvColiMan {
public:
    // a list of objects linked through m_prev/m_next (the names are not the original's)
    struct List {
        DrEnvColiObj* m_head;
        DrEnvColiObj* m_tail;
        // obj linked last
        void push_back(DrEnvColiObj* obj) {
            if (m_tail) {
                m_tail->m_next = obj;
                obj->m_prev = m_tail;
                m_tail = obj;
            } else {
                m_head = obj;
                m_tail = obj;
                obj->m_prev = nullptr;
            }
            obj->m_next = nullptr;
        }
        // obj unlinked
        void remove(DrEnvColiObj* obj) {
            if (obj->m_prev && obj->m_next) {
                obj->m_prev->m_next = obj->m_next;
                obj->m_next->m_prev = obj->m_prev;
            } else if (obj->m_prev) {
                m_tail = obj->m_prev;
                m_tail->m_next = nullptr;
            } else if (obj->m_next) {
                m_head = obj->m_next;
                m_head->m_prev = nullptr;
            } else {
                m_head = nullptr;
                m_tail = nullptr;
            }
            obj->m_prev = nullptr;
            obj->m_next = nullptr;
        }
        // deletes every object (and its work)
        void clear();
    };

    DrEnvColiMan(DrMan* drMan);
    ~DrEnvColiMan();
    void clear();
    DrEnvColiObj* createObj(const void* resource);
    void update();
    bool testEnvColi(DrEnvColiResult* result, const mm::Vec3& pos, float range);

    // field names are not the original's
    List m_list;            // 0x0, the live objects (testEnvColi walks them)
    List m_stock[2];        // 0x10, by DrMan::s_nDblStockIdx: createObj's new objects
    DrMan* m_drMan;         // 0x30
    DrEnvColiObj* m_hitObj; // 0x38, the object update's test hit last
    DrEnvColiResult m_result;  // 0x40, testEnvColi's when given none
    float m_time;           // 0x68, DrMan::m_hour (update copies it): times 1440 the minute of the day
    float m_rate;           // 0x6C
    float m_frame;          // 0x70, update counts it down by DrMan's frame time
    int m_weather;          // 0x74, DrPixlPostParm::m_weather at the last update
    float pad_78;           // 0x78
    int pad_7C;             // 0x7C
    int pad_80;             // 0x80
    float pad_84;           // 0x84, update sets 600 on a weather change and counts it down by DrMan's frame time
    float pad_88;           // 0x88, update: 0 on a weather change, then 1 / pad_84 clamped to [0, 1]
    int m_hitGroup;         // 0x8C, the last hit's EnvColiPostGroup index (update compares the new one with it)
};
}  // namespace ml

#endif
