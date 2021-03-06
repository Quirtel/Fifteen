#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QElapsedTimer>
#include <QSettings>

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
	void timerEvent(QTimerEvent *);

	QVector <QLabel*> buttons_vec; // создание вектора, хранящего надписи, их мы будем двигать по таблице

	void resizeEvent(QResizeEvent *event);

private:
	Ui::MainWindow *ui;
	QPushButton ***arr;
	QLabel *emptylabel;
	QDialog dialog;
	int prev_num;
	bool has_won();
	int moves_number; // переменная - счетчик числа ходов
	QLabel *moves_info; // строка, которая будет записывать количество ходов
	QLabel *time_label; // строка, которая будет вести счет
	QPalette pal;//палитра для того, чтобы окрасить текст в белый цвет
	bool timer_started;
	QElapsedTimer *timer; //таймер
	QDateTime mStartTime; // время начала игры
	QString all_time;
	bool can_move; // может ли игрок двигать плитки

public slots:
	void processButton();
private slots:
	void on_pushButton_clicked();
	void on_pushButton_settings_clicked();
	void Generate_Tiles(bool random = false);
};

int my_rand(int i);

#endif // MAINWINDOW_H
