namespace hise {
using namespace juce;

#define LINE(x) x "\r\n"

static const unsigned char winInstallerTemplate_lines[] =
LINE(R"([Setup])")
LINE(R"(#define AppName "%PRODUCT%")")
LINE(R"(AppName={#AppName})")
LINE(R"(AppVersion=%VERSION%)")"\n"
LINE(R"(DefaultDirName={pf}\%COMPANY%\%PRODUCT%)")
LINE(R"(DefaultGroupName={#AppName})")
LINE(R"(Compression=lzma2)")
LINE(R"(SolidCompression=yes)")
LINE(R"(OutputDir=.\build)")
LINE(R"(ArchitecturesInstallIn64BitMode=x64)")
LINE(R"(OutputBaseFilename={#AppName} Installer %VERSION%)")
LINE(R"(LicenseFile=EULA.txt)")
LINE(R"(PrivilegesRequired=admin)")
LINE(R"()")
LINE(R"(SetupLogging=yes)")
LINE(R"(ChangesAssociations=no)")
LINE(R"()")
LINE(R"([Types])")
LINE(R"(Name: "full"; Description: "Full installation")")
LINE(R"(Name: "custom"; Description: "Custom installation"; Flags: iscustom)")
LINE(R"()")
LINE(R"([Dirs])")
LINE(R"(Name: "{app}\"; Permissions: users-modify powerusers-modify admins-modify system-modify)")
LINE(R"()")
LINE(R"([Components])")
LINE(R"(Name: "app"; Description: "{#AppName} Standalone application"; Types: full custom;)")
LINE(R"(Name: "vst2_32"; Description: "{#AppName} 32-bit VSTi Plugin"; Types: full custom;)")
LINE(R"(Name: "vst2_64"; Description: "{#AppName} 64-bit VSTi Plugin"; Types: full custom; Check: Is64BitInstallMode;)")
LINE(R"(;BEGIN_AAX)")
LINE(R"(%AAXONLY%Name: "aax"; Description: "{#AppName} AAX Plugin"; Types: full custom;)")
LINE(R"(;END_AAX)")
LINE(R"()")
LINE(R"([Files])")
LINE(R"()")
LINE(R"(; Standalone)")
LINE(R"(Source: "build\App\{#AppName} x86.exe"; DestDir: "{app}"; Flags: ignoreversion; Components: app; Check: not Is64BitInstallMode)")
LINE(R"(Source: "build\App\{#AppName} x64.exe"; DestDir: "{app}"; Flags: ignoreversion; Components: app; Check: Is64BitInstallMode)")
LINE(R"()")
LINE(R"(; VST)")
LINE(R"(Source: "build\VST\{#AppName} x86.dll"; DestDir: "{code:GetVST2Dir_32}"; Flags: ignoreversion; Components: vst2_32; Check: not Is64BitInstallMode)")
LINE(R"()")
LINE(R"(Source: "build\VST\{#AppName} x86.dll"; DestDir: "{code:GetVST2Dir_32}"; Flags: ignoreversion; Components: vst2_32; Check: Is64BitInstallMode)")
LINE(R"(Source: "build\VST\{#AppName} x64.dll"; DestDir: "{code:GetVST2Dir_64}"; Flags: ignoreversion; Components: vst2_64; Check: Is64BitInstallMode)")
LINE(R"()")
LINE(R"(;BEGIN_AAX)")
LINE(R"(%AAXONLY%Source: "build\AAX\{#AppName}.aaxplugin\*.*"; DestDir: "{cf}\Avid\Audio\Plug-Ins\{#AppName}.aaxplugin\"; Flags: ignoreversion recursesubdirs; Components: aax)")
LINE(R"(;END_AAX)")
LINE(R"()")
LINE(R"([Icons])")
LINE(R"(Name: "{group}\{#AppName}"; Filename: "{app}\{#AppName} x64.exe"; Check: Is64BitInstallMode)")
LINE(R"(Name: "{group}\{#AppName}"; Filename: "{app}\{#AppName} x86.exe"; Check: not Is64BitInstallMode)")
LINE(R"(Name: "{group}\Uninstall {#AppName}"; Filename: "{app}\unins000.exe")")
LINE(R"()")
LINE(R"([Code])")
LINE(R"(var)")
LINE(R"(  OkToCopyLog : Boolean;)")
LINE(R"(  VST2DirPage_32: TInputDirWizardPage;)")
LINE(R"(  VST2DirPage_64: TInputDirWizardPage;)")
LINE(R"()")
LINE(R"(procedure InitializeWizard;)")
LINE(R"()")
LINE(R"(begin)")
LINE(R"()")
LINE(R"(  if IsWin64 then begin)")
LINE(R"(    VST2DirPage_64 := CreateInputDirPage(wpSelectDir,)")
LINE(R"(    'Confirm 64-Bit VST2 Plugin Directory', '',)")
LINE(R"(    'Select the folder in which setup should install the 64-bit VST2 Plugin, then click Next.',)")
LINE(R"(    False, '');)")
LINE(R"(    VST2DirPage_64.Add('');)")
LINE(R"(    VST2DirPage_64.Values[0] := ExpandConstant('{reg:HKLM\SOFTWARE\VST,VSTPluginsPath|{pf}\Steinberg\VSTPlugins}\');)")
LINE(R"()")
LINE(R"(    VST2DirPage_32 := CreateInputDirPage(wpSelectDir,)")
LINE(R"(      'Confirm 32-Bit VST2 Plugin Directory', '',)")
LINE(R"(      'Select the folder in which setup should install the 32-bit VST2 Plugin, then click Next.',)")
LINE(R"(      False, '');)")
LINE(R"(    VST2DirPage_32.Add('');)")
LINE(R"(    VST2DirPage_32.Values[0] := ExpandConstant('{reg:HKLM\SOFTWARE\WOW6432NODE\VST,VSTPluginsPath|{pf32}\Steinberg\VSTPlugins}\');)")
LINE(R"(  end else begin)")
LINE(R"(    VST2DirPage_32 := CreateInputDirPage(wpSelectDir,)")
LINE(R"(      'Confirm 32-Bit VST2 Plugin Directory', '',)")
LINE(R"(      'Select the folder in which setup should install the 32-bit VST2 Plugin, then click Next.',)")
LINE(R"(      False, '');)")
LINE(R"(    VST2DirPage_32.Add('');)")
LINE(R"(    VST2DirPage_32.Values[0] := ExpandConstant('{reg:HKLM\SOFTWARE\VST,VSTPluginsPath|{pf}\Steinberg\VSTPlugins}\');)")
LINE(R"(  end;)")
LINE(R"(end;)")
LINE(R"()")
LINE(R"(function GetVST2Dir_32(Param: String): String;)")
LINE(R"(begin)")
LINE(R"(  Result := VST2DirPage_32.Values[0])")
LINE(R"(end;)")
LINE(R"()")
LINE(R"(function GetVST2Dir_64(Param: String): String;)")
LINE(R"(begin)")
LINE(R"(  Result := VST2DirPage_64.Values[0])")
LINE(R"(end;)")
LINE(R"()")
LINE(R"(procedure CurStepChanged(CurStep: TSetupStep);)")
LINE(R"(begin)")
LINE(R"(  if CurStep = ssDone then)")
LINE(R"(    OkToCopyLog := True;)")
LINE(R"(end;)")
LINE(R"()")
LINE(R"(procedure DeinitializeSetup();)")
LINE(R"(begin)")
LINE(R"(  if OkToCopyLog then)")
LINE(R"(    FileCopy (ExpandConstant ('{log}'), ExpandConstant ('{app}\InstallationLogFile.log'), FALSE);)")
LINE(R"(  RestartReplace (ExpandConstant ('{log}'), '');)")
LINE(R"(end;)")
LINE(R"()")
LINE(R"([UninstallDelete])")
LINE(R"(Type: files; Name: "{app}\InstallationLogFile.log")");

#undef LINE

const char* winInstallerTemplate = (const char*)winInstallerTemplate_lines;


} // namespace hise