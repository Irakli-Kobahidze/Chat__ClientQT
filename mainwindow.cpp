#include "mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QDialog>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QTextEdit>
#include <QListWidget>
#include <QApplication>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    createMainMenu();
    createRegistrationPage();
    createLoginPage();
    createUserPanel();
    createAdminLoginPage();
    createAdminPanel();

    setWindowTitle("Chat Application");
    setMinimumSize(800, 600);
    resize(900, 700);

    if (client.connectToServer("127.0.0.1")) {
        updateStatus("Подключено к серверу");
    } else {
        updateStatus("Не подключено к серверу");
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMainMenu()
{
    mainMenuPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(mainMenuPage);

    welcomeLabel = new QLabel("Добро пожаловать в чат!");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 18pt; font-weight: bold;");
    mainLayout->addWidget(welcomeLabel);

    instructionLabel = new QLabel("Для начала работы зарегистрируйтесь или войдите в систему");
    instructionLabel->setAlignment(Qt::AlignCenter);
    instructionLabel->setWordWrap(true);
    mainLayout->addWidget(instructionLabel);

    mainLayout->addSpacing(40);

    registerButton = new QPushButton("Зарегистрироваться");
    registerButton->setMinimumHeight(50);
    registerButton->setStyleSheet("font-size: 12pt;");
    mainLayout->addWidget(registerButton);

    loginButton = new QPushButton("Войти");
    loginButton->setMinimumHeight(50);
    loginButton->setStyleSheet("font-size: 12pt;");
    mainLayout->addWidget(loginButton);

    adminLoginButton = new QPushButton("Вход для администратора");
    adminLoginButton->setMinimumHeight(50);
    adminLoginButton->setStyleSheet("font-size: 12pt;");
    mainLayout->addWidget(adminLoginButton);

    showUsersButton = new QPushButton("Показать всех пользователей");
    showUsersButton->setMinimumHeight(50);
    showUsersButton->setStyleSheet("font-size: 12pt;");
    mainLayout->addWidget(showUsersButton);

    exitButton = new QPushButton("Выйти из приложения");
    exitButton->setMinimumHeight(50);
    exitButton->setStyleSheet("font-size: 12pt;");
    mainLayout->addWidget(exitButton);

    mainLayout->addSpacing(40);

    statusLabel = new QLabel("Статус: Не подключено");
    statusLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(statusLabel);

    connect(registerButton, &QPushButton::clicked, this, &MainWindow::onRegisterClicked);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(adminLoginButton, &QPushButton::clicked, this, &MainWindow::onAdminLoginClicked);
    connect(showUsersButton, &QPushButton::clicked, this, &MainWindow::onShowUsersClicked);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::onExitClicked);

    stackedWidget->addWidget(mainMenuPage);
}

void MainWindow::createRegistrationPage()
{
    registrationPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(registrationPage);

    QLabel *titleLabel = new QLabel("Регистрация");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 16pt; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    mainLayout->addSpacing(30);

    QFormLayout *formLayout = new QFormLayout();

    registerLoginEdit = new QLineEdit();
    registerLoginEdit->setPlaceholderText("Введите логин");
    formLayout->addRow("Логин:", registerLoginEdit);

    registerPasswordEdit = new QLineEdit();
    registerPasswordEdit->setEchoMode(QLineEdit::Password);
    registerPasswordEdit->setPlaceholderText("Введите пароль");
    formLayout->addRow("Пароль:", registerPasswordEdit);

    registerNameEdit = new QLineEdit();
    registerNameEdit->setPlaceholderText("Введите ваше имя");
    formLayout->addRow("Имя:", registerNameEdit);

    mainLayout->addLayout(formLayout);
    mainLayout->addSpacing(30);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    confirmRegisterButton = new QPushButton("Зарегистрироваться");
    cancelRegisterButton = new QPushButton("Отмена");

    buttonLayout->addWidget(confirmRegisterButton);
    buttonLayout->addWidget(cancelRegisterButton);

    mainLayout->addLayout(buttonLayout);

    connect(confirmRegisterButton, &QPushButton::clicked, this, &MainWindow::onConfirmRegisterClicked);
    connect(cancelRegisterButton, &QPushButton::clicked, this, &MainWindow::onCancelRegisterClicked);

    stackedWidget->addWidget(registrationPage);
}

void MainWindow::createLoginPage()
{
    loginPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(loginPage);

    QLabel *titleLabel = new QLabel("Вход в систему");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 16pt; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    mainLayout->addSpacing(30);

    QFormLayout *formLayout = new QFormLayout();

    loginLoginEdit = new QLineEdit();
    loginLoginEdit->setPlaceholderText("Введите логин");
    formLayout->addRow("Логин:", loginLoginEdit);

    loginPasswordEdit = new QLineEdit();
    loginPasswordEdit->setEchoMode(QLineEdit::Password);
    loginPasswordEdit->setPlaceholderText("Введите пароль");
    formLayout->addRow("Пароль:", loginPasswordEdit);

    mainLayout->addLayout(formLayout);
    mainLayout->addSpacing(30);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    confirmLoginButton = new QPushButton("Войти");
    cancelLoginButton = new QPushButton("Отмена");

    buttonLayout->addWidget(confirmLoginButton);
    buttonLayout->addWidget(cancelLoginButton);

    mainLayout->addLayout(buttonLayout);

    connect(confirmLoginButton, &QPushButton::clicked, this, &MainWindow::onConfirmLoginClicked);
    connect(cancelLoginButton, &QPushButton::clicked, this, &MainWindow::onCancelLoginClicked);

    stackedWidget->addWidget(loginPage);
}

