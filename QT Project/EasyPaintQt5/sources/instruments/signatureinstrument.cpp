#include "signatureinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QPen>
#include <QPainter>

SignatureInstrument::SignatureInstrument(QObject *parent) :
	AbstractInstrument(parent)
{
}

void SignatureInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
	{
		mStartPoint = mEndPoint = event->pos();
		imageArea.setIsPaint(true);
		mImageCopy = *imageArea.getImage();
		makeUndoCommand(imageArea);
	}
}

void SignatureInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (imageArea.isPaint())
	{
		mEndPoint = event->pos();
		imageArea.setImage(mImageCopy);
		if (event->buttons() & Qt::LeftButton)
		{
			paint(imageArea, false);
		}
		else if (event->buttons() & Qt::RightButton)
		{
			paint(imageArea, true);
		}
	}
}

void SignatureInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (imageArea.isPaint())
	{
		imageArea.setImage(mImageCopy);
		if (event->button() == Qt::LeftButton)
		{
			paint(imageArea, false);
		}
		else if (event->button() == Qt::RightButton)
		{
			paint(imageArea, true);
		}
		imageArea.setIsPaint(false);
	}
}

void SignatureInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
	QPainter painter(imageArea.getImage());
	QImage name(":media/signature/usersign.png");
	painter.drawImage(mStartPoint, name);

	imageArea.setEdited(true);
	//    int rad(DataSingleton::Instance()->getPenSize() + round(sqrt((mStartPoint.x() - mEndPoint.x()) *
	//                                                                 (mStartPoint.x() - mEndPoint.x()) +
	//                                                                 (mStartPoint.y() - mEndPoint.y()) *
	//                                                                 (mStartPoint.y() - mEndPoint.y()))));
	//    mPImageArea->update(QRect(mStartPoint, mEndPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
	painter.end();
	imageArea.update();
}
