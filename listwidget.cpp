#include <QDebug>
#include <QPushButton>
#include <QSize>
#include <QRect>
#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QScreen>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QDialog>
#include <QDateTime>
#include "listwidget.h"
#include "todolist.h"
#include "todoitem.h"
#include "todoitemwidget.h"

extern ToDoList *g_list;

/*
 * TO DO
 *

- add left column for category browsing

 */

ListWidget::ListWidget()
    : QWidget(nullptr)
{

    int width = 550;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screen_rect = screen->geometry();
    setGeometry(screen_rect.width() - width, 20, width, 0);

    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    setLayout(new QVBoxLayout());
    layout()->setAlignment(Qt::AlignTop);

    QWidget *top_container = new QWidget(this);
    top_container->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    top_container->setLayout(new QHBoxLayout());

    QPushButton *add_new_button = new QPushButton(top_container);
    add_new_button->setText("+");
    connect(add_new_button, &QPushButton::clicked, this, &ListWidget::new_todo);
    top_container->layout()->addWidget(add_new_button);

    m_search = new QLineEdit(top_container);
    m_search->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    connect(m_search, &QLineEdit::textChanged, this, &ListWidget::filter_list);
    top_container->layout()->addWidget(m_search);

    layout()->addWidget(top_container);

    m_list_container = new QWidget(this);
    layout()->addWidget(m_list_container);

    m_list_container->setLayout(new QVBoxLayout());
    m_list_container->layout()->setAlignment(Qt::AlignTop);
    m_list_container->setAutoFillBackground(true);

    update_list();
}

void ListWidget::update_list() {
    auto existing_list = m_list_container->findChildren<QWidget*>();
    for (auto *item : existing_list)
        if (item) item->deleteLater();

    for (ToDoItem *it : g_list->items()) {
        TodoItemWidget *widget = new TodoItemWidget(this, it->description(), QString(it->priority()));

        connect(widget, &TodoItemWidget::edited, this, &ListWidget::edit_item);
        connect(widget, &TodoItemWidget::deleted, this, &ListWidget::delete_item);
        m_list_container->layout()->addWidget(widget);
    }

    m_search->setFocus();
}

void ListWidget::keyPressEvent(QKeyEvent *event) {
    if (event->type() == QEvent::KeyPress && event->key() == Qt::Key_Escape) {
        if (m_search->hasFocus() && !m_search->text().isEmpty())
            m_search->setText("");
        else
            hide();
    }
}

void ListWidget::focusOutEvent(QFocusEvent *) {
    hide();
}

void ListWidget::filter_list(const QString &text) {
    for (auto* widget: m_list_container->findChildren<TodoItemWidget*>())
        widget->setHidden(!widget  ->text().contains(text, Qt::CaseInsensitive));
}

void ListWidget::delete_item(TodoItemWidget *item) {
    int index = m_list_container->findChildren<TodoItemWidget*>().indexOf(item);
    if (index < 0) {
        qDebug() << "Index ©" << index << "© not found on delete";
        return;
    }

    if (!item->is_new_item()) {
        g_list->remove_item(index);
        g_list->save_file();
    }

    delete item;
}

void ListWidget::edit_item(TodoItemWidget *item) {
    QString new_description = "";
    QString new_priority = "";

    int index = m_list_container->findChildren<TodoItemWidget*>().indexOf(item);

    if (index < 0) {
        qDebug() << "Index ©" << index << "© not found on save edit";
        return;
    }

    new_description = item->description_edit()->text();
    new_priority = item->priority_edit()->text();

    if (item->is_new_item()) {
        QString creation_date = QDateTime::currentDateTime().toString("yyyy-mm-dd");
        g_list->add_new_item(new ToDoItem(0, !new_priority.isEmpty() ? new_priority.toLatin1()[0] : 0,"",creation_date,new_description));
    } else {
        g_list->at(index)->set_description(new_description);
        g_list->at(index)->set_priority(!new_priority.isEmpty() ? new_priority.toLatin1()[0] : 0);
    }
    g_list->save_file();

    update_list();
}

void ListWidget::new_todo() {
    TodoItemWidget *widget = new TodoItemWidget(this, "", 0, true);
    widget->setStyleSheet("TodoItemWidget { border: 1px solid red } ");
    connect(widget, &TodoItemWidget::edited, this, &ListWidget::edit_item);
    connect(widget, &TodoItemWidget::deleted, this, &ListWidget::delete_item);
    ((QVBoxLayout*)m_list_container->layout())->insertWidget(0,widget);
    widget->description_edit()->setFocus();
    return;
}