void MainWindow::createAdminLoginPage()
{
    adminLoginPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(adminLoginPage);

    QLabel *titleLabel = new QLabel("Вход для администратора");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 16pt; font-weight: bold; color: #e74c3c;");
    mainLayout->addWidget(titleLabel);

    mainLayout->addSpacing(30);

    QFormLayout *formLayout = new QFormLayout();

    adminLoginEdit = new QLineEdit();
    adminLoginEdit->setPlaceholderText("Введите логин администратора");
    formLayout->addRow("Логин:", adminLoginEdit);

    adminPasswordEdit = new QLineEdit();
    adminPasswordEdit->setEchoMode(QLineEdit::Password);
    adminPasswordEdit->setPlaceholderText("Введите пароль администратора");
    formLayout->addRow("Пароль:", adminPasswordEdit);

    mainLayout->addLayout(formLayout);
    mainLayout->addSpacing(30);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    confirmAdminLoginButton = new QPushButton("Войти как администратор");
    cancelAdminLoginButton = new QPushButton("Отмена");

    confirmAdminLoginButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #e74c3c;"
        "   color: white;"
        "   border: none;"
        "   padding: 10px;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c0392b;"
        "}"
        );

    buttonLayout->addWidget(confirmAdminLoginButton);
    buttonLayout->addWidget(cancelAdminLoginButton);

    mainLayout->addLayout(buttonLayout);

    connect(confirmAdminLoginButton, &QPushButton::clicked, this, &MainWindow::onConfirmAdminLoginClicked);
    connect(cancelAdminLoginButton, &QPushButton::clicked, this, &MainWindow::onCancelAdminLoginClicked);

    stackedWidget->addWidget(adminLoginPage);
}

void MainWindow::createAdminPanel()
{
    adminPanelPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(adminPanelPage);

    QLabel *titleLabel = new QLabel("Панель администратора");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 16pt; font-weight: bold; color: #e74c3c;");
    mainLayout->addWidget(titleLabel);

    QLabel *infoLabel = new QLabel("Выберите действие и пользователя из списка");
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setStyleSheet("font-size: 10pt; color: #7f8c8d; padding: 5px;");
    mainLayout->addWidget(infoLabel);

    adminTextEdit = new QTextEdit();
    adminTextEdit->setReadOnly(true);
    adminTextEdit->setStyleSheet(
        "QTextEdit {"
        "   background-color: #2c3e50;"
        "   color: white;"
        "   border: 2px solid #34495e;"
        "   border-radius: 5px;"
        "   font-size: 11pt;"
        "   padding: 10px;"
        "}"
        );
    mainLayout->addWidget(adminTextEdit);

    QGridLayout *gridLayout = new QGridLayout();

    showAllUsersButton = new QPushButton("Все пользователи");
    showOnlineUsersButton = new QPushButton("Онлайн");
    showBannedUsersButton = new QPushButton("Забаненные");

    banUserButton = new QPushButton("Выбрать для бана");
    unbanUserButton = new QPushButton("Выбрать для разбана");
    deleteUserButton = new QPushButton("Выбрать для удаления");

    QPushButton *showPrivateMessagesButton = new QPushButton("Приватные сообщения");
    QPushButton *showPublicMessagesButton = new QPushButton("Публичные сообщения");

    QString adminButtonStyle =
        "QPushButton {"
        "   background-color: #34495e;"
        "   color: white;"
        "   border: none;"
        "   padding: 10px;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "   min-height: 40px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2c3e50;"
        "}";

    banUserButton->setStyleSheet(
        adminButtonStyle +
        "QPushButton {"
        "   background-color: #e74c3c;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c0392b;"
        "}"
        );

    unbanUserButton->setStyleSheet(
        adminButtonStyle +
        "QPushButton {"
        "   background-color: #27ae60;"
        "}"
        "QPushButton:hover {"
        "   background-color: #229954;"
        "}"
        );

    deleteUserButton->setStyleSheet(
        adminButtonStyle +
        "QPushButton {"
        "   background-color: #e67e22;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d35400;"
        "}"
        );

    showPrivateMessagesButton->setStyleSheet(
        adminButtonStyle +
        "QPushButton {"
        "   background-color: #9b59b6;"
        "}"
        "QPushButton:hover {"
        "   background-color: #8e44ad;"
        "}"
        );

    showPublicMessagesButton->setStyleSheet(
        adminButtonStyle +
        "QPushButton {"
        "   background-color: #3498db;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        );

    showAllUsersButton->setStyleSheet(adminButtonStyle);
    showOnlineUsersButton->setStyleSheet(adminButtonStyle);
    showBannedUsersButton->setStyleSheet(adminButtonStyle);

    gridLayout->addWidget(showAllUsersButton, 0, 0);
    gridLayout->addWidget(showOnlineUsersButton, 0, 1);
    gridLayout->addWidget(showBannedUsersButton, 0, 2);
    gridLayout->addWidget(banUserButton, 1, 0);
    gridLayout->addWidget(unbanUserButton, 1, 1);
    gridLayout->addWidget(deleteUserButton, 1, 2);
    gridLayout->addWidget(showPrivateMessagesButton, 2, 0);
    gridLayout->addWidget(showPublicMessagesButton, 2, 1);

    mainLayout->addLayout(gridLayout);

    adminLogoutButton = new QPushButton("Выйти из админ панели");
    adminLogoutButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #95a5a6;"
        "   color: white;"
        "   border: none;"
        "   padding: 10px;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #7f8c8d;"
        "}"
        );
    mainLayout->addWidget(adminLogoutButton);

    connect(showAllUsersButton, &QPushButton::clicked, this, &MainWindow::onAdminShowAllUsers);
    connect(showOnlineUsersButton, &QPushButton::clicked, this, &MainWindow::onAdminShowOnlineUsers);
    connect(showBannedUsersButton, &QPushButton::clicked, this, &MainWindow::onAdminShowBannedUsers);
    connect(banUserButton, &QPushButton::clicked, this, &MainWindow::onAdminBanUser);
    connect(unbanUserButton, &QPushButton::clicked, this, &MainWindow::onAdminUnbanUser);
    connect(deleteUserButton, &QPushButton::clicked, this, &MainWindow::onAdminDeleteUser);
    connect(showPrivateMessagesButton, &QPushButton::clicked, this, &MainWindow::onAdminShowPrivateMessagesWarning);
    connect(showPublicMessagesButton, &QPushButton::clicked, this, &MainWindow::onAdminShowPublicMessages);
    connect(adminLogoutButton, &QPushButton::clicked, this, &MainWindow::onAdminLogout);

    stackedWidget->addWidget(adminPanelPage);
}

