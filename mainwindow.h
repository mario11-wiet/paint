#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QList>
#include <QMainWindow>
#include "painttools.h"
class PaintTools;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    int maxWidht = 100;
    bool newWidht;

private:
    PaintTools *paintTools;
    QMenu *saveMenu;
    QMenu *penColorMenu;
    QMenu *fileMenu;
    QMenu *aboutMenu;
    QMenu *circleMenu;
    QMenu *lineMenu;
    QList<QAction *> listAction;
    QAction *exitAction;
    QAction *openAction;
    QAction *importantMessageAction;
    QAction *aboutAction;
    QAction *clearAction;
    QAction *penColorAction;
    QAction *penWidthAction;
    QAction *circleColorAction;
    QAction *circleWidthAction;
    QAction *cicrleAction;
    QAction *lineColorAction;
    QAction *lineWidthAction;
    QAction *lineAction;

    void createMenu();
    void ceateAction();
    bool saveFile();
    bool saveFileAs(const QByteArray &file);

private slots:
    void penColor();
    void circleColor();
    void lineColor();
    void drawCircle();
    void drawLine();
    void lineWidht();
    void circleWidht();
    void penWidth();
    void open();
    void save();
    void importantMessage();

protected:
    void closeEvent(QCloseEvent *event) override;

};
#endif // MAINWINDOW_H
