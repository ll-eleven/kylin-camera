#include "pictureviewpage.h"
#include <QDebug>

PictureViewPage::PictureViewPage()
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
    btnpage = new QWidget;
    text->setText(tr("Album"));
    text->setStyleSheet("QWidget{color:#A6A6A6};font-size:14px;font-family:SourceHanSansCN-Regular;");
    deleteBtn->setIcon(QIcon(":/image/delete.svg"));
    hlayout->setMargin(10);
    hlayout->addStretch(10);
    hlayout->addWidget(text);
    hlayout->addStretch(10);

    btnlayout->addSpacing(5000);
    btnlayout->addWidget(deleteBtn);
    btnpage->setLayout(btnlayout);

    vlayout->addLayout(hlayout);
    vlayout->addWidget(listWidget);
    vlayout->addWidget(btnpage);
    vlayout->setMargin(0);
    this->setLayout(vlayout);

    this->setStyleSheet("background-color:#000000");
    initListWidget();
//    initListView();

}

void PictureViewPage::initListWidget()
{
    listWidget->setIconSize(QSize(120,90));
    listWidget->setResizeMode(QListView::Adjust);
    listWidget->setViewMode(QListView::IconMode);
    listWidget->setMovement(QListView::Static);
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
