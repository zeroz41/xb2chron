#ifndef CLASSES_GF_GFMENUSCRIPTMANAGER_H
#define CLASSES_GF_GFMENUSCRIPTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedQueue.h"
#include "mm/mtl/FixedVector.h"
#include "ui/EventData.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfMenuScriptManager; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B5EFC8: the scripts the menus run, each tied to a UI object whose events it queues
class GfMenuScriptManager : public ::mm::mtl::PtrSingleton< ::gf::GfMenuScriptManager> {
public:
    class ScriptListener;
    // a running script (1.0.0's regist(name, handle, id) fills one; the names are not the original's)
    struct Script {
        unsigned int m_scriptHandle;  // a free slot's handle: regist loads and starts the script under it
        mm::mtl::FixStr<64> m_name;   // the script's name
        unsigned int m_id;            // what the menu knows it by: getHandle looks it up
        unsigned int m_handle;        // its UI object's handle (regist registers the listener on it)
        int m_ctrlId;                 // setCtrlId's, -1 from regist
        unsigned char pad_54[4];
        ui::EventData m_event;  // the last event checkEvent took off the queue
        mm::mtl::FixedQueue<ui::EventData, 16> m_events;  // the UI object's events ScriptListener queues
    };
    // a script handle and whether a script holds it (1.0.0's getEmptySlot and freeSlot; the names are not the
    // original's)
    struct Slot {
        unsigned int m_handle;
        bool m_used;
    };

    GfMenuScriptManager(const GfSetupParam& param) : m_initialized(false), m_listener(nullptr) {
        initialize(param);
    }
    virtual ~GfMenuScriptManager();  // slot 0
    // inline in 3.0.1 (1.0.0 has both out of line)
    void initialize(const GfSetupParam& param);
    void finalize();
    static void build(const GfSetupParam& param);
    static void destroy();
    static bool isInitialized();
    void postUpdate(const fw::UpdateInfo& info);
    // the name of the script MNU_ScriptList gives the UI object (1.0.0's; 3.0.1's linker dropped it)
    static const char* getScriptName(unsigned int handle);
    static unsigned int getHandle(unsigned int id);
    static bool checkEvent(unsigned int handle);
    static bool getEventData(unsigned int handle, ui::EventData& event);
    static int getCtrlId(unsigned int handle);
    static void setCtrlId(unsigned int handle, int ctrlId);

    bool m_initialized;  // initialize sets it, finalize clears it
    mm::mtl::FixedVector<Script, 32> m_scripts;
    Slot m_slots[32];  // handles 4 to 35
    ScriptListener* m_listener;  // referenced: initialize makes it, finalize releases it
};
}  // namespace gf

#endif