void MainWindow::createUserPanel()
{
    userPanelPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(userPanelPage);

    QLabel *titleLabel = new QLabel("Панель пользователя");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 16pt; font-weight: bold; color: white;");
    mainLayout->addWidget(titleLabel);

    messagesTextEdit = new QTextEdit();
    messagesTextEdit->setReadOnly(true);
    messagesTextEdit->setStyleSheet(
        "QTextEdit {"
        "   background-color: darkGreen;"
        "   border: 2px solid #bdc3c7;"
        "   border-radius: 5px;"
        "   font-size: 11pt;"
        "   padding: 10px;"
        "}"
        );
    mainLayout->addWidget(messagesTextEdit);

    sendPrivateButton = new QPushButton("Отправить приватное сообщение");
    sendPrivateButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #9b59b6;"
        "   color: white;"
        "   border: none;"
        "   padding: 10px;"
        "   border-radius: 5px;"
        "   font-size: 11pt;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #8e44ad;"
        "}"
        );
    mainLayout->addWidget(sendPrivateButton);

    QHBoxLayout *publicLayout = new QHBoxLayout();

    publicMessageLineEdit = new QLineEdit();
    publicMessageLineEdit->setPlaceholderText("Введите сообщение для всех");
    publicMessageLineEdit->setStyleSheet(
        "QLineEdit {"
        "   padding: 8px;"
        "   border: 2px solid #bdc3c7;"
        "   border-radius: 5px;"
        "   font-size: 11pt;"
        "}"
        "QLineEdit:focus {"
        "   border-color: #3498db;"
        "}"
        );

    sendPublicButton = new QPushButton("Отправить всем");
    sendPublicButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border: none;"
        "   padding: 8px 16px;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        );

    publicLayout->addWidget(publicMessageLineEdit);
    publicLayout->addWidget(sendPublicButton);
    mainLayout->addLayout(publicLayout);

    QHBoxLayout *actionsLayout = new QHBoxLayout();

    viewPrivateMessagesButton = new QPushButton("Мои сообщения");
    viewPublicMessagesButton = new QPushButton("Общий чат");
    logoutButton = new QPushButton("Выйти");

    QString actionButtonStyle =
        "QPushButton {"
        "   background-color: #2c3e50;"
        "   color: white;"
        "   border: none;"
        "   padding: 8px 12px;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #34495e;"
        "}";

    viewPrivateMessagesButton->setStyleSheet(actionButtonStyle);
    viewPublicMessagesButton->setStyleSheet(actionButtonStyle);
    logoutButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #e74c3c;"
        "   color: white;"
        "   border: none;"
        "   padding: 8px 12px;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c0392b;"
        "}"
        );

    actionsLayout->addWidget(viewPrivateMessagesButton);
    actionsLayout->addWidget(viewPublicMessagesButton);
    actionsLayout->addStretch();
    actionsLayout->addWidget(logoutButton);

    mainLayout->addLayout(actionsLayout);

    connect(sendPrivateButton, &QPushButton::clicked, this, &MainWindow::onSendPrivateClicked);
    connect(sendPublicButton, &QPushButton::clicked, this, &MainWindow::onSendPublicClicked);
    connect(viewPrivateMessagesButton, &QPushButton::clicked, this, &MainWindow::onViewPrivateMessagesClicked);
    connect(viewPublicMessagesButton, &QPushButton::clicked, this, &MainWindow::onViewPublicMessagesClicked);
    connect(logoutButton, &QPushButton::clicked, this, &MainWindow::onLogoutClicked);

    stackedWidget->addWidget(userPanelPage);
}


void MainWindow::showMessage(const QString &message)
{
    QMessageBox::information(this, "Информация", message);
}

void MainWindow::updateStatus(const QString &status)
{
    statusLabel->setText("Статус: " + status);
}

void MainWindow::switchToPage(int pageIndex)
{
    stackedWidget->setCurrentIndex(pageIndex);
}

void MainWindow::onRegisterClicked()
{
    switchToPage(1);
    registerLoginEdit->clear();
    registerPasswordEdit->clear();
    registerNameEdit->clear();
}

void MainWindow::onLoginClicked()
{
    switchToPage(2);
    loginLoginEdit->clear();
    loginPasswordEdit->clear();
}

void MainWindow::onAdminLoginClicked()
{
    switchToPage(4);
    adminLoginEdit->clear();
    adminPasswordEdit->clear();
}

void MainWindow::onShowUsersClicked()
{
    showUsersDialog();
}

void MainWindow::onExitClicked()
{
    close();
}

void MainWindow::onConfirmRegisterClicked()
{
    QString login = registerLoginEdit->text().trimmed();
    QString password = registerPasswordEdit->text().trimmed();
    QString name = registerNameEdit->text().trimmed();

    if (login.isEmpty() || password.isEmpty() || name.isEmpty()) {
        showMessage("Заполните все поля!");
        return;
    }

    std::string command = "1 " + login.toStdString() + " " +
                          password.toStdString() + " " + name.toStdString();

    std::string response = client.sendCommand(command);
    showMessage(QString::fromStdString(response));

    if (response == "User added successfully!") {
        switchToPage(0);
    }
}

