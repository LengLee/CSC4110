#include "qtprogramwin.h"
#include "ui_qtprogramwin.h"

QtProgramWin::QtProgramWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtProgramWin)
{
    ui->setupUi(this);
	
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(add())); 
	connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(subtract()));
	connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(multiply()));
	connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(division()));
	connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(clear()));
}

QtProgramWin::~QtProgramWin()
{
    delete ui;
}

/*This function is the convertor from a number in Decimal format into Binary. It takes an int n and modules it by 2. 
Each time it stores the remaining number from the module and returns that number at the end.
*/

double QtProgramWin::bin(int n) {
	long long bNum = 0;
	int remember = 0;
	int i = 1;
	do {
		remember = n % 2; 
		n /= 2;
		bNum += remember * i; 
		i *= 10; 
	} while (n < 0 || n>0); 
	
	return bNum; 
}

void QtProgramWin::add() {
	long num1, num2, dec = 0, dec2 = 0, r, r2 , b=1, b2=1; 
	double c , conv; 

	
	num1 = ui->lineEdit->text().toLong();			//read from box1
	num2 = ui->lineEdit_2->text().toLong();			//read from box 2

	c = num1 + num2;		//calculates addition

	conv = bin(c);			// converts to binary

	

	ui->textBrowser->setReadOnly(true); 
	ui->textBrowser->setText(QString::number(conv, 'g', 16));		//outputs the answer
}


void QtProgramWin::subtract() {
	long num1, num2;

	double c, conv;
	num1 = ui->lineEdit->text().toLong();		//read from box 1
	num2 = ui->lineEdit_2->text().toLong();		// read from box2 

	c = num1 - num2;			//calculates the subtraction
	conv = bin(c);			// converts to binary

	ui->textBrowser->setReadOnly(true);
	ui->textBrowser->setText(QString::number(conv, 'g', 16));		//prints results
}


void QtProgramWin::multiply() { 

	long num1, num2; 
	double c,conv;
	num1 = ui->lineEdit->text().toLong();		//read from box 1
	num2 = ui->lineEdit_2->text().toLong();		// read from box 2

	c = num1 * num2;         // calculates the multiplication
	conv = bin(c);			//converts to binary

	ui->textBrowser->setReadOnly(true);
	ui->textBrowser->setText(QString::number(conv, 'g', 16));		//prints out the answer
}

void QtProgramWin::division() { 
	long num1, num2;

	double c, conv;
	num1 = ui->lineEdit->text().toLong();		//read from box 1
	num2 = ui->lineEdit_2->text().toLong();		//read from box 2

	c = num1 / num2;		//calculates the division
	conv = bin(c);			//converts to binary

	ui->textBrowser->setReadOnly(true);
	ui->textBrowser->setText(QString::number(conv, 'g', 16));	//prints out the answer
}

/* This function clears out all of the boxes in the GUI and their results.*/
  void QtProgramWin::clear() {
	ui->lineEdit->setText(QString::number(NULL));	
	ui->lineEdit_2->setText(QString::number(NULL));
	ui->textBrowser->setText(QString::number(NULL));
}     