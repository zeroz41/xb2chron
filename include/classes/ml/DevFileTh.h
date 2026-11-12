#ifndef CLASSES_ML_DEVFILETH_H
#define CLASSES_ML_DEVFILETH_H

#include "classes/ml/DevBase.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/UniquePtr.h"
#include "mm/mtl/Bitflag.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/FixedObjectAllocator.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixStr.h"
#include "classes/ml/FileHandleTh.h"
#include "ml/CriticalSection.h"
#include <condition_variable>

namespace mm { class VAL64; }
namespace ml { class CERR_STRUCT; }
namespace ml { class IWorkEvent; }
namespace ml { enum ERR_DECIDE : int; }
namespace ml { class DevFileParamTh; }
namespace ml { class DevFileAccessor; }
namespace ml { class DevFileJobTh; }
namespace ml { class FileHandleTh; }
namespace ml { class IDevFileEvent; }
// MEDIA is unsigned: DevFileArchiver::getFileInfo zero-extends it to index m_medias (umaddl)
namespace ml { enum MEDIA : unsigned int; }
namespace mm { namespace mtl { template <int LEN> class FixStr; } }
namespace ml { namespace dvfl_detail { struct LoadMediaParam; } }

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
        // the request that asks whether path exists (a FileHandleTh), none when no accessor can tell; void* as
        // DevFileTh::checkValidFile tail-calls it without a conversion
        void* checkValidFile(const char* path, IWorkEvent* listener);
        FileHandleTh* rfOpen(const DevFileParamTh& param);
        bool rfClose(FileHandleTh* handle);  // false (the return type is not known)
        void cancelRequest(FileHandleTh* handle);
        // named by the symbols: start and stop the thread's work (DevFileTh::wkStandbyLogin/wkStandbyLogout)
        bool initialize();
        bool finalize();
        // named by the symbols: a loader thread's entry (arg is the Impl): runs thUpdate while the file thread is
        // initialized, until m_stop
        static unsigned int thFileLoader(void* arg);
        // named by the symbols
        void thUpdate();
        void loadBootArchive();
        // named by the symbols: drops a finished or canceled job, its request's data and the request
        void releaseRequest(DevFileJobTh* job);
        // named by the symbols: releases the queued jobs whose m_cancel is set
        void updateCancel();
        // named by the symbols: queues a job before the first one whose request is at a higher address, wakes a loader
        void appendRequest(DevFileJobTh* job);
        // named by the symbols: starts writing size bytes of data to path through the medium's accessor; the request,
        // none when the medium cannot write
        FileHandleTh* writeFile(const char* path, IWorkEvent* listener, const void* data, int size, int);
        // named by the symbols: reads the file a parameter names at once through one medium's accessor; the data,
        // none (it does not use its object: DevFileTh::readFileBlock leaves x0 unset)
        void* readFileBlock(const DevFileParamTh& param, int* size, mm::VAL64* value,
                           const dvfl_detail::LoadMediaParam& media, DevFileAccessor* accessor);
        // DevFileTh::rfRead/rfIsBusy's work under m_handleCs, inlined there (the names are not the original's)
        bool rfRead(FileHandleTh* handle, const DevFileParamTh& param);
        bool rfIsBusy(FileHandleTh* handle);

        // 0x0, 0x2D20, 0x5A40: three lists of jobs; appendRequest queues into the first, cancelRequest searches the
        // three in order (the name is not the original's)
        mm::mtl::FixedList<DevFileJobTh*, 640> m_jobs[3];
        unsigned char pad_8760[0xF0];
        // 0x8850: the requests' slots (releaseRequest gives one back; the name is not the original's)
        mm::mtl::FixedObjectAllocator<FileHandleTh, 640> m_handles;
        unsigned char pad_5b0a8[0x8];
        // 0x5B0B0, 0x5B0F0: a medium's accessor and archive accessor (initialize, finalize, rfClose; the names are
        // not the original's)
        DevFileAccessor* m_accessors[8];
        DevFileAccessor* m_archives[8];
        mm::mtl::Bitflag<8> m_accessorReady;  // 0x5B130: initialize sets a medium's flag once its accessor started
        bool m_initialized;  // 0x5B134 (DevFileTh::isInitialized reads it; the name is not the original's)
        unsigned char pad_5b135[0x1ADB];
        mtl::ALLOC_HANDLE m_alloc;  // 0x5CC10: writeFile's accessor creates its writer job from it
        unsigned char pad_5cc14[0x4];
        IWorkEvent* m_eventCb;  // 0x5CC18 (entryCb sets it, removeCb clears it; the name is not the original's)
        // 0x5CC20: guards m_jobs (appendRequest); 0x5CC48: rfClose's (the names are not the original's)
        CriticalSection m_jobCs;
        CriticalSection m_handleCs;
        bool m_stop;  // 0x5CC70: the loader threads end when set (thFileLoader; the name is not the original's)
        int m_loaderCount;  // 0x5CC74: the loader threads running (thFileLoader; the name is not the original's)
        // 0x5CC78: appendRequest wakes a loader through it (the name is not the original's)
        std::condition_variable m_jobCond;
        // 0x5CCA0: the slot of m_handles checkValidFile tries first, wrapping at its capacity (the name is not the
        // original's)
        unsigned int m_handleCursor;
        unsigned char pad_5cca4[0xC];
    };
    // what setup copies for Impl's constructor (nnMain fills it). 6 bytes, 2-aligned: setup copies 2 bytes at 0x4,
    // then 4 at 0x0 (a 6-byte copy; a 4-byte first field would make it an 8-byte one). The static's initial value is
    // {3, 0, 1}.
    struct SetupParam {
        unsigned short m_loaderThreadNum;  // 0x0 (Impl() starts this many loader threads; the name is not the original's)
        unsigned short pad_2;
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
    // named by the symbols: the media's path of the file at path into out, from the first search path whose
    // accessor knows it; its size, negative when none does (the return type and parameter names are not known)
    static int getRealName(const char* path, mm::mtl::FixStr<256>& out);
    // named by the symbols: reads the archive at path and adds it to the DevFileArchiver for a medium; kept in
    // dvfl_detail::g_reserveArchives while there is no object (the parameter names are not the original's)
    static void registArchive(MEDIA media, const char* path, const char* name, const char* root);
    // starts reading the file a parameter names; the handle the answer to its listener's OnFileEvent carries, none
    static FileHandleTh* readFile(const DevFileParamTh& param);
    // reads the file a parameter names at once: its data, none; its size and VAL64 through the pointers
    // (fw::CommonResource::updateBlock; the parameter names are not the original's)
    static void* readFileBlock(const DevFileParamTh& param, int* size, mm::VAL64* value);
    // stops a read readFile started (the parameter names are not the original's)
    static void cancel(FileHandleTh* handle, bool flag);
    // path as the file system takes it (fw::SoundResource::update; the parameter names are not the original's)
    static void normalizeDvdFileName(mm::mtl::FixStr<256>& out, const char* path);
    // named by the symbols: the media's path of a file into out (DevFileNxTh::rfOpen builds a channel's path with it;
    // the return type and parameter names are not known)
    static void makeMediaFileName(mm::mtl::FixStr<256>& out, const char* root, const char* path);
    // named by the symbols: the media root ("rom:" in rom mount mode, else the dvd root path)
    static const char* getDvdRoot();
    // named by the symbols: the medium a path names (DevFileNxTh::getMediaPath puts the media root before the paths
    // of medium 0)
    static MEDIA getMediaType(const char* path);
    // opens the file a parameter names for reading in parts (forwards to its Impl; the parameter name is not the
    // original's)
    static FileHandleTh* rfOpen(const DevFileParamTh& param);
    // closes a handle rfOpen returned; 0 (forwards to its Impl; the parameter name is not the original's)
    static int rfClose(FileHandleTh* handle);
    // named by the symbols: whether a handle rfOpen returned is busy (event::StmPackData calls it before rfClose; the
    // parameter name is not the original's)
    static bool rfIsBusy(FileHandleTh* handle);
    // named by the symbols: reads a part of a file rfOpen opened (the parameter names are not the original's)
    static bool rfRead(FileHandleTh* handle, const DevFileParamTh& param);
    // named by the symbols: the channel a handle holds when it has none (rfRead, rfIsBusy compare against it)
    static unsigned int INVALID_FILE_CHANNEL;
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
// named by the symbols: an archive DevFileTh::registArchive keeps in g_reserveArchives (0x190 bytes: its copy
// constructor writes up to 0x190, and 2.0.0's symbols give the FixedVector capacity 16, whose size sits at 0x1900;
// fields not read yet)
struct ReserveArchiveParam {
    MEDIA m_media;                 // 0x0: registArchive's medium
    // registArchive's path, name and root (0x4, 0x88, 0x10C; the names are not the original's)
    mm::mtl::FixStr<128> m_path;
    mm::mtl::FixStr<128> m_name;
    mm::mtl::FixStr<128> m_root;
};
// 0x7100ECBC10 (this unit): the archives registArchive keeps while there is no DevFileTh
extern mm::mtl::FixedVector<ReserveArchiveParam, 16> g_reserveArchives;
// named by the symbols: a search path addMediaPath inserts into g_loadMedia (0x8C bytes: FixedVector::insert
// steps by 0x8C and checks the count against 16, as 2.0.0's symbols give; the size sits at 0x8C0; fields not
// read yet)
struct LoadMediaParam {
    MEDIA m_media;  // 0x0: the medium (DevFileTh::getFileSize indexes the accessors with it; the name is not the original's)
    int m_prio;  // 0x4: addMediaPath's prio (the name is not the original's)
    mm::mtl::FixStr<128> m_path;  // 0x8: the search path (addMediaPath; the name is not the original's)
};
// 0x7100ECD518 (this unit): the search paths addMediaPath keeps
extern mm::mtl::FixedVector<LoadMediaParam, 16> g_loadMedia;
}  // namespace dvfl_detail
}  // namespace ml

#endif