void MainWindow::onCancelRegisterClicked()
{
    switchToPage(0);
}

void MainWindow::onConfirmLoginClicked()
{
    QString login = loginLoginEdit->text().trimmed();
    QString password = loginPasswordEdit->text().trimmed();

    if (login.isEmpty() || password.isEmpty()) {
        showMessage("Заполните все поля!");
        return;
    }

    std::string command = "2 " + login.toStdString() + " " + password.toStdString();
    std::string response = client.sendCommand(command);

    if (response == "Login successful!") {
        switchToPage(3);
        messagesTextEdit->clear();
        messagesTextEdit->append("Добро пожаловать в чат!\n");
        updateStatus("Вход выполнен");
    } else {
        showMessage("Ошибка входа: " + QString::fromStdString(response));
    }
}

void MainWindow::onCancelLoginClicked()
{
    switchToPage(0);
}

void MainWindow::onConfirmAdminLoginClicked()
{
    QString login = adminLoginEdit->text().trimmed();
    QString password = adminPasswordEdit->text().trimmed();

    if (login.isEmpty() || password.isEmpty()) {
        showMessage("Заполните все поля!");
        return;
    }

    showMessage("Попытка входа как администратор...");

    bool success = client.adminLogin(login.toStdString(), password.toStdString());

    if (success) {
        switchToPage(5);
        adminTextEdit->clear();
        adminTextEdit->append("Добро пожаловать в панель администратора!\n");
        updateStatus("Режим администратора");
        showMessage("Успешный вход в режим администратора");
    } else {
        showMessage("Ошибка входа администратора: Неверные данные или сервер не отвечает");
    }
}

void MainWindow::onCancelAdminLoginClicked()
{
    switchToPage(0);
}

void MainWindow::onSendPrivateClicked()
{
    QString recipient = selectUserFromList();

    if (recipient.isEmpty()) {
        return;
    }

    QDialog *messageDialog = new QDialog(this);
    messageDialog->setWindowTitle("Сообщение для " + recipient);
    messageDialog->setMinimumSize(400, 200);

    QVBoxLayout *layout = new QVBoxLayout(messageDialog);

    QLabel *label = new QLabel("Введите сообщение для <b>" + recipient + "</b>:");
    layout->addWidget(label);

    QTextEdit *messageEdit = new QTextEdit();
    messageEdit->setPlaceholderText("Введите ваше сообщение здесь...");
    messageEdit->setMaximumHeight(100);
    layout->addWidget(messageEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel
        );
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, messageDialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, messageDialog, &QDialog::reject);

    if (messageDialog->exec() == QDialog::Accepted) {
        QString message = messageEdit->toPlainText().trimmed();

        if (message.isEmpty()) {
            showMessage("Сообщение не может быть пустым!");
            return;
        }

        std::string command = "1 " + recipient.toStdString() + " " + message.toStdString();
        std::string response = client.sendCommand(command);

        if (response == "Message sent successfully!") {
            messagesTextEdit->append(
                QString("[%1]  Для %2: %3")
                    .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                    .arg(recipient)
                    .arg(message)
                );
        }

        showMessage(QString::fromStdString(response));
    }
}

void MainWindow::onViewPrivateMessagesClicked()
{
    std::string response = client.sendCommand("3");
    messagesTextEdit->clear();
    messagesTextEdit->append("Ваши приватные сообщения\n");
    messagesTextEdit->append(QString::fromStdString(response));
}

void MainWindow::onViewPublicMessagesClicked()
{
    std::string response = client.sendCommand("4");
    messagesTextEdit->clear();
    messagesTextEdit->append("Общий чат\n");
    messagesTextEdit->append(QString::fromStdString(response));
}


void MainWindow::onAdminShowAllUsers()
{
    std::string response = client.showAllUsers();
    adminTextEdit->clear();
    adminTextEdit->append("Все пользователи:\n");
    adminTextEdit->append(QString::fromStdString(response));
}

void MainWindow::onAdminShowOnlineUsers()
{
    std::string response = client.showOnlineUsers();
    adminTextEdit->clear();
    adminTextEdit->append("Онлайн пользователи:\n");

    if (response.find("Unknown") != std::string::npos || response.find("Error") != std::string::npos) {
        adminTextEdit->append("Команда не поддерживается сервером\n");
        adminTextEdit->append("Ответ сервера: " + QString::fromStdString(response));
    } else {
        adminTextEdit->append(QString::fromStdString(response));
    }
}

void MainWindow::onAdminShowBannedUsers()
{
    std::string response = client.showBannedUsers();
    adminTextEdit->clear();
    adminTextEdit->append("Забаненные пользователи:\n");

    if (response.find("Unknown") != std::string::npos || response.find("Error") != std::string::npos) {
        adminTextEdit->append("Команда не поддерживается сервером\n");
        adminTextEdit->append("Ответ сервера: " + QString::fromStdString(response));
    } else if (response.find("No banned users") != std::string::npos) {
        adminTextEdit->append("Нет забаненных пользователей\n");
        adminTextEdit->append("Все пользователи активны и могут общаться в чате");
    } else {
        adminTextEdit->append(QString::fromStdString(response));
    }
}

