#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 連接 Save 動作
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// saveFile 函數實作
void MainWindow::saveFile()
{
    // 取得使用者要儲存的檔案路徑
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;All Files (*)"));

    // 如果使用者沒有選擇檔案則返回
    if (filePath.isEmpty())
        return;

    // 開啟檔案進行寫入
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file for writing"));
        return;
    }

    // 寫入文字（假設有一個 QTextEdit 元件名為 textEdit）
    QTextStream out(&file);
    out << ui->textEdit->toPlainText(); // 將 QTextEdit 的內容寫入檔案

    file.close();
    QMessageBox::information(this, tr("Success"), tr("File saved successfully"));
}
