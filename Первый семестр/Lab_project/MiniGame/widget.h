#ifndef WIDGET_H
#define WIDGET_H

#include <QDebug>

#include <QWidget>
#include <QDateTime>
#include <QMessageBox>

// Начальное количество мин в игре
#define BOMBS_COUNT 20

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    // Карта расположения мин (1 - есть, 0 - чисто)
    char bombs[10][10];

    // Массив, отражающий количество мин вокруг каждой ячейки
    char indicators[10][10];

    // Карта ячеек, открытых в ходе игры
    char opened[10][10];

    // Количество ячеек, открытых в ходе игры
    int cellsOpened;

    void NewGame();
    void AddIndicators(int row, int col);
    void OpenRemained();

private slots:
    void slotCellClicked(int row, int col);
    void slotRightClicked(QPoint pnt);

    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // WIDGET_H
