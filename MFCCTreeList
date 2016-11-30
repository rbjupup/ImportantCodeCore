添加项
  	HTREEITEM root=m_treeContrl.InsertItem(_T("nihao"),0,0);
	 
	HTREEITEM root1=m_treeContrl.InsertItem(_T("shenm"),0,0,root,TVI_LAST);

	m_treeContrl.InsertItem(_T("dd"),0,0,root1,TVI_LAST);
	m_treeContrl.InsertItem(_T("vv"),0,0,root1,TVI_LAST);
  

	CPoint oPoint;
	UINT nFlag;
	GetCursorPos((&oPoint));//捡取光标的位置，以屏幕坐标表示
	m_treeContrl.ScreenToClient(&oPoint);//将屏幕坐标转化为客户区坐标
	HTREEITEM oSectItem=m_treeContrl.HitTest(oPoint,&nFlag);//得到鼠标位置的树节点
	if (oSectItem==NULL)
	{
		return;
	}
	m_treeContrl.SelectItem(oSectItem);//选中此节点
	if(nFlag&TVHT_ONITEMSTATEICON)
	{
		BOOL bCheck=!m_treeContrl.GetCheck(oSectItem);
		//为了一致化树形控件的选中状态，需要设置当前选中项的复选框为改变后的状态
		m_treeContrl.SetCheck(oSectItem,bCheck);
		//一致化树形控件复选框状态
		ConsistentChildCheck(oSectItem);
		ConsistentParentCheck(oSectItem);
		//将当前选中项的复选框状态复原，MFC会自动响应复选框状态的改变绘制
		m_treeContrl.SetCheck(oSectItem,!bCheck);

	}
	*pResult = 0;
