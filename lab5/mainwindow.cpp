#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setGeometry(100, 100, 800, 600);
    label = new QLabel(this);
    label->setGeometry(labelX, labelY, labelW, labelH);

    pixmap = QPixmap(label->size());
    pixmap.fill(QColor("white"));

    painter = new QPainter(&pixmap);
    QPen pen = QPen(Qt::red);
    painter->setPen(pen);
    label->setPixmap(pixmap.scaled(label->size()));


    previewLabel = new QLabel();
    previewLabel->setFixedSize(110, 110);
    previewLabel->setFrameShape(QFrame::Box);

    previewPixmap = QPixmap(previewLabel->size());
    previewPixmap.fill(QColor("white"));

    previewPainter = new QPainter(&previewPixmap);
    QPen previewPen = QPen(Qt::red);
    previewPainter->setPen(previewPen);
    previewLabel->setPixmap(previewPixmap.scaled(previewLabel->size()));

    infoLabel = new QLabel();

    layout = new QVBoxLayout();
    layout->addWidget(previewLabel);
    layout->addWidget(infoLabel);

    open = new QPushButton("Open");
    save = new QPushButton("Save");
    brush1 = new QPushButton("Brush 1");
    brush2 = new QPushButton("Brush 2");
    brush3 = new QPushButton("Brush 3");
    brush4 = new QPushButton("Brush 4");
    brush5 = new QPushButton("Brush 5");

    createWidgets();
    createTools();
    createDockWidget();
    addWidgetsToDock();

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openImage);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveImage);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::close);
    connect(brush1, &QPushButton::clicked, this, &MainWindow::setBrush);
    connect(brush2, &QPushButton::clicked, this, &MainWindow::setBrush);
    connect(brush3, &QPushButton::clicked, this, &MainWindow::setBrush);
    connect(brush4, &QPushButton::clicked, this, &MainWindow::setBrush);
    connect(brush5, &QPushButton::clicked, this, &MainWindow::setBrush);
    connect(colorPicker, &QComboBox::currentIndexChanged, this, &MainWindow::setColor);
    connect(stylePicker, &QComboBox::currentIndexChanged, this, &MainWindow::setLineStyle);
    connect(contourColorPicker, &QComboBox::currentIndexChanged, this, &MainWindow::setContourColor);
    connect(lineThicknessSlider, &QSlider::valueChanged, this, &MainWindow::setLineTickhness);
    connect(diameter_slider, &QSlider::valueChanged, this, &MainWindow::setDiameter);
    connect(subColor1, &QComboBox::currentIndexChanged, this, &MainWindow::setSubColor1);
    connect(subColor2, &QComboBox::currentIndexChanged, this, &MainWindow::setSubColor2);
    connect(subColor3, &QComboBox::currentIndexChanged, this, &MainWindow::setSubColor3);
}


void MainWindow::createWidgets()
{
    colorPicker = new QComboBox();
    colorPicker->addItem("Red", QColor(Qt::red));
    colorPicker->addItem("Blue", QColor(Qt::blue));
    colorPicker->addItem("Green", QColor(Qt::green));
    colorPicker->addItem("Black", QColor(Qt::black));
    colorPicker->setCurrentIndex(-1);

    stylePicker = new QComboBox();
    stylePicker->addItem("Solid", (int)Qt::SolidLine);
    stylePicker->addItem("Dashed", (int)Qt::DashLine);
    stylePicker->addItem("Dotted", (int)Qt::DotLine);
    stylePicker->addItem("Dash-Dotted", (int)Qt::DashDotLine);

    contourColorPicker = new QComboBox();
    contourColorPicker->addItem("Red", QColor(Qt::red));
    contourColorPicker->addItem("Blue", QColor(Qt::blue));
    contourColorPicker->addItem("Green", QColor(Qt::green));
    contourColorPicker->addItem("Black", QColor(Qt::black));
    contourColorPicker->setCurrentIndex(-1);

    lineThicknessSlider = new QSlider(Qt::Horizontal);
    lineThicknessSlider->setRange(1, 20);
    lineThicknessSlider->setValue(1);

    diameter_slider = new QSlider(Qt::Horizontal);
    diameter_slider->setRange(1, 100);
    diameter_slider->setValue(1);

    subColor1  = new QComboBox();
    subColor1->addItem("Red", QColor(Qt::red));
    subColor1->addItem("Blue", QColor(Qt::blue));
    subColor1->addItem("Green", QColor(Qt::green));
    subColor1->addItem("Black", QColor(Qt::black));
    subColor1->setCurrentIndex(-1);

    subColor2  = new QComboBox();
    subColor2->addItem("Red", QColor(Qt::red));
    subColor2->addItem("Blue", QColor(Qt::blue));
    subColor2->addItem("Green", QColor(Qt::green));
    subColor2->addItem("Black", QColor(Qt::black));
    subColor2->setCurrentIndex(-1);

    subColor3  = new QComboBox();
    subColor3->addItem("Red", QColor(Qt::red));
    subColor3->addItem("Blue", QColor(Qt::blue));
    subColor3->addItem("Green", QColor(Qt::green));
    subColor3->addItem("Black", QColor(Qt::black));
    subColor3->setCurrentIndex(-1);
}


