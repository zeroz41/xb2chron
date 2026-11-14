#include "classes/ai/BlackBoard.h"
#include "classes/ptlib/emitter/ComputeManager.h"

namespace ptlib { namespace emitter {

unsigned int ComputeUniform::s_nUniformBlockSize[5] = {0x20, 0x200, 0x1F0, 0x230, 0x230};

ComputeUniform::ComputeUniform() {}

ComputeUniform::~ComputeUniform() { m_uniform.release(); }

void ComputeUniform::releaseUniform() { m_uniform.release(); }

void ComputeUniform::createUniform(unsigned int type, unsigned int count) {
    m_type = type;
    m_uniform.release();
    m_uniform.setup(s_nUniformBlockSize[m_type] * count);
}

}}  // namespace ptlib::emitter

namespace ai {

BlackBoard::BlackBoard() {}

BlackBoard::~BlackBoard() {}

mm::mtl::RTTI BlackBoard::m_rtti("BlackBoard", nullptr, nullptr);

}  // namespace ai
