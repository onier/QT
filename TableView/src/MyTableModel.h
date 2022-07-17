//
// Created by root on 7/17/22.
//

#ifndef PUPPY_MYTABLEMODEL_H
#define PUPPY_MYTABLEMODEL_H

#include "QAbstractTableModel"

class MyTableModel : public QAbstractTableModel {
public:
    MyTableModel();

    int rowCount(const QModelIndex &parent) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    void addValue(QString value="");

    bool isSelected(int row, int column) const;

    void setSelect(int row,int column,bool selected);
    std::vector<std::string> _indexs;
    std::vector<std::pair<std::string, std::string>> _selections;
};


#endif //PUPPY_MYTABLEMODEL_H
