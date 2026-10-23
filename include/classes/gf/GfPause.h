#ifndef CLASSES_GF_GFPAUSE_H
#define CLASSES_GF_GFPAUSE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "mm/mtl/FixedList.h"
#include "classes/gf/GfInfo.h"

namespace gf { class GfSetupParam; }
namespace gf { class GfPause; }
namespace gf { class GfSetupParam; }

namespace gf {
// a pause request: not an object but its slot's index (6 bits) and a serial number above it
// (GfPause::createPauseHandle), -1 for none
struct GF_PAUSE_HANDLE;

// table 0x7100B59510 (0xE68 bytes, GfPause::build); the field names are not the original's
class GfPause : public ::mm::mtl::PtrSingleton< ::gf::GfPause> {
public:
    typedef ::mm::mtl::FixedList<GF_PAUSE_HANDLE*, 64> HandleList;

    GfPause(const GfSetupParam& param) : m_pauseBit(0), m_prevPauseBit(0), m_serial(0) {
        initialize(param);
    }
    virtual ~GfPause();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    static GF_PAUSE_HANDLE* reqPause(unsigned int kind);
    static void destroyHandle(GF_PAUSE_HANDLE* handle);
    static void update();
    static bool isPause(unsigned int kind);

    // (1.0.0's; 3.0.1 inlines them)
    void initialize(const GfSetupParam& param) { m_initialized = true; }
    void finalize() {
        while (m_handles.m_num_nodes > 0) {
            GfSleep(1);
        }
        m_pauseBit = 0;
        m_initialized = false;
    }
    GF_PAUSE_HANDLE* createPauseHandle(unsigned int kind) {
        unsigned int index = m_kinds.alloc();
        m_kinds[index] = kind;
        return createPauseHandleByIndex(index);
    }
    GF_PAUSE_HANDLE* createPauseHandleByIndex(unsigned int index) {
        unsigned int serial = m_serial++;
        if (serial >= 0x3FFFFFF) {
            serial = m_serial++;
        }
        return reinterpret_cast<GF_PAUSE_HANDLE*>(static_cast<unsigned long>((index & 0x3F) | (serial << 6)));
    }
    void destroyPauseHandle(GF_PAUSE_HANDLE* handle);
    // the kinds of every handle held or requested
    unsigned int getPauseBit() {
        unsigned int bit = 0;
        for (HandleList::iterator it = m_handles.begin(); it != m_handles.end(); ++it) {
            bit |= m_kinds[reinterpret_cast<unsigned long>(*it) & 0x3F];
        }
        for (HandleList::iterator it = m_requests.begin(); it != m_requests.end(); ++it) {
            bit |= m_kinds[reinterpret_cast<unsigned long>(*it) & 0x3F];
        }
        return bit;
    }

    ::ml::fixed_size_alloc_inside<unsigned int, 64> m_kinds;  // each handle's kind, by its index
    HandleList m_handles;  // the pauses in effect
    HandleList m_requests;  // reqPause's, in effect from the next update
    HandleList m_releases;  // destroyHandle's, released by the next update
    unsigned int m_pauseBit;  // isPause's: every kind in effect
    unsigned int m_prevPauseBit;  // the last update's, to tell the listeners what changed
    unsigned int m_serial;  // the next handle's serial number
    bool m_initialized;
};
}  // namespace gf

#endif
