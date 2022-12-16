#ifndef FILEITEMMODEL_H
#define FILEITEMMODEL_H

#include <QAbstractListModel>

class FileItemModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit FileItemModel(QObject *parent = nullptr);

//    // Header:
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

//    // Basic functionality:
//    QModelIndex index(int row, int column,
//                      const QModelIndex &parent = QModelIndex()) const override;
//    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void append(const QString &item);
    void clear();

private:
    QList<QString> files;
};

#endif // FILEITEMMODEL_H
