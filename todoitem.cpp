#include <QDebug>
#include <QRegularExpression>

#include <stdio.h>
#include "time.h"
#include "todoitem.h"

ToDoItem::ToDoItem(bool completed, char item_priority, QString completion_date, QString creation_date, QString description)
    : m_completed(completed)
    , m_priority(item_priority)
    , m_completion_date(completion_date)
    , m_creation_date(creation_date)
    , m_description(description)
{
}

ToDoItem::ToDoItem(QString line)
    : m_line(line)
{
    consume_spaces();
    check_for_completed();

    if (m_completed) {
        consume_spaces();
        check_for_completion_date();
    } else {
        consume_spaces();
        check_for_priority();
    }

    consume_spaces();
    check_for_creation_date();

    consume_spaces();
    m_description = current_string();
}

QString ToDoItem::to_string() {

    QString result;

    result.append("Completed: ");
    result.append(m_completed ? "true" : "false");
    result.append("\n");

    if (m_completed) {
        if (!m_completion_date.isEmpty()) {
            result.append("Completed date: ");
            result.append(m_completion_date);
            result.append("\n");
        }
    } else {
        if (m_priority) {
            result.append("Priority: ");
            result.append(m_priority);
            result.append("\n");
        }
    }

    if (!m_creation_date.isEmpty()) {
        result.append("Creation date: ");
        result.append(m_creation_date);
        result.append("\n");
    }

    result.append("Description: ");
    result.append(m_description);
    result.append("\n");

    return result;
}

char ToDoItem::peek(int offset) {
    int peek_index = m_current_index + offset;

    if (peek_index > m_line.size())
        return 0;

    return m_line.at(m_current_index + offset).toLatin1();
}

void ToDoItem::check_for_completed() {
    if (peek() != 'x' || peek(1) != ' ')
        return;

    m_completed = true;
    m_current_index += 2;
}

void ToDoItem::check_for_priority() {
    if (peek() == '(' && peek(1) >= 'A' && peek(1) <= 'Z' && peek(2) == ')' && peek(3) == ' ') {
        m_priority = peek(1);
        m_current_index += 4;
    }
}

QString ToDoItem::check_for_date() {
    QString result;

    QRegularExpression regex("^(\\d{4}-\\d{2}-\\d{2})");
    QRegularExpressionMatch match = regex.match(current_string());

    if (match.hasMatch()) {
        result = match.captured();
        return result;
    }

    return {};
}

void ToDoItem::check_for_completion_date() {
    QString date = check_for_date();

    if (!date.isEmpty()) {
        m_completion_date = date;
        m_current_index += date.size();
    }
}

void ToDoItem::check_for_creation_date() {
    QString date = check_for_date();

    if (!date.isEmpty()) {
        m_creation_date = date;
        m_current_index += date.size();
    }
}

void ToDoItem::consume_spaces() {
    while (isspace(peek())) {
        ++m_current_index;
    }
}

QString ToDoItem::get_save_string() {
    QString result;

    if (m_completed) {
        result.append("x");
        result.append(" ");
        if (!m_completion_date.isEmpty()) {
            result.append(m_completion_date);
            result.append(" ");
        }
    } else {
        if (m_priority) {
            result.append("(");
            result.append(m_priority);
            result.append(")");
            result.append(" ");
        }
    }

    if (!m_creation_date.isEmpty()) {
        result.append(m_creation_date);
        result.append(" ");
    }

    result.append(m_description);

    return result;
}
