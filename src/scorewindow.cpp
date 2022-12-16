#include "scorewindow.h"
#include "./ui_scorewindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDirIterator>
#include <QDebug>
#include <QRegularExpression>
#include "fileitemmodel.h"


ScoreWindow::ScoreWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ScoreWindow)
{
    ui->setupUi(this);
    connect(ui->open_action, &QAction::triggered, this, &ScoreWindow::openFolder);
    connect(ui->filter_lineEdit, &QLineEdit::textChanged, this, &ScoreWindow::filterFiles);
    connect(ui->files_listView, &QListView::clicked, this, &ScoreWindow::selectionChanged);

    files_model = new FileItemModel(this);
    ui->files_listView->setModel(files_model);
}

ScoreWindow::~ScoreWindow()
{
    delete ui;
}

void ScoreWindow::openFolder() {
    auto base_path = folder_path != "" ? folder_path : QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    folder_path = QFileDialog::getExistingDirectory(this, "Open folder", base_path);
    if(folder_path != "") {
        files_model->clear();
    }
    updateFolderFiles();
    filterFiles(ui->filter_lineEdit->text());
}

void ScoreWindow::updateFolderFiles() {
    qDebug() << "repopulate list";
    ui->path_label->setText(folder_path);
    if(folder_path != "") {
        QDirIterator pdfIt(folder_path, {"*.pdf"}, QDir::Files, QDirIterator::Subdirectories|QDirIterator::FollowSymlinks);
        while(pdfIt.hasNext()) {
            QString filename = pdfIt.next();
            filename.remove(0, folder_path.size()+1);

            files_model->append(filename);
        }
    }
}

void ScoreWindow::filterFiles(QString filter_text) {
    if(filter_text == "") {
        filter_text = ui->filter_lineEdit->placeholderText();
    }

    auto filter_regex = QRegularExpression(filter_text, QRegularExpression::CaseInsensitiveOption);



    for(int i=0; i < files_model->rowCount(); i++) {
        auto mi = files_model->index(i);
        auto filename = files_model->data(mi).toString();
        bool match = filter_regex.match(filename).hasMatch();
        ui->files_listView->setRowHidden(i, !match);
    }

}

void ScoreWindow::selectionChanged(const QModelIndex & index) {
    auto filename = folder_path + "/" + ui->files_listView->model()->data(index).toString();
    ui->preview_pdfview->setFile(filename);
}
