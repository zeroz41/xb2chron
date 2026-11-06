#ifndef CLASSES_EVENT_STMPACKHEADER_H
#define CLASSES_EVENT_STMPACKHEADER_H

#include "classes/fw/RenderResource.h"
namespace mtl { class ALLOC_HANDLE; }

namespace event {
// table 0x7100B3C400
class StmPackHeader {
public:
    // inline (StmPackMemory::loadStream builds one in each pack)
    StmPackHeader() : m_res(nullptr) {}
    virtual ~StmPackHeader();  // slot 0
    // the handle is unused: the header is requested from MemoryManager's
    void create(mtl::ALLOC_HANDLE handle, const char* name);
    // inline: releases the resource (StmPackMemory::Pack's destructor; the name is not the original's)
    void clear() {
        if (m_res) {
            m_res->release();
            m_res = nullptr;
        }
    }
    // one cut of the pack: the asset holds a table of 0x120-byte entries from 0x10 (the names are not the original's)
    struct Entry {
        char m_path[0x100];  // getPath's
        unsigned int m_dataOfs;  // getDataOfs's: where the cut starts in the data file
        unsigned int m_dataSize;  // getDataSize's
        int m_prio;  // getPrio's
        unsigned char pad_10c[0x14];
    };
    // what m_res's getAssetData returns (the names are not the original's)
    struct Asset {
        unsigned int pad_0;
        unsigned int m_count;  // getCount's
        unsigned char pad_8[8];
        Entry m_entries[1];
        const Entry& entry(unsigned int i) const { return m_entries[i]; }
    };
    // 1.0.0's StmPackHeader::getPath, getPrio, getDataOfs, getDataSize, getCount, isLoading (out of line there,
    // inlined in 3.0.1): the i-th entry's fields, "" or 0 before the asset is there
    const char* getPath(unsigned long i) const {
        if (m_res->getAssetData() == nullptr) {
            return "";
        }
        return static_cast<const Asset*>(m_res->getAssetData())->entry(i).m_path;
    }
    int getPrio(unsigned long i) const {
        if (m_res->getAssetData() == nullptr) {
            return 0;
        }
        return static_cast<const Asset*>(m_res->getAssetData())->entry(i).m_prio;
    }
    unsigned long getDataOfs(unsigned long i) const {
        if (m_res->getAssetData() == nullptr) {
            return 0;
        }
        return static_cast<const Asset*>(m_res->getAssetData())->entry(i).m_dataOfs;
    }
    unsigned long getDataSize(unsigned long i) const {
        if (m_res->getAssetData() == nullptr) {
            return 0;
        }
        return static_cast<const Asset*>(m_res->getAssetData())->entry(i).m_dataSize;
    }
    unsigned long getCount() const {
        if (m_res->getAssetData() == nullptr) {
            return 0;
        }
        return static_cast<const Asset*>(m_res->getAssetData())->m_count;
    }
    bool isLoading() const { return !m_res->valid(); }
    // create (0x71000C1790) releases the previous one, then keeps fw::RenderResource::request's (the name is not the
    // original's)
    fw::RenderResource* m_res;  // 0x8
};
}  // namespace event

#endif
