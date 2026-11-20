#ifndef CLASSES_ML_DEBDRAWCMD_H
#define CLASSES_ML_DEBDRAWCMD_H

#include "classes/ml/DebDraw.h"
#include "mm/Col3.h"
#include "mm/Col4.h"
#include "mm/Vec3.h"

namespace grlib { class CGLibVtxVertex; }

namespace mm { class Col3; }
namespace mm { class Col4; }
namespace mm { class Vec3; }
namespace mm { template <typename> class Pnt; }
namespace mm { template <typename> class Rect; }

namespace ml {
// table 0x7100B762C8
class DebDrawCmd : public ::ml::DebDraw {
public:
    // a vertex in the buffer, 0x18 bytes: position, rgba8 colour, uv (the names are not the original's)
    struct VERTEX {
        float x;
        float y;
        float z;
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
        float u;
        float v;
        void setPos(float px, float py, float pz) {
            x = px;
            y = py;
            z = pz;
        }
        void setPos(const mm::Vec3& p) {
            x = p.x;
            y = p.y;
            z = p.z;
        }
        void setCol(const mm::Col4& col) {
            r = col.r * 255.0f;
            g = col.g * 255.0f;
            b = col.b * 255.0f;
            a = col.a * 255.0f;
        }
        void setUV(float pu, float pv) {
            u = pu;
            v = pv;
        }
        void clrUV() {
            u = 0.0f;
            v = 0.0f;
        }
    };
    // DevGraphNx::wkStandbyLogin builds it inline (no out-of-line constructor in the original)
    DebDrawCmd()
        : pad_219(false), pad_21c(mm::Col4::white), pad_230(mm::Vec3::unitY), pad_240(mm::Col4::white),
          pad_250(mm::Col4::white), pad_260(mm::Col4::white), pad_270(false), m_vtx(nullptr), pad_2d8(0),
          m_cur(nullptr) {}
    virtual ~DebDrawCmd();  // slot 0
    virtual void fastSetup();  // slot 7
    virtual void restoreShader() {}  // slot 8
    virtual void begin(unsigned int, unsigned int);  // slot 9
    virtual void end();  // slot 10
    virtual void add(mm::Vec3 const&, mm::Vec3 const&);  // slot 11
    virtual void add(mm::Pnt<int> const&, mm::Pnt<int> const&);  // slot 12
    virtual void add(int, int, int, int);  // slot 13
    virtual void add(mm::Vec3 const&);  // slot 14
    virtual void add(mm::Pnt<int> const&);  // slot 15
    virtual void add(float, float, float);  // slot 16
    virtual void add(int, int, int);  // slot 17
    virtual void add(int, int);  // slot 18
    virtual void add(mm::Vec3 const&, mm::Col4 const&);  // slot 19
    virtual void add(mm::Vec3 const&, mm::Col3 const&);  // slot 20
    virtual void add(int, int, mm::Col4 const&);  // slot 21
    virtual void add(int, int, mm::Col3 const&);  // slot 22
    virtual void add(mm::Vec3 const&, mm::Vec3 const&, mm::Col4 const&);  // slot 23
    virtual void add(mm::Rect<int> const&);  // slot 24
    virtual void add(mm::Vec3 const&, mm::Vec3 const&, mm::Vec3 const&);  // slot 25

    // render-thread jobs: allocate the vertex buffer / delete the one the argument points to
    static unsigned int thInitialize(void*, void*);
    static unsigned int thDestroy(void*, void*);

    // p relative to pad_160 through the matrix (the name is not the original's)
    void transform(const mm::Vec3& p, mm::Vec3& out) const {
        float x = p.x - pad_160.x;
        float y = p.y - pad_160.y;
        float z = p.z - pad_160.z;
        float tx = x * m_mtx.m[0][0] + y * m_mtx.m[1][0] + z * m_mtx.m[2][0] + m_mtx.m[3][0];
        float ty = x * m_mtx.m[0][1] + y * m_mtx.m[1][1] + z * m_mtx.m[2][1] + m_mtx.m[3][1];
        float tz = x * m_mtx.m[0][2] + y * m_mtx.m[1][2] + z * m_mtx.m[2][2] + m_mtx.m[3][2];
        out.y = ty;
        out.z = tz;
        out.x = tx;
    }
    // the position through the matrix when it is on (m_flags bit 3) (the name is not the original's)
    const mm::Vec3* transform(const mm::Vec3* p, mm::Vec3& tmp) const {
        if (m_flags & 8) {
            transform(*p, tmp);
            return &tmp;
        }
        return p;
    }
    // writes one vertex at the cursor (the name is not the original's)
    void putVtx(float x, float y, float z, const mm::Col4& col) {
        m_cur->setPos(x, y, z);
        m_cur->setCol(col);
        m_cur->clrUV();
        m_ofs += sizeof(VERTEX);
        m_cur++;
    }
    void putVtx(const mm::Vec3& p, const mm::Col4& col, float u, float v) {
        m_cur->setPos(p);
        m_cur->setCol(col);
        m_cur->setUV(u, v);
        m_ofs += sizeof(VERTEX);
        m_cur++;
    }
    void putVtx(const mm::Vec3& p, const mm::Col4& col) {
        m_cur->setPos(p);
        m_cur->setCol(col);
        m_cur->clrUV();
        m_ofs += sizeof(VERTEX);
        m_cur++;
    }

    bool pad_219;                    // false from the constructor
    mm::Col4 pad_21c;                // white from the constructor
    mm::Vec3 pad_230;                // mm::Vec3::unitY from the constructor
    mm::Col4 pad_240;                // white from the constructor
    mm::Col4 pad_250;                // white from the constructor
    mm::Col4 pad_260;                // white from the constructor
    bool pad_270;                    // false from the constructor
    unsigned char pad_271[0xF];
    mm::Mat44 m_mdlMtx;              // 0x280 end uploads it as the U_MDL uniform block (the name is not the original's)
    unsigned char pad_2c0[0x10];
    grlib::CGLibVtxVertex* m_vtx;    // 0x2D0 thInitialize's vertex buffer (the name is not the original's)
    unsigned int pad_2d8;            // 0x2D8 the frame's first byte offset (fastSetup)
    unsigned int m_ofs;              // 0x2DC byte offset of the cursor (the name is not the original's)
    unsigned int m_size;             // 0x2E0 the buffer's bytes, 0xC00000 (the name is not the original's)
    VERTEX* m_cur;                   // 0x2E8 the next vertex (the name is not the original's)
    bool pad_2f0;                    // 0x2F0 which half of the buffer (fastSetup flips it)
};
}  // namespace ml

#endif
