#ifndef IDCOLI_IDCOLIINPUT_H
#define IDCOLI_IDCOLIINPUT_H

namespace idcoli {

// a collision query's input. IDColiUtilColi{Simple,Result}'s statics hand the shape it holds at 0xB0 to the
// shape tests as the work of the shape their name gives (sphere, capsule, box, line or ray). Later fields are not
// declared yet; the names are not the original's.
class IDColiInput {
public:
    const void* getShape() const { return m_shape; }

    unsigned char pad_0[0x90];
    // the hit distance range (IDColiGrandMesh's lenght* tests: a ray hit lies in [m_lengthMin, m_lengthMax], a
    // sphere's within m_lengthMax); the names are not the original's
    float m_lengthMax;  // 0x90
    float m_lengthMin;  // 0x94
    unsigned char pad_98[0x18];
    unsigned char m_shape[0x38];  // 0xB0 (0xE8 is the next field the callers read)
};

}  // namespace idcoli

#endif
