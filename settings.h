#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>
#include <fstream>

namespace Ui {
	class settings;
}

class settings : public QMainWindow
{
	Q_OBJECT

public:
	explicit settings(QWidget *parent = 0);
	~settings();

private slots:
	void on_pushButton_color_clicked();

	void on_pushButton_font_clicked();

	void on_checkBox_border_clicked();

signals:
	void apply_settings();

private:
	Ui::settings *ui;
	std::fstream file;
	QPalette pal;
};

#endif // SETTINGS_H
