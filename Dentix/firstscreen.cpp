#include "firstscreen.h"
#include "ui_firstscreen.h"
FirstScreen::FirstScreen(QWidget *parent)
    : QMainWindow(parent) , ui(new Ui::FirstScreen)
{
    ui->setupUi(this);


}

FirstScreen::~FirstScreen()
{
    delete ui;
}

//login 버튼 누르면 서버랑 연결 요청과 로그인 로직 같이 동작
void FirstScreen::on_loginButton_clicked(){



    QString name = ui->nameInput->text().trimmed(); //nameInput의 text 가져옴
    QString pw = ui->pwInput->text().trimmed(); //pwInput의 text 가져옴
    if (name.isEmpty() || pw.isEmpty()){
        QMessageBox::warning(this, tr("경고"), tr("이름과 비밀번호를 모두 입력해주세요!"));
        return;
    }

    qDebug()<<"click";
    emit connectServerRequest("127.0.0.1", 54321); //서버에 연결하라고 요청
    emit loginRequest(name, pw); //request Login

}



