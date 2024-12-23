#include "imagetransform.h"
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>  // 用於文件對話框
#include <QImageWriter> // 用來處理不同的影像格式

ImageTransform::ImageTransform(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    leftLayout = new QVBoxLayout();

    // 鏡像選項
    mirrorGroup = new QGroupBox(QStringLiteral("鏡射"), this);
    groupLayout = new QVBoxLayout(mirrorGroup);

    hCheckBox = new QCheckBox(QStringLiteral("水平"), mirrorGroup);
    vCheckBox = new QCheckBox(QStringLiteral("垂直"), mirrorGroup);
    mirrorButton = new QPushButton(QStringLiteral("執行"), mirrorGroup);

    groupLayout->addWidget(hCheckBox);
    groupLayout->addWidget(vCheckBox);
    groupLayout->addWidget(mirrorButton);

    mirrorGroup->setLayout(groupLayout);
    leftLayout->addWidget(mirrorGroup);

    // 旋轉控制
    rotateDial = new QDial(this);
    rotateDial->setRange(0, 360);  // 設定旋轉角度範圍
    rotateDial->setNotchesVisible(true);

    leftLayout->addWidget(rotateDial);

    // 儲存按鈕 (在旋鈕下方)
    saveButton = new QPushButton(QStringLiteral("保存"), this);
    leftLayout->addWidget(saveButton);

    // Spacer
    vSpacer = new QSpacerItem(20, 58, QSizePolicy::Minimum, QSizePolicy::Expanding);
    leftLayout->addItem(vSpacer);

    mainLayout->addLayout(leftLayout);

    // 圖像顯示區域
    inWin = new QLabel(this);
    inWin->setScaledContents(true);

    QPixmap initPixmap(300, 200);
    initPixmap.fill(QColor(255, 255, 255)); // 初始化為白色
    inWin->setPixmap(initPixmap);
    inWin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(inWin);

    // 信號槽連接
    connect(mirrorButton, &QPushButton::clicked, this, &ImageTransform::mirroredImage);
    connect(rotateDial, &QDial::valueChanged, this, &ImageTransform::rotatedImage);
    connect(saveButton, &QPushButton::clicked, this, &ImageTransform::saveImage);  // 連接儲存按鈕
}

ImageTransform::~ImageTransform()
{
}

void ImageTransform::mirroredImage()
{
    if (srcImg.isNull()) {
        qDebug() << "源影像為空，無法執行鏡像操作！";
        return;
    }

    bool horizontal = hCheckBox->isChecked();  // 檢查是否選擇水平鏡像
    bool vertical = vCheckBox->isChecked();    // 檢查是否選擇垂直鏡像

    // 執行水平和/或垂直鏡像
    dstImg = srcImg;

    if (horizontal && vertical) {
        dstImg = srcImg.mirrored(true, true);  // 同時水平和垂直鏡像
    } else if (horizontal) {
        dstImg = srcImg.mirrored(true, false); // 只進行水平鏡像
    } else if (vertical) {
        dstImg = srcImg.mirrored(false, true); // 只進行垂直鏡像
    }

    // 更新顯示的影像
    inWin->setPixmap(QPixmap::fromImage(dstImg).scaled(inWin->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageTransform::rotatedImage()
{
    if (srcImg.isNull()) {
        qDebug() << "源影像為空，無法執行旋轉操作！";
        return;
    }

    QTransform transform;
    int angle = rotateDial->value();
    transform.rotate(angle);

    dstImg = srcImg.transformed(transform);
    inWin->setPixmap(QPixmap::fromImage(dstImg).scaled(inWin->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageTransform::setTransformedImage(const QImage &image)
{
    if (image.isNull()) {
        qDebug() << "提供的影像為空！";
        return;
    }

    srcImg = image;
    dstImg = srcImg;
    inWin->setPixmap(QPixmap::fromImage(srcImg).scaled(inWin->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageTransform::saveImage()
{
    if (dstImg.isNull()) {
        qDebug() << "轉換後的影像為空，無法保存！";
        return;
    }

    // 讓使用者選擇保存位置和檔案名稱
    QString fileName = QFileDialog::getSaveFileName(this, QStringLiteral("保存影像"), "", "Images (*.png )");

    if (!fileName.isEmpty()) {
        // 儲存檔案
        if (!dstImg.save(fileName)) {
            qDebug() << "影像保存失敗！";
        } else {
            qDebug() << "影像已保存至：" << fileName;
        }
    }
}
