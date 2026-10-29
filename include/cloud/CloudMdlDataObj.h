#ifndef CLOUD_CLOUDMDLDATAOBJ_H
#define CLOUD_CLOUDMDLDATAOBJ_H

namespace cloud {

// a cloud model's data (0x88: CloudObjMan::createMdlData allocates it), kept in CloudObjMan's model data list. Only
// what CloudObjMan uses is declared; the field names are not the original's.
class CloudMdlDataObj {
public:
    CloudMdlDataObj();
    ~CloudMdlDataObj();
    void create(const void* data);
    // false once the data is no longer used (CloudObjMan::update then releases it)
    bool update();
    // DrMdoCtlCldMdl::update/dispOffUpdate pass true/false
    void setCallDisp(bool disp);

    CloudMdlDataObj* m_pPrev;  // 0x0
    CloudMdlDataObj* m_pNext;  // 0x8
    void* m_pList;             // 0x10, the CloudList holding it
    unsigned char pad_18[0x70];
};

}  // namespace cloud

#endif
