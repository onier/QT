//
// Created by root on 7/17/22.
//

#include "MyTableModel.h"
#include "map"
#include "glog/logging.h"
#include "boost/lexical_cast.hpp"
MyTableModel::MyTableModel() {
}

int MyTableModel::rowCount(const QModelIndex &parent) const {
    return _indexs.size();
}

int MyTableModel::columnCount(const QModelIndex &parent) const {
    return _indexs.size();
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const {
    bool b = isSelected(index.row(), index.column());
    if (role == Qt::DisplayRole) {
        if (b)
            return "Select";
        else
            return "UnSelect";
    }
    if (role == Qt::CheckStateRole) {
        if (b) {
            return Qt::Checked;
        } else {
            return Qt::Unchecked;
        }
    }
    return QVariant();
}

Qt::ItemFlags MyTableModel::flags(const QModelIndex &index) const {
    if (index.row() == index.column()) {
        return Qt::NoItemFlags;
    }
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}

void MyTableModel::addValue(QString value) {
    beginResetModel();
    if(value.isEmpty()){
        _indexs.push_back("Item"+boost::lexical_cast<std::string>(_indexs.size()));
    }else{
        _indexs.push_back(value.toStdString());
    }
    endResetModel();


}


bool MyTableModel::isSelected(int row, int column) const {
    for (auto &p: _selections) {
        if ((p.first == _indexs[row] && p.second == _indexs[column]) ||
            (p.first == _indexs[column] && p.second == _indexs[row])) {
            return true;
        }
    }
    return false;
}

void MyTableModel::setSelect(int row, int column, bool selected) {
    beginResetModel();
    if (selected)
        _selections.push_back({_indexs[row], _indexs[column]});
    else {
        auto rValue = _indexs[column];
        auto cValue = _indexs[row];
        auto iter = std::remove_if(_selections.begin(),_selections.end(),[rValue,cValue](auto & p){
            if ((p.first == rValue && p.second == cValue) ||
                (p.first == cValue && p.second == rValue)) {
                return true;
            }else{
                return false;
            }
        });
        if (iter != _selections.end()) {
            _selections.erase(iter);
        }
    }
    endResetModel();
}

bool MyTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role == Qt::CheckStateRole) {
        setSelect(index.row(), index.column(), value.toBool());
    }
    return QAbstractItemModel::setData(index, value, role);
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role==Qt::DisplayRole){
        if(section<_indexs.size()){
            return _indexs[section].data();
        }
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}
