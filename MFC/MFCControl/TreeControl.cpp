检查选中
void GetCheckedItems(const CTreeCtrl& tree, CArray<HTREEITEM> *checkedItems, HTREEITEM startItem,CArray<CString> *CArryItemsName)
{
	if (startItem == NULL)
		startItem = tree.GetRootItem();

	for (HTREEITEM item = startItem; item != NULL; item = tree.GetNextItem(item, TVGN_NEXT))
	{
		// figure out if this item is checked or not
		UINT state = (tree.GetItemState(item, TVIS_STATEIMAGEMASK) >> 12) & 15;

		if (state == 2) {
			checkedItems->Add(item);
			CString name;
			name.Format("%s",tree.GetItemText(item));
			CArryItemsName->Add(name);
		}
		// deal with children if present
		HTREEITEM child = tree.GetNextItem(item, TVGN_CHILD);

		if (child != NULL)
			GetCheckedItems(tree, checkedItems, child,CArryItemsName);
	}
}
光标跟随
void TGZDLG::SetTreeItemStatus(CTreeCtrl &TreeTYPE)
{
	CPoint oPoint;
	UINT nFlag;
	GetCursorPos((&oPoint));//捡取光标的位置，以屏幕坐标表示
	TreeTYPE.ScreenToClient(&oPoint);//将屏幕坐标转化为客户区坐标
	HTREEITEM oSectItem=TreeTYPE.HitTest(oPoint,&nFlag);//得到鼠标位置的树节点
	if (oSectItem==NULL)
	{
		return ;
	}
	TreeTYPE.SelectItem(oSectItem);//选中此节点
}
