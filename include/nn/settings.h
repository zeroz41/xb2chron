#ifndef NN_SETTINGS_H
#define NN_SETTINGS_H

namespace nn { namespace settings {

// the SDK's language code: a NUL-terminated BCP 47 tag ("ja", "en-US", "zh-Hans"; 8 bytes, returned in x0 by
// nn::oe::GetDesiredLanguage)
struct LanguageCode {
    char string[8];
};
// the languages the console offers (ml::DevSettingNx::getLangList reads up to 15)
int GetAvailableLanguageCodeCount();
int GetAvailableLanguageCodes(LanguageCode* outCodes, int count);

}}  // namespace nn::settings

#endif
