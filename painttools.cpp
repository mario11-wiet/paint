#include "painttools.h"

PaintTools::PaintTools(QWidget *p): QWidget(p)
{
    setAttribute(Qt::WA_StaticContents);
    ppenColor = Qt::black;
    pcircleColor= Qt::black;
    plineColor= Qt::black;
    ppenWidht =1;
    modified = false;
    paiting = false;
}
void PaintTools::drawLine(const QPoint &point)
{
    QPainter painter(&pimage);
    painter.setPen(QPen(ppenColor, ppenWidht, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(ppoint, point);
    int rad = (ppenWidht / 2) + 2;
    update(QRect(ppoint, point).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    ppoint =point;
    modified = true;

}
//
void PaintTools::resizeEvent(QResizeEvent *event)
{
    if (width() > pimage.width() || height() > pimage.height()) {
        int newWidth = qMax(width() + 128, pimage.width());
        int newHeight = qMax(height() + 128, pimage.height());
        background(&pimage, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}
//
void  PaintTools::background(QImage *image,const QSize &size)
{
    if (image->size() == size)
        return;

    // Create a new image to display and fill it with white
    QImage newImage(size, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    // Draw the image
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
void PaintTools::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() ==Qt::LeftButton )
    {
        ppoint = event->pos();
        paiting = true;
    }
}
void PaintTools::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && paiting == true)
        drawLine(event->pos());
}
void PaintTools::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && paiting) {
        drawLine(event->pos());
        paiting = false;
    }
}

void PaintTools::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect = event->rect();
    painter.drawImage(rect, pimage, rect);
}

bool PaintTools::openImage(const QString &file)
{
    QImage imageS;
    if(imageS.load(file))
    {
        QSize newSize = imageS.size().expandedTo(size());
        background(&imageS, newSize);
        pimage = imageS;
        modified = false;
        update();
        return true;
    }
    return false;
}
bool PaintTools::save(const QString &file,const char *format)
{
    QImage imageSave = pimage;
    background(&imageSave, size());
    if (imageSave.save(file, format)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}


void PaintTools::clear()
{
    pimage.fill(qRgb(255,255,255));
    modified = true;
    update();
}



