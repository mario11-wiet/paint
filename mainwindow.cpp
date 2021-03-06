#include "mainwindow.h"
#include "painttools.h"

MainWindow::MainWindow()
{
    paintTools = new PaintTools;
    setCentralWidget(paintTools);
    ceateAction();
    createMenu();
    setWindowIcon(QIcon(":Paint2/images/photo.png"));
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
void MainWindow::circleWidht()
{
    int width = QInputDialog::getInt(this,"Circle","Circle widht:",paintTools->circleWidht(),1,maxWidht,1,&newWidht);
    if(newWidht)
    {
        paintTools->setCircleWidht(width);
    }
}
void MainWindow::drawCircle()
{
    if(paintTools->drawCircle)
    {
        paintTools->drawCircle=false;
    }
    else
    {
        paintTools->drawCircle=true;
    }
}
void MainWindow::drawLine()
{
    if(paintTools->lineDraw)
    {
        paintTools->lineDraw=false;
    }
    else
    {
        paintTools->lineDraw=true;
    }
}
void MainWindow::lineWidht()
{
    int width = QInputDialog::getInt(this,"Paint","Line widht:",paintTools->penWidht(),1,maxWidht,1,&newWidht);
    if(newWidht)
    {
        paintTools->setLineWight(width);
    }
}
void  MainWindow::importantMessage()
{
    QMessageBox::about(this, "Important message",
            tr("<p>https://github.com/mario11-wiet/Chess-with-AI</b> give a star :P</p>"));
}

void  MainWindow::importantMessage2()
{
    QMessageBox::about(this, "Important message 2",
            tr("<p>https://github.com/Akatroj/Chess-with-AI</b> give a star :P</p>"));
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
    if (paintTools->isModified()) {
       QMessageBox::StandardButton ret;

       ret = QMessageBox::question(this, "Paint","Do you want to save the changes?",
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);

        if (ret == QMessageBox::Save) {
            return saveFileAs("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
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
    openAction->setShortcuts(QKeySequence::Open);
    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());
        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        listAction.append(action);
    }

    importantMessageAction = new QAction("Important Message",this);
    connect(importantMessageAction, SIGNAL(triggered()), this, SLOT(importantMessage()));
    importantMessageAction2 = new QAction("Important Message 2",this);
    connect(importantMessageAction2, SIGNAL(triggered()), this, SLOT(importantMessage2()));
    clearAction = new QAction("Clear Screen", this);
    connect(clearAction, SIGNAL(triggered()),paintTools, SLOT(clear()));
    clearAction->setShortcuts(QKeySequence::Delete);
    //dodac skr??ty klawiszowe
    penColorAction = new QAction("Pen Color",this);
    connect(penColorAction, SIGNAL(triggered()), this, SLOT(penColor()));
    penWidthAction = new QAction("Pen Width",this);
    connect(penWidthAction, SIGNAL(triggered()), this, SLOT(penWidth()));
    //dopisac kolo i linie
    circleColorAction = new QAction("Cicle Color",this);
    connect(circleColorAction, SIGNAL(triggered()), this, SLOT(circleColor()));
    circleWidthAction = new QAction("Circle Width",this);
    connect(circleWidthAction, SIGNAL(triggered()), this, SLOT(circleWidht()));
    cicrleAction = new QAction("Draw a circle",this);
    connect(cicrleAction,SIGNAL(triggered()),this,SLOT());
    cicrleAction ->setShortcut(QKeySequence::Copy);
    lineColorAction = new QAction("Line Color",this);
    connect(lineColorAction, SIGNAL(triggered()), this, SLOT(lineColor()));
    lineWidthAction = new QAction("Line Width",this);
    connect(lineWidthAction, SIGNAL(triggered()), this, SLOT(lineWidht()));
    lineAction = new QAction("Draw a line",this);
    connect(lineAction, SIGNAL(triggered()), this, SLOT(drawLine()));
    lineAction->setShortcuts(QKeySequence::MoveToNextLine);

}


void  MainWindow::createMenu()
{
    saveMenu = new QMenu("Save As", this);
    foreach (QAction *action, listAction)
    {
        saveMenu->addAction(action);
        action->setShortcuts(QKeySequence::SaveAs);
    }
    fileMenu = new QMenu("File", this);
    fileMenu->addMenu(saveMenu);
    fileMenu->addAction(openAction);
    circleMenu = new QMenu("Circle",this);
    circleMenu->addAction(cicrleAction);
    circleMenu->addAction(circleColorAction);
    circleMenu->addAction(circleWidthAction);
    //
    lineMenu = new QMenu("Line",this);
    lineMenu->addAction(lineAction);
    lineMenu->addAction(lineColorAction);
    lineMenu->addAction(lineWidthAction);
    //
    aboutMenu = new QMenu("About",this);
    aboutMenu->addAction(importantMessageAction);
    aboutMenu->addAction(importantMessageAction2);


    menuBar()->addMenu(fileMenu);
    menuBar()->addAction(penColorAction);
    menuBar()->addAction(penWidthAction);
    menuBar()->addAction(clearAction);
    menuBar()->addMenu(circleMenu);
    menuBar()->addMenu(lineMenu);
    menuBar()->addMenu(aboutMenu);

}



