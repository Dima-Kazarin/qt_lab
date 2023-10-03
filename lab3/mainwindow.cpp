#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenu();
    createTools();
    createDockWidget();

    status_bar = new QStatusBar(this);
    this->setStatusBar(status_bar);

    text_edit = new QTextEdit();
    text_edit->setFixedSize(QSize(400, 450));
    text_edit->setFontPointSize(8);
    text_edit->setReadOnly(true);

    file_name_label = new QLabel("new_file.txt");
    file_name_label->setFixedSize(QSize(400, 10));

    group_box = new QGroupBox(this);
    layout = new QVBoxLayout(group_box);
    layout->addWidget(file_name_label);
    layout->addWidget(text_edit);

    this->setCentralWidget(group_box);

    connect(create_file, &QAction::triggered, this, &MainWindow::create);
    connect(open_file, &QAction::triggered, this, &MainWindow::open);
    connect(save_file, &QAction::triggered, this, &MainWindow::save);
    connect(save_file_as, &QAction::triggered, this, &MainWindow::save_as);
    connect(close_file, &QAction::triggered, this, &MainWindow::close);
    connect(clear_text, &QAction::triggered, this, &MainWindow::clearText);
    connect(to_upper, &QAction::triggered, this, &MainWindow::convertTextToUpper);
    connect(to_lower, &QAction::triggered, this, &MainWindow::convertTextToLower);
    connect(about, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(help_box, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(enlarge, &QAction::triggered, this, &MainWindow::enlargeFont);
    connect(reduce, &QAction::triggered, this, &MainWindow::reduceFont);
    connect(text_edit, &QTextEdit::textChanged, this, &MainWindow::markUnsavedChanges);
    connect(replace_text, &QAction::triggered, this, &MainWindow::replaceText);
}


void MainWindow::createActions()
{
    create_file = new QAction("&New");
    create_file->setIcon(QIcon(":/icons/recources/new.png"));
    create_file->setShortcut(QKeySequence::New);
    open_file = new QAction("&Open");
    open_file->setIcon(QIcon(":/icons/recources/open.png"));
    open_file->setShortcut(QKeySequence::Open);
    save_file = new QAction("&Save");
    save_file->setIcon(QIcon(":/icons/recources/save.png"));
    save_file->setShortcut(QKeySequence::Save);
    save_file_as = new QAction("&Save as");
    save_file_as->setIcon(QIcon(":/icons/recources/save_as.png"));
    save_file_as->setShortcut(QKeySequence::SaveAs);
    close_file = new QAction("&Close");
    close_file->setIcon(QIcon(":/icons/recources/close.png"));
    close_file->setShortcut(QKeySequence::Close);

    clear_text = new QAction("&Clear");
    clear_text->setIcon(QIcon(":/icons/recources/clear.png"));
    to_upper = new QAction("&To upper");
    to_upper->setIcon(QIcon(":/icons/recources/upper.png"));
    to_lower = new QAction("&To lower");
    to_lower->setIcon(QIcon(":/icons/recources/lower.png"));
    enlarge = new QAction("&Enlarge font");
    enlarge->setIcon(QIcon(":/icons/recources/enlarge.png"));
    reduce = new QAction("&Reduce font");
    reduce->setIcon(QIcon(":/icons/recources/reduce.png"));
    replace_text = new QAction("&Replace text");
    replace_text->setIcon(QIcon(":/icons/recources/replace.png"));

    about = new QAction("&About");
    about->setIcon(QIcon(":/icons/recources/about.png"));
    help_box = new QAction("&Help");
    help_box->setIcon(QIcon(":/icons/recources/help.png"));
}


void MainWindow::createMenu()
{
    menu_bar = this->menuBar();

    file = menu_bar->addMenu("&File");
    edit = menu_bar->addMenu("&Edit");
    help = menu_bar->addMenu("&Help");

    file->addAction(create_file);
    file->addSeparator();
    file->addAction(open_file);
    file->addSeparator();
    file->addAction(save_file);
    file->addSeparator();
    file->addAction(save_file_as);
    file->addSeparator();
    file->addAction(close_file);

    edit->addAction(clear_text);
    edit->addSeparator();
    edit->addAction(to_upper);
    edit->addAction(to_lower);
    edit->addSeparator();
    edit->addAction(enlarge);
    edit->addAction(reduce);
    edit->addSeparator();
    edit->addAction(replace_text);

    help->addAction(about);
    edit->addSeparator();
    help->addAction(help_box);
}


void MainWindow::createTools()
{
    tools = addToolBar("Tools");
    tools->addAction(enlarge);
    tools->addAction(reduce);
    tools->addAction(clear_text);
    tools->addAction(to_upper);
    tools->addAction(to_lower);
}


void MainWindow::createDockWidget()
{
    create_f = new QToolButton();
    create_f->setDefaultAction(create_file);
    create_f->setFixedSize(QSize(50, 50));

    open_f = new QToolButton();
    open_f->setDefaultAction(open_file);
    open_f->setFixedSize(QSize(50, 50));

    save_f = new QToolButton();
    save_f->setDefaultAction(save_file);
    save_f->setFixedSize(QSize(50, 50));

    save_as_f = new QToolButton();
    save_as_f->setDefaultAction(save_file_as);
    save_as_f->setFixedSize(QSize(50, 50));

    close_f = new QToolButton();
    close_f->setDefaultAction(close_file);
    close_f->setFixedSize(QSize(50, 50));

    clear = new QToolButton();
    clear->setDefaultAction(clear_text);
    clear->setFixedSize(QSize(50, 50));

    upper = new QToolButton();
    upper->setDefaultAction(to_upper);
    upper->setFixedSize(QSize(50, 50));

    lower = new QToolButton();
    lower->setDefaultAction(to_lower);
    lower->setFixedSize(QSize(50 ,50));

    enlarge_font = new QToolButton();
    enlarge_font->setDefaultAction(enlarge);
    enlarge_font->setFixedSize(QSize(50, 50));

    reduce_font = new QToolButton();
    reduce_font->setDefaultAction(reduce);
    reduce_font->setFixedSize(QSize(50, 50));

    replace = new QToolButton();
    replace->setDefaultAction(replace_text);
    replace->setFixedSize(QSize(50, 50));

    dock_grid = new QGridLayout();
    dock_grid->addWidget(enlarge_font, 0, 0);
    dock_grid->addWidget(reduce_font, 1, 0);
    dock_grid->addWidget(clear, 2, 0);
    dock_grid->addWidget(upper, 3, 0);
    dock_grid->addWidget(lower, 4, 0);
    dock_grid->addWidget(replace, 5, 0);
    dock_grid->setAlignment(Qt::AlignLeft|Qt::AlignTop);

    dock = new QDockWidget("Edit", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    dock->setFixedSize(QSize(200, 500));

    dock_widget = new QWidget(dock);
    dock_widget->setLayout(dock_grid);
    dock->setWidget(dock_widget);
    this->addDockWidget(Qt::LeftDockWidgetArea, dock);

    dock_layout = new QHBoxLayout();
    dock_layout->addWidget(create_f);
    dock_layout->addWidget(open_f);
    dock_layout->addWidget(save_f);
    dock_layout->addWidget(save_as_f);
    dock_layout->addWidget(close_f);

    dock_file = new QDockWidget("File", this);
    dock_file->setAllowedAreas(Qt::TopDockWidgetArea);
    dock_file->setFixedSize(QSize(300, 90));

    dock_file_widget = new QWidget(dock_file);
    dock_file_widget->setLayout(dock_layout);
    dock_file->setWidget(dock_file_widget);
    this->addDockWidget(Qt::TopDockWidgetArea, dock_file);
    this->setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
}


void MainWindow::enlargeFont()
{
    int text_font = text_edit->fontPointSize();
    text_edit->setFontPointSize(text_font + 2);
    status_bar->showMessage("Enlarged font size");
}


void MainWindow::reduceFont()
{
    int text_font = text_edit->fontPointSize();
    if (text_font > 2)
        text_edit->setFontPointSize(text_font - 2);
        status_bar->showMessage("Reduced font size");
}


void MainWindow::showAboutDialog()
{
    QMessageBox aboutBox;
    aboutBox.setWindowTitle("About the application");
    aboutBox.setText("This app will help you work with text");
    aboutBox.setInformativeText("Version of the application: 1.0");
    aboutBox.exec();
}


void MainWindow::showHelpDialog()
{
    QMessageBox helpBox;
    helpBox.setWindowTitle("About the application");
    helpBox.setText("A quick guide to using this application:\n"
                    "1. Create a new file: `File -> New` or `Ctrl+N`.\n"
                    "2. Open an existing file: `File -> Open` or `Ctrl+O`.\n"
                    "3. Save the file: `File -> Save` or `Ctrl+S`.\n"
                    "4. Save the file with a new name: `File -> Save as`.\n"
                    "5. Close the file: `File -> Close`.\n"
                    "6. Clear text: `Edit -> Clear`.\n"
                    "7. Convert text to uppercase: `Edit -> To upper`.\n"
                    "8. Convert text to lowercase: `Edit -> To lower`.\n"
                    "9. Change font size: `Edit -> Enlarge font` or `Edit -> Reduce font`.\n"
                    "10. Replace text: `Edit -> Replace text`\n"
                    "11. Help and About: `Help -> About` and `Help -> Help`.\n"
                    "12. Tracking unsaved changes: An '*' is added to the file name if there are unsaved changes.\n");
    helpBox.exec();
}


void MainWindow::convertTextToUpper()
{
    QString text = text_edit->toPlainText();
    text = text.toUpper();
    text_edit->setPlainText(text);
    status_bar->showMessage("Converted text to uppercase");
}


void MainWindow::convertTextToLower()
{
    QString text = text_edit->toPlainText();
    text = text.toLower();
    text_edit->setPlainText(text);
    status_bar->showMessage("Converted text to lowercase");
}


void MainWindow::replaceText()
{
    QString current_text = text_edit->toPlainText();
    QString find_text = QInputDialog::getText(this, "Find", "Enter the word/character to find:");

    if (find_text.isEmpty()) return;

    QString replace_text = QInputDialog::getText(this, "Replace", "Enter the word/character to replace with:");
    current_text.replace(find_text, replace_text);
    text_edit->setPlainText(current_text);
    status_bar->showMessage("Replaced from - " + find_text + " to - " + replace_text);
}


void MainWindow::setUnsavedChanges(bool has_unsaved_changes)
{
    unsaved_changes = has_unsaved_changes;
    QString file_name = file_name_label->text();

    if (unsaved_changes && !file_name.endsWith("*"))
        file_name_label->setText(file_name + "*");

    else if (!unsaved_changes && file_name.endsWith("*"))
    {
        file_name.chop(1);
        file_name_label->setText(file_name);
    }
}


void MainWindow::markUnsavedChanges()
{
    setUnsavedChanges(true);
}


void MainWindow::clearText()
{
    text_edit->clear();
    status_bar->showMessage("Cleared textfield");
}


void MainWindow::create()
{
    text_edit->clear();
    text_edit->setReadOnly(false);
    save_file->setEnabled(false);
    file_name_label->setText("new_file.txt");
    status_bar->showMessage("Created new file");
}


void MainWindow::save()
{
    QFile file(current_file_name);

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("Can not open file"));
        return;
    }
    else
    {
        QTextStream output_stream(&file);
        QString txt = text_edit->toPlainText();
        status_bar->showMessage("File saved");
        output_stream << txt;
        output_stream.flush();
        file.close();
        setUnsavedChanges(false);
    }
}


