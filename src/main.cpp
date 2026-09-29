#include "stdafx.h"
#include "PacmanClient.h"
#include "PolicyMsgQueue.h"
#include "StringLoader.h"
#include "Translation.h"

typedef struct _MESSAGETOASTDATA
{
    ULONGLONG
    appId; // Used for setting the notification glow and retrieving the icon
    PWSTR pszText1;   // Display string
    PWSTR pszText2;   // Display string
    PWSTR pszTaskUri; // Executed when the notification is clicked
    PWSTR
    pszSound; // the event sound that will play when this toast is displayed
} MESSAGETOASTDATA, *LPMESSAGETOASTDATA;

extern "C" HRESULT WINAPI
SHPostMessageToast(LPMESSAGETOASTDATA pMessageToastData);

/**
 * Decode the product id embedded in an account SID of the form
 * "S-1-5-112-0-0X80-0X<hex>": the 76 hex characters after the last 'X' are
 * converted back into the product id string.
 *
 * @param account    Account SID string.
 * @param productID  Buffer that receives the decoded product id string.
 * @param length     Capacity of the buffer, in characters.
 *
 * @return TRUE if a product id was decoded, FALSE otherwise.
 */
BOOL
GetProductID(wchar_t *account, wchar_t *productID, DWORD length)
{
    memset(productID, 0, length * sizeof(wchar_t));
    account = wcsrchr(account, L'X');
    if (account)
    {
        account++;
        if (wcslen(account) >= 76)
        {
            wchar_t s[3];
            s[2] = 0;
            for (int x = 0; x < 76; x += 2)
            {
                s[0] = account[0];
                s[1] = account[1];

                DWORD symbol = wcstoul(s, NULL, 16);
                productID[x / 2] = symbol;
                account += 2;
            }
            return TRUE;
        }
    }
    return FALSE;
    //S-1-5-112-0-0X80-0X7B42353338324442462D303932332D343139352D423638422D4639334237454537364645397D
}

/**
 * Entry point. Waits on the policy message queue; for each ACCESS_DENIED
 * message it resolves the offending application, and for promotable apps posts
 * a localized "requires root access" toast that offers to unlock it.
 *
 * @param argc    Argument count (unused).
 * @param argv    Argument vector (unused).
 *
 * @return 0.
 */
int
_tmain(int argc, _TCHAR *argv[])
{

    HANDLE hMsgQueue = GetPolicyMsgQueue(TRUE);
    if (hMsgQueue)
    {
        while (true)
        {
            if (WaitForSingleObject(hMsgQueue, INFINITE) == 0)
            {
                DWORD dwBytesRead = 0;
                DWORD dwMsgFlags = 0;
                FULLUNLOCK_POLICY_MESSAGE msg;
                if (ReadMsgQueue(hMsgQueue, &msg,
                                 sizeof(FULLUNLOCK_POLICY_MESSAGE),
                                 &dwBytesRead, 5000, &dwMsgFlags) == TRUE)
                {
                    wchar_t productID[100];
                    GetProductID(msg.userAccount, productID, 100);
                    GUID guid;
                    CLSIDFromString(productID, &guid);
                    CApplicationInfo *info = NULL;
                    GetApplicationInfoByProductID(guid, &info);
                    if (info)
                    {
                        if (info->AppInstallType() == 3)
                        {
                            MESSAGETOASTDATA data;
                            data.appId = info->GetAppID();

                            wchar_t *newTitle =
                                GetLocalizedString(info->GetTitle());
                            if (newTitle)
                            {
                                data.pszText1 = newTitle;
                                data.pszText2 =
                                    GetTranslation(RequiresRootAccess);

                                wchar_t uri[2000];
                                swprintf(
                                    uri,
                                    L"app://794eb6ae-b2f9-4bfb-9277-4161e4d9e3f5/_default?promote=%ls&promoteaccess=%ls",
                                    productID, msg.requestedAccess);
                                data.pszTaskUri = uri;
                                data.pszSound =
                                    NULL; //L"\\Windows\\Alarm-01.wma";

                                HRESULT hr = SHPostMessageToast(&data);
                                delete[] newTitle;
                            }
                        }
                        delete info;
                    }
                }
            }
        }
    }
    CloseHandle(hMsgQueue);

    return 0;
}
