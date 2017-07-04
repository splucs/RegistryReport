#pragma once

//SYSTEM
#define WINNT_CURVERSION_KEY	L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"
#define CURBUILD_STR			L"CurrentBuild"
#define PRODUCTNAME_STR			L"ProductName"
#define PRODUCTID_STR			L"ProductId"
#define BUILDBRANCH_STR			L"BuildBranch"
#define BUILDGUID_STR			L"BuildGUID"
#define ORGANIZATION_STR		L"RegisteredOrganization"
#define OWNER_STR				L"RegisteredOwner"
#define SYSROOT_STR				L"SystemRoot"
#define RELEASEID_STR			L"ReleaseId"
#define EDITIONID_STR			L"EditionId"
#define INSTALLTYPE_STR			L"InstallationType"

#define WIN_CURVERSION_KEY		L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion"
#define COMMONFILESDIR_STR		L"CommonFilesDir"
#define COMMONFILES86DIR_STR	L"CommonFilesDir (x86)"
#define PROGRAMFILESDIR_STR		L"ProgramFilesDir"
#define PROGRAMFILES86DIR_STR	L"ProgramFilesDir (x86)"
#define DEVICEPATH_STR			L"DevicePath"

#define CRIPTOGRAPHY_KEY		L"SOFTWARE\\Microsoft\\Cryptography"
#define MACHINEGUID_STR			L"MachineGuid"

//OFFICE
#define OFFICE32_2003_KEY		L"SOFTWARE\\Microsoft\\Office\\11.0\\Registration"
#define OFFICE32_2007_KEY		L"SOFTWARE\\Microsoft\\Office\\12.0\\Registration"
#define OFFICE32_2010_KEY		L"SOFTWARE\\Microsoft\\Office\\14.0\\Registration"
#define OFFICE32_2013_KEY		L"SOFTWARE\\Microsoft\\Office\\15.0\\Registration"
#define OFFICE32_2016_KEY		L"SOFTWARE\\Microsoft\\Office\\16.0\\Registration"
#define OFFICE64_2003_KEY		L"SOFTWARE\\WOW6432Node\\Microsoft\\Office\\11.0\\Registration"
#define OFFICE64_2007_KEY		L"SOFTWARE\\WOW6432Node\\Microsoft\\Office\\12.0\\Registration"
#define OFFICE64_2010_KEY		L"SOFTWARE\\WOW6432Node\\Microsoft\\Office\\14.0\\Registration"
#define OFFICE64_2013_KEY		L"SOFTWARE\\WOW6432Node\\Microsoft\\Office\\15.0\\Registration"
#define OFFICE64_2016_KEY		L"SOFTWARE\\WOW6432Node\\Microsoft\\Office\\16.0\\Registration"
#define DIGITALPRODID_STR		L"DigitalProductId"

//LOGON
#define WINLOGON_KEY			L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"
#define AUTOADMIN_STR			L"AutoAdminLogon"
#define DEFAULT_DOMAIN_STR		L"DefaultDomainName"
#define DEFAULT_USER_STR		L"DefaultUserName"
#define SCREENSAVER_STR			L"ScreenSaverGracePeriod"
#define SHELL_STR				L"Shell"
#define SHUTDOWNFLAGS_DW		L"ShutdownFlags"

#define LOGON_KEY				L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\LogonUI"
#define LASTUSER_STR			L"LastLoggedOnUser"
#define LASTUSERSID_STR			L"LastLoggedOnUserSID"

#define LOGONANIMATION_KEY		L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\LogonUI\\BootAnimation"
#define DISABLESTARTUPSOUND_DW	L"DisableStartupSound"

//EXPLORER
#define LOCKSCREEN_KEY			L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Lock Screen"
#define SLIDESHOWENABLED_DW		L"SlideshowEnabled"

#define EXPLORERADV_KEY			L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced"
#define HIDDEN_DW				L"Hidden"
#define SUPERHIDDEN_DW			L"ShowSuperHidden"
#define ENABLESTARTMENU_DW		L"EnableStartMenu"
#define FILTER_DW				L"Filter"
#define HIDEFILEEXT_DW			L"HideFileExt"

#define	APPLETS_KEY				L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Applets\\Regedit"
#define LASTEDITEDREG_STR		L"LastKey"

//DOMAIN
#define VOLATILE_KEY			L"Volatile Environment"
#define APPDATA_STR				L"APPDATA"
#define HOMEDRIVE_STR			L"HOMEDRIVE"
#define HOMEPATH_STR			L"HOMEPATH"
#define LOCALAPPDATA_STR		L"LOCALAPPDATA"
#define LOGONSERVER_STR			L"LOGONSERVER"
#define USERDOMAIN_STR			L"USERDOMAIN"
#define USERNAME_STR			L"USERNAME"
#define USERPROFILE_STR			L"USERFPROFILE"

#define TCPIP_KEY				L"SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters"
#define HOSTNAME_STR			L"HostName"
#define DOMAIN_STR				L"Domain"

//PAINT
#define	PAINT_KEY				L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Applets\\Paint\\Recent File List"
#define PAINTLASTUSED1_STR		L"File1"
#define PAINTLASTUSED2_STR		L"File2"
#define PAINTLASTUSED3_STR		L"File3"
#define PAINTLASTUSED4_STR		L"File4"
#define PAINTLASTUSED5_STR		L"File5"

//TIME ZONE
#define TIMEZONE_KEY			L"SYSTEM\\CurrentControlSet\\Control\\TimeZoneInformation"
#define DYNDAYLIGHTDISABLED_DW	L"DynamicDaylightTimeDisabled"
#define TIMEZONENAME_STR		L"TimeZoneKeyName"