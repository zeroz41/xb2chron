#ifndef ML_DRENVCOLIMAN_H
#define ML_DRENVCOLIMAN_H

namespace mm { class Vec3; }

namespace ml {
class DrEnvColiResult;

// the environment collision of one view (DrEnvironmentMan's); ScnRenderDrEnvColi reads what a test hit
class DrEnvColiMan {
public:
    bool testEnvColi(DrEnvColiResult* result, const mm::Vec3& pos, float range);

    // field names are not the original's
    unsigned char pad_0[0x60];
    int m_windId;     // ScnRenderDrEnvColi::getWindId
    unsigned int m_flags;  // bit 2: room (ScnRenderDrEnvColi::isRoom)
};
}  // namespace ml

#endif
