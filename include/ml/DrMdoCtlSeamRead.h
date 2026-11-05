#ifndef ML_DRMDOCTLSEAMREAD_H
#define ML_DRMDOCTLSEAMREAD_H

#include "ml/DrMdoCtlSeamLight.h"

namespace ml { class DrResMdoSeamMemObj; }
namespace ml { class DrResMdoSeamWrkMpf; }
namespace ml { class DrResMdoSeamVertex; }
namespace ml { class DrResMdoSeamTexture; }
namespace ml { class DrResMdoSeamTexList; }
namespace ml { class DrResMdoSeamWrkLight; }

namespace ml {
// One stream request DrMdoCtlSeamRead::wait*Stream completes (the field names are not the original's)
struct _wkSeamReadCall {
    DrResMdoSeamMemObj* m_pMemObj;  // 0x0: the memory the stream read into
    // 0x8: the work the stream fills; its type follows the stream
    union {
        DrResMdoSeamWrkBase* m_pBase;
        DrResMdoSeamWrkLow* m_pLow;
        DrResMdoSeamWrkInst* m_pInst;
        DrResMdoSeamWrkEnv* m_pEnv;
        DrResMdoSeamWrkMpf* m_pMpf;
        DrResMdoSeamVertex* m_pVertex;
        DrResMdoSeamTexture* m_pTexture;
        DrResMdoSeamTexList* m_pTexList;
        DrResMdoSeamWrkLight* m_pLight;
    };
    DrResMdoSeamWrkInst* m_pInst2;  // 0x10: initInstMapParts' second work
    // 0x18: the cache slot the work's set*Cache fills (call*Stream: the request's _wkSeamReadWait::m_idx)
    unsigned short m_cacheIdx;
    unsigned short m_attr;  // 0x1A: the request's _wkSeamReadWait::m_attr
    unsigned short m_readIdx;  // 0x1C: its bit in m_readWaitBits
    // 0x1E: the stream kind, an index into DrMdoCtlSeamRead::s_pSeamWaitCall (call*Stream set it)
    unsigned short m_type;
    // 0x20: the size read (call*Stream); waitBaseVertexStream passes it to DrResMdoSeamWrkBase::setVertexCache
    int m_cacheParam;
};

// One stream request DrResMdoSeamParmRead::calcReadParms makes and DrMdoCtlSeamRead::call*Stream starts (0x10; the
// field names are not the original's)
struct _wkSeamReadWait {
    // 0x0: the work the stream fills; its type follows the stream (not set for the map and model streams, which take
    // a free work of their own)
    union {
        DrResMdoSeamWrkBase* m_pBase;
        DrResMdoSeamWrkLow* m_pLow;
        DrResMdoSeamWrkInst* m_pInst;
        DrResMdoSeamWrkEnv* m_pEnv;
        DrResMdoSeamWrkMpf* m_pMpf;
        DrResMdoSeamVertex* m_pVertex;
        DrResMdoSeamTexture* m_pTexture;
        DrResMdoSeamTexList* m_pTexList;
        DrResMdoSeamWrkLight* m_pLight;
    };
    unsigned short m_idx;   // 0x8: the entry of the stream's map header table
    unsigned short m_type;  // 0xA: the stream kind, an index into DrMdoCtlSeamRead::s_pSeamReadCall
    unsigned char m_attr;   // 0xC: passed on to _wkSeamReadCall::m_attr (the meaning is unknown)
    unsigned char pad_D[0x3];
};

// One part of the seam model control: the DrMdoCtlSeam* classes have no table of their own and DrMdoCtlSeamAll's
// methods call each part's methods on the same object (this unchanged), so they form one chain of bases between
// DrMdoCtlSeam and DrMdoCtlSeamAll. The order of the chain is not proven (every part sits at offset 0).
class DrMdoCtlSeamRead : public ::ml::DrMdoCtlSeamLight {
public:
    void waitBaseMapStream(_wkSeamReadCall* call, bool ok);
    void waitLowMdlStream(_wkSeamReadCall* call, bool ok);
    void waitInstMapStream(_wkSeamReadCall* call, bool ok);
    void waitEnvMdlStream(_wkSeamReadCall* call, bool ok);
    void waitMpfEtcStream(_wkSeamReadCall* call, bool ok);
    void waitMpfPoliStream(_wkSeamReadCall* call, bool ok);
    void waitBaseVertexStream(_wkSeamReadCall* call, bool ok);
    void waitVertexStream(_wkSeamReadCall* call, bool ok);
    void waitTexutreStream(_wkSeamReadCall* call, bool ok);
    void waitHeightTexutreStream(_wkSeamReadCall* call, bool ok);
    void waitTexListStream(_wkSeamReadCall* call, bool ok);
    void waitInstPosStream(_wkSeamReadCall* call, bool ok);
    void waitLightStream(_wkSeamReadCall* call, bool ok);
    void waitMpfMdlStream(_wkSeamReadCall* call, bool ok);
    void updateReadList();
    void updateReadCall();
    void callBaseMapStream(_wkSeamReadWait* wait);
    void callLowMdlStream(_wkSeamReadWait* wait);
    void callInstMapStream(_wkSeamReadWait* wait);
    void callMpfMdlStream(_wkSeamReadWait* wait);
    void callEnvMdlStream(_wkSeamReadWait* wait);
    void callBaseVertexStream(_wkSeamReadWait* wait);
    void callVertexStream(_wkSeamReadWait* wait);
    void callTexutreStream(_wkSeamReadWait* wait);
    void callHeightTexutreStream(_wkSeamReadWait* wait);
    void callTexListStream(_wkSeamReadWait* wait);
    void callInstPosStream(_wkSeamReadWait* wait);
    void callMpfEtclStream(_wkSeamReadWait* wait);
    void callMpfPolilStream(_wkSeamReadWait* wait);
    void callLightStream(_wkSeamReadWait* wait);

    // by _wkSeamReadCall::m_type / _wkSeamReadWait::m_type (15 entries, the last empty)
    static void (DrMdoCtlSeamRead::*s_pSeamWaitCall[15])(_wkSeamReadCall* call, bool ok);
    static void (DrMdoCtlSeamRead::*s_pSeamReadCall[15])(_wkSeamReadWait* wait);

    // 0x1370: the streams being read; updateReadList hands each to its wait*Stream and drops the finished ones (the
    // names are not the original's)
    _wkSeamReadCall m_readCall[8];
    int m_readCallNum;  // 0x14B0
};
}  // namespace ml

#endif
