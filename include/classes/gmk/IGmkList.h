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
        // the gimmicks' position: its copy assignment checks for self-assignment (CreateInfo's out-of-line move
        // assignment 0x71005C8D90 copies its three words under `this != &other`), so it is not mm::Vec3 (the name
        // is not the original's)
        class Pos {
        public:
            Pos() : x(0.0f), y(0.0f), z(0.0f) {}
            Pos& operator=(const Pos& v) {
                if (this != &v) {
                    x = v.x;
                    y = v.y;
                    z = v.z;
                }
                return *this;
            }
            Pos& operator=(const mm::Vec3& v) {
                x = v.x;
                y = v.y;
                z = v.z;
                return *this;
            }
            // every component within 1e-6 of zero (as mm::Vec3::isZero; the name is not the original's)
            bool isZero() const { return ::fabsf(x) <= 1e-6f && ::fabsf(y) <= 1e-6f && ::fabsf(z) <= 1e-6f; }
            float x;
            float y;
            float z;
        } __attribute__((aligned(16)));

        CreateInfo() : m_param(nullptr), m_rotY(0.0f) {}
        mtl::ALLOC_HANDLE m_allocHandle;  // the resource's memory (CommonResource::request takes it)
        void* m_param;  // copied as 8 bytes (the name is not the original's)
        mm::mtl::FixStr<256> m_path;  // the gimmick resource's path (CommonResource::request takes it)
        mm::mtl::FixStr<32> m_bdatName;  // the BDAT table's name (Bdat::getFP takes it), empty for none
        Pos m_pos;  // where the list places its gimmicks (the name is not the original's)
        float m_rotY;  // their rotation: TGmkList::createGmk takes its sine and cosine (the name is not the original's)
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
