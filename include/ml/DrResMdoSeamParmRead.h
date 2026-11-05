#ifndef ML_DRRESMDOSEAMPARMREAD_H
#define ML_DRRESMDOSEAMPARMREAD_H

#include "mm/Vec3.h"

namespace ml {
class DrResMdoSeamWrkInst;
struct wkSeamReadPacDataInf;
struct _wkSeamReadWait;
struct _wkSeamReadCall;

// The read parameters of the seamless map: the positions to read around and the models to keep. 0x638 bytes
// (begin stores the pack data at 0x630). Field and type names are not the original's.
class DrResMdoSeamParmRead {
public:
    enum { STOCK_BASE_MAP_MAX = 8, STOCK_INST_MAP_MAX = 8, STOCK_LOW_MDL_MAX = 8, STOCK_MPF_MDL_MAX = 4,
           STOCK_LIGHT_MAX = 4, POS_MAX = 3 };
    enum { FLAG_POS = 1 << 0 };
    enum { STOCK_TYPE_INST = 2 };
    struct StockInst {
        DrResMdoSeamWrkInst* wrk;  // 0x0
        unsigned short no;         // 0x8
        unsigned short type;       // 0xA (setStockInstMap: STOCK_TYPE_INST)
        unsigned char pad_C[0x4];
    };

    DrResMdoSeamParmRead();
    ~DrResMdoSeamParmRead();
    void begin(wkSeamReadPacDataInf* pac);
    void setStockBaseMap(int no);
    void setStockInstMap(int no, DrResMdoSeamWrkInst* wrk);
    void setStockMpfMdl(int no);
    void setStockEnvMdl(int no);
    void setStockLowMdl(int no);
    void setStockLight(int no);
    void resetHeightLvTexture();
    // fills waits with the streams to start (DrMdoCtlSeamRead::updateReadCall), given the ones being read; returns
    // how many (the parameter names are not the original's)
    int calcReadParms(_wkSeamReadWait* waits, bool& errOn, bool& failed, int errMode, const _wkSeamReadCall* calls,
                      int callNum);
    void addPos(const mm::Vec3& pos);

    unsigned int m_flags;                                // 0x0
    unsigned char pad_4[0xC];
    mm::Vec3 m_pos[POS_MAX];                             // 0x10
    int m_posCnt;                                        // 0x40
    unsigned char pad_44[0xC];
    unsigned char pad_50[0x8];                           // the constructor clears it
    unsigned char pad_58[0x4];                           // the constructor clears it
    unsigned char pad_5C[0xC];
    unsigned short m_stockEnvMdl;                        // 0x68
    unsigned short m_stockBaseMap[STOCK_BASE_MAP_MAX];   // 0x6A
    unsigned char pad_7A[0x6];
    StockInst m_stockInstMap[STOCK_INST_MAP_MAX];        // 0x80
    unsigned short m_stockLowMdl[STOCK_LOW_MDL_MAX];     // 0x100
    unsigned short m_stockMpfMdl[STOCK_MPF_MDL_MAX];     // 0x110
    unsigned short m_stockLight[STOCK_LIGHT_MAX];        // 0x118
    unsigned char pad_120[0x4B0];
    unsigned short m_stockBaseMapCnt;                    // 0x5D0
    unsigned short m_stockInstMapCnt;                    // 0x5D2
    unsigned short m_stockLowMdlCnt;                     // 0x5D4
    unsigned short m_stockMpfMdlCnt;                     // 0x5D6
    unsigned short m_stockLightCnt;                      // 0x5D8
    unsigned char pad_5DA[0xE];
    unsigned short m_heightLvTexCnt;                     // 0x5E8 (resetHeightLvTexture clears it)
    unsigned char pad_5EA[0x42];
    unsigned char pad_62C[0x2];                          // the constructor clears it
    unsigned char pad_62E[0x2];
    wkSeamReadPacDataInf* m_pacData;                     // 0x630
};
}  // namespace ml

#endif
