
#include <QApplication>
#include "QTableView"
#include "MyTableModel.h"
#include "thread"
#include "MyTable.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MyTableModel *model = new MyTableModel();

    QTableView *ww = new QTableView();
    ww->setModel(model);
    ww->show();
    for (int i = 0; i < 1; ++i) {
        QTableView *w = new QTableView();
        w->setSelectionModel(ww->selectionModel());
        w->setModel(model);
        w->show();
    }


#include "chrono"

    std::thread th([model]() {
        for (int i = 0; i < 20; ++i) {
            using namespace std::chrono_literals;
            model->addValue();
        }
    });
    th.detach();
    return a.exec();
}
