#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QImage>
#include <QWidget>

class ImageProcessor : public QMainWindow {
    Q_OBJECT

public:
    explicit ImageProcessor(QWidget *parent = nullptr);
    ~ImageProcessor();

private slots:
    void showOpenFile(); // 開啟影像檔案
    void zoomIn();       // 放大
    void zoomOut();      // 縮小

private:
    void createActions();   // 建立動作
    void createMenus();     // 建立選單
    void createToolBar();   // 建立工具列
    void loadFile(QString); // 載入檔案
    void createZoomWindow(double factor); // 建立縮放視窗

    QLabel *imgWin;         // 圖片顯示視窗
    QImage img;             // 當前影像
    QString filename;       // 影像檔案名
    QWidget *central;       // 中央視窗

    // 選單和工具列動作
    QMenu *fileMenu;
    QMenu *toolMenu;
    QAction *openFileAction;
    QAction *exitAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
};

#endif // IMAGEPROCESSOR_H
