#include "widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    direct = new QLabel("->", this);
    direct->setGeometry(220, 60, 100, 100);

    change_direction = new QCheckBox("Invert", this);
    change_direction->move(60, 60);

    clear = new QPushButton("Clear", this);
    clear->move(60, 150);

    convert = new QPushButton("Convert", this);
    convert->move(190, 150);

    input = new QLineEdit(this);
    input->setGeometry(60, 100, 50, 20);

    output = new QLineEdit(this);
    output->setGeometry(270, 100, 50, 20);

    choose_input = new QComboBox(this);
    choose_input->move(120, 100);

    choose_output = new QComboBox(this);
    choose_output->move(330, 100);

    resize = new QSpinBox(this);
    resize->move(350, 150);
    resize->setMinimum(2);
    resize->setMaximum(20);
    resize->setSingleStep(2);
    resize->setValue(10);

    current_size = new QProgressBar(this);
    current_size->move(353, 190);
    current_size->setOrientation(Qt::Vertical);
    current_size->setValue(50);

    weight = new QRadioButton("Weight", this);
    length = new QRadioButton("Length", this);
    speed = new QRadioButton("Speed", this);

    group = new QButtonGroup(this);
    group->addButton(weight);
    group->addButton(length);
    group->addButton(speed);

    lout = new QVBoxLayout(this);
    lout->addWidget(weight);
    lout->addWidget(length);
    lout->addWidget(speed);

    container = new QWidget(this);
    container->setLayout(lout);
    container->setGeometry(60, 200, 100, 100);

    connect(clear, SIGNAL(clicked()), this, SLOT(clear_all()));
    connect(group, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(set_combobox_values()));
    length->click();
    connect(convert, SIGNAL(clicked()), this, SLOT(convert_values()));
    connect(change_direction, SIGNAL(clicked()), this, SLOT(change_direct()));
    connect(resize, SIGNAL(valueChanged(int)), this, SLOT(change_size()));
}

void Widget::clear_all()
{
    direct->setText("->");
    input->clear();
    output->clear();
    choose_input->clear();
    choose_output->clear();
    length->click();
    change_direction->setChecked(false);
    resize->setValue(10);
    input->setStyleSheet("font-size: 12px;");
    output->setStyleSheet("font-size: 12px;");
    direct->setStyleSheet("font-size: 12px;");
}

void Widget::change_direct()
{
    input->clear();
    output->clear();

    if (change_direction->isChecked())
        direct->setText("<-");
    else
        direct->setText("->");
}

void Widget::set_combobox_values()
{
    choose_input->clear();
    choose_output->clear();

    QAbstractButton *selectedRadioButton = group->checkedButton();
    if (selectedRadioButton == length)
    {
        choose_input->addItems(length_units.keys());
        choose_output->addItems(length_units.keys());
    }
    else if (selectedRadioButton == weight)
    {
        choose_input->addItems(weight_units.keys());
        choose_output->addItems(weight_units.keys());
    }
    else
    {
        choose_input->addItems(speed_units.keys());
        choose_output->addItems(speed_units.keys());
    }
}

void Widget::convert_values()
{
    QString input_text;
    QString output_text;
    double input_value;
    QLineEdit *op;
    double result = 0;

    if (change_direction->isChecked())
    {
        input_text = choose_output->currentText();
        output_text = choose_input->currentText();
        input_value = output->text().toDouble();
        op = input;
    }
    else
    {
        input_text = choose_input->currentText();
        output_text = choose_output->currentText();
        input_value = input->text().toDouble();
        op = output;
    }

    if (length->isChecked())
        result = input_value * (length_units[input_text] / length_units[output_text]);
    else if (weight->isChecked())
        result = input_value * (weight_units[input_text] / weight_units[output_text]);
    else if (speed->isChecked())
        result = input_value * (speed_units[input_text] / speed_units[output_text]);

    op->setText(QString::number(result));
}

void Widget::change_size()
{
    int size = resize->text().toInt();
    current_size->setValue(size * 5);

    input->setStyleSheet("font-size:" + QString::number(size + 2) + "px;");
    output->setStyleSheet("font-size:" + QString::number(size + 2) + "px;");
    direct->setStyleSheet("font-size:" + QString::number(size + 2) + "px;");

    if (size < 10)
    {
        input->setGeometry(60, 100, size * 5, 20 - size * 0.2);
        output->setGeometry(270, 100, size * 5, 20 - size * 0.2);
    }
    else if (size == 10)
    {
        input->setGeometry(60, 100, 50, 20);
        output->setGeometry(270, 100, 50, 20);
        choose_input->move(120, 100);
        choose_output->move(330, 100);
    }
    else
    {
        input->setGeometry(60, 100, size * 5, 20 + size * 0.2);
        output->setGeometry(270, 100, size * 5, 20 + size * 0.2);
        choose_input->move(120 + size * 2, 100);
        choose_output->move(330 + size * 2, 100);
    }
}

Widget::~Widget()
{
}


