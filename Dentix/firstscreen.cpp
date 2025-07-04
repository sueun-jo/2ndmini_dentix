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

//submit 버튼 누르면 서버랑 연결 요청과 로그인 로직 같이 동작
void FirstScreen::on_submitButton_clicked(){

    QString name = ui->nameInput->text().trimmed(); //nameInput의 text 가져옴
    QString pw = ui->pwInput->text().trimmed(); //pwInput의 text 가져옴
    if (name.isEmpty() || pw.isEmpty()){
        QMessageBox::warning(this, tr("경고"), tr("이름과 비밀번호를 모두 입력해주세요!"));
        return;
    }

    client->connectToServer("127.0.0.1", 54321); //서버 연결
    client->requestLogin(name, pw); //서버한테 login 요청

}
