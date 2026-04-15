#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpacerItem>
#include "Chat.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Главное меню
    void onRegisterClicked();
    void onLoginClicked();
    void onAdminLoginClicked();
    void onShowUsersClicked();
    void onExitClicked();

    // Регистрация
    void onConfirmRegisterClicked();
    void onCancelRegisterClicked();

    // Вход
    void onConfirmLoginClicked();
    void onCancelLoginClicked();

    // Админ вход
    void onConfirmAdminLoginClicked();
    void onCancelAdminLoginClicked();

    // Панель пользователя
    void onSendPrivateClicked();
    void onSendPublicClicked();
    void onViewPrivateMessagesClicked();
    void onViewPublicMessagesClicked();
    void onLogoutClicked();

    // Админ панель
    void onAdminShowAllUsers();
    void onAdminShowOnlineUsers();
    void onAdminShowBannedUsers();
    void onAdminBanUser();
    void onAdminUnbanUser();
    void onAdminDeleteUser();
    void onAdminShowPrivateMessagesWarning();
    void onAdminShowPublicMessages();
    void onAdminLogout();

private:
    void createMainMenu();
    void createRegistrationPage();
    void createLoginPage();
    void createUserPanel();
    void createAdminLoginPage();
    void createAdminPanel();
    void showMessage(const QString &message);
    void updateStatus(const QString &status);
    void switchToPage(int pageIndex);
    void showUsersDialog();
    QString selectUserFromList();
    QString selectUserForAction(const QString& title, const QString& action);

    // Основные виджеты
    QStackedWidget *stackedWidget;
    QWidget *mainMenuPage;
    QWidget *registrationPage;
    QWidget *loginPage;
    QWidget *userPanelPage;
    QWidget *adminLoginPage;
    QWidget *adminPanelPage;

    // Элементы главного меню
    QLabel *welcomeLabel;
    QLabel *instructionLabel;
    QLabel *statusLabel;
    QPushButton *registerButton;
    QPushButton *loginButton;
    QPushButton *adminLoginButton;
    QPushButton *showUsersButton;
    QPushButton *exitButton;

    // Элементы регистрации
    QLineEdit *registerLoginEdit;
    QLineEdit *registerPasswordEdit;
    QLineEdit *registerNameEdit;
    QPushButton *confirmRegisterButton;
    QPushButton *cancelRegisterButton;

    // Элементы входа
    QLineEdit *loginLoginEdit;
    QLineEdit *loginPasswordEdit;
    QPushButton *confirmLoginButton;
    QPushButton *cancelLoginButton;

    // Элементы админ входа
    QLineEdit *adminLoginEdit;
    QLineEdit *adminPasswordEdit;
    QPushButton *confirmAdminLoginButton;
    QPushButton *cancelAdminLoginButton;

    // Элементы панели пользователя
    QTextEdit *messagesTextEdit;
    QLineEdit *publicMessageLineEdit;
    QPushButton *sendPrivateButton;
    QPushButton *sendPublicButton;
    QPushButton *viewPrivateMessagesButton;
    QPushButton *viewPublicMessagesButton;
    QPushButton *logoutButton;

    // Элементы админ панели
    QTextEdit *adminTextEdit;
    QPushButton *showAllUsersButton;
    QPushButton *showOnlineUsersButton;
    QPushButton *showBannedUsersButton;
    QPushButton *banUserButton;
    QPushButton *unbanUserButton;
    QPushButton *deleteUserButton;
    QPushButton *adminLogoutButton;

    ChatClient client;
};

#endif
