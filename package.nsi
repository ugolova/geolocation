############################################################################################
#      NSIS Installation Script created by NSIS Quick Setup Script Generator v1.09.18
#               Entirely Edited with NullSoft Scriptable Installation System                
#              by Vlasis K. Barkas aka Red Wine red_wine@freemail.gr Sep 2006               
############################################################################################

!define APP_NAME "DynamicMap"
!define COMP_NAME "Karasavov, Lubeznikov, Fertikov"
!define WEB_SITE "https://github.com/threadend/geolocation"
!define VERSION "1.0.1.0"
!define COPYRIGHT "Karasavov, Lubeznikov, Fertikov  © 2014"
!define DESCRIPTION "Dynamic Map of St Petersburg Subway/Railway"
!define INSTALLER_NAME "dynamicmap-installer.exe"
!define MAIN_APP_EXE "dynamicmap.exe"
!define INSTALL_TYPE "SetShellVarContext current"
!define REG_ROOT "HKCU"
!define REG_APP_PATH "Software\Microsoft\Windows\CurrentVersion\App Paths\${MAIN_APP_EXE}"
!define UNINSTALL_PATH "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"

!define REG_START_MENU "Start Menu Folder"

var SM_Folder

######################################################################

VIProductVersion  "${VERSION}"
VIAddVersionKey "ProductName"  "${APP_NAME}"
VIAddVersionKey "CompanyName"  "${COMP_NAME}"
VIAddVersionKey "LegalCopyright"  "${COPYRIGHT}"
VIAddVersionKey "FileDescription"  "${DESCRIPTION}"
VIAddVersionKey "FileVersion"  "${VERSION}"

######################################################################

SetCompressor ZLIB
Name "${APP_NAME}"
Caption "${APP_NAME}"
OutFile "${INSTALLER_NAME}"
BrandingText "${APP_NAME}"
XPStyle on
InstallDirRegKey "${REG_ROOT}" "${REG_APP_PATH}" ""
InstallDir "$PROGRAMFILES\DynamicMap"

######################################################################

!include "MUI.nsh"

!define MUI_ABORTWARNING
!define MUI_UNABORTWARNING

!insertmacro MUI_PAGE_WELCOME

!ifdef LICENSE_TXT
!insertmacro MUI_PAGE_LICENSE "${LICENSE_TXT}"
!endif

!insertmacro MUI_PAGE_DIRECTORY

!ifdef REG_START_MENU
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "DynamicMap"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${REG_ROOT}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${UNINSTALL_PATH}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${REG_START_MENU}"
!insertmacro MUI_PAGE_STARTMENU Application $SM_Folder
!endif

!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM

!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

######################################################################

Section -MainProgram
${INSTALL_TYPE}
SetOverwrite ifnewer
SetOutPath "$INSTDIR"
File "package\dynamicmap.exe"
File "package\icudt51.dll"
File "package\icuin51.dll"
File "package\icuuc51.dll"
File "package\libgcc_s_dw2-1.dll"
File "package\libstdc++-6.dll"
File "package\libwinpthread-1.dll"
File "package\Qt5Core.dll"
File "package\Qt5Gui.dll"
File "package\Qt5Multimedia.dll"
File "package\Qt5MultimediaWidgets.dll"
File "package\Qt5Network.dll"
File "package\Qt5OpenGL.dll"
File "package\Qt5Positioning.dll"
File "package\Qt5PrintSupport.dll"
File "package\Qt5Qml.dll"
File "package\Qt5Quick.dll"
File "package\Qt5Sensors.dll"
File "package\Qt5Sql.dll"
File "package\Qt5WebKit.dll"
File "package\Qt5WebKitWidgets.dll"
File "package\Qt5Widgets.dll"
SetOutPath "$INSTDIR\plugins"
File "package\plugins\qwindows.dll"
SectionEnd

######################################################################

Section -Icons_Reg
SetOutPath "$INSTDIR"
WriteUninstaller "$INSTDIR\uninstall.exe"

!ifdef REG_START_MENU
!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
CreateDirectory "$SMPROGRAMS\$SM_Folder"
CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}" "-platformpluginpath plugins"
CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}" "-platformpluginpath plugins"
CreateShortCut "$SMPROGRAMS\$SM_Folder\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

