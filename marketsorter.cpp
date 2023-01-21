#include "marketsorter.h"
#include "./ui_marketsorter.h"

MarketSorter::MarketSorter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MarketSorter)
{
    ui->setupUi(this);

    m_sorterModel = new SorterModel(this);

    m_timer = new QTimer(this);
    m_timer->setInterval(30);
    m_timer->callOnTimeout(m_sorterModel, &SorterModel::generateData);
    m_timer->start();

    ui->tableView->setModel(m_sorterModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MarketSorter::~MarketSorter()
{
    delete ui;
}

