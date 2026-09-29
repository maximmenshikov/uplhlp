//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
///  <file_doc_scope tref="aygshell" />

/*++

Module Name:

    aygshell.h
 
Abstract:

    Shell defines.

--*/

#pragma once

#ifndef __AYGSHELL7_H__
#define __AYGSHELL7_H__


#include <windows.h>
//#include <ole2.h>
//#include <wtypes.h>
#include <shellapi.h>
#include <sipapi.h>
//#include <shime.h>
#include <shlobj.h>
#include <prsht.h>
#include <winuserm.h>
#include <commctrl.h>
#include <commdlg.h>
//#include <changeinfo.h>
//#include <storagecard.h>
//#include <Frame/FrameDataTypes.h>
//#include "vibrate.h"
//#include <ShellPsl.h>
#ifdef __cplusplus
extern "C" {
#endif

// To enable autodoc tags
//@doc

// This event is set when the shell APIs are ready to be called.
#define SHELL_API_READY_EVENT  TEXT("SYSTEM/ShellAPIReady")

// This event is set when the shell window is ready to process messages.
#define SHELL_INIT_EVENT TEXT("SYSTEM/ShellInit")


//#define SHN_FIRST               (0U-1000U)       // Shell reserved
    
#define SHNN_FIRST              (0U-1000U)        // Shell Notifications
#define SHNN_LAST               (0U-1020U)        // Shell Notifications

//#define SHN_LAST                (0U-11000U)

//
// flags in the fdwFlags field of SIPINFO.
// some of these are defined in sipapi.h in the OS.
//
#define SIPF_DISABLECOMPLETION      0x08


//
// Supported system parameters.
//
#ifndef SPI_SETSIPINFO
#define SPI_SETSIPINFO          224
#endif
#define SPI_GETSIPINFO          225
#define SPI_SETCURRENTIM        226
#define SPI_GETCURRENTIM        227
#define SPI_SETCOMPLETIONINFO   223
#define SPI_APPBUTTONCHANGE     228
#define SPI_RESERVED            229
#define SPI_SYNCSETTINGSCHANGE  230


//Pocket PC  special controls
#define WC_SIPPREF    L"SIPPREF"

// BOOL SHGetDocumentsFolder(LPCTSTR pszPath, LPTSTR pszDocs)
// this retrieves the path to the documents directory for
// the volume specified in pszPath.
// return FALSE if there is no such directory (e.g. storage card
// path but no storage card exists
//
// pszDocs is the out parameter and must be at least MAX_PATH long
BOOL SHGetDocumentsFolder(LPCTSTR pszVolume, LPTSTR pszDocs);

//
// SHSipInfo function.
//
WINSHELLAPI
BOOL
SHSipInfo(
    UINT uiAction,
    UINT uiParam,
    PVOID pvParam,
    UINT fWinIni );

BOOL SHInitExtraControls(void);

//++++++
//
// SHInitDialog 
//

typedef struct tagSHINITDLGINFO
{
    DWORD dwMask;
    HWND  hDlg;
    DWORD dwFlags;
} SHINITDLGINFO, *PSHINITDLGINFO;


//
// The functions
//

BOOL SHInitDialog(PSHINITDLGINFO pshidi);

//
// Valid mask values
//

#define SHIDIM_FLAGS                0x0001

//
// Valid flags
//

#define SHIDIF_DONEBUTTON           0x0001
#define SHIDIF_SIZEDLG              0x0002
#define SHIDIF_SIZEDLGFULLSCREEN    0x0004
#define SHIDIF_SIPDOWN              0x0008
#define SHIDIF_FULLSCREENNOMENUBAR  0x0010
#define SHIDIF_EMPTYMENU            0x0020
#define SHIDIF_WANTSCROLLBAR        0x0040
#define SHIDIF_CANCELBUTTON         0x0080

//
// End SHInitDialog
//
//------

HBITMAP SHLoadImageResource(HINSTANCE hinst, UINT uIdGif);
HBITMAP SHLoadImageFile(LPCTSTR pszFileName);

//++++++
//
// Shell Menubar support
//

// Allows menus on softkeys (which have no ID) to be accessed through TB_GETBUTTONINFO/TB_SETBUTTONINFO
// by using an index (0 or 1) and setting TBIF_BYINDEX. 
#ifndef TBIF_BYINDEX
#define TBIF_BYINDEX 0x80000000
#endif

#define NOMENU 0xFFFF
#define IDC_COMMANDBANDS    100

// These defines MUST be < 100.  This is so apps can use these defines
// to get strings from the shell.
#define IDS_SHNEW           1
#define IDS_SHEDIT          2
#define IDS_SHTOOLS         3

//
// Shared New menu support
//
#define  IDM_SHAREDNEW        10
#define  IDM_SHAREDNEWDEFAULT 11
#define  IDM_SHAREDMENU       12

//
// Valid dwFlags
//
#define SHCMBF_EMPTYBAR      0x0001
#define SHCMBF_HIDDEN        0x0002 // create it hidden
#define SHCMBF_HIDESIPBUTTON 0x0004
#define SHCMBF_COLORBK       0x0008
#define SHCMBF_HMENU         0x0010 // specify an hmenu for resource rather than toolbar info
#define SHCMBF_NOACTION      0x0020 // Do not include the shell "Action" menu item in the menu
#define SHCMBF_APPBARRES     0x0040 // specify an APPLICATIONBARRESOURCEDATA resource rather than toolbar info or hmenu
// Do not overlap CABF_* values

// Index of application menu "button"
#define BTTN_MENU       (UINT)-1

typedef struct tagSHMENUBARINFO
{
    DWORD     cbSize;               // IN  - Indicates which members of struct are valid
    HWND      hwndParent;           // IN
    DWORD     dwFlags;              // IN  - Some features we want
    UINT      nToolBarId;           // IN  - Which toolbar are we using
    HINSTANCE hInstRes;             // IN  - Instance that owns the resources
    int       nBmpId;
    int       cBmpImages;           // IN  - Count of bitmap images
    HWND      hwndMB;               // OUT
    COLORREF  clrBk;                // IN  - background color of the menu bar (excluding sip)
} SHMENUBARINFO, *PSHMENUBARINFO;

BOOL  SHCreateMenuBar(SHMENUBARINFO *pmbi);

/****************************************************************************

        SHCMBM_OVERRIDEKEY
            This is used to modify the default handling of key messages sent
            to the soft key control of the foreground app.  
            
            wParam = nVirtkey,
            dwMask = (DWORD)LOWORD(lParam),
            dwBits = (DWORD)HIWORD(lParam)
                SHMBOF_NODEFAULT    0x00000001 // do not do default handling of this key
                SHMBOF_NOTIFY       0x00000002 // send the owner the WM_* messages for this key
                
 ****************************************************************************/

#define SHCMBM_SETSUBMENU   (WM_USER + 400) // wparam == id of button, lParam == hmenu, return is old hmenu
#define SHCMBM_GETSUBMENU   (WM_USER + 401) // lParam == ID
#define SHCMBM_GETMENU      (WM_USER + 402) // get the owning hmenu (as specified in the load resource)
#define SHCMBM_OVERRIDEKEY  (WM_USER + 403)
#define SHCMBM_SETBKCOLOR   (WM_USER + 406) // lParam == COLORREF

// Returns menubar owned by a window
HWND WINAPI SHFindMenuBar(HWND hwnd);


#define SHMBOF_NODEFAULT    0x00000001 // do not do default handling of this key
#define SHMBOF_NOTIFY       0x00000002 // send us the WM_* messages for this key



// Does the default handling of pressing the back button.
void WINAPI SHNavigateBack();


// Enable/disable softkeys by command or index.
// Parameters:
//        hwndMenuBar Handle to the softkey bar as returned from SHCreateMenuBar or SHFindMenuBar
//        uid         The Command ID or index (if bByIndex is set) of the softkey to enable/disable
//        bByIndex    If TRUE, uid is interpreted as an index (0 or 1), otherwise uid is a command ID.
//        bEnable     Set TRUE to enable, FALSE to disable the softkey.
WINSHELLAPI HRESULT  SHEnableSoftkey(HWND hwndMenuBar, UINT uid,  BOOL bByIndex, BOOL bEnable);


//
// End Shell Menubar support
//
//------

//++++++
//
// SHHandleWMActivate and SHHandleWMSettingChange fun
//

typedef struct
{
    DWORD cbSize;
    HWND hwndLastFocus;
    UINT fSipUp :1;
    UINT fSipOnDeactivation :1;
    UINT fActive :1;
    UINT fReserved :29;
} SHACTIVATEINFO, *PSHACTIVATEINFO;

#define SHA_INPUTDIALOG 0x00000001

WINSHELLAPI BOOL SHHandleWMActivate(HWND hwnd, WPARAM wParam, LPARAM lParam, SHACTIVATEINFO* psai, DWORD dwFlags);
WINSHELLAPI BOOL SHHandleWMSettingChange(HWND hwnd, WPARAM wParam, LPARAM lParam, SHACTIVATEINFO* psai);

//
// End SHHandleWMActivate and SHHandleWMSettingChange fun
//
//------


//++++++
//
// SHRecognizeGesture structs
//

typedef struct tagSHRGI {
    DWORD cbSize;
    HWND hwndClient;
    POINT ptDown;
    DWORD dwFlags;
} SHRGINFO, *PSHRGINFO;


//
// Gesture notifications
//
#define  GN_CONTEXTMENU       1000


//
// Gesture flags
//
#define  SHRG_RETURNCMD       0x00000001
#define  SHRG_NOTIFYPARENT    0x00000002
// use the longer (mixed ink) delay timer
// useful for cases where you might click down first, verify you're
// got the right spot, then start dragging... and it's not clear
// you wanted a context menu
#define  SHRG_LONGDELAY       0x00000008 
#define  SHRG_NOANIMATION     0x00000010

//
// Struct sent through WM_NOTIFY when SHRG_NOTIFYPARENT is used
//
typedef struct tagNMRGINFO 
{
    NMHDR hdr;
    POINT ptAction;
    DWORD dwItemSpec;
} NMRGINFO, *PNMRGINFO;

WINSHELLAPI DWORD SHRecognizeGesture(SHRGINFO *shrg);

//
// End SHRecognizeGesture
//
//------



//++++++
//
// SHFullScreen
//

BOOL SHFullScreen(HWND hwndRequester, DWORD dwState);


//
// Valid states
//

#define SHFS_DEFAULT                0x0000
#define SHFS_SHOWTASKBAR            0x0001
#define SHFS_HIDETASKBAR            0x0002
#define SHFS_SHOWSIPBUTTON          0x0004
#define SHFS_HIDESIPBUTTON          0x0008
#define SHFS_SHOWSTARTICON          0x0010
#define SHFS_HIDESTARTICON          0x0020
#define SHFS_SHOWMENUBAR            0x0040
#define SHFS_HIDEMENUBAR            0x0080
#define SHFS_AUTOMENUBAR            0x0100


//
// Menu bar notifications
//
#define MBN_SHOWMENUBAR 1106
#define MBN_HIDEMENUBAR 1107

//
// End SHFullScreen
//
//------


//++++++
//
// SHDoneButton
//

BOOL SHDoneButton(HWND hwndRequester, DWORD dwState);


//
// Valid states
//

#define SHDB_SHOW                   0x0001
#define SHDB_HIDE                   0x0002
#define SHDB_SHOWCANCEL             0x0004


//
// Disable the navigation button bestowed by the Shell
// (NOTE: this only works if WS_CAPTION is not set)

#define WS_NONAVDONEBUTTON WS_MINIMIZEBOX

//
// End SHDoneButton
//
//------


//++++++
//
// SHEnumPropSheetHandlers
//

// this is the maximum number of extension pages that can be added
// to a property sheet

#define MAX_EXTENSION_PAGES 6

// For property sheet extension - enumerates the subkeys under the
// class key hkey.  For each handler, the class is instantiated,
// queried for IShellPropSheetExt and AddPages is called.  The
// handle to the page is inserted in the array prghPropPages, and
// the pointer to the IShellPropSheetExt is added to prgpispse
// with one reference from the caller (these should be released
// by the caller after PropertySheet() is called).  These two arrays
// should be allocated before calling SHEnumPropSheetHandlers.
//
// Typical usage of this function would be:
//
//  - allocate an array of HPROPSHEETPAGEs for the standard pages plus
//    MAX_EXTENSION_PAGES extension pages
//  - fill a PROPSHEETPAGE struct and call CreatePropertySheetPage() on each
//    standard page
//  - store the HPROPSHEETPAGE for the standard pages at the beginning of
//    the array
//  - open a registry key where the app has defined ISV extension
//  - allocate an array of MAX_EXTENSION_PAGES IShellPropSheetExt interface
//    pointers
//  - call SHEnumPropSheetHandlers(), passing in the hkey, a pointer to the
//    first free HPROPSHEETPAGE array element, and a pointer to the array of
//    IShellPropSheetExt interface pointers
//  - call PropertySheet() to display the property sheet
//  - Release each interface pointer in the array of interface pointers
//  - free both arrays

// SHEnumPropSheetHandlers assumes that prghPropPages and prgpispse have been
// allocated with enough space for up to MAX_EXTENSION_PAGES elements.  The
// number of pages added is returned in *pcPages.

BOOL SHEnumPropSheetHandlers(HKEY hkey, int *pcPages, HPROPSHEETPAGE
        *prghPropPages, IShellPropSheetExt **prgpispse);

//
// End SHEnumPropSheetHandlers
//
//------


//++++++
//
// SHLoadContextMenuExtensions
//
//    Loads context menu extensions from handlers listed in the registry for
//    the context/class pair specified.  Menu items are added to hmenu in the
//    range [idCmdFirst, idCmdLast].  A handle to the context menu extensions
//    abstraction object is returned in *phCMExtensions.  It must be freed by
//    a call to SHFreeContextMenuExtensions.

BOOL SHLoadContextMenuExtensions(IUnknown *punkOwner, LPCTSTR pszContext,
    LPCTSTR pszClass, HMENU hmenu, UINT idCmdFirst, UINT idCmdLast,
    HANDLE *phCMExtensions);

//
// End SHLoadContextMenuExtensions
//
//------


//++++++
//
// SHInvokeContextMenuCommand
//
//    Invokes a command from a context menu.  Issues the command in the
//    extension that added it to the menu.

BOOL SHInvokeContextMenuCommand(HWND hwndOwner, UINT idCmd,
        HANDLE hCMExtensions);

//
// End SHInvokeContextMenuCommand
//
//------


//++++++
//
// SHFreeContextMenuExtensions
//

//    Releases memory allocated for context menu processing.

BOOL SHFreeContextMenuExtensions(HANDLE hCMExtensions);

//
// End SHFreeContextMenuExtensions
//
//------


//++++++
//
//  SHGetEmergencyCallList
//
//       Gets a list of emergency calls

HRESULT SHGetEmergencyCallList(TCHAR *pwszBuffer, UINT uLenBuf);

//
// End SHGetEmergencyCallList
//
//------


//////////////////////////////////////////////////////////////////////////////
//
// Input Context API
//
// These are definitions and APIs for the interacting with the input context
// properties of individual windows
//
// {

// Word correct Options
enum SHIC_FEATURE
{
    SHIC_FEATURE_RESTOREDEFAULT       = 0,
    SHIC_FEATURE_AUTOCORRECT          = 0x00000001L,
    SHIC_FEATURE_AUTOSUGGEST          = 0x00000002L,
    SHIC_FEATURE_HAVETRAILER          = 0x00000003L,
    SHIC_FEATURE_SPELLCHECK           = 0x00000004L,
    SHIC_FEATURE_CANDONDEMAND         = 0x00000005L,
    SHIC_FEATURE_AUTOCAPITALIZE       = 0x00000006L,
    SHIC_FEATURE_AUTOAPOSTROPHE       = 0x00000007L,
    SHIC_FEATURE_AUTOACCENT           = 0x00000008L,
    SHIC_FEATURE_PERIODSHORTCUT       = 0x00000009L,
    SHIC_FEATURE_PRIVATE              = 0x0000000aL,
    SHIC_FEATURE_AUTOCORRECTFIRSTWORD = 0x0000000bL,
    SHIC_FEATURE_CLASS                = 0x00000010L,
    SHIC_FEATURES_RAW                 = 0x00000020L
};

typedef enum SHIC_FEATURE SHIC_FEATURE;

// Predefined input context classes
#define SHIC_CLASS_DEFAULT              TEXT("")
#define SHIC_CLASS_EMAIL                TEXT("email")
#define SHIC_CLASS_URL                  TEXT("url")
#define SHIC_CLASS_PHONE                TEXT("phone")
#define SHIC_CLASS_NAME                 TEXT("name")
#define SHIC_CLASS_PHONE_AND_EMAIL      TEXT("phoneAndEmail")
#define SHIC_CLASS_MAXLEN               (MAX_PATH - 11)

//@topic Input Context Features |
// The input context API supports the following features and their corresponding values:
//
//@flag   SHIC_FEATURE_RESTOREDEFAULT   | Restore original input context state. (no corresponding value)
//@flag   SHIC_FEATURE_AUTOCORRECT      | Turn auto-corrections on and off. (TRUE, FALSE)
//@flag   SHIC_FEATURE_AUTOSUGGEST      | Turn dictionary suggestions on and off. (TRUE, FALSE)
//@flag   SHIC_FEATURE_HAVETRAILER      | Specify whether to append trailer characters after replacing words.
//                                      (TRUE, FALSE)
//@flag   SHIC_FEATURE_SPELLCHECK       | Turn spell-check feature on and off (TRUE, FALSE)
//@flag   SHIC_FEATURE_CANDONDEMAND     | Turn candidates-on-demand on and off (TRUE, FALSE)
//@flag   SHIC_FEATURE_AUTOCAPITALIZE   | Turn auto-capitalization on and off (TRUE, FALSE)
//@flag   SHIC_FEATURE_AUTOAPOSTROPHE   | Enables or disables the automatic insertion of apostrophe (TRUE, FALSE)
//@flag   SHIC_FEATURE_AUTOACCENT       | Turn the auto-accent feature on and off (TRUE, FALSE)
//@flag   SHIC_FEATURE_PERIODSHORTCUT   | Turn on or off feature that translates two spaces following
//                                        a word into a period and a space.
//@flag   SHIC_FEATURE_PRIVATE          | Sets the private attribute for a control which prevents text from
//  
//@flag   SHIC_FEATURE_AUTOCORRECTFIRSTWORD | Allows auto-correction for first words in the sentence 
//                                            (First letter is upper-case)
//@flag   SHIC_FEATURES_RAW             | Only for use with SHGetInputContext - causes the raw bitmap of
//                                        all feature settings (except class) to be returned.
//@flag   SHIC_FEATURE_CLASS            | Make this control behave like a specific semantic type.
//                                      (SHIC_CLASS_DEFAULT, SHIC_CLASS_EMAIL, SHIC_CLASS_URL,
//                                      SHIC_CLASS_PHONE, SHIC_CLASS_NAME, SHIC_CLASS_PHONE_AND_EMAIL)
//
//@comm All SHIC_FEATUREs are inherited from parent if undefined. That is, if they are not defined in
//      a window or the window's SHIC class, the API looks at the parent chain to find the setting
//      that applies to the window.
//
//@xref <f SHSetInputContext> <f SHGetInputContext>
//


//++++++
//
//@func HRESULT | SHSetInputContext | Changes the state of an input context feature
//
//@parm HWND            | hwnd      | IN - Window whose context will be set
//@parm DWORD           | dwFeature | IN - Input context feature to change
//@parm const LPVOID    | lpValue   | IN - New value assigned to feature
//
//@rdesc Returns one of the following values:
//@flag S_OK                    | If everything went well
//@flag ERROR_INVALID_PARAMETER | if hwnd was NULL or lpValue was NULL for a feature
//                                that does not support it, such as SHIC_FEATURE_AUTOCORRECT,
//                                SHIC_FEATURE_AUTOCOMPLETE and SHIC_FEATURE_HAVETRAILER.
//@flag ERROR_NOT_SUPPORTED     | If the feature specified was invalid
//@flag ERROR_INVALID_DATA      | If the specified value is not a legal option
//
//@xref <l Input_Context_Features> <f SHGetInputContext>
//

HRESULT SHSetInputContext( HWND hwnd, DWORD dwFeature, const LPVOID lpValue );

//
// End SHSetInputContext
//
//------


//++++++
//
//@func HRESULT | SHGetInputContext | Retrieves current state of an input context feature
//
//@parm HWND    | hwnd      | IN - Window whose context will be retrieved
//@parm DWORD   | dwFeature | IN - Input context feature to retrieve
//@parm LPVOID  | lpValue   | OUT - Buffer to hold current value of feature
//@parm LPDWORD | pdwSize   | IN/OUT - size of the buffer passed in to retrieve the value
//
//@rdesc Returns one of the following values:
//@flag S_OK                        | If everything went well
//@flag ERROR_INVALID_PARAMETER     | If hwnd or lpdwSize passed were NULL
//@flag ERROR_NOT_SUPPORTED         | If the feature specified was invalid
//@flag ERROR_INSUFFICIENT_BUFFER   | If buffer passed is too small
//
//@comm Retrieves the current state/value of the specified
//      input context feature. If the value is not explicitly set, it
//      looks at the features set by the context class. If no class was
//      set explicitly, or the class didn't set that value, it returns
//      the default value for that feature, which would be the
//      currently active one.
//      If lpValue is NULL and lpdwSize is not NULL, it returns the
//      size of the buffer needed in lpdwSize.
//
//@xref <l Input_Context_Features> <f SHSetInputContext>
//

HRESULT SHGetInputContext( HWND hwnd, DWORD dwFeature, LPVOID lpValue, LPDWORD lpdwSize );


//
// End SHGetInputContext
//
//------


// }
//
// end Input Context API
//
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
//
// SHUIMETRICS - UI Metrics that applications might be interested in
//
// These are definitions and APIs for Shell UI Metrics
//
// {

// Call RegisterWindowMessage on this string if you are interested in knowing when UI Metrics have changed
// wParam will be 0, lParam will be one of the SHUIMETRICTYPE values to indicate what value has changed.  
// Call SHGetUIMetrics to find out the new value if interested
#define SH_UIMETRIC_CHANGE    TEXT("SH_UIMETRIC_CHANGE")

// Enumeration of metrics you can ask for
typedef enum tagSHUIMETRIC
{
    SHUIM_INVALID = 0,    // Illegal

    // Note that you will receive a notification for SHUIM_FONTSIZE_POINT when one of these three values changes
    SHUIM_FONTSIZE_POINT,       // Application font size (hundredhts of a point) -- buffer is pointer to DWORD
    SHUIM_FONTSIZE_PIXEL,       // Application font size (in pixels) -- buffer is pointer to DWORD
    SHUIM_FONTSIZE_PERCENTAGE,  // Application font size as percentage of normal -- buffer is pointer to DWORD
} SHUIMETRIC;
 
HRESULT SHGetUIMetrics(SHUIMETRIC shuim, PVOID pvBuffer, DWORD cbBufferSize, DWORD *pcbRequired);

// }
//
// end Shell UI Metrics
//
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//
// SHNAPI - Shell Notification API
//
// These are definitions and APIs for the Shell Notifications system
//
// {

// formerly in the Windows Mobile shlobj.h
// FILECHANGEINFO defined in changeinfo.h

#define WM_FILECHANGEINFO   (WM_APP + 0x101)

typedef struct tagFILECHANGENOTIFY {
    DWORD dwRefCount;
    FILECHANGEINFO fci;
} FILECHANGENOTIFY;

typedef struct tagSHCHANGENOTIFYENTRY {
    DWORD   dwEventMask;    // Events to watch
    LPTSTR  pszWatchDir;    // Directory or root for the events we want. NULL means all.
    BOOL    fRecursive;     // Indicates whether look just for pszWatchDir or recursively.
} SHCHANGENOTIFYENTRY;


// These were explicitly removed from shlobj.h
BOOL WINAPI SHChangeNotifyRegister( HWND hwnd, SHCHANGENOTIFYENTRY *pshcne);
BOOL WINAPI SHChangeNotifyDeregister( HWND hwnd );
void WINAPI SHChangeNotifyFree( FILECHANGENOTIFY *pfcn );


// notification priority

typedef enum _SHNP
{
    SHNP_INFORM = 0x1B1,    // deprecated
    SHNP_ICONIC,
} SHNP;


// notification update mask
#define SHNUM_PRIORITY      0x0001
#define SHNUM_DURATION      0x0002
#define SHNUM_ICON          0x0004
#define SHNUM_HTML          0x0008
#define SHNUM_TITLE         0x0010
#define SHNUM_SOFTKEYS      0x0020
#define SHNUM_TODAYKEY      0x0040
#define SHNUM_TODAYEXEC     0x0080
#define SHNUM_SOFTKEYCMDS   0x0100
#define SHNUM_FLAGS         0x0200
#define SHNUM_NOTIFTEXT     0x0400
#define SHNUM_NOTIFICON     0x0800
#define SHNUM_SKTITLE       0x1000
#define SHNUM_OCCUR         0x2000
#define SHNUM_LAST_VALUE__  SHNUM_OCCUR  // mask guard, internal

// notification data

// TODO: remove ///////////////
    #define NOTIF_NUM_SOFTKEYS 2
    typedef struct _SOFTKEYCMD
    {
        WPARAM wpCmd;
        DWORD grfFlags;
    } SOFTKEYCMD;
    typedef struct _SOFTKEYNOTIFY
    {
        LPCTSTR pszTitle;
        SOFTKEYCMD skc;
    } SOFTKEYNOTIFY;

    typedef struct _SOFTKEYMENU
    {
        HMENU   hMenu;
        SOFTKEYCMD *prgskc;
        UINT    cskc;
    } SOFTKEYMENU;
///////////////////////////////

typedef struct _SHNOTIFICATIONDATA
{
    DWORD        cbStruct;      // for verification and versioning
    DWORD        dwID;          // identifier for this particular notification
    SHNP         npPriority;    // priority
    DWORD        csDuration;    // duration of the notification (usage depends on prio)
    HICON        hicon;         // the icon for the notification
    DWORD        grfFlags;      // flags - see SHNF_ flags below
    CLSID        clsid;         // unique identifier for the notification class
    HWND         hwndSink;      // window to receive command choices, dismiss, etc.
    LPCWSTR      pszHTML;       // HTML content for the bubble
    LPCWSTR      pszTitle;      // Optional title for bubble
    LPARAM       lParam;        // User-defined parameter
    LPCWSTR *    rgszText;      // Multi-line notification text (array of LPCWSTR strings).
    DWORD        cTextSize;     // Number of lines in the multi-line notification text (size of rgszText array)
    HICON        hNotifIcon;    // Icon that gives a visual context to the notification.
                                // This icon is displayed in the notification UI.
    LPCWSTR      pszSkTitle;    // SK1 title.  Represents an action that can be performed with the notification.
    DWORD        cOccurrences;  // Number of times the event that this notification represents has occurred.
} SHNOTIFICATIONDATA, *PSHNOTIFICATIONDATA;

typedef struct _SHNOTIFICATIONID
{
    CLSID   clsid;
    DWORD   dwID;
} SHNOTIFICATIONID;

// Flags

// For SHNP_INFORM priority and above, don't display the notification bubble
// when it's initially added; the icon will display for the duration then it
// will go straight into the tray.  The user can view the icon / see the
// bubble by opening the tray.
#define SHNF_STRAIGHTTOTRAY  0x00000001

// Critical information - highlights the border and title of the bubble.
#define SHNF_CRITICAL        0x00000002

// Force the message (bubble) to display even if settings says not to.
#define SHNF_FORCEMESSAGE    0x00000008

// Force the display to turn on for notification.
#define SHNF_DISPLAYON       0x00000010

// Force the notification to be silent and not vibrate, regardless of Settings
#define SHNF_SILENT          0x00000020

// Softkey bar is created from an HMENU passed in skm structure 
#define SHNF_HASMENU         0x00000040

// Draw the current time with the title
#define SHNF_TITLETIME       0x00000080

// A notification with "stack" support
#define SHNF_SPINNERS        0x00000100

// RE-play physical alerts on an update
#define SHNF_ALERTONUPDATE   0x00000200

// Capture the VK_TTALK button and forward it to the notification's sink window
#define SHNF_WANTVKTTALK     0x00000400

// Last value for the SHNF.  Internal.  Used for validation.
#define SHNF_LASTVALUE__    SHNF_WANTVKTTALK

// notification message and codes for window-based notification
// the notification's dwID is in hdr.idFrom

#pragma warning(push)
#pragma warning(disable:4201)   // nameless struct/union

typedef struct _NMSHN
{
    NMHDR   hdr;
    LPARAM lParam;
    DWORD dwReturn;
    union
    {
        LPCTSTR pszLink;
        BOOL    fTimeout;
        POINT   pt;
    };
} NMSHN;
#pragma warning(pop)

#define SHNN_LINKSEL            (SHNN_FIRST-0)
// nmshn.pszLink contains the link text of the choice that was selected

#define SHNN_DISMISS            (SHNN_FIRST-1)
// nmshn.fTimeout is TRUE if duration expired, FALSE if user tapped away

#define SHNN_SHOW               (SHNN_FIRST-2)
// nmshn.pt contains the point to which the bubble points

#define SHNN_NAVPREV            (SHNN_FIRST-3)
// Toast stack left spinner clicked / DPAD LEFT

#define SHNN_NAVNEXT           (SHNN_FIRST-4)
// Toast stack right spinner clicked / DPAD RIGHT

#define SHNN_ACTIVATE           (SHNN_FIRST-5)
// Toast DPAD Action

#define SHNN_ICONCLICKED        (SHNN_FIRST-6)
// nmshn.pt contains the point where the user clicked

#define SHNN_HOTKEY             (SHNN_FIRST-7)
// A hotkey has been pressed - modifiers are in the loword of the nmshn.lParam, 
// the virtual key code is in the hiword.
// If the sink window returns 0 in response to this notification, then
// the notification toast will be hidden and VK_TTALK key default behavior
// will be performed.

//===========================================================================
//
// Interface: IShellNotificationCallback
//
//  The IShellNotificationCallback interface is used by the Shell to advise
// the notification owner of actions taken on the notification.
//
// [Member functions]
//
// IShellNotificationCallback::OnShow
//
//  Reserved.  Return E_NOTIMPL.
//
// IShellNotificationCallback::OnCommandSelected
//
//  This member function is called when the user selects a link of the form
// <A HREF="cmd:#">link</A>.
//
//  Parameters:
//   dwID       -- the identifier of the notification
//   wCmdID     -- this is the # in the link
//
// IShellNotificationCallback::OnLinkSelected
//
//  This member function is called when the user selects one of the action
// choice links in the notification bubble window.
//
//  Parameters:
//   dwID       -- the identifier of the notification
//   pszLink    -- the link content that was selected
//   lParam     -- the lParam of the notification
//
// IShellNotificationCallback::OnDismiss
//
//  This member function is called when the user taps away from the bubble
// window or if a SHNP_INFORM priority notification's duration expires.
//
//  Parameters:
//   dwID       -- the identifier of the notification
//   fTimeout   -- the notification timed out (SHNP_INFORM only)
//   lParam     -- the lParam of the notification
//   
//===========================================================================

#undef  INTERFACE
#define INTERFACE   IShellNotificationCallback

DECLARE_INTERFACE_(IShellNotificationCallback, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** IShellNotificationCallback methods ***
    STDMETHOD(OnShow)(THIS_ DWORD dwID, POINT pt, LPARAM lParam) PURE;
    STDMETHOD(OnCommandSelected)(THIS_ DWORD dwID, WORD wCmdID)
        PURE;
    STDMETHOD(OnLinkSelected)(THIS_ DWORD dwID, LPCTSTR pszLink, LPARAM lParam)
        PURE;
    STDMETHOD(OnDismiss)(THIS_ DWORD dwID, BOOL fTimeout, LPARAM lParam) PURE;
};


// SHNotificationAdd
//
//   Add a notification.

LRESULT SHNotificationAdd(SHNOTIFICATIONDATA const * pndAdd);

// SHNotificationUpdate
//
//   Update aspects of a pending notification.

LRESULT SHNotificationUpdate(DWORD grnumUpdateMask, SHNOTIFICATIONDATA const * pndNew);

// SHNotificationRemove
//
//   Remove a notification.  This is usually in reponse to some
//   action taken on the data outside of the notification system - for example
//   if a message is read or deleted.

LRESULT SHNotificationRemove(const CLSID *pclsid, DWORD dwID);

// SHNotificationGetData
//
//   Get the data for a notification.  Used by a handler to get information
//   stored in the notification by the poster.

LRESULT SHNotificationGetData(CLSID const * pclsid, DWORD dwID, SHNOTIFICATIONDATA * pndBuffer);

// SHNotificationGetAll
//
//  Get all notifications.

LRESULT SHNotificationGetAll(SHNOTIFICATIONID ** prgNotif, DWORD * pdwCount);

// SHNotificationFreeData
//
//  Free the resources that SHNOTIFICATIONDATA structure contains

LRESULT SHNotificationFreeData(SHNOTIFICATIONDATA * pnd);

// SHNotificationUserAction
//
//  Notifies the sink window of the notification of the user action.

LRESULT SHNotificationUserAction(REFCLSID clsid, DWORD dwID);

//++++++
//
// GetOpenFileNameEx
//
//  This function extends the GetOpenFileName provided by WinCE to support our Thumbnail view and provide support
//  for other extensions not supported by default in WinCE

//
// Sort order
//
typedef enum tagOFN_SORTORDER
{
   OFN_SORTORDER_AUTO,
   OFN_SORTORDER_DATE,
   OFN_SORTORDER_NAME,
   OFN_SORTORDER_SIZE,
   OFN_SORTORDER_ASCENDING = 0x00008000

} OFN_SORTORDER;

//
// Extended Flags  
//
typedef enum tagOFN_EXFLAG
{
    OFN_EXFLAG_EXPLORERVIEW                      = 0x00000000,
    OFN_EXFLAG_DETAILSVIEW                       = 0x00000001,
    OFN_EXFLAG_THUMBNAILVIEW                     = 0x00000002,
    OFN_EXFLAG_MESSAGING_FILE_CREATE             = 0x00000004,
    OFN_EXFLAG_CAMERACAPTURE_MODE_VIDEOONLY      = 0x00000008,
    OFN_EXFLAG_CAMERACAPTURE_MODE_VIDEOWITHAUDIO = 0x00000010,
    OFN_EXFLAG_CAMERACAPTURE_MODE_VIDEODEFAULT   = 0x00000020,
    OFN_EXFLAG_LOCKDIRECTORY                     = 0x00000100,
    OFN_EXFLAG_NOFILECREATE                      = 0x00000200,
} OFN_EXFLAG;


typedef struct tagOPENFILENAMEEX
{
    // Fields which map to OPENFILENAME
   DWORD        lStructSize;
   HWND         hwndOwner;
   HINSTANCE    hInstance;
   LPCTSTR      lpstrFilter;
   LPTSTR       lpstrCustomFilter;
   DWORD        nMaxCustFilter;
   DWORD        nFilterIndex;
   LPTSTR       lpstrFile;
   DWORD        nMaxFile;
   LPTSTR       lpstrFileTitle;
   DWORD        nMaxFileTitle;
   LPCTSTR      lpstrInitialDir;
   LPCTSTR      lpstrTitle;
   DWORD        Flags;
   WORD         nFileOffset;
   WORD         nFileExtension;
   LPCTSTR      lpstrDefExt;
   LPARAM       lCustData;
   LPOFNHOOKPROC lpfnHook;
   LPCTSTR      lpTemplateName;

   // Extended fields
   DWORD       dwSortOrder;
   DWORD       ExFlags;
}OPENFILENAMEEX, *LPOPENFILENAMEEX ;


//
// The functions
//

BOOL GetOpenFileNameEx(LPOPENFILENAMEEX lpofnex);

//
// End GetOpenFileNameEX
//
//------

// }
//
// end SHNAPI
//
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//
// DrawFocusRectColor
//
// Draw a rectangle in the style and color used to indicate that the rectangle has
// the focus, respecting the current theme.
//

#define DFRC_FOCUSCOLOR             0  // Draw using focus color for current theme
#define DFRC_SELECTEDBRUSH          1  // Draw using selected brush (can be used for erasing)


BOOL DrawFocusRectColor(HDC hdc, const RECT* lprc, UINT uFlags);

//
// end DrawFocusRectColor
//
//////////////////////////////////////////////////////////////////////////////


// For use with SHIdleTimerResetEx
//0x00000001  - no longer in use
//0x00000002  - no longer in use
#define FLUSH_SESSION   0x00000004  // reset flush session timer
#define IDLE_SESSION    0x00000008  // reset system idle timer (call SystemIdleTimerReset)

// Reset shell's idle timer
void WINAPI SHIdleTimerReset();

// SHIdleTimerResetEx
// 
// Parameters
// dwFlags
//   [in] Specifies which shell session timer should be reset. On Smartphone, this parameter can be any
//    combination of the following values.  
//   FLUSH_SESSION - reset flush session timer
//   IDLE_SESSION - reset the system idle timer
// Return Values
//      S_OK on success
HRESULT WINAPI SHIdleTimerResetEx(DWORD dwFlags);

// ExitWindowsEx : Shuts down the system.
//
BOOL ExitWindowsEx(
  UINT uFlags,       // shutdown operation
  DWORD dwReserved   // reserved
);
// Parameters
// uFlags 
//  [in] Specifies the type of shutdown. This parameter must be one of the following values. 
//      EWX_POWEROFF - Shuts down the system and turns off the power. (not supported on PocketPC)
//      EWX_REBOOT - Shuts down the system and reboots
//
//      The following modifiers can be OR'd in with EWX_REBOOT to modify its behavior
//      EWX_DEFER  - Reboot will be deferred until it is safe
//      EWX_PROMPT - User will be prompted before a reboot
// dwReserved 
//  [in] Reserved; this parameter is ignored.
// Return Values
//  If the function succeeds, the return value is nonzero. If the function fails, the return value is zero. 
//
// Remarks
//  The ExitWindowsEx function returns as soon as it has initiated the shutdown. The shutdown then proceeds asynchronously. 

//////////////////////////////////////////////////////////////////////////////
//
// Flags for camera capture UI

/// <summary>
/// This is the enumerator for photo quality
/// </summary>
/// <remarks>
///
/// </remarks>
typedef enum
{
    CAMERACAPTUREEX_PHOTO_QUALITY_DEFAULT = 0,
    CAMERACAPTUREEX_PHOTO_QUALITY_BASIC,
    CAMERACAPTUREEX_PHOTO_QUALITY_NORMAL,
    CAMERACAPTUREEX_PHOTO_QUALITY_FINE,
    CAMERACAPTUREEX_PHOTO_QUALITY_SUPERFINE,
} CAMERACAPTUREEX_PHOTO_QUALITY;

/// <summary>
/// This is the enumerator for file type
/// </summary>
/// <remarks>
///
/// </remarks>
typedef enum
{
    CAMERACAPTUREEX_FILE_TYPE_ALL       = 0x00,
    CAMERACAPTUREEX_FILE_TYPE_STANDARD  = 0x01,
    CAMERACAPTUREEX_FILE_TYPE_MESSAGING = 0x02,
} CAMERACAPTUREEX_FILE_TYPE;


/// <summary>
/// This is the enumerator for capture modes
/// </summary>
/// <remarks>
///
/// </remarks>
typedef enum
{
    CAMERACAPTUREEX_CAPTURE_MODE_PHOTO = 0x01,
    CAMERACAPTUREEX_CAPTURE_MODE_VIDEO = 0x02,
} CAMERACAPTUREEX_CAPTURE_MODE;

/// <summary>
/// This is the enumerator for audio option
/// </summary>
/// <remarks>
///
/// </remarks>
typedef enum
{
    CAMERACAPTUREEX_AUDIO_OPTION_FREE = 0,
    CAMERACAPTUREEX_AUDIO_OPTION_ON,
    CAMERACAPTUREEX_AUDIO_OPTION_OFF,
} CAMERACAPTUREEX_AUDIO_OPTION;

/// <summary>
/// This is the extended version of SHCAMERACAPTURE structure that
/// used to configure the behavior of camera
/// </summary>
/// <list>
///   <item>
///     <term>DWORD cbSize</term>
///     <description>The size of SHCAMERACAPTUREEX structure in bytes</description>
///   </item>
///   <item>
///     <term>HWND hwndOwner</term>
///     <description>A handle to the owner window. Can be NULL</description>
///   </item>
///   <item>
///     <term>TCHAR szFile[MAX_PATH]</term>
///     <description>
///       The fully-qualified path-name of the captured photo file or video file if
///       the photo or video has been successfully captured.
///     </description>
///   </item>
///   <item>
///     <term>LPCTSTR pszDir</term>
///     <description>
///       Specifies the directory for storing the captured photo or video file. If
///       this parameter is NULL, the captured file will be saved to a camera app preferred
///     </description>
///   </item>
///   <item>
///     <term>LPCTSTR pszFileName</term>
///     <description>
///       Specifies the file name, not include the suffix, for the captured photo
///       or video clip. If the file already exists and it is not read-only file,
///       it will be overwritten; if the file name is not specified by the caller,
///       a camera app perferred file name will be used. 
///       Note: The combination of pszDir and pszFileName must not exceed 256 characters.
///     </description>
///   </item>
///   <item>
///     <term>LPCTSTR pszTitle</term>
///     <description>
///       The title will be used as the title when create the main window. 
///       Note: since camera is full screen app, the title won't be displayed. the caller
///       can use this title to distinguish different camera API windows.
///     </description>
///   </item>
///   <item>
///     <term>CAMERACAPTUREEX_PHOTO_QUALITY PhotoQuality</term>
///     <description>
///       One of the CAMERACAPTUREEX_PHOTO_QUALITY enumeration values, which specifies
///       the quality of the captured photo.
///     </description>
///   </item>
///   <item>
///     <term>DWORD dwFileTypes</term>
///     <description>
///       This is the bit mask of CAMERACAPTUREEX_FILE_TYPE enumeration values, which
///       specifies a file type.
///       For example, whether the file is suitable to be used by an MMS application.
///     </description>
///   </item>
///   <item>
///     <term>dwResolutionWidth</term>
///     <description>
///       The image width, in pixels. When dwResolutionWidth equals 0, means any width
///       is acceptable.
///     </description>
///   </item>
///   <item>
///     <term>DWORD dwResolutionHeight</term>
///     <description>
///       The image height, in pixels. When dwResolutionHeight equals 0, means any
///       height is acceptable
///     </description>
///   </item>
///   <item>
///     <term>DWORD dwVideoTimeLimit</term>
///     <description>
///       The maximum length of time in seconds, allowed for a video clip. 0 indicates
///       that there is no limitation.
///     </description>
///   </item>
///   <item>
///     <term>DWORD dwModes</term>
///     <description>
/// This is the bit mask of the capture CAMERACAPTUREEX_CAPTURE_MODE. if both video and photo
/// bit are set, camera API will have both photo and video mode available.
///     </description>
///   </item>
///   <item>
///     <term>DWORD dwInitialMode</term>
///     <description>
///       If both CAMERACAPTUREEX_MODE_PHOTO and CAMERACAPTUREEX_MODE_VIDEO are set
///       in Modes, the InitialMode must be either CAMERACAPTUREEX_MODE_PHOTO or
///       CAMERACAPTUREEX_MODE_VIDEO;
///       if only one of CAMERACAPTUREEX_MODE_PHOTO or CAMERACAPTUREEX_MODE_VIDEO
///       is set in Modes, the InitialMode will be ignored.
///     </description>
///   </item>
///   <item>
///     <term>CAMERACAPTUREEX_AUDIO_OPTION AudioOption</term>
///     <description>
///       One of the CAMERACAPTUREEX_AUDIO_OPTION enumeration values, which specifies
///       whether audio will be included in video clip. 
///     </description>
///   </item>
///   <item>
///     <term>DWORD fPostCaptureScreen</term>
///     <description>
///       Specify if the post capture screen is needed; 0 mean no post capture screen;
///       other value means have post capture screen.
///     </description>
///   </item>
/// </list>
typedef struct tagSHCAMERACAPTUREEX
{
    DWORD cbSize;
    HWND hwndOwner;
    TCHAR szFile[MAX_PATH];
    LPCTSTR pszDir;
    LPCTSTR pszFileName;
    LPCTSTR pszTitle;
    CAMERACAPTUREEX_PHOTO_QUALITY PhotoQuality;
    DWORD dwFileTypes;
    DWORD dwResolutionWidth;
    DWORD dwResolutionHeight;
    DWORD dwVideoTimeLimit;
    DWORD dwModes;
    DWORD dwInitialMode;
    CAMERACAPTUREEX_AUDIO_OPTION AudioOption;
    BOOL fPostCaptureScreen;
}SHCAMERACAPTUREEX, *PSHCAMERACAPTUREEX;

/// <summary>
/// The second version of API to invoke the camera capture dialog. Itis a stub now.
/// </summary>
/// <param name="pshcc">structure used to configure the behavior of camera </param>
/// <returns>
/// E_NOTIMPL.
/// </returns>
/// <remarks>
///
/// </remarks>

HRESULT SHCameraCaptureEx (PSHCAMERACAPTUREEX pshcc);

//
// end of flags for camera capture UI
//
//////////////////////////////////////////////////////////////////////////////


/// <summary>
/// Adjust the power timeout when the device is locked/unlocked.
/// </summary>
/// <param name="dwTimeout">timeout to set in seconds. If 0 then default value is assumed</param>
/// <remarks>
/// This API is used to adjust the power timeout when the device is
/// locked. It is called by the Shell when locking and
/// unlocking the device
/// </remarks>
HRESULT SHSetPowerTimeoutForLock(DWORD dwTimeout);

//////////////////////////////////////////////////////////////////////////////
//
// IsMatchFromKeyMap
//
// Given a filter string, text string, and matching options, IsMatchFromKeyMap
// determines if there is a way to match the two strings using one or more of the
// mappings configured on the device.  In case of a possible match, IsMatchFromKeyMap
// can optionally output data about what was matched.
//
// Parameters:
//  pszFilter
//   [in] String containing search filter to use.
//  pszText
//   [in] String containing text to apply pszFilter to.
//  dwFlags
//   [in] Bit flags specifying how to perform the matching.
//  cMatchBufferLengths
//   [in] Minimum count of elements in prgbMatchCounts and pszMatchedText if they're non-NULL
//  prgbMatchCounts
//   [out] Optional pointer to an array of at least cMatchBufferLengths BYTEs.
//         If pszFilter and pszText match then prgbMatchCounts[i] is the number of contiguous
//         characters matched starting from pszText[i].
//  pszMatchedText
//   [out] Optional pointer to an array of at least cMatchBufferLengths TCHARs.
//         If pszFilter and pszText match then pszMatchedText will be a string representing what matched.
//
// Return Value:
//  TRUE if the strings match.
//  FALSE otherwise.
//
// Remarks:
//
//   IsMatchFromKeyMap uses one or more of the following mappings to match the strings:
//     Hardware keyboard mappings
//     Phone keypad mappings (e.g. 2:abc, 3:def, etc.)
//     Equivalence mappings (e.g. case, width, kana-type, and accent insensitive matching)
//
//   IsMatchFromKeyMap may also use one or more of the following advanced matching features:
//     Wildcard (note that the default wildcard character is '1' but can be changed/disabled by the OEM)
//     Delimited matching (e.g. match "Barry Johnson" with a filter string of "b john")
//     Skippable characters matching (e.g. match "Vlatka Juric-Sedic" with a filter string of "juricsed")
//     Wraparound matching (e.g. match "Johnson, Barry" with a filter string of "barryj"
//
//   The very first time IsMatchFromKeyMap is called for a process may take longer to return
//   than subsequent calls because internal data initialization is required the first time
//   this function is called.  If this delay on first match session is noticeable with your
//   application, try calling IsMatchFromKeyMap(_T(""), _T(""), 0, 0, NULL, NULL)
//   at an appropriate time before the user starts inputting a filter string.
//
//   pszFilter only supports up to KEYMAP_CCH_MAXFILTER TCHARs
//   pszText only supports up to KEYMAP_CCH_MAXTEXT TCHARs
//   dwFlags can be any KEYMAP_IMF_* value
//   cMatchBufferLengths should at least be as large as the length of pszText + 1 for a terminating NULL
//
//   Here are some example matching scenarios of what prgbMatchCounts and pszMatchedText will contain
//   when using dwFlags of KEYMAP_IMF_NAME | KEYMAP_IMF_NOKEYBOARDMAPPINGS:
//
//     A filter of "jo" against a name of "Barry Johnson" would produce:
//       prgbMatchCounts[6] = 2 (and all other values of prgbMatchCounts up to index 12 will be 0)
//       pszMatchedText = "Jo"
//     A filter of "bar" against a name of "Barry Johnson" would produce:
//       prgbMatchCounts[0] = 3
//       pszMatchedText = "Bar"
//     A filter of "j bar" against a name of "Barry Johnson" would produce:
//       prgbMatchCounts[0] = 3; prgbMatchCounts[6] = 1
//       pszMatchedText = "J Bar"
//     A filter of "barryjohnson" against "Barry Johnson" would produce:
//       prgbMatchCounts[0] = 13
//       pszMatchedText = "Barry Johnson"
//     A filter of "johnsonbarry" against "Barry Johnson" would produce:
//       prgbMatchCounts[0] = 5; prgbMatchCounts[6] = 7
//       pszMatchedText = "Johnson Barry" 
//     A filter of "vlatkajuric" against "Juric-Sedic, Vlatka" would produce:
//       prgbMatchCounts[0] = 5; prgbMatchCounts[13] = 6
//       pszMatchedText = "Vlatka Juric"
//
BOOL IsMatchFromKeyMap(__in LPCTSTR pszFilter, __in LPCTSTR pszText, DWORD dwFlags, UINT cMatchBufferLengths, __out_bcount_opt(cMatchBufferLengths) BYTE *prgbMatchCounts, __out_ecount_opt(cMatchBufferLengths) LPWSTR pszMatchedText);

// IsMatchFromKeyMap maximum string parameter lengths
#define KEYMAP_CCH_MAXFILTER    250
#define KEYMAP_CCH_MAXTEXT      1027

// IsMatchFromKeyMap supported flags
// Note that equivalence mappings cannot be turned off.
// Note that advanced matching features cannot be turned off from this API.
//   - Although space is always a delimiter, a custom delimiter character can also
//     be configured by the OEM or by ISVs via the LoadKeyMap API.
enum KEYMAP_ISMATCHFLAGS
{
    // Let IsMatchFromKeyMap determine whether pszText should be matching using
    // name, number, or text matching logic.  This flag is useful when iterating
    // across a list of mixed content where some items should match via name,
    // some via number, or some via plain text.
    KEYMAP_IMF_AUTORECOGNIZE                = 0x1,

    // pszText is the name of a person or business.  This affects how matching is
    // performed, especially with regards to names in the "last, first" format.
    KEYMAP_IMF_NAME                         = 0x2,

    // pszText is a telephone number.  This affects how matching is performed,
    // especially with regards to ignoring formatting characters in the number.
    KEYMAP_IMF_NUMBER                       = 0x4,

    // pszText is plain text.  This affects how matching is performed, especially
    // by not applying name or number specific logic.
    KEYMAP_IMF_TEXT                         = 0x8,

    // Do not use hardware keyboard mappings.  Default is on.
    // This flag is useful for reducing overmatching when the user isn't using
    // the hardware keyboard.
    KEYMAP_IMF_NOKEYBOARDMAPPINGS           = 0x100,

    // Use phone keypad mappings.  Default is off.
    // Note that the default phone keypad mappings are the ITU E 1.161 mappings
    // of 2:ABC, 3:DEF, etc. though OEMs can configure these mappings differently.
    // This flag is useful when the user is using the phone keypad.
    KEYMAP_IMF_USEPHONEKEYPADMAPPINGS    = 0x200,
};

//////////////////////////////////////////////////////////////////////////////
//
// KeyMapCharacter
//
// Apply one or more of the mappings configured on the device to the character input.
//
// Parameters:
//  chInput
//   [in] Character to map.
//  cKeyMaps
//   [in] Flags specifying what type(s) of mappings to apply.
//
// Return Value:
//  Mapped character value if successful.
//  0 otherwise.
TCHAR KeyMapCharacter(TCHAR chInput, DWORD dwFlags);

// KeyMapCharacter supported flags
enum KEYMAP_MAPCHARACTERFLAGS
{
    // Letters to digits via ITU E 1.161.  Digits are output unchanged.
    // Ex: chInput of A, B, or C outputs 2; D, E, or F outputs 3; etc.
    // Iterating across a string like "1800ABCDEFG" would output "18002223334"
    // REMARKS: This flag is no longer supported, KeyMapCharacter will return 0.
    KEYMAP_MCF_ALPHATOPHONE                 = 0x1,

    // Character to first matching character using the hardware keyboard mappings.
    // The phone application uses this mapping to determine what to display in the
    // No Matches text when the filter string matches nothing.
    // Ex: If the hardware keyboard has "T5", "I8", and "M?" keys and the hardware
    // keyboard mappings list 't', 'i', and 'm' as the first matching characters for
    // '5', '8', and '?' respectively then if the user types "58?" and it doesn't happen
    // to match any entries then the No Matches text will display "tim" instead of "58?"
    KEYMAP_MCF_KEYMAPTOFIRSTMATCH,

    // Character to filter character that would match it using the hardware keyboard mappings.
    // Ex: If the hardware keyboard has a "K:" key then chInput of 'k' will output ':'
    // The original character will be returned if there is no mapping
    KEYMAP_MCF_KEYMAPTOFILTERCHAR,

    // Characters to phone characters using the on-screen keypad mappings.
    // Ex: By default, the on-screen keypad mappings are based on ITU E 1.161
    // so chInput of 'T', 'i', 'm' would output '8', '4', '6'.  The OEM can
    // customize these mappings differently though so it's better to use
    // KEYMAP_MCF_KEYMAPTOPHONEKEYPAD instead of KEYMAP_MCF_ALPHATOPHONE if the
    // user is inputting characters via a phone keypad.
    KEYMAP_MCF_KEYMAPTOPHONEKEYPAD
};

//////////////////////////////////////////////////////////////////////////////
//
// KEYMAPPING struct
//
// Use to specify keyboard mapping data for use with LoadKeyMap function.
//
// Fields:
//   chHardware
//     WM_CHAR value sent when the affected key is pressed
//     without using <shift> or other modifiers.
//   rgchMatches
//     WM_CHAR values that should match chHardware.
//
// Remarks:
//   rgchMatches must be '\0' terminated.
//   chHardware values must be unique.
//   rgchMatches individual values must be unique.
//   chHardware and rgchMatches values must be lowercase or caseless.
//
typedef struct _KEYMAPPING
{
    WCHAR chHardware;
    WCHAR *rgchMatches;
} KEYMAPPING, *PKEYMAPPING;

//////////////////////////////////////////////////////////////////////////////
//
// LoadKeyMap
//
// Load keyboard mapping data and override current keyboard mapping.
// Usable by trusted callers only.
//
// Parameters:
//  prgKeyMaps
//   [in opt] Pointer to array of KEYMAPPINGs to load.
//  cKeyMaps
//   [in] Count of KEYMAPPINGs to load.
//
// Return Value:
//  (HANDLE) Handle to KeyMap identifier for use with UnloadKeyMap.
//  INVALID_HANDLE_VALUE in case of failure.
//
// Remarks:
//  Default keyboard mapping data is always restored on reboot.
//  It can also be restored by calling UnloadKeyMap.
//  Be sure to call UnloadKeyMap if the device for this mapping data is disconnected.
//  Set prgKeyMaps to NULL to set keyboard mappings for an unambiguous keyboard.
//
HANDLE LoadKeyMap(__in_ecount_opt(cKeyMaps) const PKEYMAPPING prgKeyMaps, DWORD cKeyMaps);

//////////////////////////////////////////////////////////////////////////////
//
// UnloadKeyMap
//
// Unload keyboard mapping data and restore default keyboard mapping data.
// Usable by trusted callers only.
//
// Parameters:
//  hKeyMap
//   [in] HANDLE to KeyMap identifier returned by LoadKeyMap.
//
// Return Value:
//  Standard HRESULT.
//
HRESULT UnloadKeyMap(HANDLE hKeyMap);


//////////////////////////////////////////////////////////////////////////////
//
// SHSetImeMode
//
//   This function will pass the SHIME_MODE value to IME if it is present.
//   Or it will pass this SHIME_MODE info to keyboard driver if the IME is disabled. 
//
// Parameters:
//  hWnd
//   [in] Handle to the window whose IME  mode is to be changed.
//        If the window handle is NULL then only keyboard driver will be notified.
//  nMode
//   [in] It is one of SHIME_MODE values.
//
// Return value:
//  S_OK means succeeded, otherwise means failure.
//
HRESULT SHSetImeMode(HWND hWnd, SHIME_MODE nMode);


//////////////////////////////////////////////////////////////////////////////
//
// SHGetImeMode
//
//   This function will get the SHIME_MODE value from IME if it is present.
//   Otherwise, it will try to get SHIME_MODE from keyboard driver.
//
// Parameters:
//  hWnd
//   [in] Handle to the window whose IME  mode is to be queried.
//        If the window handle is NULL then only keyboard driver's IME mode
//        will be queried.
// pnMode
//   [out] A pointer to a DWORD to receive the SHIME_MODE value.
//
// Return value:
//  S_OK means succeeded, otherwise means failure.
//
HRESULT SHGetImeMode(HWND hWnd, SHIME_MODE* pnMode);

// Structure used to set/get information when associating a menu item with a 
// softkey button. See SHSetAssignedMenuItem and SHGetAssignedMenuItem.
typedef struct _SHAMI
{
    UINT    cbSize;         // Size of the SHAMI structure, in bytes.
    DWORD   dwFlags;        // Optional SHAMIF_* flags.
    LPTSTR  pszAltLabel;    // Optional button label (e.x. shorter label then associated menu item).
    UINT    cchAltLabel;    // Button label buffer size (including NULL).
}   SHAMI, *LPSHAMI;    


// The menu item to be assigned to the softkey button does not currently exist in the menu. 
// The softkey parent window can add the menu item to the menu upon receiving WM_INITMENUPOPUP otherwise 
// the menu item will be added to the menu automatically at a position that corresponds to the assigned softkey index.
// Note: uFlags must be set to MF_BYCOMMAND when this flag is used in conjunction with SHSetAssignedMenuItem.
#define SHAMIF_ADDMENUITEMONPOPUP 0x0001 

// Action menu item ID.
#define MIID_ACTION 0xFFFE 

/// <summary>
/// Set a menu item to be assigned to the menu bar.
/// </summary>
/// <param name="hwndMB">
/// Window handle to the menu bar.
/// </param>
/// <param name="hMenu">
/// Handle to the menu that contains the menu item. If NULL no menu 
/// item is assigned to the specified menu bar button.
/// </param>
/// <param name="uItem">
/// Specifies the menu item to be assigned, as determined by the 
/// uFlags parameter. Ignored if hMenu is NULL.
/// 
///  Note: The menu item cannot be a separator, have an associated popup 
///        menu or be owner drawn.
/// </param>
/// <param name="uFlags">
/// Specifies how the uItem parameter is interpreted. Ignored if 
/// hMenu is NULL. This parameter must be one of the following values:
///
/// <para>
///        MF_BYCOMMAND 
///            Indicates that uItem gives the identifier of the
///            menu item. The MF_BYCOMMAND flag is the default flag if neither 
///            the MF_BYCOMMAND nor MF_BYPOSITION flag is specified. 
/// </para>
/// <para>
///        MF_BYPOSITION 
///            Indicates that uItem gives the zero-based 
///            relative position of the menu item. 
/// </para>
/// </param>
/// <param name="uAssignedIndex">
/// Index of the menu bar button that will display the menu item.
///
/// Note: This value should be less than the maximum number of menu bar
/// buttons. See the SN_MAXMENUBARBUTTONS_VALUE (or SN_MAXMENUBARIMAGEBUTTONS_VALUE 
/// if MBS_IMAGEBUTTONS set) state. Otherwise S_FALSE is returned.
/// </param>
/// <param name="lpshami">
/// [in, optional] Pointer to a SHAMI structure that contains information
/// about the menu item assignment.
/// </param>
/// <returns>S_OK indicates success; otherwise, returns a failure code.</returns>
HRESULT SHSetAssignedMenuItem(HWND hwndMB, HMENU hMenu, UINT uItem, UINT uFlags, UINT uAssignedIndex, LPSHAMI lpshami);

/// <summary>
/// Get the menu item assigned to the menu bar.
/// </summary>
/// <param name="hwndMB">
/// Window handle to the menu bar.
/// </param>
/// <param name="phMenu">
/// [out] Handle to the menu that contains the menu item assigned to the
/// menu bar is returned or NULL if no menu item has been assigned.
/// </param>
/// <param name="puItem">
/// [out] The menu item assigned to the menu bar as determined by the 
/// uFlags parameter or -1 if no menu has been assigned to the softkey.
/// </param>
/// <param name="uFlags">
/// Specifies how the uItem parameter is interpreted.  
/// This parameter must be one of the following values:
/// <para>
///        MF_BYCOMMAND 
///            Indicates that puItem will point to the identifier of the
///            menu item. The MF_BYCOMMAND flag is the default flag if neither 
///            the MF_BYCOMMAND nor MF_BYPOSITION flag is specified. 
/// </para>
/// <para>
///        MF_BYPOSITION 
///            Indicates that puItem will point to the zero-based 
///            relative position of the menu item. 
/// </para>
/// </param>
/// <param name="uAssignedIndex">
/// Index of the softkey to retrieve info from.
///
/// Note: This value should be less than the maximum number of softkey
/// buttons. See the SN_MAXMENUBARBUTTONS_VALUE state. Otherwise 
/// S_FALSE is returned.
/// </param>
/// <param name="lpshami">
/// [out, optional] Pointer to a SHAMI structure that receives information
/// about the menu item assignment.
/// </param>
/// <returns>S_OK indicates success; otherwise, returns a failure code.</returns>
HRESULT SHGetAssignedMenuItem(HWND hwndMB, HMENU* phMenu, UINT* puItem, UINT uFlags, UINT uAssignedIndex, LPSHAMI lpshami);

//~~~~~~~~~~~~
//
//  GetDeviceFeatureLevel
//

// The infrared support level of device. Below is the list of return value of pdwFeatureLevel.
// 
// DFL_NOINFRARED - The device doesn't include infrared capability.
// DFL_INFRARED - The device includes infrared capability.
// 
#define DFLI_INFRARED           0xc0020002
#define DFL_NOINFRARED          0
#define DFL_INFRARED            1

// The vibration support level of device. Below is the list of return value of pdwFeatureLevel.
// 
// DFL_NOVIBRATION - The device doesn't include vibration capability.
// DFL_VIBRATION - The device includes vibration capability.
//
#define DFLI_VIBRATION          0xc0020003
#define DFL_NOVIBRATION         0
#define DFL_VIBRATION           1

// Telephone capabilities support level.
// 
// DFL_NOPHONE - The device does not include telephone capabilities.
// DFL_PHONE - The device includes telephone capabilities.
// DFL_PHONE_LOCKFACILITY - The device supports locking one or more of the installed telephone services.
// DFL_PHONE_INTLPLUS - Indicates that the phone UI will generate a '+' when the user presses and holds '0'.
// 
#define DFLI_PHONE                          0xc0020005
#define DFL_NOPHONE                         0x00000000
#define DFL_PHONE                           0x00000001
#define DFL_PHONE_LOCKFACILITY              0x00000008
#define DFL_PHONE_INTLPLUS                  0x00000100

// The Bluetooth support level. Below is the list of return value of pdwFeatureLevel.
// 
// DFL_NOBTH - The device doesn't include Bluetooth capability.
// DFL_BTH - The device includes Bluetooth capability.
// DFL_BTH_CONNECTABLE - The Bluetooth state is set to connectable.
// DFL_BTH_DISCOVERABLE - The Bluetooth state is set to discoverable.
// 
#define CONNECT_MODE_SHIFT      1

#define DFLI_BTH                0xc0020006
#define DFL_NOBTH               0x00
#define DFL_BTH                 0x01
#define DFL_BTH_CONNECTABLE     BTH_CONNECTABLE << CONNECT_MODE_SHIFT
#define DFL_BTH_DISCOVERABLE    BTH_DISCOVERABLE << CONNECT_MODE_SHIFT

// The Bluetooth hands free support level. Below is the list of return value of pdwFeatureLevel.
// 
// DFL_NOHANDSFREE - The device doesn't include hands free capability.
// DFL_HANDSFREE - The device include hands free capability.
// 
#define DFLI_BTH_HANDSFREE      0xc002000B
#define DFL_NOHANDSFREE         0
#define DFL_HANDSFREE           1

// The sound recording support level. Below is the list of return value of pdwFeatureLevel.
// 
// DFL_NOSOUND_RECORDING - The device doesn't include sound recording capability.
// DFL_SOUND_RECORDING - The device includes sound recording capability.
// 
#define DFLI_SOUND_RECORDING    0xc0020016
#define DFL_NOSOUND_RECORDING   0
#define DFL_SOUND_RECORDING     1

// CONTACT FIELDS SUPPORTED BY THE CURRENT SIM.
// Bits 0-7 are a value indicating the number of email addresses 
// supported per contact. 
// Bits 8-15 are a value indicating the number of additional phone 
// numbers supported per contact.
// Bits 16-19 are a value indicating the number of USIM groups 
// supported.
// Bits 20-27 are a value indicating the number of additional number 
// tags supported.
// Bit 28 is unused.
// Bit 29 indicates if the hidden flag is supported.
// Bit 30 indicates that the additional name is supported.
// Bit 31, the most significant bit, indicates that the default name and 
// number are supported. This will only be FALSE if there is no SIM 
// support, or the device has never been booted with a SIM, or the SIM 
// really has no phonebook support at all.
// 
// If you boot with no SIM you'll get the capabilities from the 
// previous boot that did have a SIM.
// 
#define DFLI_SIMCTS_CONTACTSFIELDS          0xc0020017
#define DFL_SIMCTS_EMAILCOUNT               0x000000FF
#define DFL_SIMCTS_ADDNLNUMBERCOUNT         0x0000FF00
#define DFL_SIMCTS_GROUPCOUNT               0x000F0000
#define DFL_SIMCTS_PHONENUMBERTAGS          0x0FF00000
#define DFL_SIMCTS_HIDDENFLAG               0x20000000
#define DFL_SIMCTS_SECONDNAME               0x40000000
#define DFL_SIMCTS_BASE                     0x80000000



// The hardware keyboard support level. Below is the list of return value of pdwFeatureLevel. 
// 
// DFL_NOKEYBOARD - The device doesn't include hardware keyboard.
// DFL_QWERTYKBD - The device includes QWERTY keyboard.
// DFL_12KEYPAD - The device includes 12 keys keypad.
// 
#define DFLI_KEYBOARD           0xc002001A
#define DFL_NOKEYBOARD          0
#define DFL_QWERTYKBD           1
#define DFL_12KEYPAD            2

// The soft key support level.
// 
// The return value of pdwFeatureLevel is the number of hardware buttons
// corresponding to software buttons in menu bar.
// 
#define DFLI_SOFTKEYS           0xc002001B


HRESULT GetDeviceFeatureLevel(DWORD dwIndex, DWORD *pdwFeatureLevel);


//
//  end GetDeviceFeatureLevel
//
//~~~~~~~~~~~~

// Possible status display modes
#define STATUS_DISPLAY_MODE_STANDARD              0
#define STATUS_DISPLAY_MODE_STANDARD_BLUETOOTH    1
#define STATUS_DISPLAY_MODE_EXTENDED              2

/// <summary>
/// Sets the display mode for the system's title bar
/// </summary>
/// <param name="hwndRequester">
///     Handle to the top-level window requesting the status display mode
/// </param>
/// <param name="dwMode">
///     The mode the status display should be in
/// </param>
/// <returns>
///     E_INVALIDARG if dwMode is an invalid value.
///     Otherwise, the result of changing the status mode.
/// </returns>
/// <remarks>
///
///     STATUS_DISPLAY_MODE_STANDARD will cause the title bar to display a
///     minimal set of icons.
///
///     STATUS_DISPLAY_MODE_STANDARD_BLUETOOTH will cause the title bar to
///     display a minimal set of icons, but will include the bluetooth icon
///
///     STATUS_DISPLAY_MODE_EXTENDED will cause the title bar to display
///     many status icons. This will cut down on the available room to display
///     text in the titlebar.
/// </remarks>
HRESULT WINAPI SetStatusDisplayMode(HWND hwndRequester, DWORD dwMode);


/// <summary>
///   Opens the specified control panel settings.
/// </summary>
/// <param name="pszCpl">
///   [in] Control panel to open. This must be one of the following:
///   <list type="table">
///     <listheader>
///       <term>Value</term>
///       <description>Description</description>
///     </listheader>
///     <item>
///       <term>NULL or empty string</term>
///       <description>
///         Opens the control panel task list.
///       </description>
///     </item>
///     <item>
///       <term>GUID String</term>
///       <description>
///         Unique identifier of a control panel to open.
///         Example: {7EC037F2-1D6A-4f4b-9415-6494CF1D480A}
///       </description>
///     </item>
///     <item>
///       <term>Canonical Name</term>
///       <description>
///         Canonical name of a control panel to open. Case is ignored.
///         Example: Microsoft.DateTime
///       </description>
///     </item>
///   </list>
/// </param>
/// <returns>
///   HRESULT. S_OK if the control panel application was launched.
/// </returns>
/// <remarks>
///   <para>
///     The control panel is opened in a separate process. This function
///     returns immediately and does not provide any useful information
///     about the state of the control panel.
///   </para>
/// </remarks>
HRESULT LaunchCpl(__in_opt LPCTSTR pszCpl);

/// <summary>
///    Used to update the text of a popup window and, if this is the foreground
///    window, to have the change be reflected in the titlebar
/// </summary>
/// <param name="hwnd">
///    Handle to the window whose text is to be changed
/// </param>
/// <param name="pszString">
///     Pointer to a null-terminated string to be used as the new  
/// </param>
/// <returns>
///     HRESULT.
/// </returns>
HRESULT SHSetPopupWindowText(HWND hwnd, __in LPCTSTR pszString);


// Enums and structures used to communicate with applications that have
// registered themselves with the shell via SHRegisterApplication


typedef enum 
{
    /// <summary>
    ///  A second instance of a single-instanced app was attempted to be 
    ///  launched. The extended message info will contain the unicode-encoded
    ///  command line of the second instance
    /// </summary>
    REGISTEREDAPPNOTIFICATION_NEWINSTANCE       = 0,

    /// <summary>
    ///  The shell has determined that this app is inactive. Apps should free 
    ///  memory and take further steps to reduce their impact on the system.
    ///  launched
    /// </summary>
    REGISTEREDAPPNOTIFICATION_APPINACTIVE       = 1,

    /// <summary>
    ///  The shell wants this process to exit. Apps should save their state and
    ///  close. If an app ignores this message, the shell will call 
    ///  TerminateProcess() on this application.
    /// </summary>
    REGISTEREDAPPNOTIFICATION_SAVESTATEANDCLOSE = 2,

    /// <summary>
    ///  The system has entered a low memory state. If the process has any
    ///  "host-like" behaviors it should suspend creating new instances of 
    ///  items until the system has freed memory and sends the process a
    ///  REGISTEREDAPPNOTIFICATION_HIGHMEMORYSTATE notification.
    /// </summary>
    REGISTEREDAPPNOTIFICATION_LOWMEMORYSTATE    = 3,

    /// <summary>
    ///  The system has freed enough memory and is in a stable memory state.
    ///  If the process has "host-like" behaviors that it modified when 
    ///  handling the REGISTEREDAPPNOTIFICATION_LOWMEMORYSTATE message it
    ///  should feel free to revert back to its normal behavior.
    /// </summary>
    REGISTEREDAPPNOTIFICATION_HIGHMEMORYSTATE   = 4,

    /// <summary>
    ///  Sent to registered top level windows. An application should attempt to
    ///  release as many resources as possible when sent this message by 
    ///  unloading dialog boxes, destroying windows, or freeing up as much
    ///  local storage as possible without changing the internal state.
    /// </summary>
    REGISTEREDAPPNOTIFICATION_HIBERNATE         = 5,
} REGISTEREDAPPNOTIFICATION_TYPE;

#pragma warning(push)
#pragma warning(disable:4200) // nonstandard extensions warning
#pragma warning(disable:4201) // nameless struct/union

/// <summary>
///  The layout of the messages that the shell will send applications through
///  a message queue
/// </summary>
///   <item>
///     <term>REGISTEREDAPPNOTIFICATION_TYPE dwType</term>
///     <description>The type of notification</description>
///   </item>
///   <item>
///     <term>DWORD cbExtendedMessageSize</term>
///     <description>
///       The size of the extended message data. See the enum for the different
///       notification types to see which messages will have extended info
///     </description>
///   </item>
///   <item>
///     <term>BYTE pvExtendedMessage[0]</term>
///     <description>The buffer containing extended message info</description>
///   </item>
typedef struct 
{
    REGISTEREDAPPNOTIFICATION_TYPE dwType;
    DWORD cbExtendedMessageSize;
    BYTE pvExtendedMessage[0];
} REGISTEREDAPPNOTIFICATION;
#pragma warning(pop)

/// <summary>
///     The maximum size of a registered app notification message that will be
///     sent by the shell
///
///     From other parts of the code, #define MAX_URL 1024
/// </summary>
#define MAXSIZE_REGISTEREDAPPNOTIFICATION (sizeof(REGISTEREDAPPNOTIFICATION) + 1024*sizeof(WCHAR))

/// <summary>
///     The shell should treat this application as a normal process.
/// </summary>
#define SHREGISTERPROCESS_NORMALPROCESS     0

/// <summary>
///     The shell should automatically relaunch this process if it terminates
///     when it is in the inactive state. Apps using this flag should use the 
///     API SHAppRelaunchedByShell() to determine if the user launched the app
///     or if the shell relaunched it
/// </summary>
#define SHREGISTERPROCESS_RELAUNCHPROCESS   1

/// <summary>
///     The shell should treat this application as an app that does work in the
///     background without user interaction. This app may not present any UI to
///     the user. The shell will attempt to keep this process running 
///     regardless of perceived inactivity or low memory situations.
/// </summary>
#define SHREGISTERPROCESS_BACKGROUNDPROCESS 2

/// <summary>
///     The shell should treat this application as a single-instance app. If an
///     attempt to launch a second instance of this app via ShellExecute is
///     made, the shell will block it and instead notify the current running
///     instance of the application. However, if the second instance is launched
///     via CreateProcess(), the shell will not interfere.
/// </summary>
#define SHREGISTERPROCESS_SINGLEINSTANCE    4

/// <summary>
///     This application understands what it means to be inactive, and will 
///     respond to messages from the shell when the shell deems the app to be
///     inactive. The app will reduce its memory footprint and other system
///     requirements, and in exchange, will be allowed to live a longer life 
///     in the background.
/// </summary>
#define SHREGISTERPROCESS_INACTIVEAWARE     8

/// <summary>
///     Structure used to register a process via SHRegisterProcess()
/// </summary>
///   <item>
///     <term>DWORD cbSize</term>
///     <description>Size of this structure</description>
///   </item>
///   <item>
///     <term>HWND hwndNotificationWindow</term>
///     <description>
///       If specified, will recieve notifications when the shell sends the
///       process a notification
///     </description>
///   </item>
///   <item>
///     <term>UINT uMessageToSend</term>
///     <description>
///        The window message sent to hwndNotificationWindow if specified
///     </description>
///   </item>
///   <item>
///     <term>DWORD dwFlags</term>
///     <description>
///         Flags used to control the registered process's behavior. See
///         the various SHREGISTERPROCESS_* flags for options
///     </description>
///   </item>
///   <item>
///     <term>hMessageQueue</term>
///     <description>
///       Message queue handle returned by the shell that processes should
///       use to get notification information from the shell
///     </description>
///   </item>
typedef struct 
{
    DWORD cbSize;
    HWND hwndNotificationWindow;
    UINT uMessageToSend;
    DWORD dwFlags;
    HANDLE hMessageQueue;
} SHREGISTERPROCESS;

/// <summary>
///     Used to register an process with the system. This will give the
///     process a message queue handle that it can use to get notifications
///     from the shell
/// </summary>
/// <param name="pshrg">
///    Structure that defines how the process should be registered
/// </param>
/// <returns>
///     HRESULT.
/// </returns>
HRESULT SHRegisterProcess(
    SHREGISTERPROCESS* pshrg
);

/// <summary>
///     Structure used to register a top level window as a seperate application
///     via SHRegisterApplication()
/// </summary>
///   <item>
///     <term>DWORD cbSize</term>
///     <description>Size of this structure</description>
///   </item>
///   <item>
///     <term>HWND hwndTopLevelWindow</term>
///     <description>
///       The top level window that the shell will treat as a seperate
///       application
///     </description>
///   </item>
///   <item>
///     <term>uMessageToSend</term>
///     <description>
///       The window message to send to the top level window if the shell
///       has sent a message to the application's message queue
///     </description>
///   </item>
///   <item>
///     <term>hMessageQueue</term>
///     <description>
///       Message queue handle returned by the shell that processes should
///       use to get notification information from the shell
///     </description>
///   </item>
typedef struct 
{
    DWORD cbSize;
    HWND hwndTopLevelWindow;
    UINT uMessageToSend;
    HANDLE hMessageQueue;
} SHREGISTERAPPLICATION;

/// <summary>
///     Used to register a top level window with the system. This will cause
///     the shell to treat this top level window as a seperate "application"
///     and will send the window messages seperately from the owner process.
///     The shell may ask this window to close regardless of the state of the
///     other top level windows owned by the process.
/// </summary>
/// <param name="pshrg">
///    Structure that defines how the top level window should be registered
/// </param>
/// <returns>
///     HRESULT.
/// </returns>
HRESULT SHRegisterApplication(
    SHREGISTERAPPLICATION* pshrg
);

/// <summary>
///     Different actions to ask the shell to perform
/// </summary>
typedef enum 
{
    SHELL_ACTION_CANCEL                         = 0,
    SHELL_ACTION_TERMINATE                      = 1,
    SHELL_ACTION_TERMINATE_FOR_SERIALIZATION    = 1,
    SHELL_ACTION_TERMINATE_SICK_PROCESS         = 2,
    SHELL_ACTION_MEMORYGOOD                     = 3,
    SHELL_ACTION_MEMORYLOW                      = 4,
    SHELL_ACTION_NOTIFY_SICK_PROCESS            = 5,
    SHELL_ACTION_TERMINATE_FOR_COMPLETION       = 6,
} SHELL_ACTION;


/// <summary>
///     Flags to inform the shell if it should perform the action on a
///     process or a task
/// </summary>
#define SHTRIGGERSHELLACTION_TASK     0
#define SHTRIGGERSHELLACTION_PROCESS  1

#pragma warning(push)
#pragma warning(disable:4201)   // nameless struct/union

/// <summary>
///     Structure used to call SHTriggerShellAction
/// </summary>
///   <item>
///     <term>DWORD cbSize</term>
///     <description>Size of the structure</description>
///   </item>
///   <item>
///     <term>TASKID dwTaskId/DWORD dwPid</term>
///     <description>Either the process ID or the task ID to perform the action on.</description>
///   </item>
///   <item>
///     <term>DWORD dwFlags</term>
///     <description>Flags to specify specific behaviors for this action</description>
///   </item>
///   <item>
///     <term>SHELL_ACTION dwAction</term>
///     <description>The action the shell should perform</description>
///   </item>
///   <item>
///     <term>LPWSTR pszDescription</term>
///     <description>Description of action</description>
///   </item>
typedef struct 
{
    DWORD cbSize;
    union
    {
        TASKID dwTaskId;
        DWORD dwPid;
    };
    DWORD dwFlags;
    SHELL_ACTION dwAction;
    LPWSTR pszDescription;
} SHTRIGGERSHELLACTION;

#pragma warning (pop)

/// <summary>
///     Function used for testing to cause the shell to perform some specific
///     functions. 
/// </summary>
/// <param name="pAction">
///    Structure that describes the action the shell should perform
/// </param>
/// <returns>
///     HRESULT.
/// </returns>
/// <remarks>
///     This function is only callable by processes that are running in the
///     supervisor or above chamber
/// </remarks>
HRESULT SHTriggerShellAction(
    __in SHTRIGGERSHELLACTION* pAction
);

/// <summary>
/// Cause one's own process to terminate immediately, as if the shell had  
/// terminated it due to an OOM condition.
/// However, the process's pages stay on the backstack, and the process
/// will be rehydrated if a page is navigated to.
/// </summary>
HRESULT SHDehydrateProcess(void);


/// <summary>
/// Called when a process has hit an OOM condition and wants to terminate.
/// Note, this function will not return.
/// </summary>
/// <param name="cbFailedAllocationSize">
///    The allocation size that failed
/// </param>
void SHTerminateProcessForOOM(
    DWORD cbFailedAllocationSize
);

/// <summary>
/// Called when a process has hit an OOM condition and wants to terminate.
/// Note, this function will not return.
/// </summary>
void SHTerminateProcessForOOM_NoAllocSize(
);

// Max length of the command line  argument string 
// If this value is changed, also change corresponding value in
// Misc.cpp and ExecutionManager.cpp
#define MAX_SHLAUNCHTASK_ARG_LENGTH 32767 // 2^15 - 1 wchars or 2^16 bytes (including '\0')

// The parameters for the task launch were correct, but there currently isn't
// enough memory to complete the task. The shell will free memory and then 
// launch the task at a later date.
#define S_TASKLAUNCH_DEFERRED MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_ITF, 0x100)

/// <summary>
///     Deprecated function
/// </summary>
/// <param name="pszTaskUri">
/// </param>
/// <param name="pszCmdLineArguments">
/// </param>
/// <param name="lphSession">
/// </param>
HRESULT SHLaunchTask(
    __in_z      LPCWSTR     pszTaskUri,
    __in        LPCWSTR     pszCmdLineArguments,
    __out_opt   HANDLE*     lphSession
);

/// <summary>
///     Function used to launch a task.
/// </summary>
/// <param name="ulAppId">
///    [in] App Id
/// </param>
/// <param name="pszTokenId">
///    [in] Token ID
/// </param>
/// <param name="lphSession">
/// </param>
/// <returns>
///     HRESULT. 
/// </returns>
HRESULT SHLaunchSession(
    ULONGLONG ulAppId, 
    __in_z_opt LPCWSTR pszTokenId,
    __out_opt HANDLE* lphSession
);

/// <summary>
///     Function used to launch a task based on URI.
/// </summary>
/// <param name="szTaskUri">
///    [in] Fully qualifed Task URI, including parameters. I.E.
///    app://0000000000000003/_default?Arg1=Data1&Arg2=Data2
/// </param>
/// <param name="lphSession">
///    [out] Session handle
/// </param>
/// <returns>
///     HRESULT. 
/// </returns>
HRESULT SHLaunchSessionByUri(
    __in_z LPCWSTR szTaskUri,
    __out_opt HANDLE* lphSession
);

/// <summary>
///     Function used to launch a task based on URI as well as
///     a session ID used to identify said task on a 
///     subsequent launch. 
/// </summary>
/// <param name="szTaskUri">
///    [in] Fully qualifed Task URI, including parameters. I.E.
///    app://0000000000000003/_default?Arg1=Data1&Arg2=Data2
/// </param>
/// <param name="szSessionId">
///    [in] A session identifier string. This parameter is used 
///     as follows given the applicable application activation policy:
///   <para>
///     Resume/Replace/Multi-Session - A newly created session is given the
///     ID specified.
///   </para>
///   <para>
///     Resume With Params/Replace With Params - If a session with an ID
///     matching this parameter already exists, that session
///     is resumed or replaced, as appropriate. Else, a new session is 
///     created using this ID. 
///   </para>
/// </param>
/// <param name="pSerializedPropertyBag">
///     Serialized property bag containing the arguments for this task. This
///     can be non-null only if the task uri does not have parameters
///     in it already.
/// </param>
/// <param name="cbSerializedPropertyBag">
///     Size of the serialized property bag in bytes
/// </param>
/// <param name="lphSession">
/// </param>
/// <remarks>
///     Only the <paramref name="szSessionId"/> is used to find an existing session. 
///     Task parameters are not used as matching criterion.
/// </remarks>
/// <returns>
///     HRESULT. 
/// </returns>
HRESULT SHLaunchSessionByUriEx(
    __in_z LPCWSTR szTaskUri,
    __in_z LPCWSTR szSessionId,
    __in_bcount_opt(cbSerializedPropertyBag) CONST BYTE* pSerializedPropertyBag,
    DWORD cbSerializedPropertyBag,
    __out_opt HANDLE* lphSession
);

/// <summary>
///    Function used to launch a task in suspended mode.
/// </summary>
/// <param name="pszTaskUri">
///    [in] Fully qualifed Task URI
/// </param>
/// <param name="pszTaskParams">
///    [in] Arguments to launch task. Multiple arguments
///    should be separated by spaces.
/// </param>
/// <param name="pdwPid">
///    [out] Pointer to the PID of the Process that hosts this Task
/// </param>
/// <param name="lphTask">
///     [in/out] pointer to created task's handle. If the input value is 0, 
///     we'll first attempt a "resume style" reactivation if this task URI
///     is currently running. If it isn't running, a new task will be launched.
///     If a non-0 value is passed, in, that existing session will be reactived
///     in a suspended state.
/// </param>
/// <returns>
/// S_OK if new process launched in suspended mode
/// S_FALSE if existing process was used to launch the task
/// </returns>
HRESULT SHLaunchTaskSuspended(
    __in_z  LPCWSTR     pszTaskUri,
    __in    LPCWSTR     pszTaskParams,
    __out   DWORD*      pdwPid,
    __out   HANDLE*     lphTask
);


/// <summary>
///     Function used to lookup a session by name.  
///     Will only return a session with the same ProductID as the caller.
/// </summary>
/// <param name="pszSessionName">
///    The session name.
/// </param>
/// <param name="phSession">
///    [out] Pointer to the returned session handle.
/// </param>
/// <returns>
///    S_OK or E_NOT_FOUND
/// </returns>
HRESULT SHFindSession(
    __in_z_opt LPCWSTR pszSessionName,
    __out      HANDLE *phSession
);


//-----------Session Handle based APIs Begin---------//

/// <summary>
///     Function used to Fetch the Pid of the process that launched the
///     root Task of the Session.
/// </summary>
/// <param name="hSession">
///     [in] Session Handle
/// </param>
/// <param name="pdwPid">
///     [out] Pointer to the PID of the Process that hosts this Task
/// </param>
/// <returns>
///     HRESULT
/// </returns>
HRESULT SHGetSessionPid(
    __in    HANDLE  hSession,
    __out   DWORD*  pdwPid
);

/// <summary>
///     Function used to close a session.
/// </summary>
/// <param name="hSession">
///     [in] Session Handle
/// </param>
/// <returns>
///     HRESULT. 
/// </returns>
HRESULT SHCloseSession(
    __in    HANDLE  hSession
);

/// <summary>
///     Function used get the friendly name associated with a session
/// </summary>
/// <param name="hSession">
///     [in] The session for which to get the friendly name
/// </param>
/// <param name="pszSessionName">
///     [in] The buffer which to receive the friendly name
/// </param>
/// <param name="pcchSessionName">
///     [in/out] Pointer to the DWORD containing the length of the provided 
///     buffer in characters.
///
///     If pszSessionName is NULL, or if the provided buffer size is not big
///     enough, this parameter will contain the required length of the buffer
/// </param>
/// <returns>
///     HRESULT
/// </returns>
HRESULT SHGetSessionName(
    HANDLE hSession,
    __ecount_opt(*pcchSessionName) WCHAR* pszSessionName,
    __inout DWORD* pcchSessionName);

/// <summary>
///     Function used set the friendly name associated with a session
/// </summary>
/// <param name="hSession">
///     [in] The session for which to set the friendly name
/// </param>
/// <param name="szSessionName">
///     [in] The friendly name to set for the session.
/// </param>
/// <returns>
///     HRESULT
/// </returns>
HRESULT SHSetSessionName(
    HANDLE hSession,
    __in_opt LPCWSTR szSessionName);



//-----------Session Handle-based APIs End---------//

/// <summary>
/// ExecMan Host flags
/// </summary>
#define HOSTFLAGS_ISHYDRATED        0x01    // Host is not in tomb-stoned state
#define HOSTFLAGS_ISDEHYDRATED      0x02    // Host is in tomb-stoned state
#define HOSTFLAGS_ISREGISTERED      0x04    // Host has registered with EM
#define HOSTFLAGS_LAUNCHEDSUSPENDED 0x08    // Host was launched in suspended mode
#define HOSTFLAGS_EVERDEHYDRATED    0x10    // Host has been dehydrated at least once
#define HOSTFLAGS_ISFROZEN          0x20    // Host is in frozen state 

/// <summary>
///     Function used to Fetch the Host flags for the Root Task that belongs to
///     the Session specified by the passed in TaskUri. This API will not work
///     for non-root Tasks
/// </summary>
/// <param name="pszTaskUri">
///     [in] TaskUri/SessionUri
/// </param>
/// <param name="pdwHostFlags">
///     [out] Pointer to the DWORD value indicating the Host flags
/// </param>
/// <returns>
///     HRESULT
/// </returns>
HRESULT SHGetHostFlagsForTask(
    __in_z LPCWSTR  pszTaskUri,
    __out  DWORD*   pdwHostFlags
);

/// <summary>
///     Function used to Fetch whether the Root Task that belongs to the
///     Session specified by the passed in TaskUri is hydrated and in
///     suspended mode.
/// </summary>
/// <param name="pszTaskUri">
///     [in] TaskUri/SessionUri
/// </param>
/// <param name="pfIsHydratedAndSuspended">
///     [out] Pointer to the BOOL value indicating whether the Task is
///     hydrated and suspended
/// </param>
/// <returns>
///     HRESULT
/// </returns>
HRESULT SHGetIsTaskHydratedAndSuspended(
    __in_z LPCWSTR  pszTaskUri,
    __out  BOOL*    pfIsHydratedAndSuspended
);

/// <summary>
/// Fetches the static HostLaunch event valid only for Hosts being debugged
/// </summary>
/// <param name="phDebugHostLaunchingEvent">
/// [out] Returns the duplicated HostLaunch event handle. This handle will
/// be signaled whenever a Host that is being debugged is launched/rehydrated.
/// </param>
/// <returns>
/// HRESULT
/// </returns>
HRESULT SHGetSuspendedHostLaunchingEvent(
    __out HANDLE* phDebugHostLaunchingEvent
);

/// <summary>
/// Fetches the static HostExit event valid only for Hosts being debugged
/// </summary>
/// <param name="phDebugHostExitingEvent">
/// [out] Returns the duplicated HostExit event handle. This handle will
/// be signaled whenever a Host that is being debugged is exiting/getting dehydrated
/// </param>
/// <returns>
/// HRESULT
/// </returns>
HRESULT SHGetSuspendedHostExitingEvent(
    __out HANDLE* phDebugHostExitingEvent
);

/// <summary>
/// Fetches the static HostFrozen event valid only for Hosts being debugged
/// </summary>
/// <param name="phDebugHostFrozenEvent">
/// [out] Returns the duplicated HostFrozen event handle. This handle will
/// be signaled whenever a Host that is being debugged is in/out of the
/// frozen state.
/// </param>
/// <returns>
/// HRESULT
/// </returns>
HRESULT SHGetSuspendedHostFrozenEvent(
    __out HANDLE* phDebugHostFrozenEvent
);

/// <summary>
///     Function used to register a Task Host with the Execution Manager. 
///     The Task Host will call into this once it has initialized 
///     the EM client library and is ready to be managed.
/// </summary>
/// <param name="dwHostEndpoint">
///     The CallBackId that will be used as the Endpoint for communication with 
///     the TaskHost
/// </param>
/// <param name="pfIsMultiTenantHost">
///     [out] pointer to BOOL value indicating whether the TaskHost is a 
///     multi tenant Host. Is TRUE for MultiTenantHost, FALSE otherwise.
/// </param>
/// <returns>
///     HRESULT. 
/// </returns>
HRESULT SHRegisterTaskHost(
    __in DWORD dwHostEndpoint,
    __out BOOL* pfIsMultiTenantHost
);


/// <summary>
///     Function used to start dehydrating a task host.
///     This orphans a task host (pretends as if the host has already been
///     dehydrated). This must be followed by the task host dehydrating itself.
///     This method must be called by the task host that is trying to dehydrate
///     itself.
/// </summary>
/// <returns>
///     S_OK if the dehydration process was started
///     S_FALSE if the host is not in the state required for dehdyration
///     Other HRESULTs on error
/// </returns>
HRESULT SHBeginProcessDehydration();


/// <summary>
///     Function used to indicate if an auto-dehydrating host is eligible for
///     dehydration or not. This method is meant to be called by 
///     auto-dehydrating task host processes.
/// </summary>
/// <param name="fEligible">
///     [in] BOOL value indicating if the host process is eligible or not
/// </param>
/// <returns>
///     S_OK on SUCCESS
///     Other HRESULTs on error
/// </returns>
HRESULT SHSetAutoDehydratingHostEligibility(BOOL fEligible);

/// <summary>
///     Available dehydration modes of a task host
/// </summary>
#define DEHYDRATION_MODE_NONE       (0x0L)
#define DEHYDRATION_MODE_DEHYDRATE  (0x1L)
#define DEHYDRATION_MODE_FREEZE     (0x2L)

typedef DWORD DEHYDRATION_MODE;

/// <summary>
///     Function used to indicate the host dehydration mode. 
///     This method is meant to be called by the host processes.
/// </summary>
/// <param name="dwMode">
///     [in] Value indicating the host process dehydration mode 
/// </param>
/// <returns>
///     S_OK on SUCCESS
///     Other HRESULTs on error
/// </returns>
HRESULT SHSetHostDehydrationMode(DEHYDRATION_MODE dwMode);


/// <summary>
///     Function used to notify the execution manager that
///     the task host is freezing. ExecMAn returns an unfreeze
///     event on which the Host waits after freezing.
/// </summary>
/// <param name="phUnfreezeEvent">
///     [out] The pointer to the unfreeze event that will signal when the host
///     is supposed to start unfreezing. 
/// </param>
/// <returns>
///     S_FALSE indicates that the Host should NOT freeze
///     S_OK on SUCCESS
///     Other HRESULTs on error
/// </returns>
HRESULT SHHostFreezing(__out HANDLE* phUnfreezeEvent);

/// <summary>
///     Available methods to shut down a task host
/// </summary>
///   <item>
///     <term>TERMINATETASKHOST_CANCEL</term>
///     <description>
///       All of the tasks associated with this task host will be canceled when the
///       host is terminated
///     </description>
///   </item>
typedef enum 
{
    TERMINATETASKHOST_CANCEL = 1,
} TERMINATETASKHOST_ACTION;

/// <summary>
///     Function used to end the process that contains the specified
///     task host.
/// </summary>
/// <param name="dwPid">
///     PID of the task host to shut down 
/// </param>
/// <param name="dwAction">
///     The way the process should be shut down
/// </param>
/// <returns>
///     HRESULT. 
/// </returns>
HRESULT TerminateTaskHost(
    DWORD dwPid,
    TERMINATETASKHOST_ACTION dwAction
);

/// <summary>
///     Function used to register a test harness with the system. The system
///     will treat this process differently (not kill it in OOM conditions, 
///     etc).
/// </summary>
/// <param name="pszProcessName">
///    Fully qualifed path of the test process name
/// </param>
/// <returns>
///     HRESULT. 
/// </returns>
/// <remarks>
///     The function call will fail if the calling process is not running in 
///     TCB.
/// </remarks>
HRESULT RegisterTestHarness(
    __in_z LPCWSTR pszProcessName
);

/// <summary>
///     Function used to register a test harness with the system. The system
///     will treat this process differently (not kill it in OOM conditions, 
///     etc).
/// </summary>
/// <param name="pszProcessName">
///    Fully qualifed path of the test process name
/// </param>
/// <returns>
///     HRESULT. 
/// </returns>
/// <remarks>
///     The function call will fail if the calling process is not running in 
///     TCB.
/// </remarks>
HRESULT UnregisterTestHarness(
    __in_z LPCWSTR pszProcessName
);


HRESULT WINAPI CreateReminder(
  LPCWSTR pszTitle,
  LPCWSTR pszDetails,
  LPCWSTR pszApplication,
  LPCWSTR pszArguments,
  LPCWSTR pszSound,
  DWORD dwActionFlags,
  DWORD dwEndTimeLow,
  DWORD dwEndTimeHigh,
  CEOID oid  
);

typedef enum {
    MESSAGE_TOAST_TYPE_DEFAULT = 0,
    MESSAGE_TOAST_TYPE_ACHIEVEMENT = 1,
} MESSAGE_TOAST_TYPE;

typedef struct _MESSAGETOASTDATA{
    ULONGLONG appId;  // Used for setting the notification glow and retrieving the icon
    PWSTR pszText1; // Display string
    PWSTR pszText2; // Display string
    PWSTR pszTaskUri ; // Executed when the notification is clicked
    PWSTR pszSound   ; // the event sound that will play when this toast is displayed
} MESSAGETOASTDATA, *LPMESSAGETOASTDATA;

HRESULT WINAPI SHPostMessageToast(LPMESSAGETOASTDATA pMessageToastData);

HRESULT WINAPI RaiseGameAchievementMessageToast(LPMESSAGETOASTDATA pAchievementData);

/// <summary>
///     Returns the amount of memory that the foreground UI app is allowed to use.
/// </summary>
/// <returns>
///     S_OK on success
///     Other HRESULTs on error
/// </returns>
HRESULT SHGetApplicationCap(
    __out DWORD *pcbApplicationCap);

/// <summary>
///     Deletes the sound file from windows/ringtones directory
/// </summary>
/// <returns>
///     S_OK on success
///     Other HRESULTs on error
/// </returns>
HRESULT SHDeleteSoundFile(__in LPCWSTR pszSoundFile);


#include <ResourceManagementValues.h>


/// <summary>
/// Get a value from the Resource Manager that will inform an app  
/// as to how it should restrain its own resource usage in order to be well-behaved 
/// and to stay within the hard limits imposed by the Resource Manager.
/// </summary>
/// <param name="rmv">A RMV_* value that identifies the Resource Management value 
///   the caller wishes to retrieve</param>
/// <param name="pdwValue">The returned value</param>
/// <returns>
/// S_FALSE if the ResourceManager has no value for this caller process
/// </returns>
HRESULT
SHGetResourceManagementValue(
    DWORD rmv,
    DWORD *pdwValue);



#define MAXPAGEIDLENGTH 256
#define MAXTASKURI  1024

/// <summary>
/// Information about a page
/// </summary>
typedef struct _PAGEINFO
{
    TASKID taskId;
    TASKID sessionId;
    DWORD dwProcessId;
    DWORD hPageHandle;
    HWND hwnd;
    DWORD orientations; // supported UI orientations
    WCHAR szTaskUri[MAXTASKURI];
    WCHAR szPageId[MAXPAGEIDLENGTH];
} PAGEINFO;


/// <summary>
/// Gets information about the foreground page
/// </summary>
/// <param name="pPageInfo">Returns information about the foreground page.</param>
HRESULT 
SHGetForegroundPageInfo(
          __out PAGEINFO* pPageInfo);

/// <summary>
/// A test hook to expose how much memory is being used by various categories 
/// of processes.
/// </summary>
/// <param name="pcbUsedByOs">Bytes used by system processes</param>
/// <param name="pcbUsedByAgents">Bytes used by background agents</param>
/// <param name="pcbUsedByForeground">Bytes used by the foreground UI app</param>
/// <param name="pcbReservedForOsAndAgents">Bytes reserved for (but not necessarily used by) the OS and all agents</param>
/// <param name="pcbReservedByAgents">Bytes reserved for (but not necessarily used by) all agents</param>
/// <param name="pcbTotal">Total memory usage of the entire system</param>
HRESULT
SHGetMemoryUsage(
    __out DWORD* pcbUsedByOs, 
    __out DWORD* pcbUsedByAgents, 
    __out DWORD* pcbUsedByForeground,     
    __out DWORD *pcbReservedForOsAndAgents,
    __out DWORD *pcbReservedByAgents,
    __out DWORD* pcbTotal);
    

/// <summary>
/// Gets the Product ID of the specified process.
/// </summary>
/// <param name="pProductId">Pointer to the returned Product ID</param>
/// <param name="pid">The Process ID</param>
HRESULT
SHGetProductIdFromProcessId(
    DWORD pid,
    __out GUID* pProductId);

/// <summary>
/// Check if an product is being debugged.
/// </summary>
/// <param name="pProductId">
///     pointer to product ID
/// </param>
/// <param name="pfDebugging">
///     pointer to the returned value
/// </param>
/// <returns>
/// HRESULT
/// </returns>
HRESULT
SHIsDebugSessionActive(
    __in GUID* pProductId, 
    __out BOOL* pfDebugging);

/// <summary>
/// Gets the process ID of the foreground page (not necessarily the foreground UI page)
/// </summary>
/// <param name="pdwProcessId">Out pointer to the process ID</param>
/// <returns>
/// HRESULT
/// </returns>
HRESULT
SHGetForegroundProcessId(
    __out DWORD* pdwProcessId);


#ifdef __cplusplus
inline HRESULT SHLaunchStart(HANDLE *phSession = NULL)
{
    return SHLaunchSessionByUri(L"app://5B04B775-356B-4AA0-AAF8-6491FFEA5602/Start", phSession);
}

} // extern "C"
#endif


#endif // __AYGSHELL_H__