void MainWindow::onAdminShowPrivateMessagesWarning()
{
    QMessageBox::information(this, "Конфиденциальность переписки",
                             "<html><body style='font-size: 12pt; color: black;'>"
                             "<h3 style='color: #e74c3c; text-align: center;'>Статья 23 Конституции РФ</h3>"
                             "<div style='background-color: #f8f9fa; padding: 15px; border-radius: 8px; border: 2px solid #e74c3c; margin: 10px 0;'>"
                             "<p style='color: black;'><b>1.</b> Каждый имеет право на неприкосновенность частной жизни, личную и семейную тайну, защиту своей чести и доброго имени.</p>"  // ДОБАВЛЕНО style='color: black;'
                             "<p style='color: black;'><b>2.</b> Каждый имеет право на тайну переписки, телефонных переговоров, почтовых, телеграфных и иных сообщений. "  // ДОБАВЛЕНО style='color: black;'
                             "<span style='color: #e74c3c; font-weight: bold;'>Ограничение этого права допускается только на основании судебного решения.</span></p>"
                             "</div>"
                             "<p style='text-align: center; color: #7f8c8d; font-style: italic;'>"
                             "⚠️ Доступ к приватным сообщениям пользователей ограничен законодательством"
                             "</p>"
                             "</body></html>");
}
void MainWindow::onAdminShowPublicMessages()
{
    QDialog *messagesDialog = new QDialog(this);
    messagesDialog->setWindowTitle("Все публичные сообщения");
    messagesDialog->setMinimumSize(700, 500);
    messagesDialog->setStyleSheet(
        "QDialog {"
        "   background-color: #ecf0f1;"
        "}"
        );

    QVBoxLayout *mainLayout = new QVBoxLayout(messagesDialog);

    QLabel *titleLabel = new QLabel("История публичных сообщений");
    titleLabel->setStyleSheet(
        "font-size: 16pt;"
        "font-weight: bold;"
        "color: black;"
        "padding: 15px;"
        "background-color: #3498db;"
        "color: white;"
        "border-radius: 8px;"
        "margin: 5px;"
        );
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    QLabel *infoLabel = new QLabel("Публичные сообщения доступны всем пользователям чата");
    infoLabel->setStyleSheet(
        "font-size: 10pt;"
        "color: black;"
        "padding: 5px;"
        "text-align: center;"
        "font-style: italic;"
        );
    mainLayout->addWidget(infoLabel);

    QTextEdit *messagesTextEdit = new QTextEdit();
    messagesTextEdit->setReadOnly(true);
    messagesTextEdit->setStyleSheet(
        "QTextEdit {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #bdc3c7;"
        "   border-radius: 8px;"
        "   font-size: 11pt;"
        "   padding: 10px;"
        "   margin: 5px;"
        "}"
        );

    std::string response = client.showPublicMessages();
    QString messagesText = QString::fromStdString(response);

    if (messagesText.contains("No public messages available")) {
        messagesTextEdit->setHtml(
            "<div style='text-align: center; padding: 50px; color: #7f8c8d;'>"
            "<h3>Публичных сообщений пока нет</h3>"
            "<p>Пользователи еще не отправляли сообщений в общий чат</p>"
            "</div>"
            );
    } else {
        QString formattedText = "<div style='font-family: Arial, sans-serif;'>";

        QStringList lines = messagesText.split('\n', Qt::SkipEmptyParts);
        for (const QString &line : lines) {
            if (line.contains(":")) {
                QString formattedLine = line;
                formattedLine.replace(" - ", " <strong>→</strong> ");
                formattedLine = "<div style='margin: 8px 0; padding: 8px; background-color: #f8f9fa; border-radius: 5px; border-left: 4px solid #3498db;'>" +
                                formattedLine + "</div>";
                formattedText += formattedLine;
            } else if (!line.trimmed().isEmpty()) {
                formattedText += "<h3 style='color: #2c3e50; margin: 15px 0 10px 0;'>" + line + "</h3>";
            }
        }
        formattedText += "</div>";
        messagesTextEdit->setHtml(formattedText);
    }

    mainLayout->addWidget(messagesTextEdit);

    QLabel *statsLabel = new QLabel();
    int messageCount = messagesText.count("→");
    statsLabel->setText(QString("Всего сообщений: %1").arg(messageCount));
    statsLabel->setStyleSheet(
        "font-size: 10pt;"
        "color: #27ae60;"
        "padding: 8px;"
        "background-color: #d5f4e6;"
        "border-radius: 5px;"
        "margin: 5px;"
        );
    statsLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(statsLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *refreshButton = new QPushButton("Обновить");
    QPushButton *closeButton = new QPushButton("Закрыть");

    refreshButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border: none;"
        "   padding: 8px 16px;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        );

    closeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #95a5a6;"
        "   color: white;"
        "   border: none;"
        "   padding: 8px 16px;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #7f8c8d;"
        "}"
        );

    buttonLayout->addWidget(refreshButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);

    mainLayout->addLayout(buttonLayout);

    connect(refreshButton, &QPushButton::clicked, [this, messagesTextEdit]() {
        std::string response = client.showPublicMessages();
        QString messagesText = QString::fromStdString(response);

        if (messagesText.contains("No public messages available")) {
            messagesTextEdit->setHtml(
                "<div style='text-align: center; padding: 50px; color: #7f8c8d;'>"
                "<h3>Публичных сообщений пока нет</h3>"
                "<p>Пользователи еще не отправляли сообщений в общий чат</p>"
                "</div>"
                );
        } else {
            QString formattedText = "<div style='font-family: Arial, sans-serif;'>";
            QStringList lines = messagesText.split('\n', Qt::SkipEmptyParts);
            for (const QString &line : lines) {
                if (line.contains(":")) {
                    QString formattedLine = line;
                    formattedLine.replace(" - ", " <strong>→</strong> ");
                    formattedLine = "<div style='margin: 8px 0; padding: 8px; background-color: #f8f9fa; border-radius: 5px; border-left: 4px solid #3498db;'>" +
                                    formattedLine + "</div>";
                    formattedText += formattedLine;
                } else if (!line.trimmed().isEmpty()) {
                    formattedText += "<h3 style='color: #2c3e50; margin: 15px 0 10px 0;'>" + line + "</h3>";
                }
            }
            formattedText += "</div>";
            messagesTextEdit->setHtml(formattedText);
        }
    });

    connect(closeButton, &QPushButton::clicked, messagesDialog, &QDialog::accept);

    messagesDialog->exec();
}

