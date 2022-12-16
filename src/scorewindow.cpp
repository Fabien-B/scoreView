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
    files_model = new FileItemModel(this);

    ui->setupUi(this);
    ui->files_listView->setModel(files_model);

    //ui->files_listView->setStyleSheet("QListView::item{background: green;}");
    //QString st = "QListView {show-decoration-selected: 1; }QListView::item:alternate {    background: #EEEEEE;}QListView::item:selected {    border: 1px solid #6a6ea9;}QListView::item:selected:!active {    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #ABAFE5, stop: 1 #8588B2);}QListView::item:selected:active {    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #6a6ea9, stop: 1 #888dd9);}QListView::item:hover {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FAFBFE, stop: 1 #DCDEF1);}";
    //ui->files_listView->setStyleSheet("font-size: 50px");
    //ui->files_listView->setGridSize(QSize(100, 50));

    connect(ui->open_action, &QAction::triggered, this, &ScoreWindow::openFolder);
    connect(ui->filter_lineEdit, &QLineEdit::textChanged, this, &ScoreWindow::filterFiles);
    connect(ui->files_listView->selectionModel(), &QItemSelectionModel::currentChanged, this, &ScoreWindow::selectionChanged);
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

void ScoreWindow::selectionChanged(const QModelIndex & index, const QModelIndex & prev) {
    auto filename = folder_path + "/" + ui->files_listView->model()->data(index).toString();
    ui->preview_pdfview->setFile(filename);
}
