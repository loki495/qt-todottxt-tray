#include "todolist.h"
#include "todoitem.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>

ToDoList::ToDoList(QString path)
{
    m_path = path;
    read_file();
}

void ToDoList::read_file() {

    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug().noquote().nospace() << "Error opening file \"" << m_path << "\"";
        return;
    }

    while (!file.atEnd()) {
        QString line = file.readLine().trimmed();
        if (!line.isEmpty())
            m_items.append(new ToDoItem(line));
    }

    file.close();
}

void ToDoList::save_file() {
    QFile file(m_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug().noquote().nospace() << "Error opening save file \"" << m_path << "\"";
        return;
    }

    for (ToDoItem *item : m_items) {
        file.write(item->get_save_string().toStdString().c_str());
        if (item != *m_items.end())
            file.write("\n");
    }

    file.close();
}

void ToDoList::add_new_item(ToDoItem *item) {
    m_items.prepend(item);
}
