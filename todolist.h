#ifndef TODOPARSER_H
#define TODOPARSER_H

#include <QVector>

class ToDoItem;
class QString;

class ToDoList
{
public:
    ToDoList(QString path);

    QVector<ToDoItem *> items() const { return m_items; }
    void remove_item(int i) { if (i < m_items.size()) m_items.remove(i); }
    ToDoItem *at(int index) { return m_items.at(index); }

    void read_file();
    void save_file();

    void add_new_item(ToDoItem *);

private:
    QVector<ToDoItem *> m_items;
    QString m_path;

};

#endif // TODOPARSER_H
