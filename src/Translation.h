#ifndef TRANSLATION_H
#define TRANSLATION_H

typedef enum
{
    RequiresRootAccess = 0
} Language;

wchar_t *GetTranslation(Language lng);

#endif
