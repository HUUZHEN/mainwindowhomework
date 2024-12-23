// In imageprocessor.h
#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include <QImage>
#include "imagetransform.h"

class ImageProcessor : public QMainWindow {
    Q_OBJECT

public:
    explicit ImageProcessor(QWidget *parent = nullptr);
    ~ImageProcessor();

private slots:
    void showOpenFile();         // 開啟檔案槽函數
    void zoomIn();               // 放大影像槽函數
    void zoomOut();              // 縮小影像槽函數
    void showGeometryTransform();// 幾何轉換槽函數
    void saveFile();             // 儲存檔案槽函數

protected:
    void closeEvent(QCloseEvent *event) override; // Add this declaration

private:
    void createActions();        // 建立動作
    void createMenus();          // 建立功能表
    void createToolBar();        // 建立工具列
    void loadFile(QString filename); // 加載影像檔案
    void createZoomWindow(double factor); // 建立縮放窗口

    QLabel *imgWin;              // 顯示影像的 QLabel
    QWidget *central;            // 中央 Widget
    QImage img;                  // 儲存影像的 QImage
    QString filename;            // 儲存檔案路徑
    ImageTransform *gWin;        // 幾何轉換視窗

    QAction *openFileAction;     // 開啟檔案動作
    QAction *saveFileAction;     // 儲存檔案動作
    QAction *exitAction;         // 結束動作
    QAction *zoomInAction;       // 放大動作
    QAction *zoomOutAction;      // 縮小動作
    QAction *geometryAction;     // 幾何轉換動作

    QMenu *fileMenu;             // 檔案功能表
    QMenu *toolMenu;             // 工具功能表
    QToolBar *fileTool;          // 工具列
};

#endif // IMAGEPROCESSOR_H
