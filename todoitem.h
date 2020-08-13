#ifndef TODOITEM_H
#define TODOITEM_H

#include <time.h>
#include <QString>

class ToDoItem {
public:
    ToDoItem(QString);
    ToDoItem(bool completed, char item_priority, QString completion_date, QString creation_date, QString description);

    bool completed() const { return m_completed; }
    void setCompleted(bool completed) { m_completed = completed; }

    char priority() const { return m_priority; }
    void set_priority(char priority) { m_priority = priority; }

    QString completion_date() const { return m_completion_date; }
    QString creation_date() const { return m_creation_date; }

    QString description() const { return m_description; }
    void set_description(QString d) { m_description = d; }

    QString current_string() { return m_line.right(m_line.size() - m_current_index); }
    QString to_string();

    QString get_save_string();

private:

    char peek(int offset = 0);
    void consume_spaces();

    void check_for_completed();
    void check_for_priority();
    QString check_for_date();
    void check_for_completion_date();
    void check_for_creation_date();

    bool m_completed { false };
    char m_priority { 0 };
    QString m_completion_date { };
    QString m_creation_date { };
    QString m_description { };

    QString m_line;
    int m_current_index { 0 };
};

#endif // TODOITEM_H
