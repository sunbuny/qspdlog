#pragma once

#include <QAbstractListModel>
#include <deque>
#include <optional>
#include <QFont>

class QLoguruModel : public QAbstractListModel
{
public:
    Q_OBJECT
public:
    struct entry_t {
        std::string time;
        std::string elapsed;
        int level;
        std::string message;
        std::string loggerName;
    };

public:
    QLoguruModel(QObject* parent = nullptr);
    ~QLoguruModel() override = default;

    void addEntry(entry_t entry);
    void clear();

    void setMaxEntries(std::optional<std::size_t> maxEntries);
    std::optional<std::size_t> getMaxEntries() const;

    void setLoggerForeground(std::string_view loggerName, std::optional<QColor> color);
    std::optional<QColor> getLoggerForeground(std::string_view loggerName) const;

    void setLoggerBackground(std::string_view loggerName, std::optional<QBrush> brush);
    std::optional<QBrush> getLoggerBackground(std::string_view loggerName) const;

    void setLoggerFont(std::string_view loggerName, std::optional<QFont> font);
    std::optional<QFont> getLoggerFont(std::string_view loggerName) const;

#pragma region QAbstractListModel
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override;
    QVariant headerData(
        int section, Qt::Orientation orientation, int role = Qt::DisplayRole
    ) const override;
#pragma endregion

private:
    std::deque<entry_t> _items;
    std::optional<std::size_t> _maxEntries;
    std::map<std::string, QBrush> _backgroundMappings;
    std::map<std::string, QColor> _foregroundMappings;
    std::map<std::string, QFont> _fontMappings;
};
