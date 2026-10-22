#ifndef CLASSES_GMK_IGMKLIST_H
#define CLASSES_GMK_IGMKLIST_H

namespace gmk { class AGmkBase; }

namespace gmk {
// table none (its derived classes')
class IGmkList {
public:
    class CreateInfo;
    virtual ~IGmkList();  // slot 0
    virtual void getGmkType() const = 0;  // slot 2
    virtual bool isValid() const = 0;  // slot 3
    virtual void getCreateInfo() const = 0;  // slot 4
    virtual unsigned int getInstNum() const = 0;  // slot 5: how many gimmicks it holds
    virtual gmk::AGmkBase* getInst(unsigned int) const = 0;  // slot 6: one of them, none for an empty place
    virtual void getBindedBdatFp() const = 0;  // slot 7
    virtual void setUpdateGmkNumPerFrame(unsigned int) = 0;  // slot 8
    virtual void create(gmk::IGmkList::CreateInfo const&) = 0;  // slot 9
    virtual void dispose() = 0;  // slot 10
    virtual void update(float) = 0;  // slot 11
    virtual void updateImmediate() = 0;  // slot 12
    virtual void debugUpdateMmf() = 0;  // slot 13
    virtual void debugDraw() const = 0;  // slot 14
    virtual void debugGetDocId() const;  // slot 15
};
}  // namespace gmk

#endif
