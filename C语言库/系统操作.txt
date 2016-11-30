打开文件下的dos常用命令获取cmd指令
WaitProcess




运行cmd指令并等待指令结束退出
void WaitProcess(LPTSTR FileName= "cmd.exe" ,LPTSTR Param = "/c exproce.exe D:\\")
{
	SHELLEXECUTEINFO ShellInfo = {0};
	ShellInfo.cbSize	= sizeof(SHELLEXECUTEINFO);
	ShellInfo.fMask	= SEE_MASK_NOCLOSEPROCESS;
	ShellInfo.hwnd	= 0;
	ShellInfo.lpVerb	= 0;
	ShellInfo.lpFile	= FileName;     /////传入cmd.exe路径
	ShellInfo.lpParameters	= Param;    //////传入   /c  copy ....
	ShellInfo.lpDirectory	= 0;
	ShellInfo.nShow	= 0;
	ShellInfo.hInstApp	= 0;

	ShellExecuteEx(&ShellInfo);
	WaitForSingleObject(ShellInfo.hProcess,-1);
}