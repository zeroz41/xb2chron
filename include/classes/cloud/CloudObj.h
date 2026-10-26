#ifndef CLASSES_CLOUD_CLOUDOBJ_H
#define CLASSES_CLOUD_CLOUDOBJ_H

namespace cloud {
class CloudObj;

// CloudObj's list links: a base without a table (CloudObj's constructor zeroes them before it stores its table,
// as a base's constructor does). The names are not the original's.
class CloudObjLink {
public:
    CloudObjLink() : m_pPrev(nullptr), m_pNext(nullptr), m_pList(nullptr) {}

    CloudObj* m_pPrev;  // 0x8
    CloudObj* m_pNext;  // 0x10, CloudObjMan::update walks its objects through it
    void* m_pList;      // 0x18, the CloudList holding it (CloudObjMan's object list)
};

// table 0x7100B7A118. The constructor is out of line (the derived constructors call it); the destructor is
// inline (the derived destructors call nothing).
class CloudObj : public CloudObjLink {
public:
    CloudObj();
    virtual ~CloudObj() {}  // slot 0
    virtual void update() = 0;  // slot 2
    virtual void alphaRender() = 0;  // slot 3
    virtual void alphaRenderSec() {}  // slot 4
};
}  // namespace cloud

#endif
