/*! \author Amarildo Rajta \date 2023-01-07
 *  \details DT079G Project - Forrest Jump game */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


//extern Game* game;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief The MainWindow class
 */
class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    /*!
     * \brief The MainWindow class constructor
     * \param parent The QWidget to use as a parent class, defaulted to nullptr
     */
    MainWindow(QWidget *parent = nullptr);
    /*!
     * \brief The MainWindow class destructor
     */
    ~MainWindow();

private slots:
    /*!
     * \brief When clicking the button, close this window and start game
     */
    void on_pushButton_clicked();

private:
    /*!
     * \brief Subclass of MainWindow
     */
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