void MainWindow::onAdminBanUser()
{
    QString selectedLogin = selectUserForAction("Бан пользователя", "Забанить выбранного пользователя");

    if (!selectedLogin.isEmpty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение бана",
                                      QString("Вы уверены, что хотите забанить пользователя с логином:\n\n"
                                              "%1\n\n"
                                              "Это действие нельзя будет отменить!").arg(selectedLogin),
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            std::string response = client.banUser(selectedLogin.toStdString());

            if (response.find("Unknown") != std::string::npos || response.find("Error") != std::string::npos) {
                showMessage("Ошибка: " + QString::fromStdString(response));
            } else {
                showMessage(QString::fromStdString(response));
                onAdminShowBannedUsers();
            }
            adminTextEdit->append("\n" + QString::fromStdString(response));
        } else {
            showMessage("❌ Действие отменено");
        }
    }
}

void MainWindow::onAdminUnbanUser()
{
    std::string bannedResponse = client.showBannedUsers();

    if (bannedResponse.find("No banned users") != std::string::npos) {
        showMessage("❌ Нет забаненных пользователей для разбана");
        return;
    }

    QString selectedLogin = selectUserForAction("Разбан пользователя", "Разбанить выбранного пользователя");

    if (!selectedLogin.isEmpty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение разбана",
                                      QString("Вы уверены, что хотите разбанить пользователя с логином:\n\n"
                                              "%1").arg(selectedLogin),
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            std::string response = client.unbanUser(selectedLogin.toStdString());

            if (response.find("Unknown") != std::string::npos || response.find("Error") != std::string::npos) {
                showMessage("Ошибка: " + QString::fromStdString(response));
            } else {
                showMessage(QString::fromStdString(response));
                onAdminShowBannedUsers();
            }
            adminTextEdit->append("\n" + QString::fromStdString(response));
        } else {
            showMessage("❌ Действие отменено");
        }
    }
}

void MainWindow::onAdminDeleteUser()
{
    QString selectedLogin = selectUserForAction("Удаление пользователя", "Удалить выбранного пользователя");

    if (!selectedLogin.isEmpty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, "⚠️ ОПАСНОЕ ДЕЙСТВИЕ",
                                     QString("ВНИМАНИЕ! Вы собираетесь УДАЛИТЬ пользователя:\n\n"
                                             "%1\n\n"
                                             "Это действие:\n"
                                             "• Удалит все сообщения пользователя\n"
                                             "• Удалит аккаунт без возможности восстановления\n"
                                             "• Не может быть отменено\n\n"
                                             "Вы уверены, что хотите продолжить?").arg(selectedLogin),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                     QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            QMessageBox::StandardButton finalReply;
            finalReply = QMessageBox::critical(this, "ФИНАЛЬНОЕ ПОДТВЕРЖДЕНИЕ",
                                               QString("ПОСЛЕДНЕЕ ПРЕДУПРЕЖДЕНИЕ!\n\n"
                                                       "Вы УДАЛЯЕТЕ пользователя: %1\n\n"
                                                       "Нажмите OK для подтверждения удаления,"
                                                       "или Cancel для отмены.").arg(selectedLogin),
                                               QMessageBox::Ok | QMessageBox::Cancel,
                                               QMessageBox::Cancel);

            if (finalReply == QMessageBox::Ok) {
                std::string response = client.deleteUser(selectedLogin.toStdString());

                if (response.find("Unknown") != std::string::npos || response.find("Error") != std::string::npos) {
                    showMessage("Ошибка: " + QString::fromStdString(response));
                } else {
                    showMessage(QString::fromStdString(response));
                    onAdminShowAllUsers();
                }
                adminTextEdit->append("\n" + QString::fromStdString(response));
            } else {
                showMessage("Удаление отменено");
            }
        } else {
            showMessage("Действие отменено");
        }
    }
}

void MainWindow::onAdminLogout()
{
    // Отправляем команду выхода из админ панели
    client.sendCommand("7");
    switchToPage(0);
    updateStatus("Не в системе");
    showMessage("Вы вышли из режима администратора");
}

void MainWindow::onLogoutClicked()
{
    // Отправляем команду выхода из пользовательской панели
    client.sendCommand("5");
    switchToPage(0);
    updateStatus("Не в системе");
    showMessage("Вы вышли из системы");
}

void MainWindow::showUsersDialog()
{
    QDialog *usersDialog = new QDialog(this);
    usersDialog->setWindowTitle("Список пользователей");
    usersDialog->setMinimumSize(400, 300);
    usersDialog->setStyleSheet("background-color: white;");
    QVBoxLayout *layout = new QVBoxLayout(usersDialog);

    QLabel *titleLabel = new QLabel("Список пользователей");
    titleLabel->setStyleSheet("font-size: 14pt; font-weight: bold; padding: 10px; color: black;");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    QTextEdit *usersTextEdit = new QTextEdit();
    usersTextEdit->setReadOnly(true);
    usersTextEdit->setStyleSheet(
        "QTextEdit {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #bdc3c7;"
        "   border-radius: 5px;"
        "   font-size: 11pt;"
        "   padding: 10px;"
        "}"
        );

    std::string response = client.sendCommand("3");
    QString usersText = QString::fromStdString(response);

    if (usersText.contains("No users registered")) {
        usersTextEdit->setHtml("<div style='text-align: center; color: black; padding: 50px;'>❌ Пользователи не найдены</div>");  // ИЗМЕНЕНО color: black;
    } else {
        usersTextEdit->setPlainText(usersText);
    }

    layout->addWidget(usersTextEdit);

    QPushButton *closeButton = new QPushButton("Закрыть");
    closeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #95a5a6;"
        "   color: white;"
        "   border: none;"
        "   padding: 8px 16px;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #7f8c8d;"
        "}"
        );
    connect(closeButton, &QPushButton::clicked, usersDialog, &QDialog::accept);
    layout->addWidget(closeButton, 0, Qt::AlignCenter);

    usersDialog->exec();
}

