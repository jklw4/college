#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QtWidgets/Qwidget>
#include <QLineEdit>
#include <QDropEvent>
#include <QMimeData>
#include <QDragEnterEvent>

class CustomLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    CustomLineEdit(QWidget *parent = nullptr);
    ~CustomLineEdit();

protected:
    //< 拖动文件到窗口 触发
    void dragEnterEvent(QDragEnterEvent *event);
    //< 拖动文件到窗口移动文件 触发
    void dragMoveEvent(QDragMoveEvent *event);
    //< 拖动文件到窗口释放文件触发
    void dropEvent(QDropEvent *event);
};


#endif // CUSTOMLINEEDIT_H
