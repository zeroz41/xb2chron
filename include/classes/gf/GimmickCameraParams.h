#ifndef CLASSES_GF_GIMMICKCAMERAPARAMS_H
#define CLASSES_GF_GIMMICKCAMERAPARAMS_H

namespace gf {
// table 0x7100B45EC8: a gimmick camera parameter file ("GCP\0", a count and a version, the entries from 0x10)
class GimmickCameraParams {
public:
    // one entry (0x2c bytes; 1.0.0's GfMenuModelViewCamera(Param const&) copies its first six floats)
    struct Param {
        unsigned char pad_0[0x2c];
    };
    // the header setup checks (the names are not the original's)
    struct Header {
        int m_magic;    // 'GCP'
        int m_size;     // entries
        int m_version;  // what the caller expects
        unsigned char pad_c[4];
        Param m_params[1];
    };

    GimmickCameraParams();
    GimmickCameraParams(void* data, int version);
    virtual ~GimmickCameraParams();  // slot 0
    void setup(void* data, int version);
    int getSize() const;
    const Param* getParam(int index) const;

    int m_size;         // getSize's
    Param* m_params;    // the file's entries
};
}  // namespace gf

#endif
