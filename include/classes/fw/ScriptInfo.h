#ifndef CLASSES_FW_SCRIPTINFO_H
#define CLASSES_FW_SCRIPTINFO_H

#include "classes/ml/IWorkEvent.h"
#include "mm/mtl/FixStr.h"

namespace ml { class EventFileTh; }
namespace ml { class FileHandleTh; }
namespace ml { enum FILE_PRIO : int; }
namespace fw { class ScriptManager; }

namespace fw {
// table 0x7100B42B78; 0x240 bytes (mm::mtl::Array<ScriptInfo>::reserve's stride): a script ScriptManager reads into
// a buffer and runs on monolib's virtual machine (vmLink, vmStart)
class ScriptInfo : public ::ml::IWorkEvent {
public:
    // m_flags' bits (the names are not the original's; bit 4 is not used here)
    enum {
        FLAG_LOADING = 1 << 0,  // reading
        FLAG_LOADED = 1 << 1,  // isLoaded
        FLAG_STARTED = 1 << 2,  // start was called
        FLAG_LINKED = 1 << 3,  // vmLink succeeded (vmUnlink undoes it)
        FLAG_LOAD_ERR = 1 << 5,  // isLoadErr
        FLAG_ACTIVE = 1 << 6,  // isActive: started, not finished
    };

    ScriptInfo();
    virtual ~ScriptInfo();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7: a read's end
    // unlinks or cancels the read, then forgets the script
    void destroy();
    // empty, for a manager under an id (ScriptManager::createScript hands it its buffer; the parameter names are
    // not the original's)
    void initialize(ScriptManager* manager, int id, void* buffer, unsigned int size);
    // reads a script into the buffer (one already read under the path is kept)
    void load(const mm::mtl::FixStr<256>& path, ml::FILE_PRIO prio);
    void start();
    // links the read script and starts it, then waits for its end
    void execute();
    bool isLoaded() const;
    bool isLoadErr() const;
    bool isFinish() const;
    bool isActive() const;

    // the names are not the original's
    void* m_buffer;  // initialize's: the script is read here and run from it
    unsigned int m_size;  // the buffer's
    mm::mtl::FixStr<256> m_path;  // load's
    mm::mtl::FixStr<256> m_fileName;  // the path's file name (ml::PathUtil::getFilePtrFromPath)
    int m_id;  // initialize's: what notifyEvent tells the manager's listeners
    // handle, state and flags: destroy zeroes the 16 bytes at once (one stp through the handle's address in the
    // destructor)
    ml::FileHandleTh* m_handle;  // the read DevFileTh::readFile started, until OnFileEvent
    int m_state;  // 0: none, 1: read (waiting for start), 2: running, 3: finished
    unsigned int m_flags;  // FLAG_*
    unsigned char pad_230[0x8];  // zeroed by the constructor
    ScriptManager* m_manager;  // initialize's
};
}  // namespace fw

#endif