QString MainWindow::selectUserFromList()
{
    QDialog *selectDialog = new QDialog(this);
    selectDialog->setWindowTitle("Выберите получателя");
    selectDialog->setMinimumSize(400, 400);
    selectDialog->setStyleSheet("background-color: white;");

    QVBoxLayout *mainLayout = new QVBoxLayout(selectDialog);

    QLabel *titleLabel = new QLabel("✉️ Выберите получателя");
    titleLabel->setStyleSheet("font-size: 14pt; font-weight: bold; padding: 10px; color: black;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    QListWidget *usersList = new QListWidget();
    usersList->setStyleSheet(
        "QListWidget {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #bdc3c7;"
        "   border-radius: 5px;"
        "   padding: 5px;"
        "   font-family: Arial;"
        "   font-size: 11pt;"
        "}"
        "QListWidget::item {"
        "   padding: 10px;"
        "   border-bottom: 1px solid #ecf0f1;"
        "   color: black;"
        "   font-family: Arial;"
        "   font-size: 11pt;"
        "   font-weight: normal;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border-radius: 3px;"
        "   font-weight: bold;"
        "}"
        );

    std::string response = client.sendCommand("6");
    QString usersText = QString::fromStdString(response);

    QStringList users;
    if (!usersText.contains("No users registered")) {
        QStringList lines = usersText.split('\n');
        for (const QString &line : lines) {
            if (line.contains("-") && line.contains("(login:")) {
                // Извлекаем имя пользователя
                QString name = line.section('-', 1).section('(', 0, 0).trimmed();
                if (!name.isEmpty()) {
                    users.append(name);
                }
            }
        }
    }

    for (const QString &user : users) {
        QListWidgetItem *item = new QListWidgetItem(user);
        item->setData(Qt::UserRole, user);
        item->setForeground(QBrush(QColor(0, 0, 0)));
        usersList->addItem(item);
    }

    if (users.isEmpty()) {
        QListWidgetItem *item = new QListWidgetItem("❌ Пользователи не найдены");
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        item->setTextAlignment(Qt::AlignCenter);
        item->setForeground(QBrush(QColor(128, 128, 128))); // серый текст для неактивного элемента
        usersList->addItem(item);
    }

    mainLayout->addWidget(usersList);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QString buttonStyle =
        "QPushButton {"
        "   padding: 8px 16px;"
        "   border: none;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "   font-family: Arial;"
        "   font-size: 11pt;"
        "   color: black;"
        "   min-width: 80px;"
        "}"
        "QPushButton:hover {"
        "   border: 2px solid #2c3e50;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #2c3e50;"
        "   color: white;"
        "}";

    buttonBox->button(QDialogButtonBox::Ok)->setText("Выбрать");
    buttonBox->button(QDialogButtonBox::Ok)->setStyleSheet(
        buttonStyle +
        "QPushButton {"
        "   background-color: #27ae60;"
        "   color: white;"
        "}"
        "QPushButton:hover {"
        "   background-color: #229954;"
        "   border: 2px solid #1e8449;"
        "   color: white;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1e8449;"
        "   color: white;"
        "}"
        );

    // Кнопка Отмена
    buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");
    buttonBox->button(QDialogButtonBox::Cancel)->setStyleSheet(
        buttonStyle +
        "QPushButton {"
        "   background-color: #e74c3c;"
        "   color: white;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c0392b;"
        "   border: 2px solid #922b21;"
        "   color: white;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #922b21;"
        "   color: white;"
        "}"
        );

    // Изначально кнопка отключена
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    mainLayout->addWidget(buttonBox);

    // Переменная для результата
    QString selectedUser;

    connect(usersList, &QListWidget::itemSelectionChanged, [&]() {
        QList<QListWidgetItem*> selectedItems = usersList->selectedItems();
        if (!selectedItems.isEmpty() && !users.isEmpty()) {
            selectedUser = selectedItems.first()->data(Qt::UserRole).toString();
            buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        } else {
            buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
    });

    connect(buttonBox, &QDialogButtonBox::accepted, selectDialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, selectDialog, &QDialog::reject);

    // Показываем диалог и возвращаем результат
    if (selectDialog->exec() == QDialog::Accepted) {
        return selectedUser;
    }

    return "";
}

QString MainWindow::selectUserForAction(const QString& title, const QString& action)
{
    QDialog *selectDialog = new QDialog(this);
    selectDialog->setWindowTitle(title);
    selectDialog->setMinimumSize(500, 500);
    selectDialog->setStyleSheet("background-color: white;");

    QVBoxLayout *mainLayout = new QVBoxLayout(selectDialog);

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("font-size: 14pt; font-weight: bold; padding: 10px; color: black;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    QLabel *actionLabel = new QLabel("Действие: " + action);
    actionLabel->setStyleSheet("font-size: 11pt; padding: 5px; color: black;");
    actionLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(actionLabel);

    QListWidget *usersList = new QListWidget();
    usersList->setStyleSheet(
        "QListWidget {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #bdc3c7;"
        "   border-radius: 5px;"
        "   padding: 5px;"
        "   font-family: Arial;"
        "   font-size: 11pt;"
        "}"
        "QListWidget::item {"
        "   padding: 12px;"
        "   border-bottom: 1px solid #ecf0f1;"
        "   color: black;"
        "   font-family: Arial;"
        "   font-size: 11pt;"
        "   font-weight: normal;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border-radius: 3px;"
        "   font-weight: bold;"
        "}"
        );

    std::string response = client.sendCommand("3");
    QString usersText = QString::fromStdString(response);

    QStringList users;
    QMap<QString, QString> userLoginMap;

    if (!usersText.contains("No users registered")) {
        QStringList lines = usersText.split('\n');
        for (const QString &line : lines) {
            if (line.contains("-") && line.contains("(login:")) {
                QString name = line.section('-', 1).section('(', 0, 0).trimmed();
                QString login = line.section("(login:", 1).section(')', 0, 0).trimmed();

                if (!name.isEmpty() && !login.isEmpty()) {
                    users.append(name);
                    userLoginMap[name] = login;
                }
            }
        }
    }

    for (const QString &user : users) {
        QString login = userLoginMap[user];
        QListWidgetItem *item = new QListWidgetItem();

        QString itemText = QString("%1\n     Логин: %2")
                               .arg(user)
                               .arg(login);

        item->setText(itemText);
        item->setData(Qt::UserRole, login);
        item->setData(Qt::UserRole + 1, user);

        // Устанавливаем цвет фона
        if (action.contains("забанить")) {
            item->setBackground(QColor(255, 230, 230));
            item->setForeground(QBrush(QColor(194, 54, 22)));
        } else if (action.contains("разбанить")) {
            item->setBackground(QColor(230, 255, 230));
            item->setForeground(QBrush(QColor(39, 174, 96)));
        } else if (action.contains("удалить")) {
            item->setBackground(QColor(255, 240, 230));
            item->setForeground(QBrush(QColor(230, 126, 34)));
        } else {
            item->setForeground(QBrush(QColor(0, 0, 0)));
        }

        usersList->addItem(item);
    }

    if (users.isEmpty()) {
        QListWidgetItem *item = new QListWidgetItem("Пользователи не найдены");
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        item->setTextAlignment(Qt::AlignCenter);
        item->setForeground(QBrush(QColor(128, 128, 128))); // серый текст
        usersList->addItem(item);
    }

    mainLayout->addWidget(usersList);

    // Кнопки
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QString buttonStyle =
        "QPushButton {"
        "   padding: 10px 20px;"
        "   border: none;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "   font-family: Arial;"
        "   font-size: 11pt;"
        "   color: white;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   border: 2px solid #2c3e50;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #2c3e50;"
        "   color: white;"
        "}";

    if (action.contains("забанить")) {
        buttonBox->button(QDialogButtonBox::Ok)->setText("🚫 Забанить");
        buttonBox->button(QDialogButtonBox::Ok)->setStyleSheet(
            buttonStyle +
            "QPushButton {"
            "   background-color: #e74c3c;"
            "   color: white;"
            "}"
            "QPushButton:hover {"
            "   background-color: #c0392b;"
            "   border: 2px solid #922b21;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #922b21;"
            "   color: white;"
            "}"
            );
    } else if (action.contains("разбанить")) {
        buttonBox->button(QDialogButtonBox::Ok)->setText("✅ Разбанить");
        buttonBox->button(QDialogButtonBox::Ok)->setStyleSheet(
            buttonStyle +
            "QPushButton {"
            "   background-color: #27ae60;"
            "   color: white;"
            "}"
            "QPushButton:hover {"
            "   background-color: #229954;"
            "   border: 2px solid #1e8449;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #1e8449;"
            "   color: white;"
            "}"
            );
    } else if (action.contains("удалить")) {
        buttonBox->button(QDialogButtonBox::Ok)->setText("🗑️ Удалить");
        buttonBox->button(QDialogButtonBox::Ok)->setStyleSheet(
            buttonStyle +
            "QPushButton {"
            "   background-color: #e67e22;"
            "   color: white;"
            "}"
            "QPushButton:hover {"
            "   background-color: #d35400;"
            "   border: 2px solid #a84300;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #a84300;"
            "   color: white;"
            "}"
            );
    }

    buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");
    buttonBox->button(QDialogButtonBox::Cancel)->setStyleSheet(
        buttonStyle +
        "QPushButton {"
        "   background-color: #95a5a6;"
        "   color: white;"
        "}"
        "QPushButton:hover {"
        "   background-color: #7f8c8d;"
        "   border: 2px solid #6c7b7d;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #6c7b7d;"
        "   color: white;"
        "}"
        );

    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    mainLayout->addWidget(buttonBox);

    QString selectedLogin;

    // Обработчики событий
    connect(usersList, &QListWidget::itemSelectionChanged, [&]() {
        QList<QListWidgetItem*> selectedItems = usersList->selectedItems();
        if (!selectedItems.isEmpty() && !users.isEmpty()) {
            selectedLogin = selectedItems.first()->data(Qt::UserRole).toString();
            buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        } else {
            buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
    });

    // Двойной клик по пользователю
    connect(usersList, &QListWidget::itemDoubleClicked, [&](QListWidgetItem* item) {
        if (!users.isEmpty()) {
            selectedLogin = item->data(Qt::UserRole).toString();
            selectDialog->accept();
        }
    });

    connect(buttonBox, &QDialogButtonBox::accepted, selectDialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, selectDialog, &QDialog::reject);

    // Показываем диалог и возвращаем результат
    if (selectDialog->exec() == QDialog::Accepted) {
        return selectedLogin;
    }

    return "";
}

void MainWindow::onSendPublicClicked()
{
    QString message = publicMessageLineEdit->text().trimmed();

    if (message.isEmpty()) {
        showMessage("Введите сообщение!");
        return;
    }

    std::string command = "2 " + message.toStdString();
    std::string response = client.sendCommand(command);

    if (response.find("Message from") != std::string::npos) {
        messagesTextEdit->append(QString("[%1] Всем: %2")
                                     .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                                     .arg(message));
        publicMessageLineEdit->clear();
    }

    showMessage(QString::fromStdString(response));
}
