#include "fw/LangUtil.h"
#include "fw/LangUtil.h"
#include "classes/ml/DevSetting.h"

namespace fw {

LangType LangUtil::m_selectLang;
LangType LangUtil::m_selectVoice;
LangType LangUtil::m_defaultLang;
LangType LangUtil::m_defaultVoice;

// each language's folders, by LangType: [0] its texts', [1] its voices' (the name is not the original's)
static mm::mtl::FixStr<16> s_folders[2][15] = {
    {
        mm::mtl::FixStr<16>("jp"), mm::mtl::FixStr<16>("gb"), mm::mtl::FixStr<16>("fr"), mm::mtl::FixStr<16>("ge"),
        mm::mtl::FixStr<16>("it"), mm::mtl::FixStr<16>("sp"), mm::mtl::FixStr<16>("cn"), mm::mtl::FixStr<16>("kr"),
        mm::mtl::FixStr<16>("nl"), mm::mtl::FixStr<16>("pt"), mm::mtl::FixStr<16>("ru"), mm::mtl::FixStr<16>("tw"),
        mm::mtl::FixStr<16>("gb"), mm::mtl::FixStr<16>("fr"), mm::mtl::FixStr<16>("sp"),
    },
    {
        mm::mtl::FixStr<16>("jp"), mm::mtl::FixStr<16>("us"), mm::mtl::FixStr<16>("us"), mm::mtl::FixStr<16>("us"),
        mm::mtl::FixStr<16>("us"), mm::mtl::FixStr<16>("us"), mm::mtl::FixStr<16>("jp"), mm::mtl::FixStr<16>("us"),
        mm::mtl::FixStr<16>("us"), mm::mtl::FixStr<16>("us"), mm::mtl::FixStr<16>("us"), mm::mtl::FixStr<16>("jp"),
        mm::mtl::FixStr<16>("us"), mm::mtl::FixStr<16>("us"), mm::mtl::FixStr<16>("us"),
    },
};

void LangUtil::initialize() {
    LangType lang = static_cast<LangType>(ml::DevSetting::getLang());
    m_defaultLang = m_selectLang = lang;
    // the Japanese voices (0) where the language's voice folder is "jp", the others' (1) otherwise
    m_defaultVoice = m_selectVoice = static_cast<LangType>(strcmp(s_folders[1][lang].m_str, "jp") != 0);
}

int LangUtil::getLangType() {
    return m_selectLang;
}

LangType LangUtil::getVoiceType() {
    return m_selectVoice;
}

void LangUtil::setLangType(LangType type) {
    LangList list;
    getLangList(list);
    for (LangList::iterator it = list.begin(); it != list.end(); ++it) {
        if (it->first == type) {
            m_selectLang = type;
            return;
        }
    }
    m_selectLang = static_cast<LangType>(1);
}

LangUtil::LangList& LangUtil::getLangList(LangList& list) {
    mm::mtl::FixedVector<ml::LangType, 15> langs;
    ml::DevSetting::getLangList(langs);
    list.clear();
    if (!langs.empty()) {
        const ml::LangType* it = langs.begin();
        const ml::LangType* end = langs.end();
        do {
            ml::LangType lang = *it;
            std::pair<LangType, mm::mtl::FixStr<16> > entry;
            entry.first = static_cast<LangType>(lang);
            entry.second = s_folders[0][lang];
            list.push_back(entry);
        } while (++it != end);
    }
    return list;
}


void LangUtil::setVoiceType(LangType type) {
    LangList list;
    getVoiceList(list);
    for (LangList::iterator it = list.begin(); it != list.end(); ++it) {
        if (it->first == type) {
            m_selectVoice = type;
            return;
        }
    }
    m_selectVoice = static_cast<LangType>(strcmp(s_folders[1][m_selectLang].m_str, "jp") != 0);
}

LangUtil::LangList& LangUtil::getVoiceList(LangList& list) {
    list.clear();
    LangList langs;
    getLangList(langs);
    for (const std::pair<LangType, mm::mtl::FixStr<16> >& lang : langs) {
        const mm::mtl::FixStr<16>& folder = s_folders[1][lang.first];
        bool found = false;
        for (const std::pair<LangType, mm::mtl::FixStr<16> >& voice : list) {
            if (strcmp(voice.second.m_str, folder.m_str) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::pair<LangType, mm::mtl::FixStr<16> > entry;
            entry.first = lang.first;
            entry.second = folder;
            list.push_back(entry);
        }
    }
    return list;
}

const mm::mtl::FixStr<16>& LangUtil::getLangFolder() {
    return s_folders[0][m_selectLang];
}

const char* LangUtil::getVoiceFolder() {
    return s_folders[1][m_selectVoice].m_str;
}

}  // namespace fw
