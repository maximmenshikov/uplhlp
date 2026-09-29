#include "stdafx.h"
#include "adb7.h"

extern "C"
{
    HRESULT CeGetProcessAccount(HANDLE hProcess, PACCTID accountId,
                                DWORD cbSize);
}

/**
 * Return the owning account of a process.
 *
 * @param hProcess    Process handle.
 *
 * @return The account id of the process owner.
 */
ACCTID
GetAccount(HANDLE hProcess)
{
    ACCTID account;
    CeGetProcessAccount(hProcess, &account, sizeof(ACCTID));
    return account;
}

/**
 * Resolve an account id to its SID name via ADB.
 *
 * @param accountID            Account id to resolve.
 * @param lpwszAccountName     Buffer that receives the name.
 * @param dwAccountNameLength  Size of the buffer, in characters.
 *
 * @return TRUE on success, FALSE on failure.
 */
BOOL
GetAccountName(ACCTID accountID, LPWSTR lpwszAccountName,
               DWORD dwAccountNameLength)
{
    DWORD strSize = dwAccountNameLength;
    ACCTID account = accountID;
    if (ADBNameFromAccountID(&account, lpwszAccountName, &strSize) ==
        ERROR_SUCCESS)
        return TRUE;
    return FALSE;
}

/**
 * Resolve an account id to its name and normalize it via ADB.
 *
 * @param accountID            Account id to resolve.
 * @param lpwszAccountName     Buffer that receives the normalized name.
 * @param dwAccountNameLength  Size of the buffer, in characters.
 *
 * @return FALSE. On success the normalized name is written to
 *         lpwszAccountName.
 */
BOOL
GetNormalizedAccountName(ACCTID accountID, LPWSTR lpwszAccountName,
                         DWORD dwAccountNameLength)
{
    ACCTID account = accountID;

    wchar_t name[500];
    DWORD nameLength = 500;
    if (GetAccountName(account, name, nameLength) == TRUE)
    {
        DWORD strSize = dwAccountNameLength;
        ADBNormalizeAccountName(name, lpwszAccountName, &strSize);
    }
    return FALSE;
}

/**
 * Resolve a SID name to its account id via ADB.
 *
 * @param lpwszAccountName    Account SID name.
 *
 * @return The account id, or 0 if it could not be resolved.
 */
ACCTID
Name2AccountID(LPWSTR lpwszAccountName)
{
    ACCTID account = 0;
    ADBAccountIDFromName(lpwszAccountName, &account);
    return account;
}
