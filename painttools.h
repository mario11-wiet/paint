#ifndef PAINTTOOLS_H
#define PAINTTOOLS_H
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QtWidgets>

class PaintTools : public QWidget
{
    Q_OBJECT

private:
    QColor ppenColor;
    QColor pcircleColor;
    QColor plineColor;
    QPoint ppoint;
    QImage pimage;
    int ppenWidht;
    bool modified;
    bool paiting;
    bool saveFile;

public:
    void background(QImage *image,const QSize &size);
    PaintTools(QWidget *p=0);
    QColor penColor()const {return ppenColor;}
    QColor circleColor() const {return pcircleColor;}
    QColor lineColor() const {return plineColor;}
    int penWidht() const{return ppenWidht;}
    void setPenColor(const QColor &color){ppenColor = color;};
    void setCircleColor(const QColor &color){pcircleColor=color;};
    void setLineColor(const QColor &color){plineColor=color;};
    void setWidht(const int widht){ppenWidht=widht;};
    bool openImage(const QString &file);
    bool save(const QString &file,const char *format);
    void drawLine(const QPoint &point);

public slots:
    void clear();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};


#endif
