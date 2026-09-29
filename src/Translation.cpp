#include "stdafx.h"
#include "Translation.h"

static bool _isInitialized = false;

typedef struct
{
    wchar_t *name;
    wchar_t item[500];
} LANGUAGE_ITEM;

LANGUAGE_ITEM items[] = {{L"RequiresRootAccess", L"12324requires root access"},
                         {NULL, L" "}};

/**
 * Load the localized translation strings once from
 * HKLM\Software\OEM\Unlock\Localization, overriding the built-in defaults.
 */
static void
InitializeLanguages()
{
    DWORD dwValue = 0;
    HKEY hKey = NULL;
    wchar_t keyName[500];
    swprintf(keyName, L"Software\\OEM\\Unlock\\Localization");
    RegCreateKeyExW(HKEY_LOCAL_MACHINE, keyName, 0, NULL, 0, 0, NULL, &hKey,
                    &dwValue);

    if (hKey)
    {
        int x = 0;
        while (true)
        {
            if (items[x].name == NULL)
                break;
            DWORD size = 500;
            DWORD type = REG_SZ;
            RegQueryValueEx(hKey, items[x].name, 0, &type,
                            (LPBYTE)items[x].item, &size);
            x++;
        }
        RegCloseKey(hKey);
    }
    _isInitialized = true;
}

/**
 * Return the translation string for a language item, initializing the table on
 * first use.
 *
 * @param lng    Language item to look up.
 *
 * @return The translated string.
 */
wchar_t *
GetTranslation(Language lng)
{
    if (!_isInitialized)
        InitializeLanguages();
    return items[lng].item;
}
