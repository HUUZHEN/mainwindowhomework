#include "imageprocessor.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle(QStringLiteral("影像處理"));
    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    imgWin = new QLabel();
    QPixmap *initPixmap = new QPixmap(300, 200);
    initPixmap->fill(QColor(255, 255, 255));
    imgWin->resize(300, 200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    mainLayout->addWidget(imgWin);
    setCentralWidget(central);
    createActions();
    createMenus();
    createToolBars();
}

void ImageProcessor::createActions() {
    openFileAction = new QAction(QStringLiteral("開啟檔案 (&O)"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("開啟影像檔案"));
    connect(openFileAction, &QAction::triggered, this, &ImageProcessor::showOpenFile);

    exitAction = new QAction(QStringLiteral("結束 (&Q)"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程式"));
    connect(exitAction, &QAction::triggered, this, &ImageProcessor::close);
}

void ImageProcessor::createMenus() {
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案 (&F)"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exitAction);
}

void ImageProcessor::createToolBars() {
    fileTool = addToolBar("File");
    fileTool->addAction(openFileAction);
}

void ImageProcessor::loadFile(QString filename) {
    qDebug() << QString("File name: %1").arg(filename);

    // 嘗試加載影像
    if (img.load(filename)) {
        imgWin->setPixmap(QPixmap::fromImage(img));
        imgWin->resize(img.size());  // 調整標籤大小以適應影像
    }
}

void ImageProcessor::showOpenFile() {
    filename = QFileDialog::getOpenFileName(
        this,
        QStringLiteral("開啟影像"),
        ".",
        QStringLiteral("影像檔案 (*.bmp *.png *.jpg);;所有檔案 (*.*)")
        );

    // 確認檔案名稱是否有效
    if (!filename.isEmpty()) {
        loadFile(filename);
    } else {
        qDebug() << "No file selected.";
    }
}
