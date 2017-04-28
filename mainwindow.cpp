#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QLabel>
#include <QtGui>
#include <QVector>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QSettings>
#include <QColor>
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	arr = NULL;
	moves_number = 0;
	moves_info = new QLabel(ui->statusBar);
	time_label = new QLabel(ui->statusBar);

	moves_info->setText("Число ходов: 0");
	ui->statusBar->insertWidget(0,moves_info,50);
	ui->statusBar->insertWidget(1,time_label);

	Generate_Tiles(false);
}

void MainWindow::Generate_Tiles(bool random) // функция для рандомного создания плиток
{
	QSettings set("Neridia, Inc.", "Fifteen"); // открываем настройки

	if (!random)
	{
		timer_started = false;
		time_label->setText("Время: 00:00");
		moves_info->setText("Число ходов: 0");
	}
	else
	{
		startTimer(0);
		mStartTime = QDateTime::currentDateTime();
		timer_started = true;
		can_move = true;
	}

	int z = 0;
	if (arr != NULL) //если массив уже инициализирован
	{
		for (int i = 0; i < 4; i++) // проходим по матрице плиток (двумерному массиву)
		{
			for (int j = 0; j < 4; j++,z++)
			{
				if (z >= 16) break;

				if (arr[i][j] != NULL)
				{
					ui->gridLayout->removeWidget(arr[i][j]); //удаляем плитку с экрана
					disconnect(arr[i][j], SIGNAL(pressed()), this, SLOT(processButton()));

					delete arr[i][j]; // удаляем плитку из памяти
					arr[i][j] = NULL; // для безопасности присваиваем NULL
				}
			}
		}
		delete arr;
	}

	z = 0;
	arr = new QPushButton**[4];// создаем массив заново

	srand(time(NULL));

	std::vector<int> vec; // создаем вектор данных, он нужен для того, чтобы можно было перемешивать номера плиток
	for (int i = 0; i < 15; i++)
	{
		vec.push_back(i); // забиваем в него числа от 1 до 15
	}

	std::random_shuffle(vec.begin(),vec.end(),my_rand); // собственно, перемешиваем числа

	for (int i = 0; i < 4; i++)
	{
		arr[i] = new QPushButton*[4]; //создаем строку в двумерном массиве

		for (int j = 0; j < 4; j++,z++)
		{
			arr[i][j] = NULL;
			if (z >= 15) break;

			QPushButton *label = new QPushButton(this); // создаем плитку

			pal.setColor(QPalette::ButtonText, Qt::white);
			if (random == true)
			{
				label->setText(QString::number(vec[z]+1)); // текст, который будет на ней отображаться - число из вектора
			}
			else
			{
				label->setText(QString::number(z+1)); // текст, который будет на ней отображаться - число
			}
			label->setFont(QFont(set.value("font-family").toString(), set.value("font-size").toInt(), QFont::Bold)); // делаем побольше шрифт
			label->setPalette(pal);
			label->setMinimumSize(80,80);
			label->setStyleSheet("background-color:"+ QColor::fromRgb(set.value("tilesColor-red").toInt(),
			                                                          set.value("tilesColor-green").toInt(),
			                                                          set.value("tilesColor-blue").toInt(),255).name() +"; border:2px solid white; border-radius: " +set.value("border-radius").toString() + "px;"); // делаем её зеленой

			connect(label, SIGNAL(pressed()), this, SLOT(processButton()));

			arr[i][j] = label; // записываем кнопку в массив
		}
	}


	z = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++, z++)
		{
			if (z >= 15) break;
			ui->gridLayout->addWidget(arr[i][j],i,j); // добавляем плитку на экран
		}
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

bool MainWindow::has_won() // функция, которая проверяет, расставлены ли плитки по порядку(выиграл ли игрок)
{
	int z = 0;
	bool is_winner = false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++, z++)
		{
			if (z >= 15) break;
			if (arr[i][j] != NULL)
			{
				if (arr[i][j]->text() == QString::number(z+1))
					is_winner = true;
				else
				{
					is_winner = false;
					return is_winner;
				}
			}
			else return false;
		}
	}
	return is_winner;
}

