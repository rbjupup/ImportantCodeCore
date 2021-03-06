/*************************************************************
目录
*************************************************************/
函数名称 : IplImageToBitmap     (实现Opencv和GDI图像互转)
函数名称 : BitmapToIplImage     (实现Opencv和GDI图像互转)






/*************************************************************
函数名称 : IplImageToBitmap
函数功能 : 实现Opencv和GDI图像互转
使用示例 :
CDC*pDC = GetDC();
Graphics graph(pDC->GetSafeHdc());
IplImage*pImage = cvLoadImage("c:\\test.jpg",1);
Bitmap*img = IplImageToBitmap(pImage);
graph.DrawImage(img,0,0);
*************************************************************/


Bitmap* IplImageToBitmap(IplImage* pIplImg)
{
if(pIplImg)
{
Bitmap *pBitmap = new Bitmap (pIplImg->width, pIplImg->height, PixelFormat24bppRGB);
if (! pBitmap)
return NULL;
BitmapData bmpData;
Rect rect(0, 0, pIplImg->width, pIplImg->height);
pBitmap->LockBits(&rect, ImageLockModeWrite, PixelFormat24bppRGB, &bmpData);
BYTE *pByte = (BYTE*)bmpData.Scan0;
if (pIplImg->widthStep == bmpData.Stride) //likely
memcpy(bmpData.Scan0, pIplImg->imageDataOrigin, pIplImg->imageSize);
pBitmap->UnlockBits(&bmpData);
return pBitmap;
}
else
return NULL;
}

/*************************************************************
函数名称 : BitmapToIplImage
函数功能 : 实现Opencv和GDI图像互转
使用示例 :
CDC* pDC = GetDC();
Bitmap *img = Bitmap::FromFile(L"c:\\test.jpg");
IplImage *pImage =BitmapToIplImage(img);
cvShowImage(" 图片 ",pImage);
*************************************************************/
IplImage* BitmapToIplImage(Bitmap* pBitmap)
{
if (pBitmap)
{
BitmapData bmpData;
Rect rect (0,0,pBitmap->GetWidth (),pBitmap->GetHeight());
pBitmap->LockBits(&rect, ImageLockModeRead, PixelFormat24bppRGB, &bmpData);
BYTE* temp = NULL;
If(bmpData.Stride>0)
temp = (BYTE*)bmpData.Scan0;
else
temp = (BYTE*)bmpData.Scan0 + bmpData.Stride*
(pBitmap->GetHeight()-1);
IplImage* pIplImg = cvCreateImage(cvSize(pBitmap->
GetWidth(), pBitmap->GetHeight()), IPL_DEPTH_8U, 3);
if (! pIplImg)
{
pBitmap->UnlockBits(&bmpData);
return NULL;
}
memcpy (pIplImg ->imageData, temp, abs (bmpData.
Stride)*bmpData.Height);
pBitmap->UnlockBits(&bmpData);
if (bmpData.Stride<0) {
cvFlip(pIplImg, NULL,0);
return pIplImg;
}
else
return NULL;
}
