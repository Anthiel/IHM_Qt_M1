#include "colorfilter.h"

ColorFilter::ColorFilter(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    _hue_display->setPalette(QPalette(QColor(255,255,255)));
    _filter_color_display->setPalette(QPalette(QColor(255,255,255)));

    connect(_hue, SIGNAL(clicked()), this, SLOT(hue()));
    connect(_filter_color, SIGNAL(clicked()), this, SLOT(filterColor()));
}

void ColorFilter::hue() {openColor(FILTER);}
void ColorFilter::filterColor() {openColor(TO_FILTER);}

void ColorFilter::openColor(int to_open)
{
    QColorDialog colorDialog;
    QColor init_color;
    switch (to_open)
    {
        case TO_FILTER:
            init_color = getFilterColor();
            break;
        case FILTER:
            init_color = getHue();
            break;
        default:
            init_color = QColor(255,255,255);
            break;
    }

    QColor color;
    color = colorDialog.getColor(init_color);
    if( color.isValid() )
    {
        QPalette pal;
        pal.setColor(QPalette::Window, color);
        switch (to_open)
        {
            case TO_FILTER:
                _filter_color_display->setPalette(pal);
                break;
            case FILTER:
                _hue_display->setPalette(pal);
                break;
            default:
                break;
        }
    }

}
