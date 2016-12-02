/************************************************************************
函数名称: SetScrollSizes 
函数功能: 设置滚动条view的 
输入参数: TCHAR * 字符串 TCHAR *字符串 
输出参数: 结果字符串
例子:https://msdn.microsoft.com/en-us/library/3t073d82.aspx
************************************************************************/
CScrollView::SetScrollSizes(
    int nMapMode,  
    SIZE sizeTotal,  
    const SIZE& sizePage = sizeDefault,  
    const SIZE& sizeLine = sizeDefault);
