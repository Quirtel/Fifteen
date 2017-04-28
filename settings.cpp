#include "settings.h"
#include "ui_settings.h"
#include <fstream>
#include <QSettings>
#include <QtCore>
#include <QFontDialog>
#include <QColorDialog>
#include "mainwindow.h"

settings::settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::settings)
{
	ui->setupUi(this);
}

settings::~settings()
{
	delete ui;
}

void settings::on_pushButton_color_clicked()
{
	QSettings set("Neridia, Inc.", "Fifteen");
	QColor dlg = QColorDialog::getColor(QColor::fromRgb(set.value("tilesColor-red").toInt(),
	                                                    set.value("tilesColor-green").toInt(),
	                                                    set.value("tilesColor-blue").toInt(),255),this,"Color",QColorDialog::DontUseNativeDialog);

	qDebug() << "Color: " << dlg.red() << "," << dlg.green() << "," << dlg.blue();
	if (dlg.isValid())
	{
		set.setValue("tilesColor-red", dlg.red());
		set.setValue("tilesColor-green", dlg.green());
		set.setValue("tilesColor-blue", dlg.blue());

		emit apply_settings();
	}
}

void settings::on_pushButton_font_clicked()
{
	QSettings set("Neridia, Inc.", "Fifteen");
	bool ok;
	QFont font = QFontDialog::getFont(&ok, QFont(set.value("font-family").toString(), set.value("font-size").toInt(), QFont::Bold),this,"Font",QFontDialog::DontUseNativeDialog);

	if (ok)
	{
		set.setValue("font-family", font.family());
		set.setValue("font-size", font.pointSize());
		set.setValue("font-isBold", font.bold());

		emit apply_settings();
	}

}
