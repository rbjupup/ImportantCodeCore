初始化
1)Char * 初始化
	QString str = "Hello";
  QString converts the const char * data into Unicode using the fromAscii() function. 
 
2)QChar[]数组初始
static const QChar data[4] = { 0x0055, 0x006e, 0x10e3, 0x03a3 };  
QString str(data, 4);  

QRegExp pattern;  
static const QChar unicode[] = { 0x005A, 0x007F, 0x00A4, 0x0060,  
0x1009, 0x0020, 0x0020};  
int size = sizeof(unicode) / sizeof(QChar);  
QString str = QString::fromRawData(unicode, size);  

QString str;  
str.resize(4);  
  
str[0] = QChar('U');  
str[1] = QChar('n');  
str[2] = QChar(0x10e3);  
str[3] = QChar(0x03a3);  

QString str;  
for (int i = 0; i < str.size(); ++i) {  
     if (str.at(i) >= QChar('a') && str.at(i) <= QChar('f'))  
         qDebug() << "Found character in range [a-f]";  
 }  


操作
QString str = "and";  
 str.prepend("rock ");     // str == "rock and"  
 str.append(" roll");        // str == "rock and roll"  
 str.replace(5, 3, "&");   // str == "rock & roll"  
  
 QString x = "free";  
 QString y = "dom";  
 x.append(y);           // x == "freedom"  
 x.insert(x.size(), y);//x == "freedom"  
  
 QString str = "Meal";  
 str.insert(1, QString("ontr"));  
 // str == "Montreal"  
  
 QString s = "Montreal";  
 s.remove(1, 4);     // s == "Meal"  移除1-4字符  
  
 QString str("LOGOUT\r\n");  
 str.chop(2);          // str == "LOGOUT" 从字符串后面移除2字符  
  
 QString str = "Vladivostok";  
 str.truncate(4);     //  str == "Vlad" 到4截断字符  
  
 QString s = "Hello world";  
 s.resize(5);         // s == "Hello"  
 s.resize(8);        // s == "Hello???" (where ? stands for any character)  
  
 QString t = "Hello";  
 t += QString(10, 'X');  
 // t == "HelloXXXXXXXXXX"  
  
QString r = "Hello";  
 r = r.leftJustified(10, ' ');  
 // r == "Hello     "  
  
 QString x = "Pineapple";  
 QString y = x.left(4);      // y == "Pine"  
  
 QString x = "Pineapple";  
 QString y = x.right(5);      // y == "apple"  
  
 QString str = "Pineapple";  
 str = str.rightJustified(5, '.', true);    // str == "Pinea"  
  
 QString str = "Bananas";  
 str.endsWith("anas");         // returns true  
 str.endsWith("pple");         // returns false  
  
 QString str = "Berlin";  
 str.fill('z');  
 // str == "zzzzzz"  
  
 str.fill('A', 2);  
 // str == "AA"  
  
 QString x = "sticky question";  
 QString y = "sti";  
 x.indexOf(y);               // returns 0  
 x.indexOf(y, 1);            // returns 10  
 x.indexOf(y, 10);           // returns 10  
 x.indexOf(y, 11);           // returns -1  
  
 QString x = "crazy azimuths";  
 QString y = "az";  
 x.lastIndexOf(y);           // returns 6  
 x.lastIndexOf(y, 6);        // returns 6  
 x.lastIndexOf(y, 5);        // returns 2  
 x.lastIndexOf(y, 1);        // returns -1  
  
  
 QString x = "Nine pineapples";  
 QString y = x.mid(5, 4);            // y == "pine"  
 QString z = x.mid(5);               // z == "pineapples"  
  
  
 long a = 63;  
 QString s = QString::number(a, 16);             // s == "3f"  
 QString t = QString::number(a, 16).toUpper();     // t == "3F"  
   
 QString s = "Montreal";  
 s.remove(1, 4);  
 // s == "Meal"  
  
 QString t = "Ali Baba";  
 t.remove(QChar('a'), Qt::CaseInsensitive);  
 // t == "li Bb"  
  
 QString x = "Say yes!";  
 QString y = "no";  
 x.replace(4, 3, y);  
 // x == "Say no!"  
  
 QString str = "colour behaviour flavour neighbour";  
 str.replace(QString("ou"), QString("o"));  
 // str == "color behavior flavor neighbor"  
  
 QString str;  
 //! [51]  
 QString csv = "forename,middlename,surname,phone";  
 QString path = "/usr/local/bin/myapp"; // First field is empty  
 QString::SectionFlag flag = QString::SectionSkipEmpty;  
  
 str = csv.section(',', 2, 2);   // str == "surname"  
 str = path.section('/', 3, 4);  // str == "bin/myapp"  
 str = path.section('/', 3, 3, flag); // str == "myapp"  
  
 //字符串转换成整型  
 QString str;  
 str.setNum(1234);       // str == "1234"  
 //字符串转成整型  
 long a = 63;  
 QString s = QString::number(a, 16);             // s == "3f"  
 QString t = QString::number(a, 16).toUpper();     // t == "3F"  
  
 QString str = "a,,b,c";  
 QStringList list1 = str.split(",");  
 // list1: [ "a", "", "b", "c" ]  
 QStringList list2 = str.split(",", QString::SkipEmptyParts);  
 // list2: [ "a", "b", "c" ]  
  
  
QString str = "  lots\t of\nwhitespace\r\n ";  
 str = str.trimmed();  
 // str == "lots\t of\nwhitespace"  
  
 //判断字符串相等  
 int x = QString::compare("aUtO", "AuTo", Qt::CaseInsensitive);  // x == 0  
 int y = QString::compare("auto", "Car", Qt::CaseSensitive);     // y > 0  
 int z = QString::compare("auto", "Car", Qt::CaseInsensitive);   // z < 0  
  
  
Qstring 转换char*问题!    
方法一:    
 QString qstr("hello,word");    
 const char * p = qstr.toLocal8Bit().data();    
 方法二:    
 const char *p = qstr.toStdString().data();    
 //转换过来的是常量    
  
 方法三：    
 QString str="abc";    
 char *ch;    
 QByteArray ba = str.toLatin1()    
 ch = ba.data();    