void MainWindow::createTools()
{
    tool_bar = addToolBar("Tools");
    tool_bar->addWidget(brush1);
    tool_bar->addWidget(brush2);
    tool_bar->addWidget(brush3);
    tool_bar->addWidget(brush4);
    tool_bar->addWidget(brush5);
}


void MainWindow::createDockWidget()
{
    dock_grid = new QGridLayout();
    dock_grid->setAlignment(Qt::AlignRight | Qt::AlignTop);

    dock = new QDockWidget("Edit", this);
    dock->setAllowedAreas(Qt::RightDockWidgetArea);
    dock->setFixedSize(QSize(200, 500));

    dock_widget = new QWidget(dock);
    dock_widget->setLayout(dock_grid);
    dock->setWidget(dock_widget);
    this->addDockWidget(Qt::RightDockWidgetArea, dock);
}


void MainWindow::hideWidgets()
{
    stylePicker->hide();
    contourColorPicker->hide();
    diameter_slider->hide();
    subColor1->hide();
    subColor2->hide();
    subColor3->hide();
}


void MainWindow::showWidgets()
{
    hideWidgets();

    if (brushIndex != ANIMAL and brushIndex != AEROGRAPH)
    {
        stylePicker->show();
        contourColorPicker->show();
        diameter_slider->show();
    }
    else if (brushIndex == AEROGRAPH)
        diameter_slider->show();
    else
    {
        subColor1->show();
        subColor2->show();
        subColor3->show();
    }
}


void MainWindow::addWidgetsToDock()
{
    dock_grid->addLayout(layout, 0, 0);
    dock_grid->addWidget(colorPicker, 1, 0);
    dock_grid->addWidget(lineThicknessSlider, 2, 0);
    dock_grid->addWidget(stylePicker, 3, 0);
    dock_grid->addWidget(contourColorPicker, 4, 0);
    dock_grid->addWidget(diameter_slider, 5, 0);

    dock_grid->addWidget(subColor1, 3, 0);
    dock_grid->addWidget(subColor2, 4, 0);
    dock_grid->addWidget(subColor3, 5, 0);
    hideWidgets();
}


void MainWindow::setColor(int index)
{
    QColor selectedColor = colorPicker->itemData(index).value<QColor>();
    currentColor = selectedColor;
    QPen pen(currentColor);
    painter->setPen(pen);

    updatePreviewLabel();
}


void MainWindow::setLineTickhness(int thickness)
{
    lineThickness = thickness;

    updatePreviewLabel();
}


void MainWindow::setLineStyle(int index)
{
    int selectedStyleInt = stylePicker->itemData(index).value<int>();
    lineStyle = Qt::PenStyle(selectedStyleInt);

    updatePreviewLabel();
}


void MainWindow::setContourColor(int index)
{
    QColor selectedColor = contourColorPicker->itemData(index).value<QColor>();
    currentContourColor = selectedColor;

    updatePreviewLabel();
}


void MainWindow::setDiameter(int diameter)
{
    circle_diameter = diameter;

    updatePreviewLabel();
}


void MainWindow::setSubColor1(int index)
{
    QColor selectedColor = subColor1->itemData(index).value<QColor>();
    color_1 = selectedColor;

    updatePreviewLabel();
}

void MainWindow::setSubColor2(int index)
{
    QColor selectedColor = subColor2->itemData(index).value<QColor>();
    color_2 = selectedColor;

    updatePreviewLabel();
}

void MainWindow::setSubColor3(int index)
{
    QColor selectedColor = subColor3->itemData(index).value<QColor>();
    color_3 = selectedColor;

    updatePreviewLabel();
}


