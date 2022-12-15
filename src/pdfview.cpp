#include "pdfview.h"
#include <QPaintEvent>
#include <QPainter>
#include <poppler-qt5.h>
#include <QDebug>


PdfView::PdfView(QWidget *parent) : QWidget{parent},
    filename(""), page_no(0)

{

}

void PdfView::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    if(filename == "") {
        return;
    }

    Poppler::Document* document = Poppler::Document::load(filename);
    if(document) {
        // Access page of the PDF file
        Poppler::Page* pdfPage = document->page(page_no);  // Document starts at page 0
        if (pdfPage) {
            auto page_size = pdfPage->pageSize();
            double w_ratio = static_cast<double>(rect().height()) / page_size.width();
            double h_ratio = static_cast<double>(rect().width()) / page_size.height();
            qDebug() << rect() << size() << sizeHint() << w_ratio << h_ratio;
            //document->setRenderHint(Poppler::Document::TextAntialiasing);
            //document->setRenderHint(Poppler::Document::Antialiasing);
            //document->setRenderHint(Poppler::Document::ThinLineSolid);
            //document->setRenderHint(Poppler::Document::ThinLineShape);


            int dpi = qMin(w_ratio, h_ratio) * 72;
            qDebug() << dpi;
            QImage image = pdfPage->renderToImage(dpi, dpi, -1, -1, -1, -1, Poppler::Page::Rotate270);
            //QImage rotatedImg = image.transformed(QMatrix().rotate(90.0));
            //QImage rotatedImg = image.transformed(QTransform(QMatrix().rotate(-90)));
            //auto imgScaled = rotatedImg.scaled(rect().size(), Qt::KeepAspectRatio);
            p.drawImage(image.rect(), image);
            delete pdfPage;
        }
        delete document;
    }

}
