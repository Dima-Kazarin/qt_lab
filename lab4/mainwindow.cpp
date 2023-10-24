#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(QSize(640, 480));

    label = new QLabel(this);
    label->setGeometry(10, 50, 500, 400);
    pixmap = QPixmap(label->size());
    this->setCentralWidget(label);

    slider = new QSlider();
    slider->setFixedHeight(50);
    slider->setRange(1, 100);
    slider->setValue(1);

    spin_box = new QSpinBox();
    spin_box->setRange(-360, 360);
    spin_box->setValue(0);

    combo_box = new QComboBox();
    combo_box->addItems(colors);
    combo_box->setCurrentIndex(-1);

    brightness_slider = new QSlider(Qt::Horizontal);
    brightness_slider->setRange(-50, 50);
    brightness_slider->setValue(0);
    brightness_slider->setFixedWidth(50);

    double_spin_box = new QDoubleSpinBox();
    double_spin_box->setRange(0.1, 30.0);
    double_spin_box->setSingleStep(0.1);
    double_spin_box->setValue(1.0);

    createActions();
    createTools();
    createMenu();
    createDockWidget();
    addWidgetsToDock();

    save_image->setEnabled(false);

    connect(open_image, &QAction::triggered, this, &MainWindow::openImage);
    connect(save_image, &QAction::triggered, this, &MainWindow::saveImage);
    connect(make_gray, &QAction::triggered, this, &MainWindow::grayscaleImage);
    connect(make_sepia, &QAction::triggered, this, &MainWindow::sepiaImage);
    connect(make_invert, &QAction::triggered, this, &MainWindow::invertImage);
    connect(apply, &QAction::triggered, this, &MainWindow::applyImage);
    connect(tile_action, &QAction::triggered, this, &MainWindow::tileToDock);
    connect(twirl_action, &QAction::triggered, this, &MainWindow::twirlToDock);
    connect(monochrome, &QAction::triggered, this, &MainWindow::monochromeToDock);
    connect(brigthness, &QAction::triggered, this, &MainWindow::brigthnessToDock);
    connect(logarithmic, &QAction::triggered, this, &MainWindow::logarithmicToDock);
    connect(slider, &QSlider::valueChanged, this, &MainWindow::tile);
    connect(spin_box, &QSpinBox::valueChanged, this, &MainWindow::twirl);
    connect(combo_box, &QComboBox::currentIndexChanged, this, &MainWindow::updateMonochromeColor);
    connect(brightness_slider, &QSlider::valueChanged, this, &MainWindow::updateBrightness);
    connect(double_spin_box, &QDoubleSpinBox::valueChanged, this, &MainWindow::updateLogarithmic);
}


void MainWindow::createActions()
{
    open_image = new QAction("&Open");
    save_image = new QAction("&Save");
    make_gray = new QAction("&To gray");
    make_sepia = new QAction("&Sepia");
    make_invert = new QAction("&Invert");
    apply = new QAction("&Apply");
    tile_action = new QAction("&Tile");
    twirl_action = new QAction("&Twirl");
    monochrome = new QAction("&Monochrome");
    brigthness = new QAction("&Brigthness");
    logarithmic = new QAction("&Log");
}


void MainWindow::createTools()
{
    tool_bar = addToolBar("Tools");
    tool_bar->addAction(make_gray);
    tool_bar->addAction(make_sepia);
    tool_bar->addAction(make_invert);
    tool_bar->addAction(apply);
    tool_bar->addAction(tile_action);
    tool_bar->addAction(twirl_action);
    tool_bar->addAction(monochrome);
    tool_bar->addAction(brigthness);
    tool_bar->addAction(logarithmic);
}