!ifdef WEB_SITE
WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
!endif
!insertmacro MUI_STARTMENU_WRITE_END
!endif

!ifndef REG_START_MENU
CreateDirectory "$SMPROGRAMS\DynamicMap"
CreateShortCut "$SMPROGRAMS\DynamicMap\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}" "-platformpluginpath plugins"
CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}" "-platformpluginpath plugins"
CreateShortCut "$SMPROGRAMS\DynamicMap\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

!ifdef WEB_SITE
WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
CreateShortCut "$SMPROGRAMS\DynamicMap\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
!endif
!endif

WriteRegStr ${REG_ROOT} "${REG_APP_PATH}" "" "$INSTDIR\${MAIN_APP_EXE}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayName" "${APP_NAME}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "UninstallString" "$INSTDIR\uninstall.exe"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayIcon" "$INSTDIR\${MAIN_APP_EXE}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayVersion" "${VERSION}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "Publisher" "${COMP_NAME}"

!ifdef WEB_SITE
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "URLInfoAbout" "${WEB_SITE}"
!endif
SectionEnd

######################################################################

Section Uninstall
${INSTALL_TYPE}
Delete "$INSTDIR\dynamicmap.exe"
Delete "$INSTDIR\icudt51.dll"
Delete "$INSTDIR\icuin51.dll"
Delete "$INSTDIR\icuuc51.dll"
Delete "$INSTDIR\libgcc_s_dw2-1.dll"
Delete "$INSTDIR\libstdc++-6.dll"
Delete "$INSTDIR\libwinpthread-1.dll"
Delete "$INSTDIR\Qt5Core.dll"
Delete "$INSTDIR\Qt5Gui.dll"
Delete "$INSTDIR\Qt5Multimedia.dll"
Delete "$INSTDIR\Qt5MultimediaWidgets.dll"
Delete "$INSTDIR\Qt5Network.dll"
Delete "$INSTDIR\Qt5OpenGL.dll"
Delete "$INSTDIR\Qt5Positioning.dll"
Delete "$INSTDIR\Qt5PrintSupport.dll"
Delete "$INSTDIR\Qt5Qml.dll"
Delete "$INSTDIR\Qt5Quick.dll"
Delete "$INSTDIR\Qt5Sensors.dll"
Delete "$INSTDIR\Qt5Sql.dll"
Delete "$INSTDIR\Qt5WebKit.dll"
Delete "$INSTDIR\Qt5WebKitWidgets.dll"
Delete "$INSTDIR\Qt5Widgets.dll"
Delete "$INSTDIR\plugins\qwindows.dll"
 
RmDir "$INSTDIR\plugins"
 
Delete "$INSTDIR\uninstall.exe"
!ifdef WEB_SITE
Delete "$INSTDIR\${APP_NAME} website.url"
!endif

RmDir "$INSTDIR"

!ifdef REG_START_MENU
!insertmacro MUI_STARTMENU_GETFOLDER "Application" $SM_Folder
Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk"
Delete "$SMPROGRAMS\$SM_Folder\Uninstall ${APP_NAME}.lnk"
!ifdef WEB_SITE
Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk"
!endif
Delete "$DESKTOP\${APP_NAME}.lnk"

RmDir "$SMPROGRAMS\$SM_Folder"
!endif

!ifndef REG_START_MENU
Delete "$SMPROGRAMS\DynamicMap\${APP_NAME}.lnk"
Delete "$SMPROGRAMS\DynamicMap\Uninstall ${APP_NAME}.lnk"
!ifdef WEB_SITE
Delete "$SMPROGRAMS\DynamicMap\${APP_NAME} Website.lnk"
!endif
Delete "$DESKTOP\${APP_NAME}.lnk"

RmDir "$SMPROGRAMS\DynamicMap"
!endif

DeleteRegKey ${REG_ROOT} "${REG_APP_PATH}"
DeleteRegKey ${REG_ROOT} "${UNINSTALL_PATH}"
SectionEnd

######################################################################

