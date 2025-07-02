#include "firstscreen.h"
#include "ui_firstscreen.h"

FirstScreen::FirstScreen(Client* client, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FirstScreen)
{
    ui->setupUi(this);
}

FirstScreen::~FirstScreen()
{
    delete ui;
}

void FirstScreen::on_submitButton_clicked(){
    QString name = ui->nameInput->text(); //nameInput의 text 가져옴
    if (name.isEmpty()){
        QMessageBox::warning(this, "경고", "이름은 비워둘 수 없습니다.");
        return;
    }
    else{
        MainWindow *mw = new MainWindow();
        mw->show();
        this->close(); //현재 화면 종료
    }
}
