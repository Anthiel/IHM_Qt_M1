#ifndef COLORFILTER_H
#define COLORFILTER_H

#include "ui_colorfilter.h"
#include <QColorDialog>

const uint TO_FILTER=1;
const uint FILTER=2;

class ColorFilter : public QDialog, private Ui::ColorFilter
{
    Q_OBJECT

public:
    explicit ColorFilter(QWidget *parent = nullptr);

    inline int getThreshold() const {return _filter_thr->value();}
    inline QColor getFilterColor() const {return _filter_color_display->palette().color(QWidget::backgroundRole());}
    inline QColor getHue() const {return _hue_display->palette().color(QWidget::backgroundRole());}

private:
    void openColor(int to_open);

private slots:
    void hue();
    void filterColor();
};

#endif // COLORFILTER_H
