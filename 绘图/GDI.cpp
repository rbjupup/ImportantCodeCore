/*************************************************************
目录
*************************************************************/
GDI+环境初始化
保存文件
函数名称 : addPathtest() (路径叠加示例)
/*************************************************************
函数名称 : GDI+环境初始化
使用示例 :
*************************************************************/
#include <gdiplus.h>
#pragma comment (lib,"GdiPlus.lib")
using namespace Gdiplus;
(点开头文件就能看到)

//全局变量
ULONG_PTR gdiplusToken;
//初始化环境
GdiplusStartupInput gdiplusstartupinput;
GdiplusStartup(&gdiplusToken, &gdiplusstartupinput, NULL);
//释放
GdiplusShutdown(gdiplusToken);




/*************************************************************
函数名称 : saveImg()
函数功能 : 保存文件示例
函数名称 : GetEncoderClsid()
函数功能 : 根据文件名获取CLSID
使用示例 :
CLSID t_encoderClsid;
GetEncoderClsid(L"image/bmp",&t_encoderClsid);
*************************************************************/
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)  
{  
	UINT  num = 0;  
	UINT  size = 0;  
	ImageCodecInfo* pImageCodecInfo = NULL;  
	GetImageEncodersSize(&num, &size);  
	if(size == 0)  
		return -1;  

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));  
	if(pImageCodecInfo == NULL)  
		return -1;  

	GetImageEncoders(num, size, pImageCodecInfo);  
	for(UINT j = 0; j < num; ++j)  
	{  
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )  
		{  
			*pClsid = pImageCodecInfo[j].Clsid;  
			free(pImageCodecInfo);  
			return j;  
		}      
	}  
	free(pImageCodecInfo);  
	return -1;  
}   
void saveImg() {	
Bitmap *m_pbitmap = new Bitmap(1000,1000,PixelFormat16bppRGB555);
Graphics *t_pgraphics = Graphics::FromImage(m_pbitmap);
t_pgraphics->DrawLine(&Pen(Color::White),Point(0,0),Point(1000,1000));
CLSID t_encoderClsid;
GetEncoderClsid(L"image/bmp",&t_encoderClsid);
CString strBmp;
strBmp.Format(_T("D:\\1.bmp"));
USES_CONVERSION;
m_pbitmap->Save(T2W(strBmp.GetBuffer()),&t_encoderClsid,NULL);
strBmp.ReleaseBuffer();
 }

/*************************************************************
函数名称 : addPathtest()
函数功能 : 路径叠加示例
函数类型 : addPath()例程
使用示例 :
*************************************************************/
void addPathtest()
{
	Bitmap *m_pbitmap = new Bitmap(1000,1000,PixelFormat16bppRGB555);
	Graphics *p_graphics = Graphics::FromImage(m_pbitmap);
	Pen pen(Color(255,0,255),2);
	Rect rect(0,0,100,50);
	GraphicsPath path;
	path.AddLine(100,100,100,200);
	path.AddLine(100,200,200,200);
	path.AddLine(200,200,200,100);
	path.AddLine(200,100,100,100);
	GraphicsPath path2;
 	path2.AddEllipse(150,150,30,30);

	path.AddPath(&path2,false);

	p_graphics->FillPath(&SolidBrush(Color::White),&path);

	CLSID t_encoderClsid;
	GetEncoderClsid(L"image/bmp",&t_encoderClsid);
	CString strBmp;
	strBmp.Format(_T("D:\\1.bmp"));
	USES_CONVERSION;
	m_pbitmap->Save(T2W(strBmp.GetBuffer()),&t_encoderClsid,NULL);
	strBmp.ReleaseBuffer();
}
