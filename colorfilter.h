#ifndef COLORFILTER_H
#define COLORFILTER_H

#include "ui_colorfilter.h"

class ColorFilter : public QDialog, private Ui::ColorFilter
{
    Q_OBJECT

public:
    explicit ColorFilter(QWidget *parent = nullptr);

    inline int getThreshold() const {return _filter_thr->value();}
    inline int getFilterColor() const {return _filter_color->value();}
    inline int getHue() const {return _hue->value();}
};

#endif // COLORFILTER_H
