#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QDialog>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void MoveCell(QPushButton *w, int arr_i, int arr_j);
	QVector <QLabel*> buttons_vec; // создание вектора, хранящего надписи, их мы будем двигать по таблице
	QPushButton ***arr;
	QLabel *emptylabel;
	QDialog dialog;
	int prev_num;
	bool has_won();
	void Generate_Tiles();
	int moves_number; // переменная - счетчик числа ходов
	QLabel *moves_info; // строка, которая будет записывать количество ходов
	QPalette pal;//палитра для того, чтобы окрасить текст в белый цвет
private:
	Ui::MainWindow *ui;
public slots:
	void processButton();
private slots:
	void on_pushButton_clicked();
};

int my_rand(int i);

#endif // MAINWINDOW_H
