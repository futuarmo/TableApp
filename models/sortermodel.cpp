#include "sortermodel.h"

#include <QBrush>
#include <QDebug>
#include <sstream>
#include <iomanip>
#include <random>

namespace {
    const int itemsCount = 100;
}

SorterModel::SorterModel(QObject *parent)
{
    m_securities.reserve(itemsCount);


    for (size_t i = 1; i <= itemsCount; i++) {
        std::ostringstream ss;
        ss << "S";
        ss << std::setw(3) << std::setfill('0') << i;
        m_securities.push_back(ss.str());
    }

    m_prevBids = std::vector<int>(itemsCount);
    m_prevAsks = std::vector<int>(itemsCount);
    m_prevCloses = m_prevBids = std::vector<int>(itemsCount);
    m_bids = m_prevBids = std::vector<int>(itemsCount);
    m_asks = m_prevBids = std::vector<int>(itemsCount);
    m_closes = m_prevBids = std::vector<int>(itemsCount);
}

int SorterModel::rowCount(const QModelIndex &parent) const {
    return static_cast<int>(m_securities.size());
}

int SorterModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

void SorterModel::generateData() {
    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_int_distribution<std::mt19937::result_type> bidDist(1,1000000);
    for (int i = 0; i < itemsCount; i++) {
        m_prevBids[i] = m_bids[i];
        m_bids[i] = bidDist(rng);

        std::uniform_int_distribution<std::mt19937::result_type> askDist(m_bids[i],1000000);
        m_prevAsks[i] = m_asks[i];
        m_asks[i] = askDist(rng);

        std::uniform_int_distribution<std::mt19937::result_type> closeDist(m_bids[i],m_asks[i]);
        m_prevCloses[i] = m_closes[i];
        m_closes[i] = closeDist(rng);
    }


    QAbstractItemModel::beginResetModel();
    QAbstractItemModel::endResetModel();
}

QVariant SorterModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_securities.size())
        return QVariant();

    int row = index.row();

    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0:
            return QString::fromStdString(m_securities.at(row));
        case 1:
            return QVariant::fromValue(m_bids[row]);
        case 2:
            return QVariant::fromValue(m_asks[row]);
        case 3:
            return QVariant::fromValue(m_closes[row]);
        default:
            return QVariant();
        }
        break;
    case Qt::ForegroundRole:
        switch (index.column()) {
        case 0:
            return QBrush(Qt::white);
        case 1:
            return m_prevBids[row] > m_bids[row] ? QBrush(Qt::red) : QBrush(Qt::green);
        case 2:
            return m_prevAsks[row] > m_asks[row] ? QBrush(Qt::red) : QBrush(Qt::green);
        case 3:
            return m_prevCloses[row] > m_closes[row] ? QBrush(Qt::red) : QBrush(Qt::green);
        }
        break;
    case Qt::BackgroundRole:
        switch (index.column()) {
        case 0:
        case 1:
        case 2:
        case 3:
            return QBrush(Qt::black);
        }
        break;
    }
    return QVariant();
}

QVariant SorterModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return tr("Security");
        case 1:
            return tr("Bid");
        case 2:
            return tr("Ask");
        case 3:
            return tr("Last");
        default:
            return QVariant();
        }
    }
    return QVariant();
}
