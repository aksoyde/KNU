#include "widget.h"
#include "ui_widget.h"

/**
 * @brief Widget::Widget
 * @param parent
 *
 * Конструктор главного окна.
 * Соединяет сигналы и слоты виджетов для обработки действий во время игры
 */
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, SIGNAL(cellClicked(int,int)), SLOT(slotCellClicked(int,int)));
    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), SLOT(slotRightClicked(QPoint)));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode (QHeaderView::Fixed);
    ui->tableWidget->verticalHeader()->setSectionResizeMode (QHeaderView::Fixed);

    NewGame();
}

Widget::~Widget()
{
    delete ui;
}

/**
 * @brief Widget::AddIndicators
 * @param row
 * @param col
 *
 * Пересчитывает значения индикаторов мин в ячейках.
 * Вызывается при формировании поля перед началом игры
 */
void Widget::AddIndicators(int row, int col)
{
    if (row > 0)
        ++indicators[row - 1][col];

    if (row < 9)
        ++indicators[row + 1][col];

    if (col > 0)
        ++indicators[row][col - 1];

    if (col < 9)
        ++indicators[row][col + 1];

    if (row > 0 && col > 0)
        ++indicators[row - 1][col - 1];

    if (row < 9 && col < 9)
        ++indicators[row + 1][col + 1];

    if (row > 0 && col < 9)
        ++indicators[row - 1][col + 1];

    if (row < 9 && col > 0)
        ++indicators[row + 1][col - 1];
}

/**
 * @brief Widget::OpenRemained
 *
 * Окрывает оставшееся поле в случае поражения
 */
void Widget::OpenRemained()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (!opened[i][j])
            {
                if (!bombs[i][j])
                {
                    ui->tableWidget->item(i, j)->setText(QString::number(indicators[i][j]));

                    if (indicators[i][j] == 0)
                        ui->tableWidget->item(i, j)->setBackgroundColor(QColor::fromRgb(0, 240, 0));

                    if (indicators[i][j] > 0 && indicators[i][j] < 5)
                        ui->tableWidget->item(i, j)->setBackgroundColor(QColor::fromRgb(240, 240, 0));

                    if (indicators[i][j] >= 5)
                        ui->tableWidget->item(i, j)->setBackgroundColor(QColor::fromRgb(240, 0, 0));
                }
                else
                {
                    ui->tableWidget->item(i, j)->setText("*");

                    QFont font = ui->tableWidget->item(i, j)->font();
                    font.setPointSize(28);
                    ui->tableWidget->item(i, j)->setFont(font);
                }
            }
}

/**
 * @brief Widget::NewGame
 *
 * Начинает новую игру.
 * Формирует минное поле 10х10, располагая BOMBS_COUNT мин случайным образом.
 * BOMBS_COUNT задан в widget.h
 */
void Widget::NewGame()
{
    // Чистим поле
    ui->tableWidget->clear();

    cellsOpened = 0;

    /* Обнуляем значения массивов,
     * закрываем все ячейки (красим в серый цвет),
     * настраиваем шрифты в ячейках */
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
        {
            bombs[i][j] = 0;
            indicators[i][j] = 0;
            opened[i][j] = 0;
            QTableWidgetItem* newItem =new QTableWidgetItem;
            newItem->setBackgroundColor(QColor::fromRgb(240, 240, 240));
            newItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            QFont font = newItem->font();
            font.setBold(true);
            font.setPointSize(16);
            newItem->setFont(font);
            ui->tableWidget->setItem(i, j, newItem);
        }

    srand(QDateTime::currentDateTime().toTime_t());

    /* Генерируем случайные координаты новых мин,
     * и отмечаем их расположение на карте (массив bombs) */
    for (int i = 0; i < BOMBS_COUNT; i++)
    {
        int row, col;

        do
        {
            row = rand() % 10;
            col = rand() % 10;
        }
        while (bombs[row][col]);

        //qDebug() << row << col;

        bombs[row][col] = 1;
        AddIndicators(row, col);
    }
}

/**
 * @brief Widget::slotCellClicked
 * @param row
 * @param col
 *
 * Обрабатывает нажатие на ячейку поля левой кнопкой мыши
 */
void Widget::slotCellClicked(int row, int col)
{
    //qDebug() << row << col;

    // Если ячейка уже открыта, выходим
    if (opened[row][col])
        return;

    // Если ячейка помечена как подозрительная, не открываем
    if (ui->tableWidget->item(row, col)->text().compare("!") == 0)
        return;

    // Отмечаем ячейку открытой и увеличиваем счётчик
    opened[row][col] = 1;
    ++cellsOpened;

    /* Если в открытой ячейке мина,
     * выводим сообщение о поражении и начинаем игру заново */
    if (bombs[row][col])
    {
        ui->tableWidget->item(row, col)->setText("*");

        QFont font = ui->tableWidget->item(row, col)->font();
        font.setPointSize(28);
        ui->tableWidget->item(row, col)->setFont(font);

        OpenRemained();
        QMessageBox msg(QMessageBox::Information, "Сапёр", "Поражение!", QMessageBox::Ok);
        msg.exec();
        NewGame();
        return;
    }
    /* Если открытая ячейка чиста,
     * открываем её, выводим в ней количество мин, находящихся поблизости (индикатор),
     * и окрашиваем её в цвет в зависимости от значения индикатора */
    else
    {
        ui->tableWidget->item(row, col)->setText(QString::number(indicators[row][col]));

        if (indicators[row][col] == 0)
            ui->tableWidget->item(row, col)->setBackgroundColor(QColor::fromRgb(0, 240, 0));

        if (indicators[row][col] > 0 && indicators[row][col] < 5)
            ui->tableWidget->item(row, col)->setBackgroundColor(QColor::fromRgb(240, 240, 0));

        if (indicators[row][col] >= 5)
            ui->tableWidget->item(row, col)->setBackgroundColor(QColor::fromRgb(240, 0, 0));
    }

    /* Условие победы:
     * открыто 100 - BOMBS_COUNT чистых ячеек, ячейки с минами закрыты.
     * В этом случае выводим сообщение и начинаем игру заново */
    if (cellsOpened >= 100 - BOMBS_COUNT)
    {
        QMessageBox msg(QMessageBox::Information, "Сапёр", "Победа!", QMessageBox::Ok);
        msg.exec();
        NewGame();
    }
}

/**
 * @brief Widget::slotRightClicked
 * @param pnt
 *
 * Обрабатывает нажатие на ячейку поля правой кнопкой мыши
 */
void Widget::slotRightClicked(QPoint pnt)
{
    QTableWidgetItem* cur = ui->tableWidget->itemAt(pnt);

    // Проверка того, что кнопка нажата на одной из ячеек
    if (!cur)
        return;

    // Если ячейка уже открыта, выходим
    if (opened[cur->row()][cur->column()])
        return;

    /* Если ячейка помечена как подозрительная,
     * снимаем эту отметку, и наоборот,
     * если не помечена, помечаем */
    if (cur->text().compare("!") == 0)
        cur->setText("");
    else
        cur->setText("!");

    //qDebug() << cur->row() << cur->column();
}

void Widget::on_pushButton_2_clicked()
{
    QApplication::quit();
}

void Widget::on_pushButton_clicked()
{
    NewGame();
}
