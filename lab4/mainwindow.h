#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>
#include <QGuiApplication>
#include <QDir>
#include <QRgb>
#include <QVector2D>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QGridLayout>
#include <QDockWidget>
#include <QSlider>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void grayscaleImage();
    void sepiaImage();
    void invertImage();
    void saveImage();
    void openImage();
    void applyImage();
    void tileToDock();
    void twirlToDock();
    void monochromeToDock();
    void brigthnessToDock();
    void logarithmicToDock();
    void tile();
    void twirl();
    void updateMonochromeColor();
    void updateBrightness();
    void updateLogarithmic();

private:
    void createActions();
    void createTools();
    void createMenu();
    void createDockWidget();
    void drawImage();
    void addWidgetsToDock();
    void changeWidget();
    void hideWidgets();
    QRgb averageBlockColor(QImage &imgBLock);

    QLabel *label;
    QPixmap pixmap;
    QImage image, imgCopy;
    int CELL_SIZE = 50;
    int maxAngle = 1;
    QString current_file_name;
    QColor monochromeColor;

    QToolBar *tool_bar;
    QMenuBar *menu_bar;
    QMenu *file;
    QAction *open_image, *save_image, *make_gray, *make_sepia, *make_invert, *apply, *tile_action,
        *twirl_action, *monochrome, *brigthness, *logarithmic;
    QGridLayout *dock_grid;
    QDockWidget *dock;
    QWidget *dock_widget;
    QSlider *slider, *brightness_slider;
    QSpinBox *spin_box;
    QImage originalImage;
    QComboBox *combo_box;
    QDoubleSpinBox *double_spin_box;

    QStringList colors = {"Red", "Green", "Blue"};
};

#endif // MAINWINDOW_H
