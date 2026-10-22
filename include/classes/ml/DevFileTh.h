#ifndef CLASSES_ML_DEVFILETH_H
#define CLASSES_ML_DEVFILETH_H

#include "classes/ml/DevBase.h"

namespace mm { class VAL64; }
namespace ml { class CERR_STRUCT; }
namespace ml { class IWorkEvent; }
namespace ml { enum ERR_DECIDE : int; }
namespace ml { class DevFileParamTh; }
namespace ml { class FileHandleTh; }
namespace mm { namespace mtl { template <int LEN> class FixStr; } }

namespace ml {
// a base of ml::DevFileTh no evidence names yet
class TUnk_B76D68 {
public:
    virtual ~TUnk_B76D68();
};
// a base of ml::DevFileTh no evidence names yet
class TUnk_B76D88 {
public:
    virtual ~TUnk_B76D88();
    virtual void icbError(ml::CERR_STRUCT*) = 0;
    virtual void icbDecide(ml::CERR_STRUCT*, ml::ERR_DECIDE) = 0;
};
// table 0x7100B76CC0; base at 0x1B0 unknown (TUnk_B76D68), base at 0x1B8 unknown (TUnk_B76D88)
class DevFileTh : public ::ml::DevBase, public TUnk_B76D68, public TUnk_B76D88 {
public:
    virtual ~DevFileTh();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15

    // its object logged in
    static bool isInitialized();
    virtual void icbError(ml::CERR_STRUCT*);  // slot 17
    virtual void icbDecide(ml::CERR_STRUCT*, ml::ERR_DECIDE);  // slot 18
    // asks whether a file exists; the answer comes to listener's OnFileEvent (fw::LocalizeResource's update). What
    // it returns is a pointer or none (unused by its callers seen so far); the parameter names are not the original's
    static void* checkValidFile(const char* path, ml::IWorkEvent* listener);
    // a file's size, negative when it has none (GfFileSizePool::execFileSizeJob passes no VAL64)
    static int getFileSize(const char* path, mm::VAL64*);
    // starts reading the file a parameter names; the handle the answer to its listener's OnFileEvent carries, none
    static FileHandleTh* readFile(const DevFileParamTh& param);
    // stops a read readFile started (the parameter names are not the original's)
    static void cancel(FileHandleTh* handle, bool flag);
    // path as the file system takes it (fw::SoundResource::update; the parameter names are not the original's)
    static void normalizeDvdFileName(mm::mtl::FixStr<256>& out, const char* path);
};
}  // namespace ml

#endif
