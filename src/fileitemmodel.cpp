#include "fileitemmodel.h"



FileItemModel::FileItemModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

//QVariant FileItemModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    // FIXME: Implement me!
//}

//QModelIndex FileItemModel::index(int row, int column, const QModelIndex &parent) const
//{
//    // FIXME: Implement me!
//}

//QModelIndex FileItemModel::parent(const QModelIndex &index) const
//{
//    // FIXME: Implement me!
//}

int FileItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return files.size();
}

//int FileItemModel::columnCount(const QModelIndex &parent) const
//{
//    if (!parent.isValid())
//        return 0;

//    // FIXME: Implement me!
//}

QVariant FileItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole) {
        return files[index.row()];
    }

    return QVariant();
}

void FileItemModel::append(const QString &item)
{
    beginInsertRows(QModelIndex(), files.count(), files.count());
    files.append(item);
    endInsertRows();
}

void FileItemModel::clear() {
    beginResetModel();
    files.clear();
    endResetModel();
}
