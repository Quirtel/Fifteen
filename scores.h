#ifndef SCORES_H
#define SCORES_H

#include <QMainWindow>

namespace Ui {
	class Scores;
}

class Scores : public QMainWindow
{
	Q_OBJECT

public:
	explicit Scores(QWidget *parent = 0);
	~Scores();

private:
	Ui::Scores *ui;
};

#endif // SCORES_H
