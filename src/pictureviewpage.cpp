#include "pictureviewpage.h"
#include <QDebug>

PictureViewPage::PictureViewPage(QWidget *parent)
    : QWidget(parent)
{
//  this->setWindowFlags(Qt::FramelessWindowHint);
//  this->setAttribute(Qt::WA_TranslucentBackground, true);
    grid = new QGridLayout;
    deleteBtn = new QPushButton;
    text = new QLabel(this);
    listWidget = new QListWidget(this);
//    listview = new QListView(this);
    vlayout = new QVBoxLayout;
    hlayout = new QHBoxLayout;
    btnlayout = new QHBoxLayout;
    title = new QWidget;
    btnpage = new QWidget;
    text->setText(tr("Album"));
    text->setStyleSheet("font-size:16px;font-family:SourceHanSansCN-Regular;");
    deleteBtn->setIcon(QIcon(":/image/delete.svg"));
    deleteBtn->setFlat(true);
    hlayout->setMargin(0);
    hlayout->addStretch(10);
    hlayout->addWidget(text);
    hlayout->addStretch(10);
    btnlayout->addSpacing(5000);
    btnlayout->addWidget(deleteBtn);
    btnpage->setLayout(btnlayout);
    btnpage->setFixedHeight(40);
    title->setLayout(hlayout);
    title->setFixedHeight(30);
    deleteBtn->setFlat(true);

    vlayout->addWidget(title);
    vlayout->addWidget(listWidget);
    vlayout->addWidget(btnpage);
    vlayout->setMargin(0);
    this->setLayout(vlayout);

    initListWidget();
//    initListView();

}

void PictureViewPage::initListWidget()
{
    listWidget->setIconSize(QSize(120,90));
    listWidget->setResizeMode(QListView::Adjust);
    listWidget->setViewMode(QListView::IconMode);
    listWidget->setMovement(QListView::Static);
    listWidget->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    listWidget->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    listWidget->setFrameShape(QListWidget::NoFrame);
    listWidget->setSpacing(0);
    listWidget->setStyleSheet("background-color:#000000");
    listWidget->horizontalScrollBar()->setDisabled(true);
    imageLabel = new QLabel;
    imageLabel->setWindowTitle("TITLE");
}


void PictureViewPage::initListView(){
    listview->setIconSize(QSize(120,90));
    listview->setViewMode(QListView::IconMode);
    listview->setResizeMode(QListView::Adjust);
    listview->setMovement(QListView::Static);
}