void MainWindow::drawAnimalOnPreview()
{
    QPainterPath path;

    QPainterPath firstpath;

    firstpath.moveTo(100, 75);
    firstpath.lineTo(100, 100);
    firstpath.lineTo(125, 100);

    firstpath.moveTo(100, 75);
    firstpath.arcTo(75, 75, 50, 50, 90, -90);

    firstpath.moveTo(100, 75);
    firstpath.lineTo(100, 60);
    firstpath.lineTo(85, 60);

    firstpath.moveTo(100, 75);
    firstpath.arcTo(85, 45, 30, 30, 270, -90);

    firstpath.moveTo(125, 80);
    firstpath.lineTo(125, 50);
    firstpath.arcTo(110, 47.5, 30, 30, 90, 180);
    firstpath.translate(-55, -20);
    path.addPath(firstpath);


    QPainterPath secondpath;
    secondpath.moveTo(100, 60);
    secondpath.lineTo(100, 55);
    secondpath.lineTo(105, 55);
    secondpath.arcTo(95, 50, 10, 10, 0, -90);

    secondpath.moveTo(125, 100);
    secondpath.lineTo(125, 80);
    secondpath.arcTo(115, 77.5, 20, 22.5, 90, -180);
    secondpath.translate(-55, -20);
    path.addPath(secondpath);


    QPainterPath thirdpath;
    thirdpath.moveTo(100, 100);
    thirdpath.lineTo(90, 100);
    thirdpath.arcTo(90, 95, 10, 10, 0, 180);
    thirdpath.moveTo(97.5, 65);
    thirdpath.arcTo(92.5, 62.5, 5, 5, 0, 360);
    thirdpath.translate(-55, -20);
    path.addPath(thirdpath);


    QPen previewPen;
    previewPen.setWidth(1);
    previewPainter->setPen(previewPen);

    previewPainter->fillPath(firstpath, color_1);
    previewPainter->fillPath(secondpath, color_2);
    previewPainter->fillPath(thirdpath, color_3);

    previewPainter->setBrush(Qt::NoBrush);

    previewPainter->drawPath(path);
}


void MainWindow::updatePreviewLabel()
{
    previewPixmap.fill(QColor("white"));
    int radius = circle_diameter / 2;

    if (brushIndex == CURVE)
    {
        QPen previewPen(currentColor);
        previewPen.setWidth(lineThickness);
        previewPainter->setPen(previewPen);
        previewPainter->drawLine(20, 50, 80, 50);
        previewLabel->setPixmap(previewPixmap.scaled(previewLabel->size()));

        infoLabel->clear();
    }
    else if (brushIndex == CIRCLE)
    {
        QPen previewPen(currentContourColor);
        previewPen.setWidth(1);
        previewPen.setStyle(lineStyle);
        previewPainter->setPen(previewPen);
        previewPainter->setBrush(QBrush(currentColor));
        previewPainter->drawEllipse(QPoint(55, 55), radius, radius);
        previewLabel->setPixmap(previewPixmap.scaled(previewLabel->size()));

        infoLabel->setText("Radius - " + QString::number(radius));
    }
    else if (brushIndex == POLYGON)
    {
        QPen previewPen(currentContourColor);
        previewPen.setWidth(1);
        previewPen.setStyle(lineStyle);
        previewPainter->setPen(previewPen);
        previewPainter->setBrush(QBrush(currentColor));
        drawPentagonPoints(50, 50, radius, 0);
        previewPainter->drawPolygon(pentagonPoints);
        previewLabel->setPixmap(previewPixmap.scaled(previewLabel->size()));

        infoLabel->setText("Radius - " + QString::number(radius));
    }
    else if (brushIndex == ANIMAL)
    {
        drawAnimalOnPreview();
        previewLabel->setPixmap(previewPixmap.scaled(previewLabel->size()));
    }
    else if (brushIndex == AEROGRAPH)
    {
        drawAerograph(previewPainter, 50, 50);
        previewLabel->setPixmap(previewPixmap.scaled(previewLabel->size()));

        infoLabel->clear();
    }
}


void MainWindow::drawCurve()
{
    QPen pen(currentColor);
    pen.setWidth(lineThickness);
    painter->setPen(pen);
    painter->drawLine(prevX, prevY, x, y);
}

void MainWindow::drawCircle()
{
    QPen pen(currentContourColor);
    pen.setWidth(1);
    pen.setStyle(lineStyle);
    painter->setPen(pen);
    painter->setBrush(QBrush(currentColor));
    painter->drawEllipse(QPoint(x, y), circle_diameter / 2, circle_diameter / 2);
}


void MainWindow::drawPentagonPoints(int centerX, int centerY, int radius, int orientation)
{
    pentagonPoints.clear();
    double angle = 360.0 / 5.0;
    for (int i = 0; i < 5; i++)
    {
        double x = centerX + radius * qCos(qDegreesToRadians(i * angle + orientation));
        double y = centerY + radius * qSin(qDegreesToRadians(i * angle + orientation));
        pentagonPoints.append(QPoint(x, y));
    }
}


void MainWindow::drawPolygon()
{
    QPen pen(currentContourColor);
    pen.setWidth(1);
    pen.setStyle(lineStyle);
    painter->setPen(pen);
    painter->setBrush(QBrush(currentColor));
    drawPentagonPoints(x, y, circle_diameter / 2, 0);
    painter->drawPolygon(pentagonPoints);
}

