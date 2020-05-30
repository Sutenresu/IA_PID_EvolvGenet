#include "graph.h"
#include <QApplication>
#include "evolution.h"
#include "gene.h"
#include <vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Graph w;
    w.show();

    return a.exec();
}
