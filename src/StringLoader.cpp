/*
	File: stringloader.cpp
	Project: FullUnlock v4.0
	State: internal
	Purpose: loading localized data from 
			 specially formatted input string
*/
#include "stdafx.h"

extern "C" HRESULT ReadResourceString(wchar_t *Dll, DWORD ResourceID,
                                      wchar_t **Result);

/**
 * Resolve a MUI-style resource reference of the form
 * "@<library>,-<resourceId>" to its localized string, using the current user
 * locale. Falls back to a heap copy of the input when it is not a reference or
 * cannot be resolved.
 *
 * @param s    Resource reference, or a plain string.
 *
 * @return The localized string, or a newly allocated copy of the input as a
 *         fallback (the caller owns the returned buffer).
 */
wchar_t *
GetLocalizedString(wchar_t *s)
{
    __try
    {
        if (s == NULL)
            return NULL;

        if (wcslen(s) > 4)
        {
            if (*s == L'@')
            {
                wchar_t libName[500];
                wcscpy_s(libName, 500, s);
                wchar_t *ln = wcsrchr(libName, L',');
                if (ln)
                {
                    *ln = 0;
                    ln++;
                    ln = wcsrchr(ln, L'-');
                    if (ln)
                    {
                        ln++;
                        wchar_t *hz;
                        int n = wcstoul(ln, &hz, 10);

                        wchar_t *goodLibName = libName;
                        goodLibName++;

                        DWORD locale = GetUserDefaultLCID();
                        wchar_t muiName[500];
                        swprintf(muiName, L"%ls.%04X.mui", goodLibName, locale);

                        BSTR str = NULL;
                        ReadResourceString(muiName, n, &str);
                        if (str == NULL)
                        {
                            ReadResourceString(goodLibName, n, &str);
                        }
                        return str;
                    }
                }
            }
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    wchar_t *fallbackResult = new wchar_t[wcslen(s) + 1];
    memset(fallbackResult, 0, (wcslen(s) + 1) * sizeof(wchar_t));
    wcscpy(fallbackResult, s);
    return fallbackResult;
}
