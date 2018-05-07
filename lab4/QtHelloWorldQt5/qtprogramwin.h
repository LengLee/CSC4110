#ifndef QTPROGRAMWIN_H
#define QTPROGRAMWIN_H

#include <QMainWindow>

namespace Ui {
class QtProgramWin;
}

class QtProgramWin : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QtProgramWin(QWidget *parent = 0);
    ~QtProgramWin();
	 
    
private:
    Ui::QtProgramWin *ui;
	
	
public slots:
	void add(); 
	void subtract();
	void multiply();
	void division();
	void clear(); 
	double bin(int); 

	
};

#endif // QTPROGRAMWIN_H
