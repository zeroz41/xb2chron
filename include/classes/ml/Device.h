#ifndef CLASSES_ML_DEVICE_H
#define CLASSES_ML_DEVICE_H

#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedList.h"

namespace ml { class LanguageInfo; }

namespace ml {
// a base of ml::Device no evidence names yet
class TUnk_B75A80 {
public:
    virtual ~TUnk_B75A80();
};
// table 0x7100B759D8; its base at 0x1A8 is its singleton (DeviceNx's destructor stores PtrSingleton<ml::Device>'s
// table there and clears its instance). TUnk_B75A80 (0x7100B75A80) is the table's second part (that base's), not a
// class of its own.
class Device : public ::ml::WorkObj, public ::mm::mtl::PtrSingleton<Device> {
public:
    // the SDK's start-up settings (DeviceNx::initializeSDK reads the file memory's size and alignment; the rest of the
    // layout is unknown; the field names are not the original's)
    struct InitParam {
        unsigned char pad_0[0x18];
        unsigned long m_fileMemSize;   // 0x18
        unsigned long m_fileMemAlign;  // 0x20
    };
    // a job jobUpdate runs on the render CPU: m_func(m_arg) (0x10 bytes: the FixedList node is 0x18; the type's and
    // its fields' names are not the original's)
    struct Job {
        void (*m_func)(void*);
        void* m_arg;
    };

    // Device::create builds a DeviceNx so (WorkObj with room for 0x20 children; size 0x378)
    Device(const char* name, WorkObj* parent) : WorkObj(name, parent, 0x20), m_groupHandle(-1), m_langInfo(nullptr) {}

    // starts the platform SDK (forwards to DeviceNx::initializeSDK)
    static void initializeSDK(const InitParam& param);
    // shuts the platform SDK down (nnMain; tail-calls DevFileNxTh::finalizeSDK)
    static void finalizeSDK();
    // every device ready (WinViewRoot::wkStandbyLogin waits on it)
    static bool isAllReady();
    // DevFont::wkStandbyLogin waits for it before making its font (0x71006A0AB0)
    static bool isColdStartReady();
    // makes the platform device ("DeviceNx") under WorkControl
    static Device* create();
    // the job wkStandbyLogin enters on its job group: runs every job of m_jobs
    static unsigned int jobUpdate(void*, void*);
    // inline: the original keeps its copies in the weak tail (wkStandbyLogin is the key function)
    virtual ~Device() {}  // slot 0
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    virtual void createDevice() = 0;  // slot 17
    virtual void createDevicePort(char const*) = 0;  // slot 18

    // 0x1B0 wkStandbyLogin's WorkCpu::createGroupHandle, released by wkStandbyLogout; -1 before (the name is not the
    // original's)
    int m_groupHandle;
    unsigned char pad_1b4[4];
    // 0x1B8 the jobs jobUpdate runs (the name is not the original's)
    mm::mtl::FixedList<Job, 16> m_jobs;
    // 0x370 wkStandbyLogin makes and initializes it, wkStandbyLogout deletes it (the name is not the original's)
    LanguageInfo* m_langInfo;
};
}  // namespace ml

#endif
