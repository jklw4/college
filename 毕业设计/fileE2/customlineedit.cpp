#include "customlineedit.h"

CustomLineEdit::CustomLineEdit(QWidget *parent) : QLineEdit(parent)
{
    setAcceptDrops(true);
}

CustomLineEdit::~CustomLineEdit()
{

}

void CustomLineEdit::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction(); //事件数据中存在路径，方向事件
    else
        event->ignore();
}

void CustomLineEdit::dragMoveEvent(QDragMoveEvent *event)
{

}

void CustomLineEdit::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls())
    {
        QList<QUrl> urls = mimeData->urls();
        QString fileName = urls.at(0).toLocalFile();
        setText(fileName);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
