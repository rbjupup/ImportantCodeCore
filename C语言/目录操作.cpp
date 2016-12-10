/*************************************************************
目录
*************************************************************/
函数名称 : FolderExist   (判断文件夹是否存在)
函数名称 : FileExist   (判断文件是否存在)
函数名称 : CreateAllDirectories   (创建长路径文件夹)
函数名称 : FindFileSameExtension   (寻找相同后缀的文件)
函数名称 : CreateFolder   (创建文件夹)
函数名称 : DelDir   (删除文件夹)
函数名称 : void splitpath(TCHAR *sFilename)   (分解路径)
	
	
/////////////////目录检查、文件检查、目录创建
BOOL FolderExist(CString strPath)
{
	WIN32_FIND_DATA   wfd;
	BOOL rValue = FALSE;
	HANDLE hFind = FindFirstFile(strPath, &wfd);
	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = TRUE;   
	}
	FindClose(hFind);
	return rValue;
}

BOOL FileExist(CString strFileName)
{
	CFileFind fFind;
	return fFind.FindFile(strFileName); 
}


BOOL CreateAllDirectories(CString strDir)
{
	//remove ending / if exists
	if(strDir.Right(1)=="\\")
		strDir=strDir.Left(strDir.GetLength()-1); 

	// base case . . .if directory exists
	if(GetFileAttributes(strDir)!=-1) 
		return FALSE;

	// recursive call, one less directory
	int nFound = strDir.ReverseFind('\\');
	CreateAllDirectories(strDir.Left(nFound)); 

	// actual work
	BOOL bSuccess = FALSE;//成功标志
	// 	CreateDirectory(strDir,NULL); 
	bSuccess = CreateDirectory(strDir, NULL) ? TRUE : FALSE;
	return bSuccess;
}
//查找文件夹中所有相同后缀的文件
CString FindFileSameExtension(CString strPath,CString strExtension)
{
	CFileFind finder; 
	CString FileName;
	CString FilePath;
	bool bExist = finder.FindFile(strPath); 
	if(bExist) 
	{ 
		finder.FindNextFile();
		FileName = finder.GetFileName();
		FilePath = finder.GetFilePath();								//文件的全路径 
		CString Exten;
		Exten = PathFindExtension(FilePath);
		if (strcmp(Exten,strExtension) == 0)		//获取文件的后缀并判断是否与要找的后缀相同
		{
			finder.Close();
			return finder.GetFileTitle();
		}
	}
	finder.Close();
	return "";
}

BOOL CreateFolder(CString strPath)
{
	// 	SECURITY_ATTRIBUTES attrib;
	// 	attrib.bInheritHandle = FALSE;
	// 	attrib.lpSecurityDescriptor = NULL;
	// 	attrib.nLength =sizeof(SECURITY_ATTRIBUTES);
	//上面定义的属性可以省略。 直接return ::CreateDirectory( path, NULL); 即可
	return ::CreateDirectory( strPath, NULL/*&attrib*/);
} 

BOOL DelDir(LPCTSTR pszDir)
{
	if(!pszDir)
	{
		return FALSE;
	}

	if(!PathFileExists(pszDir))
	{
		return TRUE;
	}

	BOOL bRet = FALSE;

	TCHAR szSearch[MAX_PATH] = {0};
	_tcscpy_s(szSearch, MAX_PATH, pszDir);
	PathAddBackslash(szSearch);
	PathAppend(szSearch, _T("*.*"));

	TCHAR szTmp[MAX_PATH] = {0};

	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile(szSearch, &data);
	while(hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			if(_tcscmp(data.cFileName, _T(".")) == 0 || _tcscmp(data.cFileName, _T("..")) == 0)
			{
				break;
			}

			_tcscpy_s(szTmp, MAX_PATH, pszDir);
			PathAddBackslash(szTmp);
			PathAppend(szTmp, data.cFileName);

			if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				bRet = DelDir(szTmp);
			}
			else
			{
				bRet = DeleteFile(szTmp);
			}
		} while (FALSE);

		if(!FindNextFile(hFind, &data))
		{
			break;
		}
	}
	FindClose(hFind);

	bRet = RemoveDirectory(pszDir);
	if(!bRet)
	{
		DWORD dwErrCode = GetLastError();
		return bRet;
	}
	return bRet;
}

/*************************************************************
函数名称 : void splitpath(TCHAR *sFilename)
函数功能 : 将文件名分解
使用示例 :
*************************************************************/
void splitpath(TCHAR *sFilename) {	
	TCHAR pstrPath[MAX_PATH];

	TCHAR sFilename[MAX_PATH];

	TCHAR sDrive[_MAX_DRIVE];

	TCHAR sDir[_MAX_DIR];

	TCHAR sFname[_MAX_FNAME];

	TCHAR sExt[_MAX_EXT];

	GetModuleFileName(NULL, sFilename, _MAX_PATH);

	_tsplitpath_s(sFilename, sDrive, sDir, sFname, sExt);
}
