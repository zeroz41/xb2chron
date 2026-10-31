#ifndef CLASSES_NAVI_NVMSHRESMAN_H
#define CLASSES_NAVI_NVMSHRESMAN_H

#include "classes/ml/IWorkEvent.h"
#include "mm/mtl/FixStr.h"
#include "navi/NvmshResData.h"

namespace ml { class EventFileTh; }
namespace ml { class FileHandleTh; }

namespace navi {
// table 0x7100B7F7E0
class NvmshResMan : public ::ml::IWorkEvent {
public:
    virtual ~NvmshResMan();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7
    void setupResource(const unsigned char* resource, const char* name);
    void releaseResource();
    // NvmshManager::jobUpdate's per-frame step
    void update();
    void tail();
    void resourceNaviUpdate();
    void resInfoUpdate(const mm::Vec3& pos, bool flag, const mm::Vec3& target, int worldId);
    void calcNaviInfoUpdate(const mm::Vec3& pos, const _NvMhAllWorldHead* head, bool flag, const mm::Vec3& target);
    void calcConectInfoUpdate(const _NvMhAllWorldHead* head, const _NvMhAllWrdConectHead* conect);
    void calcNaviObjUpdate();
    NvmshResData* createNaviDataRead(const _NvMhAllReadObj* read, int bank, int arg);

    // the resource reads in flight (OnFileEvent clears the finished one and its m_flags bit 0x10000 << index),
    // and what each read gives (the names are not the original's)
    ml::FileHandleTh* m_fileHandles[4];
    NvmshResData* m_fileData[4];
    NvmshResMemMan* m_memMan;  // 0x48, the blocks of m_buffer (the name is not the original's)
    // the navigation data's root, the world resInfoUpdate picked and its connections (the names are not the
    // original's)
    const _NvMhAllHead* m_allHead;
    const _NvMhAllWorldHead* m_worldHead;
    const _NvMhAllWrdConectHead* m_conectHead;
    // the resource file's name (setupResource: the name given, its extension replaced by ".winavd"; the
    // name is not the original's)
    mm::mtl::FixStr<64> m_fileName;
    unsigned char pad_AC[0x4];
    NvmshResData m_resData[26];  // 0xB0 (the name is not the original's)
    // the resources holding no navi (resInfoUpdate stacks them, createNaviDataRead takes the top one; the names
    // are not the original's)
    NvmshResData* m_freeData[26];
    short m_freeNum;
    unsigned char pad_16A2[0x2];
    // bit 2: NvmshAcMan::objectUpdate clears every active object's status bits, bit 4: a resource block was
    // marked by update, bit 5: skip one resourceNaviUpdate, bits 16-19: reads in flight; the name is not the
    // original's
    unsigned int m_flags;
    unsigned char* m_buffer;  // 0x16A8, the constructor's allocation (the name is not the original's)
    unsigned int m_bufferSize;  // the constructor's first size (the name is not the original's)
    // the two navi layers' tables and the info they share (in the allocation after the access work; the
    // names are not the original's)
    _NaviCalcResTbl* m_calcTbl;
    unsigned char* pad_16C0;
    _NaviCalcResInfo* m_calcInfo;
    unsigned char* pad_16D0;
    // the access objects' work buffer: m_acWorkNum ints for each of NvmshAcMan's 256 objects and its global one
    // (NvmshAcMan's constructor slices it); the names are not the original's
    int* m_acWork;
    unsigned char pad_16E0[0x4];
    int m_acWorkNum;
    short m_worldId;  // resInfoUpdate's world id (the name is not the original's)
    // tail() flips m_writeBank and sets m_readBank to the other one (the names are not the original's)
    short m_readBank;
    short m_writeBank;
};
}  // namespace navi

#endif
