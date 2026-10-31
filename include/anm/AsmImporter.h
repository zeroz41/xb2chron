#ifndef ANM_ASMIMPORTER_H
#define ANM_ASMIMPORTER_H

namespace anm { class ResStateArray; }

namespace anm {
// reads an animation state machine's binary (an "ASMB" one, version 7)
class AsmImporter {
public:
    // the root of a state machine binary: its version, kind and the states
    struct Root {
        int m_version;              // 7
        char m_magic[4];            // "ASMB"
        ResStateArray* m_states;    // fw::AnimResAsmResolver::resolvePackFiles and Factory::createASMResource read it
    };

    // the states of `binary`, its pointers resolved, or null when it is not a state machine binary
    static ResStateArray* import(void* binary);
};
}  // namespace anm

#endif
