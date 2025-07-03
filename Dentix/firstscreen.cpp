#include "firstscreen.h"
#include "ui_firstscreen.h"

FirstScreen::FirstScreen(Client* client, QWidget *parent)
    : QMainWindow(parent) , ui(new Ui::FirstScreen), client(client)
{
    ui->setupUi(this);
}

FirstScreen::~FirstScreen()
{
    delete ui;
}

//submit 버튼 누르면 이름을 json으로 전송하고 MainWindow로 화면 전환
void FirstScreen::on_submitButton_clicked(){
    QString name = ui->nameInput->text().trimmed(); //nameInput의 text 가져옴
    if (name.isEmpty()){
        QMessageBox::warning(this, "경고", "이름은 비워둘 수 없습니다.");
        return;
    }
    else{
        client->sendNameAsJson(name); //json 전송

        MainWindow *mw = new MainWindow();
        mw->show();
        this->close(); //현재 화면 종료
    }
}
