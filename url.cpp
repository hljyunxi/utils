void ParamsStr2Map(
        map<string, string>& key2value, const char* str, bool decode_uri)
{
    if (0 == str || 0 == *str) return;

    const char* ptr = str;
    char c = 0;
    string key, value, ktmp, vtmp;

    key.reserve(512);
    value.reserve(512);
    ktmp.reserve(512);
    vtmp.reserve(512);

    while (*ptr != 0)
    {
        key.clear();
        value.clear();

        while ((c = *ptr) != 0 && '&' == c) ++ptr;

        if (c != '=') // have key
        {
            const char* pkey = ptr;
            while ((c = *ptr) != 0 && c != '=' && c != '&') ++ptr;
            if (ptr != pkey) key.assign(pkey, ptr - pkey);
        }

        if ('=' == c)
        {
            while ((c = *ptr) != 0 && '=' == c) ++ptr;
            const char* pvalue = ptr;
            while ((c = *ptr) != 0 && c != '=' && c != '&') ++ptr;
            if (ptr != pvalue) value.assign(pvalue, ptr - pvalue);
        }

        if (!key.empty())
        {
            if (decode_uri)
                key2value[DecodeUri(key, ktmp)] = DecodeUri(value, vtmp);
            else
                key2value[key] = value;
        }
    }
}

void ParamsMap2Str(
        string& str, const map<string, string>& key2value, bool encode_uri)
{
    string ktmp, vtmp;
    bool firstone = true;

    ktmp.reserve(512);
    vtmp.reserve(512);

    typeof(key2value.begin()) it = key2value.begin();
    for (; it != key2value.end(); ++it)
    {
        if (!firstone) str.push_back('&');
        firstone = false;

        if (encode_uri)
            str.append(EncodeUri(it->first, ktmp)).append("=")
                    .append(EncodeUri(it->second, vtmp));
        else
            str.append(it->first).append("=").append(it->second);
    }
}

void CookiesStr2Map(map<string, string>& key2value, const char* str)
{
    if (0 == str || 0 == *str) return;

    const char* ptr = str;
    char c = 0;
    string key, value;

    key.reserve(512);
    value.reserve(512);

    while (*ptr != 0)
    {
        key.clear();
        value.clear();

        while ((c = *ptr) != 0 && (';' == c || ' ' == c)) ++ptr;

        if (c != '=') // have key
        {
            const char* pkey = ptr;
            while ((c = *ptr) != 0 && c != '=' && c != ';' && c != ' ') ++ptr;
            if (ptr != pkey) key.assign(pkey, ptr - pkey);
            while ((c = *ptr) != 0 && ' ' == c) ++ptr;
        }

        if ('=' == c)
        {
            while ((c = *ptr) != 0 && '=' == c || ' ' == c) ++ptr;
            const char* pvalue = ptr;
            while ((c = *ptr) != 0 && c != '=' && c != ';' && c != ' ') ++ptr;
            if (ptr != pvalue) value.assign(pvalue, ptr - pvalue);
        }

        if (!key.empty()) key2value[key] = value;
    }
}

void CookiesMap2Str(
        string& str, const map<string, string>& key2value, bool add_space)
{
    bool firstone = true;

    typeof(key2value.begin()) it = key2value.begin();
    for (; it != key2value.end(); ++it)
    {
        if (!firstone)
        {
            str.push_back(';');
            if (add_space) str.push_back(' ');
        }
        firstone = false;
        str.append(it->first).append("=").append(it->second);
    }
}
