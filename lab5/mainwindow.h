#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QToolBar>
#include <QGridLayout>
#include <QSlider>
#include <QDockWidget>
#include <QComboBox>
#include <QPolygon>
#include <QPainterPath>
#include <QGroupBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QLabel *label, *previewLabel, *infoLabel;
    QPixmap pixmap, previewPixmap;
    QPainter *painter, *previewPainter;

    QPushButton *open, *save, *brush1, *brush2, *brush3, *brush4, *brush5;

    int x = -1, y = -1;
    int prevX = -1, prevY = -1;
    int labelX = 100, labelY = 100, labelW = 500, labelH = 400;

    enum brushes{CURVE, CIRCLE, POLYGON, ANIMAL, AEROGRAPH};
    int brushIndex = -1;

    void draw();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openImage();
    void saveImage();
    void setBrush();
    void setColor(int index);
    void setLineTickhness(int thickness);
    void setLineStyle(int index);
    void setContourColor(int index);
    void setDiameter(int index);
    void setSubColor1(int index);
    void setSubColor2(int index);
    void setSubColor3(int index);
    void updatePreviewLabel();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    QToolBar *tool_bar;
    QGridLayout *dock_grid;
    QDockWidget *dock;
    QWidget *dock_widget;
    QPolygon pentagonPoints;

    QComboBox *colorPicker, *stylePicker, *contourColorPicker, *subColor1, *subColor2, *subColor3;
    QSlider *lineThicknessSlider, *diameter_slider;
    QColor currentColor, currentContourColor, color_1, color_2, color_3;
    Qt::PenStyle lineStyle = Qt::SolidLine;
    int lineThickness = 1, circle_diameter = 10;

    QVBoxLayout *layout;
    QGroupBox *groupBox;

    void createTools();
    void createWidgets();
    void createDockWidget();
    void addWidgetsToDock();
    void hideWidgets();
    void showWidgets();
    void drawCurve();
    void drawCircle();
    void drawPolygon();
    void drawAnimal();
    void drawAnimalOnPreview();
    void drawPentagonPoints(int centerX, int centerY, int radius, int orientation);
    void drawAerograph(QPainter *painter, int x, int y);
};
#endif // MAINWINDOW_H
