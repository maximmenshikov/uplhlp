# uplhlp — Policy Helper

`uplhlp.exe` is a usermode helper for Windows CE and Windows Phone 7. It comes
from the FullUnlock v4.0 project (© Maxim Menshikov (ultrashot), 2012). It is the companion to the
`upl` policy engine. `upl` posts a message whenever it denies access to a
third-party app. `uplhlp` turns that message into a localized toast notification
that offers to unlock the app.

This is legacy research and homebrew code for a platform that reached end of
life long ago.

## How it works

`uplhlp` runs a message loop (`main.cpp`):

1. It opens the shared policy message queue (`PolicyMsgQueue.cpp`). `upl` writes
   `ACCESS_DENIED` records to the same queue. `uplhlp` blocks and waits for a
   message.
2. For each message, it decodes the offending app's product id from the account
   SID (`GetProductID`). It resolves the application through the Package Manager
   client (`PacmanClient.h` and `pacmanclient.lib`).
3. For a promotable app, it posts a toast (`SHPostMessageToast`).
   `StringLoader.cpp` localizes the text through a MUI resource lookup, backed by
   `StringLoader.lib`. `Translation.cpp` supplies a small string table that the
   registry can override. A tap on the toast launches the unlock task for that
   app.

`AccountManager.cpp` and `adb7.cpp` wrap the ADB (account database) API. The
helper uses that API to inspect account privileges.

## Layout

```
uplhlp/
├── uplhlp.vcproj       Visual Studio 2008 project (WM6 Pro ARMv4I)
├── .clang-format       Formatting rules for src/
├── src/                Project sources
│   ├── main.cpp             Message-queue loop and toast notification
│   ├── PolicyMsgQueue.cpp/.h    Shared policy message queue
│   ├── StringLoader.cpp/.h      MUI resource-string lookup (GetLocalizedString)
│   ├── Translation.cpp/.h       Localized string table
│   ├── AccountManager.cpp/.h, adb7.cpp   ADB account/privilege helpers
│   ├── stdafx.h/.cpp        Precompiled-header stub
│   ├── resource.h, uplhlp.rc
│   └── (no .def — this is an executable)
└── sdk/                Vendored SDK headers + import libraries
    ├── adb7.h, aygshell7.h, PacmanClient.h   ADB / shell / package-manager APIs
    └── coredll7.lib, aygshell7.lib, pacmanclient.lib, StringLoader.lib
```

## Building

You need Visual Studio 2008 with the Windows Mobile 6 Professional SDK (ARMV4I)
installed. To build the helper:

1. Open `uplhlp.vcproj`.
2. Build the Release configuration.

The output is `uplhlp.exe`. The include and library paths point at `src/` and
`sdk/`. The project is self-contained. `coredll7.lib`, `aygshell7.lib`,
`pacmanclient.lib`, and `StringLoader.lib` are vendored under `sdk/`. The sibling
`StringLoader` project builds `StringLoader.lib`.
