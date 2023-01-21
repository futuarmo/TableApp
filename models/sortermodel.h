#pragma once

#include <QAbstractItemModel>
#include <vector>

class SorterModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SorterModel(QObject *parent = nullptr);
    void generateData();
private:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    std::vector<std::string> m_securities;

    std::vector<int> m_prevBids;
    std::vector<int> m_prevAsks;
    std::vector<int> m_prevCloses;
    std::vector<int> m_bids;
    std::vector<int> m_asks;
    std::vector<int> m_closes;
};
