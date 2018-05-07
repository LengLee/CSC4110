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

#include "additionaltools.h"
#include "imagearea.h"
#include "dialogs/resizedialog.h"

#include <QImage>
#include <QPainter>
#include <QLabel>
#include <QTransform>
#include <QSize>
#include <QClipboard>
#include <QApplication>

AdditionalTools::AdditionalTools(ImageArea *pImageArea, QObject *parent) :
    QObject(parent)
{
    mPImageArea = pImageArea;
    mZoomedFactor = 1;
}

AdditionalTools::~AdditionalTools()
{

}

void AdditionalTools::resizeCanvas(int width, int height, bool flag)
{
    if(flag)
    {
        ResizeDialog resizeDialog(QSize(width, height));
        if(resizeDialog.exec() == QDialog::Accepted)
        {
            QSize newSize = resizeDialog.getNewSize();
            width = newSize.width();
            height = newSize.height();
        }
    }

    if(width < 1 || height < 1)
        return;
    QImage *tempImage = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(tempImage);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(QRect(0, 0, width, height));
    painter.drawImage(0, 0, *mPImageArea->getImage());
    painter.end();

    mPImageArea->setImage(*tempImage);

    mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
                        mPImageArea->getImage()->rect().bottom() + 6);
    mPImageArea->setEdited(true);
    mPImageArea->clearSelection();
}

void AdditionalTools::resizeImage()
{
    ResizeDialog resizeDialog(mPImageArea->getImage()->size());
    if(resizeDialog.exec() == QDialog::Accepted)
    {
        mPImageArea->setImage(mPImageArea->getImage()->scaled(resizeDialog.getNewSize()));
        mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
                            mPImageArea->getImage()->rect().bottom() + 6);
        mPImageArea->setEdited(true);
        mPImageArea->clearSelection();
    }
}

void AdditionalTools::rotateImage(int flag)
{
    QTransform transform;
	if (flag == 1){
		transform.rotate(90);
	}
	else if (flag == 2){
		transform.rotate(-90);
	}
	else if (flag == 3){
		transform.rotate(180);
	}

    mPImageArea->setImage(mPImageArea->getImage()->transformed(transform));
    mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
                        mPImageArea->getImage()->rect().bottom() + 6);
    mPImageArea->update();
    mPImageArea->setEdited(true);
    mPImageArea->clearSelection();
}

bool AdditionalTools::zoomImage(qreal factor)
{
    mZoomedFactor *= factor;
    if(mZoomedFactor < 0.25)
    {
        mZoomedFactor = 0.25;
        return false;
    }
    else if(mZoomedFactor > 4)
    {
        mZoomedFactor = 4;
        return false;
    }
    else
    {
        mPImageArea->setImage(mPImageArea->getImage()->transformed(QTransform::fromScale(factor, factor)));
        mPImageArea->resize((mPImageArea->rect().width())*factor, (mPImageArea->rect().height())*factor);
        emit sendNewImageSize(mPImageArea->size());
        mPImageArea->setEdited(true);
        mPImageArea->clearSelection();
        return true;
    }
}

void AdditionalTools::flipImage(int scale1, int scale2)
{
    QMatrix image;
    image.scale(scale1, scale2);

    mPImageArea->setImage(mPImageArea->getImage()->transformed(image));
    mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
        mPImageArea->getImage()->rect().bottom() + 6);
    mPImageArea->update();
    mPImageArea->setEdited(true);
    mPImageArea->clearSelection();
}


void AdditionalTools::mirrorImage(bool vertical, bool horizontal, bool mirrorOption)
{
	int height = mPImageArea->getImage()->height();
	int width = mPImageArea->getImage()->width();


	QPainter paint(mPImageArea->getImage());

	if (vertical) {
		if (mirrorOption) {
			paint.eraseRect(0, 0, width / 2, height);

		}
		else {
			paint.eraseRect(width / 2, 0, width, height);
		}
	}
	else {
		if (mirrorOption) {
			paint.eraseRect(0, 0, width, height / 2);
		}
		else {
			paint.eraseRect(0, height / 2, width, height);
		}
	}

	QImage image = mPImageArea->getImage()->mirrored(vertical, horizontal);
	paint.setCompositionMode(QPainter::CompositionMode_Multiply);
	paint.drawImage(0, 0, image);
	mPImageArea->setEdited(true);
	mPImageArea->update();
}

void AdditionalTools::mirrorVImage(bool vertical, bool horizontal, bool lr){
	
		int height = mPImageArea->getImage()->height();
		int width = mPImageArea->getImage()->width();
	//Draw the image after the mirror
	if (lr) {
		/* If it has the bool val = 0 then its a right flip , thus use this func, Leng Lee Fq1369
		QImage image = mPImageArea->getImage()->mirrored(vertical, horizontal);
		QPainter painter(mPImageArea->getImage());
		painter.setClipRect(0, 0, width/2, height);
		painter.drawImage(0, 0, image);
		mPImageArea->setEdited(true);
		mPImageArea->update();
		*/
		flipRightSide(vertical, horizontal, width, height); 
	}

	else {

		/* If it has the bool val = 0 then its a left flip , thus use this func, Leng Lee Fq1369
		QImage image = mPImageArea->getImage()->mirrored(vertical, horizontal);
		QPainter painter(mPImageArea->getImage());
		painter.setClipRect(width / 2, 0, width, height);  
		painter.drawImage(0, 0, image);
		mPImageArea->setEdited(true);
		mPImageArea->update();
		*/
		flipLeftSide(vertical, horizontal, width, height);
	
	}
}

void AdditionalTools::flipLeftSide(bool vertical, bool horizontal, int width, int height) {
	QImage image = mPImageArea->getImage()->mirrored(vertical, horizontal);
	QPainter painter(mPImageArea->getImage());
	painter.setClipRect(width / 2, 0, width, height);
	painter.drawImage(0, 0, image);
	mPImageArea->setEdited(true);
	mPImageArea->update();
}


void AdditionalTools::flipRightSide(bool vertical, bool horizontal, int width, int height) {
	QImage image = mPImageArea->getImage()->mirrored(vertical, horizontal);
	QPainter painter(mPImageArea->getImage());
	painter.setClipRect(0, 0, width / 2, height);
	painter.drawImage(0, 0, image);
	mPImageArea->setEdited(true);
	mPImageArea->update();
}




