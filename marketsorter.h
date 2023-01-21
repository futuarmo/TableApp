#pragma once

#include <QMainWindow>
#include <QTimer>

#include "models/sortermodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MarketSorter; }
QT_END_NAMESPACE

class MarketSorter : public QMainWindow
{
    Q_OBJECT

public:
    MarketSorter(QWidget *parent = nullptr);
    ~MarketSorter();

private:
    SorterModel* m_sorterModel{nullptr};
    QTimer *m_timer;

    Ui::MarketSorter *ui;
};