void MainWindow::save_as()
{
    QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), "new_file.txt", tr("Text file (*.txt)"));
    if (!file_name.isEmpty())
    {
        QFileInfo file_info(file_name);
        QString name_of_file = file_info.fileName();

        current_file_name = file_name;
        QFile file(file_name);

        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Can not open file"));
            return;
        }
        else
        {
            QTextStream output_stream(&file);
            QString txt = text_edit->toPlainText();
            file_name_label->setText(name_of_file);
            status_bar->showMessage("Saved file as - " + name_of_file);
            output_stream << txt;
            output_stream.flush();
            file.close();
            save_file->setEnabled(true);
            setUnsavedChanges(false);
        }
    }
}


void MainWindow::open()
{
    text_edit->setReadOnly(false);
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open file"), QString(), tr("Text files (*.txt)"));
    if (!file_name.isEmpty())
    {
        QFileInfo file_info(file_name);
        QString name_of_file = file_info.fileName();

        current_file_name = file_name;
        QFile file(file_name);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Can not open file"));
            return;
        }

        QTextStream input_stream(&file);
        QString txt = input_stream.readAll();
        save_file->setEnabled(true);
        file_name_label->setText(name_of_file);
        status_bar->showMessage("Opened file - " + name_of_file);
        text_edit->setText(txt);
        file.close();
        setUnsavedChanges(false);
    }
}


void MainWindow::close()
{
    if (QMessageBox::question(this, "Exit", "Do you want to exit") == QMessageBox::StandardButton::Yes)
    {
        QCoreApplication::quit();
    }
}

MainWindow::~MainWindow()
{
}


