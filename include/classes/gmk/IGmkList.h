#ifndef CLASSES_GMK_IGMKLIST_H
#define CLASSES_GMK_IGMKLIST_H

#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"
#include "mtl/AllocHandle.h"

namespace gmk { class AGmkBase; }
namespace gmk { enum GmkType : int; }

namespace gmk {
// table none (its derived classes')
class IGmkList {
public:
    // how a list loads its gimmicks (TGmkList::create copies it; dispose resets it to a default one)
    class CreateInfo {
    public:
        CreateInfo() : m_param(nullptr), m_pos(0.0f, 0.0f, 0.0f), m_flags(0) {}
        // out of line in the original (TGmkList::dispose calls it); its body is not written yet
        CreateInfo& operator=(CreateInfo&& other);
        mtl::ALLOC_HANDLE m_allocHandle;  // the resource's memory (CommonResource::request takes it)
        void* m_param;  // copied as 8 bytes (the name is not the original's)
        mm::mtl::FixStr<256> m_path;  // the gimmick resource's path (CommonResource::request takes it)
        mm::mtl::FixStr<32> m_bdatName;  // the BDAT table's name (Bdat::getFP takes it), empty for none
        mm::Vec3 m_pos;  // copied as three words (the name is not the original's)
        unsigned int m_flags;  // copied (the name is not the original's)
    };
    virtual ~IGmkList() {}  // slot 0
    virtual gmk::GmkType getGmkType() const = 0;  // slot 2
    virtual bool isValid() const = 0;  // slot 3
    virtual const CreateInfo& getCreateInfo() const = 0;  // slot 4
    virtual unsigned int getInstNum() const = 0;  // slot 5: how many gimmicks it holds
    virtual gmk::AGmkBase* getInst(unsigned int) const = 0;  // slot 6: one of them, none for an empty place
    virtual unsigned char* getBindedBdatFp() const = 0;  // slot 7
    virtual void setUpdateGmkNumPerFrame(unsigned int) = 0;  // slot 8
    virtual void create(gmk::IGmkList::CreateInfo const&) = 0;  // slot 9
    virtual void dispose() = 0;  // slot 10
    virtual void update(float) = 0;  // slot 11
    virtual bool updateImmediate() = 0;  // slot 12: whether the list is valid (isValid's answer)
    virtual void debugUpdateMmf() = 0;  // slot 13
    virtual void debugDraw() const = 0;  // slot 14
    virtual void debugGetDocId() const;  // slot 15
};
}  // namespace gmk

#endif
