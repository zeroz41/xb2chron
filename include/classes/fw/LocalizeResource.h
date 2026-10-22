#ifndef CLASSES_FW_LOCALIZERESOURCE_H
#define CLASSES_FW_LOCALIZERESOURCE_H

#include "classes/fw/CommonResource.h"
#include "classes/ml/IWorkEvent.h"
#include "mm/mtl/FixStr.h"

namespace ml { class EventFileTh; }

namespace fw {
// table 0x7100B429B8 (0x158 bytes): a resource whose file has a version per language ("<name>_<lang><ext>"),
// checked before it loads
class LocalizeResource : public ::fw::CommonResource, public ::ml::IWorkEvent {
public:
    // inline: 3.0.1 has no out-of-line copy (request holds its stores)
    LocalizeResource(mm::mtl::IAllocator* allocator, LOAD_PRIO prio)
        : CommonResource(allocator, prio, 0, 0), m_state(0) {}
    virtual ~LocalizeResource();  // slot 0
    virtual void update();  // slot 2
    virtual const char* getAssetName() const;  // slot 4: the localized path, none before
    virtual bool OnFileEvent(ml::EventFileTh* event);  // slot 5 (IWorkEvent's slot 7)
    // the resource of a path, referenced: the loaded one, else a new one (the last parameter is unused)
    static LocalizeResource* request(mm::mtl::IAllocator* allocator, const char* path, int prio, bool flag);
    // "<path without its extension>_<lang><extension>"
    void makeLocalizeFilePath(mm::mtl::FixStr<128>& path, const mm::mtl::FixStr<16>& lang);

    // the names are not the original's
    mm::mtl::FixStr<128> m_localizePath;  // the requested path, then the localized one the check found
    // 0: check the selected language's file, 1: check "us", 2/3: checking them, 4: loading
    int m_state;
};
}  // namespace fw

#endif
