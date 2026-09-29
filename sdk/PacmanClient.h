#pragma once
#ifndef PACMANCLIENT_H
#define PACMANCLIENT_H

class CApplicationInfo : public IUnknown
{
public:
	virtual unsigned long long GetAppID() = NULL;
	virtual GUID *GetProductID() = NULL;
	virtual GUID *GetInstanceID() = NULL;
	virtual GUID *GetOfferID() = NULL;
	virtual wchar_t *GetDefaultTask() = NULL;
	virtual wchar_t *GetTitle() = NULL;
	virtual wchar_t *GetApplicationIcon() = NULL;
	virtual int IsNotified() = NULL; 
	virtual int AppInstallType() = NULL; 
	virtual int GetAppState() = NULL;
	virtual int IsRevoked() = NULL; 
	virtual int IsUpdateAvailable() = NULL; 
	virtual FILETIME* GetLastTimeRun() = NULL; 
	virtual FILETIME* GetInstallDate() = NULL;
	virtual int IsUninstallable() = NULL;
	virtual int IsThemable() = NULL; 
	virtual wchar_t *GetInstallFolder() = NULL; 
	virtual wchar_t *GetDataFolder() = NULL; 
	virtual int GetRating() = NULL;
	virtual wchar_t *GetGenre() = NULL; 
	virtual wchar_t *GetPublisher() = NULL; 
	virtual wchar_t *GetAuthor() = NULL; 
	virtual wchar_t *GetDescription() = NULL; 
	virtual wchar_t *GetVersion() = NULL; 
	virtual void GetInvocationInfo(wchar_t** pszInvocationUrn, wchar_t** pszInvocationParameters) = NULL;
	virtual wchar_t *GetImagePath() = NULL; 

	virtual char GetAppPlatMajorVersion() = NULL;
	virtual char GetAppPlatMinorVersion() = NULL;
};


class CDatabaseIterator : public IUnknown
{
public:
	virtual int GetNext(CApplicationInfo **) = NULL;
};


// System APIs
extern "C" 
{
	HRESULT	GetApplicationInfoByProductID(GUID, CApplicationInfo **);
	HRESULT	GetAllApplications(CDatabaseIterator **);
	HRESULT	GetAllVisibleApplications(CDatabaseIterator **);
	BOOL	SetEventData(HANDLE hEvent, DWORD dwData);
	DWORD	GetEventData(HANDLE hEvent); 
	HRESULT PMBeginInstall(void *package);
	HRESULT PMBeginDeployPackage(void *package);
	HRESULT PMBeginUpdateDeployedPackage(void *package);
	HRESULT PMBeginUninstall(GUID guid);
	void PMRegisterForNotification(/*NotificationListener*/void *, int n1, int n2);
	void PMUnregisterFromNotification(/*NotificationListener*/void *);
}

#endif