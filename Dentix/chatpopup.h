#ifndef CHATPOPUP_H
#define CHATPOPUP_H

#include <QWidget>

namespace Ui {
class chatPopUp;
}

class chatPopUp : public QWidget
{
    Q_OBJECT

public:
    explicit chatPopUp(QWidget *parent = nullptr);
    ~chatPopUp();

private slots:
    void on_pushButton_clicked();  // 버튼 클릭 시 연결될 슬롯

private:
    Ui::chatPopUp *ui;
};

#endif // CHATPOPUP_H
