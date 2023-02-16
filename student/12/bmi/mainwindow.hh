#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_countButton_clicked();

    void on_weightLineEdit_editingFinished();

    void on_heightLineEdit_editingFinished();

    void on_weightLineEdit_textChanged(const QString &arg1);

    void on_heightLineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    double weight_ = 0;
    double height_ = 1;
};
#endif // MAINWINDOW_HH
