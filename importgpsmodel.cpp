#include "importgpsmodel.h"

ImportGpsModel::ImportGpsModel() : QAbstractTableModel(){
}

int ImportGpsModel::rowCount(const QModelIndex &parent = QModelIndex()) const
{
    return 5;
}

int ImportGpsModel::columnCount(const QModelIndex &parent = QModelIndex()) const
{
    return 5;
}

QVariant ImportGpsModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
	if (role == Qt::DisplayRole) return QVariant();
	return QVariant();
}
