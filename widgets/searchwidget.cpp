#include "searchwidget.h"
#include "global_util/util.h"

#include <QHBoxLayout>
#include <QEvent>
#include <QDebug>
#include <QKeyEvent>

SearchWidget::SearchWidget(QWidget *parent) :
    QFrame(parent),
    m_searchEdit(new QLineEdit)
{
    setObjectName("SearchFrame");
    m_searchEdit->setFixedSize(290, 30);

    m_searchEdit->setFocus();
    m_searchEdit->setContextMenuPolicy(Qt::NoContextMenu);
    m_searchEdit->setStyleSheet("background-color:transparent;"
                                "border:2px solid #666;"
                                "border-radius:5px;"
                                "color:white;");

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addStretch();
    mainLayout->addWidget(m_searchEdit);
    mainLayout->addStretch();

    setFocusPolicy(Qt::NoFocus);
    setFocusProxy(m_searchEdit);
    setLayout(mainLayout);
    m_searchEdit->setStyleSheet(getQssFromFile(":/skin/qss/searchwidget.qss"));

    connect(m_searchEdit, &QLineEdit::textChanged, [this] {
        emit searchTextChanged(m_searchEdit->text());
    });
}

QLineEdit *SearchWidget::edit()
{
    return m_searchEdit;
}

void SearchWidget::clearSearchContent()
{
    m_searchEdit->clear();
}

bool SearchWidget::event(QEvent *e)
{
    if (e->type() == QEvent::FocusIn)
        m_searchEdit->setFocus();

    return QWidget::event(e);
}