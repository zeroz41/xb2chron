#ifndef SKD_DYNAMICSIMPORTER_H
#define SKD_DYNAMICSIMPORTER_H

namespace skd { class ResDynamics; }

namespace skd {
// a dynamics binary ("SKDY", version 2) as resources
class DynamicsImporter {
public:
    // the root of a dynamics binary: its kind and the resource
    struct Root {
        int m_version;               // 2
        unsigned int m_magic;        // "SKDY" as its bytes read
        ResDynamics* m_dynamics;
    };

    // the dynamics resource of `binary`, its pointers resolved, or null when it is not a dynamics binary
    static ResDynamics* import(void* binary);
};
}  // namespace skd

#endif
