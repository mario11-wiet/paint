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
    int pcircleWidht;
    int plineWidht;
    bool modified;
    bool paiting;
    bool saveFile;

public:
    bool isModified() const { return modified; }
    void background(QImage *image,const QSize &size);
    PaintTools(QWidget *p=0);
    QColor penColor()const {return ppenColor;}
    QColor circleColor() const {return pcircleColor;}
    QColor lineColor() const {return plineColor;}
    int penWidht() const{return ppenWidht;}
    int circleWidht() const{ return pcircleWidht;}
    int lineWidht() const {return plineWidht;}
    void setCircleWidht(const int widht) {pcircleWidht =widht;}
    void setLineWight(const int widht) {plineWidht = widht;}
    void setPenColor(const QColor &color){ppenColor = color;};
    void setCircleColor(const QColor &color){pcircleColor=color;};
    void setLineColor(const QColor &color){plineColor=color;};
    void setWidht(const int widht){ppenWidht=widht;};
    bool openImage(const QString &file);
    bool save(const QString &file,const char *format);
    void drawLine(const QPoint &point);
    bool drawCircle;
    bool lineDraw;

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
