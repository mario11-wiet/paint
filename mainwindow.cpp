#include "mainwindow.h"
#include "painttools.h"

MainWindow::MainWindow()
{
    paintTools = new PaintTools;
    setCentralWidget(paintTools);
    ceateAction();
    createMenu();
    //setWindowIcon("");
    setWindowTitle("Paint");
    resize(1250,750);
}
void MainWindow::penColor()
{
    QColor color = QColorDialog::getColor(paintTools->penColor());
    paintTools -> setPenColor(color);
}

void MainWindow::circleColor()
{
    QColor color = QColorDialog::getColor(paintTools->circleColor());
    paintTools -> setCircleColor(color);
}
void MainWindow::lineColor()
{
    QColor color = QColorDialog::getColor(paintTools->lineColor());
    paintTools -> setLineColor(color);
}
void MainWindow::penWidth()
{
    int width = QInputDialog::getInt(this,"Paint","Pen widht:",paintTools->penWidht(),1,maxWidht,1,&newWidht);
    if(newWidht)
    {
        paintTools->setWidht(width);
    }
}
void  MainWindow::importantMessage()
{
    QMessageBox::about(this, "Important message",
            tr("<p>https://github.com/mario11-wiet/Chess-with-AI</b> give a star :P</p>"));
}

void  MainWindow::open()
{
    if (saveFile())
    {
        QString name = QFileDialog::getOpenFileName(this,"Open File", QDir::currentPath());
        if (!name.isEmpty())
            paintTools->openImage(name);
    }
}

bool MainWindow::saveFile()
{
    return true;
}
void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray format = action->data().toByteArray();
    saveFileAs(format);

}
bool  MainWindow::saveFileAs(const QByteArray &file)
{
    QString path = QDir::currentPath() + "/paint." + file;
    QString name = QFileDialog::getSaveFileName(this, "Save As",
                               path,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(file.toUpper()))
                               .arg(QString::fromLatin1(file)));
    if (name.isEmpty()) {
        return false;
    }
    return paintTools->save(name,file.constData());

}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (saveFile()) event->accept();
    else event->ignore();
}
void  MainWindow::ceateAction()
{
    openAction = new QAction("Open",this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());
        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        listAction.append(action);
    }
    importantMessageAction = new QAction("Important Message",this);
    connect(importantMessageAction, SIGNAL(triggered()), this, SLOT(importantMessage()));
    clearAction = new QAction("Clear Screen", this);
    connect(clearAction, SIGNAL(triggered()),paintTools, SLOT(clear()));
    //dodac skróty klawiszowe
    penColorAction = new QAction("Pen Color",this);
    connect(penColorAction, SIGNAL(triggered()), this, SLOT(penColor()));
    penWidthAction = new QAction("Pen Width",this);
    connect(penWidthAction, SIGNAL(triggered()), this, SLOT(penWidth()));
    //dopisac kolo i linie
}


void  MainWindow::about(){}
void  MainWindow::createMenu()
{
    saveMenu = new QMenu("Save As", this);
    foreach (QAction *action, listAction)
    {
        saveMenu->addAction(action);
    }
    fileMenu = new QMenu("File", this);
    fileMenu->addMenu(saveMenu);
    fileMenu->addAction(openAction);
    circleMenu = new QMenu("Circle",this);
    //
    lineMenu = new QMenu("Line",this);
    //
    aboutMenu = new QMenu("About",this);
    aboutMenu->addAction(importantMessageAction);


    menuBar()->addMenu(fileMenu);
    menuBar()->addAction(penColorAction);
    menuBar()->addAction(penWidthAction);
    menuBar()->addAction(clearAction);
    menuBar()->addMenu(circleMenu);
    menuBar()->addMenu(lineMenu);
    menuBar()->addMenu(aboutMenu);

}



