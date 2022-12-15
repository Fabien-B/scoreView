#include "scorewindow.h"
#include "./ui_scorewindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDirIterator>
#include <QDebug>
#include <QRegularExpression>

ScoreWindow::ScoreWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ScoreWindow)
{
    ui->setupUi(this);
    connect(ui->open_action, &QAction::triggered, this, &ScoreWindow::openFolder);
    connect(ui->filter_lineEdit, &QLineEdit::textChanged, this, &ScoreWindow::filterFiles);
    connect(ui->files_listWidget, &QListWidget::currentTextChanged, this, &ScoreWindow::selectionChanged);
}

ScoreWindow::~ScoreWindow()
{
    delete ui;
}

void ScoreWindow::openFolder() {
    auto base_path = folder_path != "" ? folder_path : QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    folder_path = QFileDialog::getExistingDirectory(this, "Open folder", base_path);
    if(folder_path != "") {
        ui->files_listWidget->clear();
    }
    updateFolderFiles();
    filterFiles(ui->filter_lineEdit->text());
}

void ScoreWindow::updateFolderFiles() {
    ui->path_label->setText(folder_path);
    if(folder_path != "") {
        QDirIterator pdfIt(folder_path, {"*.pdf"}, QDir::Files, QDirIterator::Subdirectories|QDirIterator::FollowSymlinks);
        while(pdfIt.hasNext()) {
            QString filename = pdfIt.next();
            filename.remove(0, folder_path.size()+1);
            ui->files_listWidget->addItem(filename);
        }
    }
}

void ScoreWindow::filterFiles(QString filter_text) {
    if(filter_text == "") {
        filter_text = ui->filter_lineEdit->placeholderText();
    }

    auto filter_regex = QRegularExpression(filter_text, QRegularExpression::CaseInsensitiveOption);

    for(int i=0; i < ui->files_listWidget->count(); i++) {
        auto item = ui->files_listWidget->item(i);
        bool match = filter_regex.match(item->text()).hasMatch();
        item->setHidden(!match);
    }

}

void ScoreWindow::selectionChanged(QString text) {
    auto filename = folder_path + "/" + text;
    //emit filePreview(filename);
    qDebug() << filename;
    ui->preview_pdfview->setFile(filename);
}
