#ifndef CLASSES_ML_DRCALCSTMLISTOBJ_H
#define CLASSES_ML_DRCALCSTMLISTOBJ_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }
namespace ml { class FileHandleTh; }
namespace ml { class DrCalcTexStmObj; }
namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// table 0x7100B7EDE8
class DrCalcStmListObj : public ::ml::IWorkEvent {
public:
    // a state of the stream (DrCalcTexStreamMan::update calls it until it returns false)
    typedef bool (DrCalcStmListObj::*StmFunc)();

    virtual ~DrCalcStmListObj();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7

    // the values (0..2) DrStmReadCheck::update passes have no recovered names
    enum DrTexUseMode {};

    void release();
    // the stream's graphics API work, once per frame stocked (DrCalcTexStreamMan::apiUpdate)
    void apiUpdate();
    // the stream's flag bits of the frame stocked (DrMan::s_nDblStockIdx)
    bool isResTex() const;
    bool isResSub() const;
    void setUseMode(DrTexUseMode mode);
    // the pointer at 0x18 of the object at 0x48 once the flag at 0x82 is set, else null (the return type is not
    // known)
    void* getAdder();
    // a low-resolution texture of the frame stocked: its memory and flags (the struct's and fields' names are not
    // the original's; getResLowTexObj picks entry 0x78 of the 0x18-byte array at 0x30 by DrMan::s_nDblStockIdx)
    struct ResTexObj {
        const unsigned char* m_pData;  // 0x0: DrResMdoTexList::texStmUpdate moves its textures here
        unsigned char pad_8[0x8];
        unsigned char m_flags;         // 0x10: bit 0 = the memory is ready
        unsigned char pad_11[0x7];
    };
    ResTexObj* getResLowTexObj();
    // the streamed vertex resource (same shape: DrResMdoVertex::update reloads its buffers from m_pData once bit 0
    // of m_flags is set)
    ResTexObj* getResVertexObj();
    // the streamed shader resource (same shape)
    ResTexObj* getResShaderObj();
    // the stream's texture idx (0x70-byte entries at 0xB0)
    grlib::CGLibTextureBuffer* getTexObj(unsigned int idx);

    // inline in every state that ends the stream (texstm_notfileWait, texstm_oldVerWait, ...): its memory given
    // back unless kept, the end state next (the name is not the original's)
    void end();
    // inline in the error waits: the frames counted, the retry state after 60 (the name is not the original's)
    bool errWait(StmFunc retry);

    bool texstm_checkTexStm();
    bool texstm_defRead();
    bool texstm_deTexCheck();
    bool texstm_notfileWait();
    bool texstm_stmchk_topLast();
    bool texstm_oldVerWait();
    bool texstm_stmchk_setWait();
    bool texstm_defErrWait();
    bool texstm_requestWait();
    bool texstm_defMidtexErrWait();
    bool texstm_fastErrWait();
    bool texstm_defupdate();

    // the flag bits (names not recovered): 0x1000 no file, 0x2000 the memory kept, 0x8000 ended,
    // 0x40000 / 0x100000 << stock index isResSub / isResTex, 0x1000000 << stock index a use mode set,
    // 0x4000000 a read pending, 0x8000000 a read failed
    enum {
        FLAG_NOTFILE = 0x1000,
        FLAG_KEEPMEM = 0x2000,
        FLAG_END = 0x8000,
        FLAG_RESSUB = 0x40000,
        FLAG_RESTEX = 0x100000,
        FLAG_USEMODE = 0x1000000,
        FLAG_READ = 0x4000000,
        FLAG_READERR = 0x8000000,
        FLAG_READSTATE = FLAG_READ | FLAG_READERR,
    };  // the names are not the original's

    // (field names are not the original's)
    unsigned char pad_8[0x8];
    DrCalcStmListObj* m_pNext;   // 0x10: DrCalcTexStreamMan::update walks the list from the manager's 0x28
    unsigned char pad_18[0x18];
    ResTexObj* m_pResObj[2];     // 0x30: by DrMan::s_nDblStockIdx, the 0x18-byte resource entries getResVertexObj,
                                 // getResShaderObj and getResLowTexObj index
    FileHandleTh* m_pFile;       // 0x40: the read OnFileEvent waits for
    DrCalcTexStmObj* m_pAddMemObj;  // 0x48: given back by release like m_pMemObj; getAdder returns its memory
    DrCalcTexStmObj* m_pMemObj;  // 0x50: given back by DrCalcTexStreamMan::clearMemObj when the stream ends
    unsigned char pad_58[0x1C];
    unsigned short m_vertexIdx;  // 0x74: getResVertexObj's entry
    unsigned short m_shaderIdx;  // 0x76: getResShaderObj's entry
    unsigned short m_lowTexIdx;  // 0x78: getResLowTexObj's entry
    unsigned char pad_7a[0x6];
    unsigned int m_flags;        // 0x80
    int m_readSize;              // 0x84: added to the manager's m_errReadSize while an error waits
    int m_stateNo;               // 0x88: the state running (each state stores its number)
    // 0x8C: frames the stream went unused (counted while m_curUseMode is 0, clamped to 0x707 and 0xE0F;
    // the ctor sets those, texstm_defupdate clears both once the stream is used)
    short m_idleFrame[2];
    unsigned char pad_90[0x14];
    short m_texNum;              // 0xA4: the stream's textures (DrResMdoTexList::createStmTexInfoList; the name is not the original's)
    // 0xA6: release counts it down to 0; DrCalcTexStreamMan::update clears m_curUseMode while it is 0 (the name is
    // not the original's)
    short m_useCount;
    short m_errWait;             // 0xA8: frames an error waits (60 before the read is tried again)
    short m_reqWait;             // 0xAA: frames texstm_requestWait waits
    unsigned char pad_ac[0x4];
    grlib::CGLibTextureBuffer* m_texBuf;  // 0xB0: the stream's textures (getTexObj)
    unsigned char pad_b8[0x10];
    int m_curUseMode;            // 0xC8: DrCalcTexStreamMan::update moves m_useMode of the frame here (0 if no texture)
    int m_useMode[2];            // 0xCC: by DrMan::s_nDblStockIdx
    unsigned char pad_d4[0x10C];
    StmFunc m_func;              // 0x1E0: the state DrCalcTexStreamMan::update runs
    StmFunc m_endFunc;           // 0x1F0: the state after the stream ends
    StmFunc m_reqFunc;           // 0x200: the state after texstm_requestWait
};
}  // namespace ml

#endif
