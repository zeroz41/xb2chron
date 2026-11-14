#ifndef CLASSES_PTLIB_EMITTER_COMPUTEMANAGER_H
#define CLASSES_PTLIB_EMITTER_COMPUTEMANAGER_H

#include "grlib/CGLibDblUniformBlock.h"

namespace ptlib { namespace emitter {
// one uniform block of the particle compute pass (particle_emitter_compute_uniform.cpp); 0x40 bytes
// (ComputeManager holds them 0x40 apart)
class ComputeUniform {
public:
    ComputeUniform();
    ~ComputeUniform();
    void createUniform(unsigned int type, unsigned int count);
    void releaseUniform();
    void createParticlesUniform();

    // each type's block size (createUniform multiplies it by the count)
    static unsigned int s_nUniformBlockSize[5];

    unsigned int m_type;  // 0x0, createUniform's type
    grlib::CGLibDblUniformBlock m_uniform;  // 0x8
};

// table 0x7100B80790 (particle_emitter_compute_impl.h). The field names are not the original's: each uniform is
// named by the type init creates it with.
class ComputeManager {
public:
    // 1.0.0 has it out of line; 3.0.1's init inlines it
    ComputeManager() {}
    virtual ~ComputeManager();  // slot 0
    static ComputeManager*& getPtr();
    static void init();
    static void term();
    // 1.0.0's initSub/termSub (3.0.1 inlines them into init/term)
    void initSub() {
        m_type0Uniform.createUniform(0, 10000);
        m_type1Uniform.createUniform(1, 2001);
        for (int i = 0; i < 2; i++) {
            m_type3Uniform[i].createUniform(3, 1);
            m_type2Uniform[i].createUniform(2, 1);
            m_type4Uniform[i].createUniform(4, 1);
        }
        m_isUpdated = false;
    }
    void termSub() {
        m_type0Uniform.releaseUniform();
        m_type1Uniform.releaseUniform();
        for (int i = 0; i < 2; i++) {
            m_type3Uniform[i].releaseUniform();
            m_type2Uniform[i].releaseUniform();
            m_type4Uniform[i].releaseUniform();
        }
    }
    void update(unsigned int view);
    void resetUpdate();
    void calculateParticle();

    ComputeUniform m_type0Uniform;     // update creates its particles every frame
    ComputeUniform m_type1Uniform;     // update creates its particles once until resetUpdate
    ComputeUniform m_type3Uniform[2];  // by m_viewIndex
    ComputeUniform m_type2Uniform[2];
    ComputeUniform m_type4Uniform[2];
    unsigned int m_viewIndex;  // 1 when update's view is not 0
    bool m_isUpdated;          // m_type1Uniform's particles were created
};
}}  // namespace ptlib::emitter

#endif
