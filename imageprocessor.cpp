#include "imageprocessor.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QToolBar>
#include <QFileDialog>
#include <QDebug>
#include <QVBoxLayout>
#include <QCloseEvent>
#include "imagetransform.h"

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle(QStringLiteral("影像處理"));

    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    imgWin = new QLabel();
    QPixmap *initPixmap = new QPixmap(1000, 500);
    gWin = new ImageTransform();
    initPixmap->fill(Qt::white);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    mainLayout->addWidget(imgWin);
    setCentralWidget(central);

    createActions();
    createMenus();
    createToolBar();
}

ImageProcessor::~ImageProcessor() {}

void ImageProcessor::createActions() {
    openFileAction = new QAction(QStringLiteral("開啟影像檔(&O)"), this);
    openFileAction->setShortcut(QKeySequence("Ctrl+O"));
    connect(openFileAction, &QAction::triggered, this, &ImageProcessor::showOpenFile);

    saveFileAction = new QAction(QStringLiteral("存檔(&S)"), this);
    saveFileAction->setShortcut(QKeySequence("Ctrl+S"));
    connect(saveFileAction, &QAction::triggered, this, &ImageProcessor::saveFile);

    exitAction = new QAction(QStringLiteral("結束"), this);
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(exitAction, &QAction::triggered, this, &ImageProcessor::close);

    zoomInAction = new QAction(QStringLiteral("放大"), this);
    connect(zoomInAction, &QAction::triggered, this, &ImageProcessor::zoomIn);

    zoomOutAction = new QAction(QStringLiteral("縮小"), this);
    connect(zoomOutAction, &QAction::triggered, this, &ImageProcessor::zoomOut);

    geometryAction = new QAction(QStringLiteral("幾何轉換"), this);
    geometryAction->setShortcut(QKeySequence("Ctrl+G"));
    geometryAction->setStatusTip(QStringLiteral("影像幾何轉換"));
    connect(geometryAction, &QAction::triggered, this, &ImageProcessor::showGeometryTransform);
}

void ImageProcessor::createMenus() {
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案(&F)"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(geometryAction);
    fileMenu->addAction(exitAction);

    toolMenu = menuBar()->addMenu(QStringLiteral("工具(&T)"));
    toolMenu->addAction(zoomInAction);
    toolMenu->addAction(zoomOutAction);
}

void ImageProcessor::createToolBar() {
    fileTool = addToolBar(QStringLiteral("工具列"));
    fileTool->addAction(openFileAction);
    fileTool->addAction(geometryAction);
    fileTool->addSeparator();
    fileTool->addAction(zoomInAction);
    fileTool->addAction(zoomOutAction);
}

void ImageProcessor::loadFile(QString filename) {
    if (!img.load(filename)) {
        qDebug() << "Failed to load image:" << filename;
        return;
    }
    imgWin->setPixmap(QPixmap::fromImage(img).scaled(imgWin->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageProcessor::showOpenFile() {
    filename = QFileDialog::getOpenFileName(this,
                                            QStringLiteral("開啟影像"),".","PNG (*.png);;JPEG (*.jpg *.jpeg);;BMP (*.bmp)");
    if (!filename.isEmpty()) {
        loadFile(filename);
    }
}
void ImageProcessor::saveFile() {
    if (img.isNull()) {
        qDebug() << "No image to save.";
        return;
    }

    QString saveFilename = QFileDialog::getSaveFileName(this,
QStringLiteral("儲存影像"),
".","PNG (*.png);;JPEG (*.jpg *.jpeg);;BMP (*.bmp)");
    if (!saveFilename.isEmpty()) {
        if (!img.save(saveFilename)) {
            qDebug() << "Failed to save image:" << saveFilename;
        } else {
            qDebug() << "Image saved to:" << saveFilename;
        }
    }
}

void ImageProcessor::zoomIn() {
    createZoomWindow(1.2); // 放大比例
}

void ImageProcessor::zoomOut() {
    createZoomWindow(0.8); // 縮小比例
}

void ImageProcessor::createZoomWindow(double factor) {
    if (img.isNull()) return;

    QWidget *zoomWindow = new QWidget();
    zoomWindow->setWindowTitle(QStringLiteral("影像處理視窗"));
    QLabel *zoomLabel = new QLabel(zoomWindow);
    QVBoxLayout *layout = new QVBoxLayout(zoomWindow);
    layout->addWidget(zoomLabel);

    QPixmap scaledPixmap = QPixmap::fromImage(img).scaled(img.size() * factor, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    zoomLabel->setPixmap(scaledPixmap);
    zoomLabel->setScaledContents(true);

    zoomWindow->resize(scaledPixmap.size());
    zoomWindow->show();
}

void ImageProcessor::showGeometryTransform() {
    if (img.isNull()) return;

    QImage transformed = img.transformed(QTransform().rotate(90));
    gWin->setTransformedImage(transformed);
    gWin->show();
}

void ImageProcessor::closeEvent(QCloseEvent *event) {
    if (gWin) {
        gWin->close();
    }
    event->accept();
}
