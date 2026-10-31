#ifndef CLASSES_ML_DEVFILETH_H
#define CLASSES_ML_DEVFILETH_H

#include "classes/ml/DevBase.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/UniquePtr.h"

namespace mm { class VAL64; }
namespace ml { class CERR_STRUCT; }
namespace ml { class IWorkEvent; }
namespace ml { enum ERR_DECIDE : int; }
namespace ml { class DevFileParamTh; }
namespace ml { class FileHandleTh; }
namespace ml { enum MEDIA : int; }
namespace mm { namespace mtl { template <int LEN> class FixStr; } }

namespace ml {
// a base of ml::DevFileTh no evidence names yet
class TUnk_B76D88 {
public:
    // inline: ~DevFileTh stores nothing at 0x1B8 after its own table
    virtual ~TUnk_B76D88() {}
    virtual bool icbError(ml::CERR_STRUCT*) = 0;
    virtual void icbDecide(ml::CERR_STRUCT*, ml::ERR_DECIDE) = 0;
};
// table 0x7100B76CC0; base at 0x1B0 mm::mtl::PtrSingleton<DevFileTh> (~DevFileTh stores its table there and clears
// its s_instance), base at 0x1B8 unknown (TUnk_B76D88)
class DevFileTh : public ::ml::DevBase, public ::mm::mtl::PtrSingleton<DevFileTh>, public TUnk_B76D88 {
public:
    // the thread's state (out of line in this unit: its destructor 0x71006B6B70)
    class Impl {
    public:
        ~Impl();
        void tail();
        FileHandleTh* readFile(const DevFileParamTh& param);
        void* checkValidFile(const char* path, IWorkEvent* listener);
        FileHandleTh* rfOpen(const DevFileParamTh& param);
        void rfClose(FileHandleTh* handle);
        void cancelRequest(FileHandleTh* handle);

        unsigned char pad_0[0x5CC18];
        IWorkEvent* m_eventCb;  // 0x5CC18 (entryCb sets it, removeCb clears it; the name is not the original's)
    };
    // what setup copies for Impl's constructor (nnMain fills it)
    struct SetupParam {
        unsigned int m_loaderThreadNum;  // 0x0 (Impl() starts this many loader threads; the name is not the original's)
        unsigned short pad_4;
    };

    virtual ~DevFileTh();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15

    // its object logged in
    static bool isInitialized();
    virtual bool icbError(ml::CERR_STRUCT*);  // slot 17
    virtual void icbDecide(ml::CERR_STRUCT*, ml::ERR_DECIDE);  // slot 18
    // asks whether a file exists; the answer comes to listener's OnFileEvent (fw::LocalizeResource's update). What
    // it returns is a pointer or none (unused by its callers seen so far); the parameter names are not the original's
    static void* checkValidFile(const char* path, ml::IWorkEvent* listener);
    // whether the file at path can be read (Framework::initialize: "bdat/jp.bin"; 1.0.0's name, static: called with
    // the path only)
    static bool checkValidFileBlock(const char* path);
    // a file's size, negative when it has none (GfFileSizePool::execFileSizeJob passes no VAL64)
    static int getFileSize(const char* path, mm::VAL64*);
    // starts reading the file a parameter names; the handle the answer to its listener's OnFileEvent carries, none
    static FileHandleTh* readFile(const DevFileParamTh& param);
    // reads the file a parameter names at once: its data, none; its size and VAL64 through the pointers
    // (fw::CommonResource::updateBlock; the parameter names are not the original's)
    static void* readFileBlock(const DevFileParamTh& param, int* size, mm::VAL64* value);
    // stops a read readFile started (the parameter names are not the original's)
    static void cancel(FileHandleTh* handle, bool flag);
    // path as the file system takes it (fw::SoundResource::update; the parameter names are not the original's)
    static void normalizeDvdFileName(mm::mtl::FixStr<256>& out, const char* path);
    // opens the file a parameter names for reading in parts (forwards to its Impl; the parameter name is not the
    // original's)
    static FileHandleTh* rfOpen(const DevFileParamTh& param);
    // closes a handle rfOpen returned; 0 (forwards to its Impl; the parameter name is not the original's)
    static int rfClose(FileHandleTh* handle);
    // named by the symbols: whether a handle rfOpen returned is busy (event::StmPackData calls it before rfClose; the
    // parameter name is not the original's)
    static bool rfIsBusy(FileHandleTh* handle);
    // named by the symbols: called once a save's write ended (GfGameSave::OnFileEvent)
    static void flushSave();
    // named by the symbols: starts writing size bytes of data to path, listener gets the end event (GfGameSave)
    static FileHandleTh* writeFile(const char* path, IWorkEvent* listener, const void* data, int size, int);
    // adds a search path for a medium when path is not empty (forwards to dvfl_detail::addMediaPath; the parameter
    // names are not the original's)
    static void addMediaPath(MEDIA media, const char* path, int prio);
    // whether its object is writing a save (the singleton's flag at 0x1C9)
    static bool isNowSaving();
    // named by the symbols: keeps the parameters for the Impl the object creates later
    static void setup(const SetupParam& param);
    // named by the symbols: sets the listener its Impl reports to; false when there is no object (the parameter
    // name is not the original's)
    static bool entryCb(IWorkEvent* listener);
    // named by the symbols: clears the listener entryCb set; false when there is no object
    static bool removeCb(IWorkEvent* listener);

    mm::mtl::UniquePtr<Impl> m_impl;  // 0x1C0 (~DevFileTh deletes it; the name is not the original's)
    unsigned char pad_1c8[0x1];
    bool m_nowSaving;  // 0x1C9 (isNowSaving reads it; the name is not the original's)
};
namespace dvfl_detail {
// 0x71006B580C (this unit)
void addMediaPath(MEDIA media, const char* path, int prio);
}  // namespace dvfl_detail
}  // namespace ml

#endif
