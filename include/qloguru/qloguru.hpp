#pragma once

#include <QFont>
#include <QWidget>


class QtLoggerSink;
class QAbstractLoguruToolBar;
class QMenu;
class QLoguruModel;
class QLoguruProxyModel;
class QTreeView;

enum class AutoScrollPolicy {
    AutoScrollPolicyDisabled =
        0, // Never scroll to the bottom, leave the scrollbar where it was.
    AutoScrollPolicyEnabled =
        1, // Always scroll to the bottom when new rows are inserted.
    AutoScrollPolicyEnabledIfBottom =
        2, // Scroll to the bottom only if the scrollbar was at the bottom
           // before inserting the new ones.
};

class QLoguru : public QWidget
{
public:
    /**
     * @brief Constructor
     *
     * @param parent The parent widget.
     */
    explicit QLoguru(QWidget* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~QLoguru();

public:
    /**
     * @brief Clear the contents of the model.
     *
     * The method will clear up all the cached messages. There's no way after
     * this to restore them.
     */
    void clear();

    /**
     * @brief Register a toolbar.
     *
     * The toolbar will be set up for the current instance. Being set up means
     * - all the actions from the toolbar will affect current instance
     * - the changes to one toolbar will be reflected in the other ones as well
     *
     * @param toolbar the toolbar
     */
    void registerToolbar(QAbstractLoguruToolBar* toolbar);

    /**
     * @brief Remove a toolbar.
     *
     * The toolbar will be removed from the current instance. The toolbar will
     * not be deleted.
     *
     * @param toolbar the toolbar
     */
    void removeToolbar(QAbstractLoguruToolBar* toolbar);


    /**
     * @brief Get the number of items in the widget.
     *
     * @return std::size_t the number of items in the widget
     */
    std::size_t itemsCount() const;

    /**
     * @brief Set the maximum number of items in the widget.
     *
     * @param std::optional<std::size_t> the maximum number of items in the
     * widget
     */
    void setMaxEntries(std::optional<std::size_t> maxEntries);

    /**
     * @brief Get the maximum number of items in the widget.
     *
     * @return std::optional<std::size_t> the maximum number of items in the
     * widget
     */
    std::optional<std::size_t> getMaxEntries() const;

    /**
     * @brief Set the foreground QBrush for the messages of the corresponding
     * logger.
     *
     * @param std::string_view the name of the logger of which to set the
     * foreground brush
     * @param std::optional<QBrush> the brush object or std::nullopt
     */
    void setLoggerForeground(
        std::string_view loggerName, std::optional<QColor> brush
    );

    /**
     * @brief Get the foreground QBrush for the messages of the corresponding
     * logger.
     *
     * @param std::string_view the name of the logger of which to get the
     * foreground brush from
     * @return std::optional<QBrush> the QBrush object or std::nullopt
     */
    std::optional<QColor> getLoggerForeground(std::string_view loggerName
    ) const;

    /**
     * @brief Set the background QBrush for the messages of the corresponding
     * logger.
     *
     * @param std::string_view the name of the logger of which to set the
     * background brush
     * @param std::optional<QBrush> the brush object or std::nullopt
     */
    void setLoggerBackground(std::string_view, std::optional<QBrush> brush);

    /**
     * @brief Get the background QBrush for the messages of the corresponding
     * logger.
     *
     * @param std::string_view the name of the logger of which to get the
     * background brush from
     * @return std::optional<QBrush> the QBrush object or std::nullopt
     */
    std::optional<QBrush> getLoggerBackground(std::string_view loggerName
    ) const;

    /**
     * @brief Set the text QFont for the messages of the corresponding
     * logger.
     *
     * @param std::string_view the name of the logger of which to set the
     * font
     * @param std::optional<QFont> the QFont object or std::nullopt
     */
    void setLoggerFont(std::string_view loggerName, std::optional<QFont> font);

    /**
     * @brief Get the text QFont for the messages of the corresponding
     * logger.
     *
     * @param std::string_view the name of the logger of which to get the
     * font from
     * @return std::optional<QFont> the QFont object or std::nullopt
     */
    std::optional<QFont> getLoggerFont(std::string_view loggerName) const;

    /**
     * @brief Set the policy of the auto-scrolling feature.
     *
     * This function will set the policy for auto-scrolling and will update all
     * the registered toolbars.
     *
     * @param policy the auto-scrolling policy
     */
    void setAutoScrollPolicy(AutoScrollPolicy policy);

private slots:
    void filterData(
        const QString& text, bool isRegularExpression, bool isCaseSensitive
    );
    void updateAutoScrollPolicy(int index);

private:
    QLoguruModel* _sourceModel;
    QLoguruProxyModel* _proxyModel;
    QTreeView* _view;
    bool _scrollIsAtBottom;
    QMetaObject::Connection _scrollConnection;
    std::shared_ptr<QtLoggerSink> _sink;
    std::list<QAbstractLoguruToolBar*> _toolbars;
};
