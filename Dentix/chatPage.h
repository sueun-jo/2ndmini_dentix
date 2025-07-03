#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QMainWindow>

namespace Ui {
class chatPage;
}

class chatPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit chatPage(QWidget *parent = nullptr);
    ~chatPage();

private:
    Ui::chatPage *ui;

};

#endif // CHATPAGE_H
