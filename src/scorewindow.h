#ifndef SCOREWINDOW_H
#define SCOREWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ScoreWindow; }
QT_END_NAMESPACE

class ScoreWindow : public QMainWindow
{
    Q_OBJECT

public:
    ScoreWindow(QWidget *parent = nullptr);
    ~ScoreWindow();

signals:
    //void filePreview(QString filename);

private slots:
    void openFolder();

private:
    void updateFolderFiles();
    void filterFiles(QString filter_text);
    void selectionChanged(QString text);

    Ui::ScoreWindow *ui;

    QString folder_path;
};
#endif // SCOREWINDOW_H
