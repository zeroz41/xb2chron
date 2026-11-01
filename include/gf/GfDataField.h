#ifndef GF_GFDATAFIELD_H
#define GF_GFDATAFIELD_H

namespace gf {
// the field's BDAT data (functions, by its symbols; this is the class's one function in the symbols)
class GfDataField {
public:
    // the voice name the party leader (a driver: BDAT id, 0 for none) says for a field skill voice category, or
    // null. Callers: GfDataBlade::getFieldSkillVoice, SCOM_FIELD_VOICE::fn_7100568D34 and createFieldSkillMiss
    // (with QuestListAcc's getFLD_FieldSkillSetting*VoiceCategory).
    static const char* getFieldSkillVoice(unsigned int driver, unsigned int category);
};
}  // namespace gf

#endif
