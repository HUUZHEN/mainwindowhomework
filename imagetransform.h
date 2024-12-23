#ifndef IMAGETRANSFORM_H
#define IMAGETRANSFORM_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QDial>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>

class ImageTransform : public QWidget
{
    Q_OBJECT

public:
    ImageTransform(QWidget *parent = nullptr);
    ~ImageTransform();

    // 用於設定原始影像
    void setTransformedImage(const QImage &image); // 更新此處，使用 const QImage&

private slots:
    void mirroredImage();  // 鏡像處理
    void rotatedImage();   // 旋轉處理
    void saveImage();      // 儲存影像

private:
    QLabel *inWin;  // 顯示影像區域
    QGroupBox *mirrorGroup;
    QCheckBox *hCheckBox;  // 水平鏡像
    QCheckBox *vCheckBox;  // 垂直鏡像
    QPushButton *mirrorButton;  // 執行鏡像的按鈕
    QPushButton *saveButton;    // 儲存影像按鈕
    QDial *rotateDial;  // 旋轉控制旋鈕
    QSpacerItem *vSpacer;  // 空間項目
    QHBoxLayout *mainLayout;  // 主布局
    QVBoxLayout *groupLayout;  // 鏡像選項的布局
    QVBoxLayout *leftLayout;   // 左側布局
    QImage srcImg;  // 原始影像
    QImage dstImg;  // 處理後影像
};

#endif // IMAGETRANSFORM_H
