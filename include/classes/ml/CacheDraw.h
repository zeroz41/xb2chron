#ifndef CLASSES_ML_CACHEDRAW_H
#define CLASSES_ML_CACHEDRAW_H

#include "mtl/AllocHandle.h"
#include "ml/CriticalSection.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/DebDraw.h"

namespace ml {
// table 0x7100B759B8
class CacheDraw {
public:
    class DADDV3_1;
    class DADDV3_2;
    class DADDV3_3;
    class DALPHA_BLEND;
    class DBEGIN;
    class DCLEAR;
    class DCOL;
    class DDOUBLESIDE;
    class DEND;
    class DFONT128;
    class DFONT256;
    class DFONT32;
    class DFONT64;
    class DFONT_COL;
    class DFONT_FLUSH;
    class DFONT_SCALE;
    class DFONT_SHADOW;
    class DLINE_WIDTH;
    class DMAT;
    class DORTHO;
    class DPERS;
    class DRARROW;
    class DRAXIS;
    class DRCAPSULE;
    class DRCIRCLE_MAT;
    class DRCONE;
    class DRCUBE;
    class DRCYLINDER;
    class DRLINE;
    class DRLINE_PNT;
    class DRRECT;
    class DRRECT_FILL;
    class DRSPHERE_REAL;
    class DRSQUARE;
    class DTEX;
    class DZCOMP;
    class DZWRITE;

    // the header every queued command carries after its table pointer: the command's number, what it draws
    // (0 a state, 1 2D, 2 3D) and its size in the buffer (the name and its fields' names are not the original's)
    struct CMD {
        CMD(unsigned char type, unsigned char kind, unsigned short size) {
            m_type = type;
            m_size = size;
            m_kind = kind;
        }
        unsigned char m_type;
        unsigned char m_kind;
        unsigned short m_size;
    };
    // a run of commands queued under one primitive number (the name and its fields' names are not the original's)
    struct GROUP {
        unsigned char* m_begin;
        unsigned char* m_end;
        int m_prim;
    };
    // one frame bank's command memory (the name and its fields' names are not the original's)
    struct BUF {
        unsigned char* m_top;
        unsigned char* m_cur;
        unsigned long m_size;
        GROUP m_group[0x200];
        unsigned int m_groupNum;
    };

    CacheDraw(mtl::ALLOC_HANDLE mem, unsigned long size);
    virtual ~CacheDraw();  // slot 0

    // 1.0.0 has these out of line (getBuf, calcCurrentBuf); 3.0.1 inlines every use
    BUF* getBuf(bool odd) {
        unsigned int bank = (odd || (WorkCpu::getCurrentThreadId() != WorkCpu::getMainThreadId() && m_forceRenderQueue))
                       ? WorkCpu::getOdd()
                       : WorkCpu::getEven();
        return &m_buf[bank];
    }
    bool calcCurrentBuf(unsigned long size) {
        BUF* buf = getBuf(false);
        GROUP* group = &buf->m_group[buf->m_groupNum];
        unsigned char* cur = buf->m_cur;
        if (group->m_begin == nullptr) {
            group->m_begin = cur;
            buf->m_group[buf->m_groupNum].m_prim = m_prim;
        }
        buf->m_cur = cur + size;
        buf->m_group[buf->m_groupNum].m_end = buf->m_cur;
        return true;
    }

    // replays the commands of priority prio (DebDraw::flushPrio)
    void flush(int prio, const mm::Mat44& view, const mm::Mat44& proj);
    bool setLineWidth(unsigned int width);
    bool setDoubleSide(bool doubleSide);
    bool setAlphaBlend(bool blend);
    bool setOrtho();
    bool setMatrix(const mm::Mat44& mtx);
    bool setCol(const mm::Col4& col);
    bool setZComp(bool on);
    bool renderRect(const mm::Rect<int>& rect);
    bool renderRectFill(const mm::Rect<int>& rect);
    bool renderCube(const mm::Vec3& min, const mm::Vec3& max);
    bool renderCircle(const mm::Mat44& mtx, float radius, unsigned int div);
    bool renderAxis(float length);
    bool renderArrow(const mm::Vec3& start, const mm::Vec3& end);
    bool renderRealSphere(float radius, unsigned int div);
    bool renderCone(float radius, float height, unsigned int div);
    bool renderCylinder(float radius, float height, unsigned int div);
    bool renderCapsule(float radius, float height, unsigned int div);
    bool renderSquare(float width, float height);
    bool renderLine(const mm::Vec3& a, const mm::Vec3& b);
    bool renderLine(const mm::Pnt<int>& a, const mm::Pnt<int>& b);
    bool fontColor(const mm::Col4& col);
    bool fontShadow(bool on);
    bool fontFlush(bool on);
    bool fontScale(float x, float y);
    bool font(short x, short y, const char* text);

    BUF m_buf[2];                         // 0x08
    mtl::ALLOC_HANDLE m_handle;           // 0x6048 the constructor's (the name is not the original's)
    int m_prim;                           // 0x604C reset_prim's (the name is not the original's)
    int m_wid;                            // 0x6050 DebDraw::get's argument, getCacheDrawWID's (the name is not the original's)
    float pad_6054;
    float pad_6058;
    unsigned char pad_605c[0x4];
    CriticalSectionNC* m_section;         // 0x6060 (the name is not the original's)
    bool m_forceRenderQueue;              // 0x6068 setForceRenderQueue's (the name is not the original's)
    int m_suspendSwap;                    // 0x606C setSuspendSwap's (the name is not the original's)
    bool pad_6070;
};
}  // namespace ml

#endif
