#include "palettebutton.h"

#include <QMouseEvent>
#include<QColorDialog>


PaletteButton::PaletteButton(const QColor &color)
{
	mCurrentColor = new QColor(0, 0, 0); 
    mColor = color;
    setMinimumSize(QSize(30, 30));
    setMaximumSize(QSize(30, 30));
    QPixmap pixmap(20, 20);
    pixmap.fill(color);
    setIcon(pixmap);
    setStatusTip(color.name());
}

void PaletteButton::mouseDoubleClickEvent(QMouseEvent *event)
{

	if (event->button() == Qt::LeftButton)
	{
		mColor = QColorDialog::getColor(*mCurrentColor, this);
		DataSingleton::Instance()->setPrimaryColor(mColor);
	}
	else if (event->button() == Qt::RightButton)
	{
		mColor = QColorDialog::getColor(*mCurrentColor, this);
		DataSingleton::Instance()->setSecondaryColor(mColor);
	}
    emit colorPicked();
}

void PaletteButton::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		DataSingleton::Instance()->setPrimaryColor(mColor);
	else if (event->button() == Qt::RightButton)
		DataSingleton::Instance()->setSecondaryColor(mColor);

	emit colorPicked();
}