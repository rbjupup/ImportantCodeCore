
setColumnCount()
setRowCount()
setHorizontalHeaderItem()
setBtn(int x,int y)

/*********************************************
功能:添加行和列 
函数:setColumnCount()
函数:setRowCount()
*********************************************/
ui->tableWidget->setColumnCount(1);
ui->tableWidget->setRowCount(2);


/*********************************************
功能:设置列名
函数:setHorizontalHeaderItem()
*********************************************/
QTableWidgetItem *item = new QTableWidgetItem();
QString stepName("name");
item->setText(stepName);
ui->tableWidget->setHorizontalHeaderItem(0,item);

/*********************************************
功能:设置行名
函数:setVerticalHeaderItem()
*********************************************/  
QTableWidgetItem *item = new QTableWidgetItem();
QString text("name");
item->setText(text);
ui->tableWidget->setVerticalHeaderItem(0, item);

/*********************************************
功能:设置按钮
函数:void setBtn(int x,int y)
*********************************************/
void setBtn(int x,int y) {
QString text("btn");
QTableWidgetItem *btn = new QTableWidgetItem(text);
ui->tableWidget->setItem(x, y, btn);
}
