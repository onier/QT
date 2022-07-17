//
// Created by root on 7/17/22.
//

#ifndef PUPPY_MYTABLE_H
#define PUPPY_MYTABLE_H

#include "QTableView"

struct MyTable : public QTableView {
protected:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override {
        QTableView::selectionChanged(selected, deselected);
    }

public:
    void setSelectionModel(QItemSelectionModel *selectionModel) override {
        QObject::connect(selectionModel, &QItemSelectionModel::selectionChanged,
                this, &MyTable::selectionChanged);
        QTableView::setSelectionModel(selectionModel);

    }
};
#endif //PUPPY_MYTABLE_H
