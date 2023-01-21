#include "marketsorter.h"
#include "models/sortermodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MarketSorter w;
    w.show();

    return a.exec();
}
