#include "pictureviewpage.h"


PictureViewPage::PictureViewPage()
{
//  this->setWindowFlags(Qt::FramelessWindowHint);
//  this->setAttribute(Qt::WA_TranslucentBackground, true);
  grid = new QGridLayout;
  text = new QLabel(this);
  listWidget = new QListWidget(this);
  vlayout = new QVBoxLayout;
  hlayout = new QHBoxLayout;
  text->setText("相册");
  text->setStyleSheet("color:#A6A6A6;font-size:14px;font-family:SourceHanSansCN-Regular;");
  hlayout->setMargin(10);
  hlayout->addStretch(10);
  hlayout->addWidget(text);
  hlayout->addStretch(10);

  vlayout->addLayout(hlayout);
  vlayout->addWidget(listWidget);
  vlayout->setMargin(0);
  this->setLayout(vlayout);

  this->setStyleSheet("background-color:#000000");
  initListWidget();
//  createListWidget();
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
