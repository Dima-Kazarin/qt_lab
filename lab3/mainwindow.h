#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QToolButton>
#include <QGridLayout>
#include <QDockWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFileInfo>
#include <QInputDialog>


class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QToolBar *tools;
    QMenuBar *menu_bar;
    QMenu *file, *edit, *help;

    QAction *create_file, *open_file, *save_file, *save_file_as, *close_file, *clear_text, *to_upper, *to_lower,
        *enlarge, *reduce, *about, *help_box, *replace_text;
    QTextEdit *text_edit;
    QToolButton *enlarge_font, *reduce_font, *clear, *upper, *lower;
    QGridLayout *dock_grid;
    QDockWidget *dock;
    QWidget *dock_widget;
    QString current_file_name;
    QLabel *file_name_label;
    QGroupBox *group_box;
    QVBoxLayout *layout;
    bool unsaved_changes;
    QStatusBar *status_bar;

public slots:
    void create();
    void open();
    void save();
    void save_as();
    void close();
    void convertTextToUpper();
    void convertTextToLower();
    void showAboutDialog();
    void showHelpDialog();
    void enlargeFont();
    void reduceFont();
    void markUnsavedChanges();
    void replaceText();
    void clearText();

public:
    void createActions();
    void createMenu();
    void createTools();
    void createDockWidget();
    void setUnsavedChanges(bool has_unsaved_changes);
};

#endif // MAINWINDOW_H
