#include <QApplication>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QWindow>
#include <QDebug>

#include "trayapp.h"
#include "todolist.h"
#include "todoitem.h"

ToDoList *g_list;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);

    app.setStyleSheet("TodoItemWidget { border: 1px solid red } ");
    app.setStyleSheet("TodoItemWidget:hover { border: 1px solid blue } ");

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
            QMessageBox::critical(nullptr, QObject::tr("Systray"),
                                  QObject::tr("I couldn't detect any system tray "
                                              "on this system."));
            return 1;
    }

    QString file = argc == 2 ? argv[1] : "/home/andres/.todo.txt";
    g_list = new ToDoList(file);
    g_list->save_file();

    QApplication::setQuitOnLastWindowClosed(false);

    new TrayApp();

    return app.exec();
}
