#include "firstscreen.h"
#include "ui_firstscreen.h"

FirstScreen::FirstScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FirstScreen)
{
    ui->setupUi(this);
    connect(ui->submitButton, &QPushButton::clicked, this, &FirstScreen::submit_clicked);
}

FirstScreen::~FirstScreen()
{
    delete ui;
}

void FirstScreen::submit_clicked(){
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
        // QTcpSocket* socket = new QTcpSocket(this);
    // socket->connectToHost("127.0.0.1", 8100); //포트와 ip는 나중에 수정, 상홍에 맞게

    // if (socket->waitForConnected(1000)){
    //     QJsonObject obj;
    //     obj["name"] = name;
    //     QJsonDocument doc(obj);
    //     QByteArray data = doc.toJson();

    //     socket->write(data);
    //     socket->flush();
    //     socket->waitForBytesWritten();
    //     socket->close();                                ./

    //     //transport success -> mainWindow로 전환
    //     MainWindow *mw = new MainWindow();
    //     mw->show();
    //     this->close(); //현재 화면 종료
    // } else {
    //     QMessageBox::critical(this, "연결 실패", "서버에 연결할 수 없습니다.");
    // }


}
