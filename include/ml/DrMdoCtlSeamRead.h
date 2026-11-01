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
    unsigned short m_cacheIdx;  // 0x18: the cache slot the work's set*Cache fills
    unsigned char pad_1A[0x2];
    unsigned short m_readIdx;  // 0x1C: its bit in m_readWaitBits
    unsigned char pad_1E[0x2];
    int m_cacheParam;  // 0x20: waitBaseVertexStream passes it to DrResMdoSeamWrkBase::setVertexCache
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
};
}  // namespace ml

#endif
