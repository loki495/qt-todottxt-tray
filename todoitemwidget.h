#ifndef TODOITEMWIDGET_H
#define TODOITEMWIDGET_H

#include <QObject>
#include <QWidget>

class QStackedLayout;
class QLineEdit;
class QLabel;

class TodoItemWidget : public QWidget
{
    Q_OBJECT
public:
    TodoItemWidget(QWidget *parent, QString text, QString priority, bool new_item = false);

    QLineEdit *description_edit() { return m_description_edit; }
    QString text() const { return m_description; }
    void setText(const QString &text) { m_description = text; }

    QLineEdit *priority_edit() { return m_priority_edit; }
    QString priority() const { return m_priority; }
    void setPriority(const QString &priority) { m_priority = priority; }


    void save_item();

    bool is_new_item() { return m_new_item; }

    bool eventFilter(QObject *obj, QEvent *event);

    void cancel_edit();

signals:
    void deleted(TodoItemWidget *);
    void edited(TodoItemWidget *);

public slots:
    void delete_item(const QString &);
    void edit_item(const QString &);

private:
    void create_view_widget();
    void create_edit_widget();

    QStackedLayout *m_stacked_layout;
    QLabel *m_priority_label;
    QLabel *m_description_label;

    QLineEdit *m_priority_edit;
    QLineEdit *m_description_edit;

    QString m_description;
    QString m_priority;

    bool m_new_item;
};

#endif // TODOITEMWIDGET_H
