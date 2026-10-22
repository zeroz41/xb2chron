#ifndef CLASSES_GF_GFREQMANAGER_H
#define CLASSES_GF_GFREQMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/UpdateInfo.h"
#include "mm/mtl/FixedQueue.h"

namespace gf { class GfReqManager; }
namespace gf { class GfSetupParam; }
namespace gf { class GfReqParam; }
namespace gf { class GfReqSmallCom; }
namespace ml { class MLTHG; }
namespace ml { class MLTH; }
namespace nn { namespace os { class FiberType; }}

namespace gf {
// table 0x7100B6A8A8: the requests (gf::GfReqCommand's), run one at a time on a micro-thread of their own
class GfReqManager : public ::mm::mtl::PtrSingleton< ::gf::GfReqManager> {
public:
    // a queued request: its data (deleted once it ran) and the function that runs it; the names are not the original's
    struct Command {
        GfReqParam* m_param;
        void (*m_func)(const GfReqParam*);
        unsigned int m_handle;  // what addCommand returned for it (isValid looks for it)
    };
    typedef mm::mtl::FixedQueue<Command, 256> CommandQueue;

    GfReqManager(const GfSetupParam& param);
    virtual ~GfReqManager();  // slot 0
    // out of line in 1.0.0; the constructor inlines it in 3.0.1 (defined inline in the unit: it cites the unit)
    inline void initialize(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    // out of line in 1.0.0; 3.0.1 keeps no copy
    static bool isInitialized() {
        GfReqManager* manager = get();
        if (manager != nullptr) {
            return manager->m_initialized;
        }
        return false;
    }
    static nn::os::FiberType* fnReqUpdate(void* arg);
    void update(const fw::UpdateInfo& info);
    void reqUpdate();
    static unsigned int addCommand(GfReqParam* param, void (*func)(const GfReqParam*));
    // out of line in 1.0.0; 3.0.1 keeps no copy. The next handle, never -1
    unsigned int getHandle() {
        m_handle++;
        if (m_handle == static_cast<unsigned int>(-1)) {
            m_handle = 0;
        }
        return m_handle;
    }
    static void terminateCommand();
    static bool isExistCommand(void (*func)(const GfReqParam*));
    static const fw::UpdateInfo& getUpdateInfo();
    static bool isValid(unsigned int handle);

    fw::UpdateInfo m_updateInfo;  // update's, for the requests (getUpdateInfo)
    ml::MLTHG* m_group;           // -1 when there is none (finalize releases it)
    ml::MLTH* m_thread;           // -1 once fnReqUpdate is done
    CommandQueue m_commands;
    GfReqSmallCom* m_smallCom;
    bool m_terminate;  // terminateCommand sets it: addCommand takes no more
    unsigned int m_handle;  // the last handle given (getHandle)
    bool m_initialized;
};
}  // namespace gf

#endif
