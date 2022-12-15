#ifndef PDFVIEW_H
#define PDFVIEW_H

#include <QWidget>

class PdfView : public QWidget
{
    Q_OBJECT
public:
    explicit PdfView(QWidget *parent = nullptr);

    void setFile(QString filename) {this->filename = filename; update();}
    void setPage(int no) {page_no = no; update();}

protected:
    void paintEvent(QPaintEvent *event);

signals:

private:
    QString filename;
    int page_no;

};

#endif // PDFVIEW_H
