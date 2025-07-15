#include "firstscreen.h"
#include "ui_firstscreen.h"
#include "client.h"
#include "logincontroller.h"
#include "mainwindow.h"
FirstScreen::FirstScreen(QWidget *parent)
    : QMainWindow(parent) , ui(new Ui::FirstScreen)
{
    ui->setupUi(this);
    //Model(client)과 Controller 객체 생성
    client = new Client(this); //client 객체 생성
    loginController = new LoginController(client,this); //(client, this) 오류 발생 문제 확인 필요

    connect(this, &FirstScreen::loginRequest, loginController, &LoginController::requestLogin);
    connect(loginController, &LoginController::loginSuccess, this, &FirstScreen::handleLoginSuccess);
    //클라이언트 시그널과 firstscreen 연결

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
    client->connectToServer("127.0.0.1", 54321); //서버에 연결하라고 요청
    loginController->requestLogin(name, pw); //request Login

}

void FirstScreen::handleLoginSuccess(const QString& userName){
    qDebug() << "[firstScreen] Login successful in FirstScreen. Switching to MainWindow." <<userName;

    mainWindow = new MainWindow();
    mainWindow ->show();

    this -> hide();
}
//컨트롤러에서 로그인 실패 처리 함수 여기서 확인
//이거 굳이 여기서 해야하나? 만들고 나중에 확인 및 삭제
void FirstScreen::handleLoginFailed(const QString &reason){
    qDebug()<< "[login failed]";
}
