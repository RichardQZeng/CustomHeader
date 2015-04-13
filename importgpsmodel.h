#ifndef IMPORTGPSMODEL_H
#define IMPORTGPSMODEL_H

#include <QAbstractTableModel>

class ImportGpsModel : public QAbstractTableModel
{
public:
    ImportGpsModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};


#endif // IMPORTGPSMODEL_H
