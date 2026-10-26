#ifndef ANM_ASMANNOTETION_H
#define ANM_ASMANNOTETION_H

namespace anm {
// an annotation of an animation state machine (anm::ResASM's set*Annotation take one; an AsmListener's callback
// gets one): its event name, a kind and the data of that kind. GfExtendPacking registers its sound triggers as
// kind 4 with the trigger as data; GfComBehaviorExtra takes kind 1's text as a command (the field names are not the original's)
class AsmAnnotetion {
public:
    const char* m_name;
    int m_type;
    union {
        const void* m_data;
        const char* m_text;  // kind 1's (GfComBehaviorExtra queues it as a command)
        int m_value;  // a number (gf::pc::registerAsmCallbackField's "look": 0 entering, 1 leaving)
    };
};
}  // namespace anm

#endif