void MainWindow::MoveCell(QPushButton *w, int arr_i, int arr_j) // передвижение плитки, если есть свободная клетка от нее, или не передвигать
{
	// проверяем, свободно ли снизу
	if (arr_i < 3)
	{
		if (arr[arr_i+1][arr_j] == NULL)
		{
			ui->gridLayout->addWidget(w,arr_i+1, arr_j);

			arr[arr_i+1][arr_j] = w;
			arr[arr_i][arr_j] = NULL;
			if (has_won())
				qDebug() << "Winner!";
			moves_number++;
			return;
		}
	}

	// проверяем, свободно ли сверху
	if (arr_i > 0)
	{
		if (arr[arr_i-1][arr_j] == NULL)
		{
			ui->gridLayout->addWidget(w,arr_i-1, arr_j);
			arr[arr_i][arr_j] = NULL;
			arr[arr_i-1][arr_j] = w;
			if (has_won())
				qDebug() << "Winner!";
			moves_number++;
			return;
		}
	}

	// проверяем, свободно ли слева
	if (arr_j > 0)
	{
		if (arr[arr_i][arr_j-1] == NULL)
		{
			ui->gridLayout->addWidget(w,arr_i, arr_j-1);
			arr[arr_i][arr_j] = NULL;
			arr[arr_i][arr_j-1] = w;
			if (has_won())
				qDebug() << "Winner!";
			moves_number++;
			return;
		}
	}

	// проверяем, свободно ли справа
	if (arr_j < 3)
	{
		if (arr[arr_i][arr_j+1] == NULL)
		{
			ui->gridLayout->addWidget(w,arr_i, arr_j+1);
			arr[arr_i][arr_j] = NULL;
			arr[arr_i][arr_j+1] = w;
			if (has_won())
				qDebug() << "Winner!";
			moves_number++;
			return;
		}
	}

}

void MainWindow::processButton() // по нажатию плитки выполняется эта функция
{
	if (can_move)
	{
		QPushButton *obj = qobject_cast<QPushButton*>(sender());
		qDebug() << obj->text();

		int i = 0, j = 0;

		// ищем индекс (на каком столбце и строке стоит плитка в матрице)

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (arr[i][j] == obj) // нашлась плитка
				{
					MoveCell(obj,i,j); // двигаем плитки
					moves_info->setText("Число ходов: " + QString::number(moves_number));
					if(has_won()) // если плитки расставлены по порядку
					{
						timer_started = false;
						can_move = false;

						QString best_score;
						QSettings set("Neridia, Inc.", "Fifteen"); // открываем настройки

						QMessageBox msg;
						msg.setText("Вы выиграли!"); // выводим сообщение о выигрыше
						msg.setStandardButtons(QMessageBox::Ok);

						//TODO: дописать лучший рекорд
						if (set.contains("best_score"))
						{
							qDebug() << "Best_score: " << set.value("best_score").toInt() << " moves_number: " << moves_number;
							if (set.value("best_score").toInt() > moves_number)
							{
								msg.setInformativeText("Вы установили новый рекорд! Ваше число ходов: " + QString::number(moves_number) + "\n");
								msg.setInformativeText(msg.informativeText() + "Предыдущий рекорд: " + set.value("best_score").toString());
								set.setValue("best_score", moves_number);
							}
							else
							{
								msg.setInformativeText("Число ходов: " + QString::number(moves_number));
							}
						}
						else
						{
							msg.setInformativeText("Число ходов: " + QString::number(moves_number));
							set.setValue("best_score", moves_number);
						}
						msg.exec();
					}
					return;
				}
			}
		}
	}
}

int my_rand(int i)
{
	return rand() % i;
}

void MainWindow::on_pushButton_clicked()
{
	moves_info->setText("Число ходов: 0");
	moves_number = 0;
	Generate_Tiles(true);
}

void MainWindow::timerEvent(QTimerEvent *)
{
	if(timer_started)
	{
		qint64 ms = mStartTime.msecsTo(QDateTime::currentDateTime());
		int h = ms / 1000 / 60 / 60;
		int m = (ms / 1000 / 60) - (h * 60);
		int s = (ms / 1000) - (m * 60);
		if (m < 10)
		{
			all_time = '0' + QString::number(m) + ':';
		}
		else {
			all_time = QString::number(m) + ':';
		}

		if (s < 10)
		{
			all_time += '0' + QString::number(s);
		}
		else {
			all_time += QString::number(s);
		}

		time_label->setText("Время: " + all_time);
	}
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	QMainWindow::resizeEvent(event); //for debugging
	qDebug() << this->width() << " " << this->height();
}

void MainWindow::on_pushButton_settings_clicked()
{
	settings *scr = new settings(this); // open settings window
	connect(scr,SIGNAL(apply_settings()),this,SLOT(Generate_Tiles()));
	scr->show();
}
