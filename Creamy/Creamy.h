#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Creamy.h"

class Creamy : public QMainWindow
{
    Q_OBJECT

public:
    Creamy(QWidget *parent = nullptr);
    ~Creamy();

private:
    Ui::CreamyClass ui;
};