void MainWindow::drawAnimal()
{
    QPainterPath path;

    QPainterPath firstpath;

    firstpath.moveTo(200, 150);
    firstpath.lineTo(200, 200);
    firstpath.lineTo(250, 200);

    firstpath.moveTo(200, 150);
    firstpath.arcTo(150, 150, 100, 100, 90, -90);

    firstpath.moveTo(200, 150);
    firstpath.lineTo(200, 120);
    firstpath.lineTo(170, 120);

    firstpath.moveTo(200, 150);
    firstpath.arcTo(170, 90, 60, 60, 270, -90);

    firstpath.moveTo(250, 160);
    firstpath.lineTo(250, 100);
    firstpath.arcTo(220, 95, 60, 60, 90, 180);
    path.addPath(firstpath);


    QPainterPath secondpath;
    secondpath.moveTo(200, 120);
    secondpath.lineTo(200, 110);
    secondpath.lineTo(210, 110);
    secondpath.arcTo(190, 100, 20, 20, 0, -90);

    secondpath.moveTo(250, 200);
    secondpath.lineTo(250, 160);
    secondpath.arcTo(230, 155, 40, 45, 90, -180);
    path.addPath(secondpath);


    QPainterPath thirdpath;
    thirdpath.moveTo(200, 200);
    thirdpath.lineTo(180, 200);
    thirdpath.arcTo(180, 190, 20, 20, 0, 180);
    thirdpath.moveTo(195, 130);
    thirdpath.arcTo(185, 125, 10, 10, 0, 360);
    path.addPath(thirdpath);

    QPen pen;
    pen.setWidth(1);
    painter->setPen(pen);

    painter->fillPath(firstpath, color_1);
    painter->fillPath(secondpath, color_2);
    painter->fillPath(thirdpath, color_3);

    painter->setBrush(Qt::NoBrush);

    painter->drawPath(path);
}


void MainWindow::drawAerograph(QPainter *painter, int x, int y)
{
    int radius = circle_diameter / 2;

    QColor airbrushColor = currentColor;
    int centerX = x;
    int centerY = y;

    int numPoints = rand() % 901 + 100;

    for (int i = 0; i < numPoints; i++)
    {
        int randX = rand() % (2 * radius) - radius;
        int randY = rand() % (2 * radius) - radius;

        double distance = qSqrt(qPow(randX, 2) + qPow(randY, 2));
        if (distance <= radius)
        {
            QPoint point(centerX + randX, centerY + randY);
            painter->setPen(QPen(airbrushColor));
            painter->drawPoint(point);
        }
    }

}


void MainWindow::draw()
{
    if (lineThickness < 1)
        lineThickness = 1;
    if (lineThickness > 20)
        lineThickness = 20;

    switch (brushIndex)
    {
    case CURVE:
        drawCurve();
        break;
    case CIRCLE:
        drawCircle();
        break;
    case POLYGON:
        drawPolygon();
        break;
    case ANIMAL:
        drawAnimal();
        break;
    case AEROGRAPH:
        drawAerograph(painter, x, y);
        break;
    default:
        break;
    }
    label->setPixmap(pixmap.scaled(label->size()));
}


void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    pixmap.load(fileName);
    if (pixmap.isNull())
    {
        QMessageBox::warning(this, QGuiApplication::applicationDisplayName(), tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
        return;
    }
    label->setPixmap(pixmap.scaled(label->size()));
}


void MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Image file (*.jpg)"));
    if (pixmap.isNull())
    {
        QMessageBox::warning(this, QGuiApplication::applicationDisplayName(), tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
        return;
    }
    else
        pixmap.save(fileName);
}



void MainWindow::setBrush()
{
    QPushButton *buttonSender = qobject_cast<QPushButton*>(sender());
    if (buttonSender == this->brush1)
    {
        brushIndex = CURVE;
        hideWidgets();
    }
    else if (buttonSender == this->brush2)
    {
        brushIndex = CIRCLE;
        showWidgets();
    }
    else if (buttonSender == this->brush3)
    {
        brushIndex = POLYGON;
        showWidgets();
    }
    else if (buttonSender == this->brush4)
    {
        brushIndex = ANIMAL;
        showWidgets();
    }
    else if (buttonSender == this->brush5)
    {
        brushIndex = AEROGRAPH;
        showWidgets();
    }
    updatePreviewLabel();
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    x = event->pos().x() - labelX;
    y = event->pos().y() - labelY;
    if (brushIndex == CIRCLE or brushIndex == POLYGON or brushIndex == ANIMAL or brushIndex == AEROGRAPH)
        draw();

    prevX = x;
    prevY = y;
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    x = event->pos().x() - labelX;
    y = event->pos().y() - labelY;
    if (brushIndex > -1)
        draw();

    prevX = x;
    prevY = y;
}


void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Escape)
        brushIndex = -1;
}


MainWindow::~MainWindow()
{
    delete ui;
}


