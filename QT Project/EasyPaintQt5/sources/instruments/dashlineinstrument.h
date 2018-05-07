

#ifndef	DASHLINEINSTRUMENT_H
#define DASHLINEINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief Line instrument class.
 *
 */
class DashLineInstrument : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit DashLineInstrument(QObject *parent = 0);
    
    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
    void paint(ImageArea &imageArea,bool isSecondaryColor = false, bool additionalFlag = false);
	
};

#endif 
