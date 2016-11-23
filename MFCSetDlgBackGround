	//添加代码对话框背景贴图  
	CPaintDC   dc(this);     
	CRect   rect;     
	GetClientRect(&rect);                                 //获取对话框长宽         
	CDC   dcBmp;                                           //定义并创建一个内存设备环境  
	dcBmp.CreateCompatibleDC(&dc);                         //创建兼容性DC  
	CBitmap   bmpBackground;     
	bmpBackground.LoadBitmap(IDB_BITMAP2);                 //载入资源中的IDB_BITMAP1图片  
	BITMAP   m_bitmap;                                     //图片变量                  
	bmpBackground.GetBitmap(&m_bitmap);                    //将图片载入位图中  
	CBitmap   *pbmpOld=dcBmp.SelectObject(&bmpBackground); //将位图选入临时内存设备环境    
	//调用函数显示图片 StretchBlt显示形状可变  
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcBmp,0,0,  
		m_bitmap.bmWidth,m_bitmap.bmHeight,SRCCOPY);      

	/******************************************************/  
	/** StretchBlt()                                     **/  
	/** 参数x、y位图目标矩形左上角x、y的坐标值 居中      **/  
	/** nWidth、nHeigth位图目标矩形的逻辑宽度和高度      **/  
	/** pSrcDC表示源设备CDC指针                          **/  
	/** xSrc、ySrc表示位图源矩形的左上角的x、y逻辑坐标值 **/  
	/** dwRop表示显示位图的光栅操作方式                  **/  
	/** SRCCOPY用于直接将位图复制到目标环境中            **/  
	/******************************************************/  
