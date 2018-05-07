/*
 * This source file is part of EasyPaint.
 *
 * Copyright (c) 2012 EasyPaint <https://github.com/Gr1N/EasyPaint>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "lineinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QPen>
#include <QPainter>
#include <QImage>
#include <qguiapplication.h> //add header file

LineInstrument::LineInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}

void LineInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        mStartPoint = mEndPoint = event->pos();
        imageArea.setIsPaint(true);
        mImageCopy = *imageArea.getImage();
        makeUndoCommand(imageArea);
    }
}

void LineInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        mEndPoint = event->pos();
        imageArea.setImage(mImageCopy);
        if(event->buttons() & Qt::LeftButton)
        {
            paint(imageArea, false);
        }
        else if(event->buttons() & Qt::RightButton)
        {
            paint(imageArea, true);
        }
    }
}

void LineInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        imageArea.setImage(mImageCopy);
        if(event->button() == Qt::LeftButton)
        {
            paint(imageArea, false);
        }
        else if(event->button() == Qt::RightButton)
        {
            paint(imageArea, true);
        }
        imageArea.setIsPaint(false);
    }
}

//Refactor - Varmitha - gb2011
void LineInstrument::lineColor(ImageArea &imageArea, QPainter &painter, bool isSecondaryColor) {
	if (isSecondaryColor)
	{
		painter.setPen(QPen(DataSingleton::Instance()->getSecondaryColor(),
			DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
			Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	}
	else
	{
		painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
			DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
			Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	}
}

void LineInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
    QPainter painter(imageArea.getImage());
	
	//Refactor - Varmitha - gb2011
	lineColor(imageArea, painter, isSecondaryColor);
	//Extract function
	/*
    if(isSecondaryColor)
    {
        painter.setPen(QPen(DataSingleton::Instance()->getSecondaryColor(),
                            DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    else
    {
        painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
                            DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
	*/
	
	if (mStartPoint != mEndPoint)
	{
		double xPt, yPt;
		if (QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier)) // check to see if the shift modifier has been initiated on keyboard
		{
			xPt = mEndPoint.x() - mStartPoint.x(); // compute new x value using absolute values
			yPt = mEndPoint.y() - mStartPoint.y(); // compute new y value using absolute values

			if (xPt >= 40 && yPt <= 50) // create a 45 degree line
			{
				double angle = 45 / 180.0 * 3.14; //set to 45 degrees rad
				double len = sqrt((pow(xPt, 2) + pow(yPt, 2))); // find length of the line
				mEndPoint.setX(cos(angle) * len + mStartPoint.x()); //set new coordinate for x
				mEndPoint.setY(sin(angle) * len + mStartPoint.y()); //set new coordinate for y
			}
			else if (xPt > 50) // create a horizontal line
			{
				mEndPoint.setY(mStartPoint.y()); // change the endpoint to the same coordinate as the start point
			}
			else if (xPt < 40) // create a vertical line
			{
				mEndPoint.setX(mStartPoint.x()); // change the endpoint to the same coordinate as the start point
			}
		}
        painter.drawLine(mStartPoint, mEndPoint);
    }

    if(mStartPoint == mEndPoint)
    {
        painter.drawPoint(mStartPoint);
    }
    imageArea.setEdited(true);
    //    int rad(DataSingleton::Instance()->getPenSize() + round(sqrt((mStartPoint.x() - mEndPoint.x()) *
    //                                                                 (mStartPoint.x() - mEndPoint.x()) +
    //                                                                 (mStartPoint.y() - mEndPoint.y()) *
    //                                                                 (mStartPoint.y() - mEndPoint.y()))));
    //    mPImageArea->update(QRect(mStartPoint, mEndPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    painter.end();
    imageArea.update();
}


