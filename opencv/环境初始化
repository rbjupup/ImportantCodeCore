/*************************************************************
目录
*************************************************************/
GDI+环境初始化
opencv231环境初始化

/*************************************************************
函数名称 : GDI+环境初始化
使用示例 :
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
	IplImage *pHelloImg;
	pHelloImg = cvLoadImage("D:\\1.bmp");
	cvShowImage("hello",pHelloImg);
*************************************************************/
#include <gdiplus.h>
#pragma comment (lib,"GdiPlus.lib")
using namespace GdiPlus(点开头文件就能看到)

//全局变量
ULONG_PTR gdiplusToken;
//初始化环境
GdiplusStartupInput gdiplusstartupinput;
GdiplusStartup(&gdiplusToken, &gdiplusstartupinput, NULL);
//释放
GdiplusShutdown(gdiplusToken);


/*************************************************************
函数名称 : opencv231环境初始化
使用示例 :
	IplImage *pHelloImg;
	pHelloImg = cvLoadImage("1.bmp");
	cvShowImage("hello",pHelloImg);
*************************************************************/
首先包含文件头目录和库目录
D:\rbj\app\OpenCV231\opencv\build\include\opencv2
D:\rbj\app\OpenCV231\opencv\build\include\opencv
D:\rbj\app\OpenCV231\opencv\build\include

D:\rbj\app\OpenCV231\opencv\build\x64\vc10\lib

然后添加依赖项
opencv_ml231d.lib
opencv_calib3d231d.lib
opencv_contrib231d.lib
opencv_core231d.lib
opencv_features2d231d.lib
opencv_flann231d.lib
opencv_gpu231d.lib
opencv_highgui231d.lib
opencv_imgproc231d.lib
opencv_legacy231d.lib
opencv_objdetect231d.lib
opencv_ts231d.lib
opencv_video231d.lib
opencv_objdetect231.lib
opencv_ts231.lib
opencv_video231.lib
opencv_calib3d231.lib
opencv_contrib231.lib
opencv_core231.lib
opencv_features2d231.lib
opencv_flann231.lib
opencv_gpu231.lib
opencv_highgui231.lib
opencv_imgproc231.lib
opencv_legacy231.lib
opencv_ml231.lib
包含头文件和命名空间

#include <opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
