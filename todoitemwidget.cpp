#include "todolist.h"
#include "todoitem.h"
#include "todoitemwidget.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QLineEdit>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>

extern ToDoList *g_list;

TodoItemWidget::TodoItemWidget(QWidget *parent, QString text, QString item_priority, bool new_item)
    : QWidget(parent)
    , m_description(text)
    , m_priority(item_priority.isNull() || item_priority.isEmpty() || item_priority[0] == 0 ? "" : item_priority)
    , m_new_item(new_item)
{
    m_stacked_layout = new QStackedLayout();
    setLayout(m_stacked_layout);
    layout()->setAlignment(Qt::AlignTop);

    setMaximumHeight(35);

    create_view_widget();
    create_edit_widget();

    if (new_item) {
        m_stacked_layout->setCurrentIndex(1);
    }
}

void TodoItemWidget::create_view_widget() {
    QWidget *container_widget = new QWidget(this);
    container_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    container_widget->setLayout(new QHBoxLayout());
    container_widget->layout()->setAlignment(Qt::AlignTop);

    m_priority_label = new QLabel(container_widget);
    m_priority_label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    m_priority_label->setMaximumWidth(16);
    m_priority_label->setMinimumHeight(25);
    m_priority_label->setText(m_priority);
    container_widget->layout()->addWidget(m_priority_label);

    m_description_label = new QLabel(container_widget);
    m_description_label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_description_label->setMinimumHeight(25);
    m_description_label->setText(m_description);
    container_widget->layout()->addWidget(m_description_label);

    QString edit_link = QString("<a href=©#©>Edit</a>");
    QLabel *edit_label = new QLabel(container_widget);
    edit_label->setText(edit_link);
    edit_label->setTextFormat(Qt::RichText);
    edit_label->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    connect(edit_label, &QLabel::linkActivated, this, &TodoItemWidget::edit_item);
    container_widget->layout()->addWidget(edit_label);

    QString delete_link = QString("<a href=©#©>Delete</a>");
    QLabel *delete_label = new QLabel(container_widget);
    delete_label->setText(delete_link);
    delete_label->setTextFormat(Qt::RichText);
    delete_label->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    connect(delete_label, &QLabel::linkActivated, this, &TodoItemWidget::delete_item);
    container_widget->layout()->addWidget(delete_label);

    layout()->addWidget(container_widget);
}

void TodoItemWidget::create_edit_widget() {
    QWidget *container_widget = new QWidget(this);
    container_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    container_widget->setLayout(new QHBoxLayout());
    container_widget->layout()->setAlignment(Qt::AlignTop | Qt::AlignJustify);

    m_priority_edit = new QLineEdit(container_widget);
    m_priority_edit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    m_priority_edit->setMaxLength(1);
    m_priority_edit->setMaximumWidth(16);
    m_priority_edit->setText(m_priority);
    m_priority_edit->installEventFilter(this);
    container_widget->layout()->addWidget(m_priority_edit);

    m_description_edit = new QLineEdit(container_widget);
    m_description_edit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_description_edit->setText(m_description);
    m_description_edit->installEventFilter(this);
    container_widget->layout()->addWidget(m_description_edit);

    QString save_link = QString("<a href=©#©>Save</a>");
    QLabel *save_label = new QLabel(container_widget);
    save_label->setText(save_link);
    save_label->setTextFormat(Qt::RichText);
    save_label->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    connect(save_label, &QLabel::linkActivated, this, [&] () {
        save_item();
    });
    container_widget->layout()->addWidget(save_label);

    QString cancel_link = QString("<a href=©#©>Cancel</a>");
    QLabel *cancel_label = new QLabel(container_widget);
    cancel_label->setText(cancel_link);
    cancel_label->setTextFormat(Qt::RichText);
    cancel_label->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    connect(cancel_label, &QLabel::linkActivated, this, [&](const QString&) {
        cancel_edit();
    });
    container_widget->layout()->addWidget(cancel_label);

    layout()->addWidget(container_widget);
}

void TodoItemWidget::delete_item(const QString&) {
    emit deleted(this);
}

void TodoItemWidget::edit_item(const QString&) {
    m_stacked_layout->setCurrentIndex(1);
}

void TodoItemWidget::save_item() {
    QString new_description = m_description_edit->text();
    QString new_priority = m_priority_edit->text();

    if (new_description.isEmpty()) {
        description_edit()->setFocus();
        return;
    }

    m_description_label->setText(new_description);
    m_priority_label->setText(new_priority);

    m_stacked_layout->setCurrentIndex(0);
    emit edited(this);
}

void TodoItemWidget::cancel_edit() {
    if (!m_new_item)
        m_stacked_layout->setCurrentIndex(0);
    else
        emit deleted(this);
}

bool TodoItemWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() != QEvent::KeyPress)
        return QObject::eventFilter(obj, event);

    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

    if (keyEvent->key() == Qt::Key_Escape) {
        cancel_edit();
        return true;
    }

    if (keyEvent->key() == Qt::Key_Return) {
        save_item();
        return true;
    }

    return QObject::eventFilter(obj, event);
}
