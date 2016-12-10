logs


#define logs(mlog)	{\
	CFile test;\
	test.Open(_T("D:\\robojun\\pcbBugLog.txt"),CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);\
	test.SeekToEnd();\
	test.Write(mlog,mlog.GetLength());\
	test.Close();\
	}