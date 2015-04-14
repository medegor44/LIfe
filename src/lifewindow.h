/*
 * GUI игры
 */
#ifndef LIFEWINDOW_H
#define LIFEWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QLabel>
#include <QFileDialog>
#include "grid.h"

class LifeWindow : public QWidget
{
    Q_OBJECT

private:
    QGraphicsView *view; // представление
    QGraphicsScene *scene; // сцена
    Grid *grid; // сетка игры

    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonsLayout;

    QPushButton *buttonStopStart;
    QPushButton *buttonsStep;
    QPushButton *buttonClear;
    QPushButton *buttonRandom;
    QLabel *label;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *exitAction;
    QAction *loadConfAction;
    QAction *saveAction;

    void createButtons();
    void createMenu();
    void createGrid();

private slots:
    void counterChanged(int c);
    void openConfig();
    void saveFile();

public:
    LifeWindow(QWidget *parent = 0);
    ~LifeWindow();
};

#endif // LIFEWINDOW_H
