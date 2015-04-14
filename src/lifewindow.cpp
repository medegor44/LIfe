#include "lifewindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

LifeWindow::LifeWindow(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    buttonsLayout = new QHBoxLayout;

    createButtons();
    createGrid();
    createMenu();

    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(view);

    connect(buttonsStep, SIGNAL(clicked()), grid, SLOT(runStep()));
    // нажата кнопка смены поколений

    connect(buttonStopStart, SIGNAL(clicked()), grid, SLOT(stopStartTimer()));
    // запуск/остановка таймера

    connect(buttonRandom, SIGNAL(clicked()), grid, SLOT(random()));
    // запуск случайной генерации поколения

    connect(buttonClear, SIGNAL(clicked()), grid, SLOT(clear()));
    // очистка поля

    connect(grid, SIGNAL(counterChanged(int)), SLOT(counterChanged(int)));
    // изменение счетчика

    setLayout(mainLayout);
}

void LifeWindow::openConfig()
{
    QString file = QFileDialog::getOpenFileName(this, "Выберите конфигурацию",
                                                "File",
                                                "Конфигураци игры(*.life)");

    grid->loadConf(file);
}

void LifeWindow::createButtons() // создание и размещение кнопок на mainLayout
{
    buttonsStep = new QPushButton("Шаг");
    buttonsLayout->addWidget(buttonsStep);

    buttonStopStart = new QPushButton("Старт/Стоп");
    buttonsLayout->addWidget(buttonStopStart);

    buttonRandom = new QPushButton("Случайно");
    buttonsLayout->addWidget(buttonRandom);

    buttonClear = new QPushButton("Очистить");
    buttonsLayout->addWidget(buttonClear);

    label = new QLabel("Текущее поколение: 0");
    buttonsLayout->addWidget(label);

    qDebug() << "Buttons created!";
}

void LifeWindow::createMenu() // создание меню приложения
{
    menuBar = new QMenuBar(this);
    fileMenu = new QMenu("Файл", this);
    menuBar->addMenu(fileMenu);

    loadConfAction = fileMenu->addAction("Открыть", this, SLOT(openConfig()));
    saveAction = fileMenu->addAction("Сохранить", this, SLOT(saveFile()));

    fileMenu->addSeparator();

    exitAction = fileMenu->addAction("Выход", this, SLOT(close()));
    mainLayout->setMenuBar(menuBar);

    qDebug() << "Menu created!";
}

void LifeWindow::saveFile()
{
    qDebug() << "Saving...";
    QString dir = QFileDialog::getSaveFileName(this,
                                               "Сохранить конфигурацию...",
                                               "/home",
                                               "Конфигурация (*.life)");
    int res = grid->saveConf(dir);

    if(!res)
        QMessageBox::information(this, "Ошибка", "Невозможно записать файл");
}

void LifeWindow::createGrid() // создание сетки игры
{
    scene = new QGraphicsScene(QRectF(0, 0, 1000, 600), this);
    grid = new Grid(scene->width(), scene->height(), 10);
    scene->addItem(grid);
    view = new QGraphicsView(scene, this);
    view->setFixedSize(scene->width()+5, scene->height()+5);

    qDebug() << "Grid created!";
}

void LifeWindow::counterChanged(int c)
{
    label->setText("Текущее поколение: " + QString::number(c));
}

LifeWindow::~LifeWindow()
{
    delete grid;
    delete buttonClear;
    delete buttonRandom;
    delete buttonsLayout;
    delete buttonsStep;
    delete buttonStopStart;
    delete mainLayout;
    delete label;

    qDebug() << "Program closed";
}