void MainWindow::createMenu()
{
    menu_bar = this->menuBar();
    file = menu_bar->addMenu("&File");

    file->addAction(open_image);
    file->addAction(save_image);
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

void MainWindow::addWidgetsToDock()
{
    dock_grid->addWidget(slider, 0, 0);
    dock_grid->addWidget(spin_box, 0, 0);
    dock_grid->addWidget(combo_box, 0, 0);
    dock_grid->addWidget(brightness_slider, 0, 0);
    dock_grid->addWidget(double_spin_box, 0, 0);
    hideWidgets();
}


void MainWindow::hideWidgets()
{
    slider->hide();
    spin_box->hide();
    combo_box->hide();
    brightness_slider->hide();
    double_spin_box->hide();
}


void MainWindow::tileToDock()
{
    hideWidgets();
    slider->show();
}


void MainWindow::twirlToDock()
{
    hideWidgets();
    spin_box->show();
}


void MainWindow::monochromeToDock()
{
    hideWidgets();
    combo_box->show();
}


void MainWindow::brigthnessToDock()
{
    hideWidgets();
    brightness_slider->show();
}


void MainWindow::logarithmicToDock()
{
    hideWidgets();
    double_spin_box->show();
}


void MainWindow::drawImage()
{
    label->setPixmap(pixmap.scaled(label->size()));
}


void MainWindow::grayscaleImage()
{
    imgCopy = image.copy(image.rect());
    int red = 0, green = 0, blue = 0;
    for (int i = 0; i < imgCopy.height(); i++)
    {
        for (int j = 0; j < imgCopy.width(); j++)
        {
            red = imgCopy.pixelColor(j, i).red();
            green = imgCopy.pixelColor(j, i).green();
            blue = imgCopy.pixelColor(j, i).blue();
            int mean = (red + green + blue) / 3;
            imgCopy.setPixel(j, i, qRgb(mean, mean, mean));
        }
    }
    image = imgCopy.copy(imgCopy.rect());
    pixmap = QPixmap::fromImage(image);
    drawImage();
}


void MainWindow::sepiaImage()
{
    imgCopy = image.copy(image.rect());
    int red = 0, green = 0, blue = 0;

    for (int i = 0; i < imgCopy.height(); i++)
    {
        for (int j = 0; j < imgCopy.width(); j++)
        {
            red = imgCopy.pixelColor(j, i).red();
            green = imgCopy.pixelColor(j, i).green();
            blue = imgCopy.pixelColor(j, i).blue();

            int sepiaRed = (int)(0.393 * red + 0.769 * green + 0.189 * blue);
            int sepiaGreen = (int)(0.349 * red + 0.686 * green + 0.168 * blue);
            int sepiaBlue = (int)(0.272 * red + 0.534 * green + 0.131 * blue);

            sepiaRed = std::min(255, std::max(0, sepiaRed));
            sepiaGreen = std::min(255, std::max(0, sepiaGreen));
            sepiaBlue = std::min(255, std::max(0, sepiaBlue));

            imgCopy.setPixel(j, i, qRgb(sepiaRed, sepiaGreen, sepiaBlue));
        }
    }
    image = imgCopy.copy(imgCopy.rect());
    pixmap = QPixmap::fromImage(image);
    drawImage();
}


void MainWindow::invertImage()
{
    imgCopy = image.copy(image.rect());
    int red = 0, green = 0, blue = 0;

    for (int i = 0; i < imgCopy.height(); i++)
    {
        for (int j = 0; j < imgCopy.width(); j++)
        {
            red = imgCopy.pixelColor(j, i).red();
            green = imgCopy.pixelColor(j, i).green();
            blue = imgCopy.pixelColor(j, i).blue();

            int invertedRed = 255 - red;
            int invertedGreen = 255 - green;
            int invertedBlue = 255 - blue;

            imgCopy.setPixel(j, i, qRgb(invertedRed, invertedGreen, invertedBlue));
        }
    }
    image = imgCopy.copy(imgCopy.rect());
    pixmap = QPixmap::fromImage(image);
    drawImage();
}


QRgb MainWindow::averageBlockColor(QImage &imgBLock)
{
    int red = 0, green = 0, blue = 0;
    for (int i = 0; i < imgBLock.height(); i++)
    {
        for (int j = 0; j < imgBLock.width(); j++)
        {
            red += imgBLock.pixelColor(j, i).red();
            green += imgBLock.pixelColor(j, i).green();
            blue += imgBLock.pixelColor(j, i).blue();
        }
    }
    red /= (CELL_SIZE * CELL_SIZE);
    green /= (CELL_SIZE * CELL_SIZE);
    blue /= (CELL_SIZE * CELL_SIZE);
    return qRgb(red, green, blue);
}


void MainWindow::tile()
{
    CELL_SIZE = slider->value();
    image = originalImage;

    for (int i = 0; i < image.height(); i += CELL_SIZE)
    {
        for (int j = 0; j < image.width(); j += CELL_SIZE)
        {
            imgCopy = image.copy(j, i, CELL_SIZE, CELL_SIZE);
            QRgb rgb = averageBlockColor(imgCopy);
            for (int y = i; y < i + CELL_SIZE; y++)
            {
                for (int x = j; x < j + CELL_SIZE; x++)
                {
                    if (x >= 0 && x < image.width() && y >= 0 && y < image.height())
                        image.setPixel(x, y, rgb);
                }
            }
        }
    }
    pixmap = QPixmap::fromImage(image);
    drawImage();
}


void MainWindow::twirl()
{
    maxAngle = spin_box->value();

    imgCopy = image.copy(image.rect());
    float maxDistance = QVector2D(imgCopy.width(), imgCopy.height()).length()/2;
    QVector2D imageCenter(imgCopy.width()/2, imgCopy.height()/2);
    for (int i = 0; i < imgCopy.height(); i++)
    {
        for (int j = 0; j < imgCopy.width(); j++)
        {
            QVector2D currentPos(j, i);
            QVector2D v = currentPos - imageCenter;
            float r = v.length();
            float twirlAngle = r/maxDistance * qDegreesToRadians(maxAngle);
            float angle = atan2(v.y(), v.x());
            QVector2D out(r*cos(angle+twirlAngle)+imageCenter.x(), r*sin(angle+twirlAngle)+imageCenter.y());
            int x = out.x();
            int y = out.y();
            if (x < 0)
                x = 0;
            if (x > imgCopy.width()-1)
                x = imgCopy.width()-1;
            if (y < 0)
                y = 0;
            if (y > imgCopy.height()-1)
                y = imgCopy.height()-1;
            imgCopy.setPixel(j, i, image.pixel(x, y));
        }
    }
    image = imgCopy.copy(imgCopy.rect());
    pixmap = QPixmap::fromImage(image);
    drawImage();
}


void MainWindow::updateMonochromeColor()
{
    int index = combo_box->currentIndex();

    switch (index)
    {
    case 0:
        monochromeColor = Qt::red;
        break;
    case 1:
        monochromeColor = Qt::green;
        break;
    case 2:
        monochromeColor = Qt::blue;
        break;
    default:
        monochromeColor = Qt::black;
        break;
    }

    imgCopy = image.copy(image.rect());
    for (int i = 0; i < imgCopy.height(); i++)
    {
        for (int j = 0; j < imgCopy.width(); j++)
        {
            int grayValue = qGray(imgCopy.pixel(j, i));
            imgCopy.setPixel(j, i, monochromeColor.rgb() | grayValue << 16 | grayValue << 8 | grayValue);
        }
    }
    image = imgCopy.copy(imgCopy.rect());
    pixmap = QPixmap::fromImage(image);
    drawImage();
}


void MainWindow::updateBrightness()
{
    int value = brightness_slider->value();

    imgCopy = image.copy(image.rect());
    for (int i = 0; i < imgCopy.height(); i++)
    {
        for (int j = 0; j < imgCopy.width(); j++)
        {
            QRgb pixel = imgCopy.pixel(j, i);
            int red = qRed(pixel) + value;
            int green = qGreen(pixel) + value;
            int blue = qBlue(pixel) + value;

            red = qMin(qMax(red, 0), 255);
            green = qMin(qMax(green, 0), 255);
            blue = qMin(qMax(blue, 0), 255);

            imgCopy.setPixel(j, i, qRgb(red, green, blue));
        }
    }
    image = imgCopy.copy(imgCopy.rect());
    pixmap = QPixmap::fromImage(image);
    drawImage();
}


void MainWindow::updateLogarithmic()
{
    double c = double_spin_box->value();

    imgCopy = image.copy(image.rect());
    for (int i = 0; i < imgCopy.height(); i++)
    {
        for (int j = 0; j < imgCopy.width(); j++)
        {
            QRgb pixel = imgCopy.pixel(j, i);

            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            red = c * qLn(1 + red);
            green = c * qLn(1 + green);
            blue = c * qLn(1 + blue);

            red = qMin(qMax(red, 0), 255);
            green = qMin(qMax(green, 0), 255);
            blue = qMin(qMax(blue, 0), 255);

            imgCopy.setPixel(j, i, qRgb(red, green, blue));
        }
    }
    image = imgCopy.copy(imgCopy.rect());
    pixmap = QPixmap::fromImage(image);
    drawImage();
}


void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    image.load(fileName);
    originalImage.load(fileName);
    image = originalImage;
    current_file_name = fileName;
    if (image.isNull())
    {
        QMessageBox::warning(this, QGuiApplication::applicationDisplayName(), tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
        return;
    }
    pixmap = QPixmap::fromImage(image);
    drawImage();
}


void MainWindow::applyImage()
{
    save_image->setEnabled(true);
    image = imgCopy;
    pixmap = QPixmap::fromImage(image);
    drawImage();
}


void MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Image file (*.jpg)"));
    current_file_name = fileName;
    if (image.isNull())
    {
        QMessageBox::warning(this, QGuiApplication::applicationDisplayName(), tr("Cannot save %1").arg(QDir::toNativeSeparators(fileName)));
        return;
    }
    else
        image.save(fileName);
}


MainWindow::~MainWindow()
{
}
