#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QHBoxLayout>

class TodoItemWidget;

class ListWidget : public QWidget
{
        Q_OBJECT
public:
    ListWidget();

    void update_list();

    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;

public slots:
    void filter_list(const QString &);
    void edit_item(TodoItemWidget* item);
    void delete_item(TodoItemWidget* item);
    void new_todo();

private:
    QWidget* m_list_container;
    QLineEdit* m_search;
};

#endif // LISTWIDGET_H
