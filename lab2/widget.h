#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QProgressBar>
#include <QButtonGroup>
#include <QVBoxLayout>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void clear_all();
    void set_combobox_values();
    void convert_values();
    void change_direct();
    void change_size();

private:
    QLabel *direct;
    QCheckBox *change_direction;
    QPushButton *clear;
    QPushButton *convert;
    QLineEdit *input;
    QLineEdit *output;
    QComboBox *choose_input;
    QComboBox *choose_output;
    QRadioButton *weight;
    QRadioButton *length;
    QRadioButton *speed;
    QSpinBox *resize;
    QProgressBar *current_size;
    QButtonGroup *group;
    QVBoxLayout *lout;
    QWidget *container;

    QMap<QString, double> length_units = {{"mm", 0.001}, {"cm", 0.01}, {"m", 1}, {"ft", 0.3048}, {"inch", 0.0254}, {"km", 1000}};
    QMap<QString, double> weight_units = {{"g", 0.001}, {"oz", 0.0283495}, {"lb", 0.453592}, {"kg", 1}, {"t", 1000}};
    QMap<QString, double> speed_units = {{"m/s", 1}, {"mph", 0.44704}, {"fps", 0.3048}, {"kph", 0.277778}};
};

#endif // WIDGET_H
