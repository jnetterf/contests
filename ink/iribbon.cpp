/* a weekend project */

#include "iribbon.h"
#include "ui_ribbon.h"

#include <QColorDialog>
#include <QButtonGroup>

IRibbon::IRibbon(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::Ribbon)
{
    ui->setupUi(this);
    QButtonGroup* x=new QButtonGroup(this);
    x->addButton(ui->tb_left);
    x->addButton(ui->tb_center);
    x->addButton(ui->tb_right);
    x->addButton(ui->tb_justify);
}

IRibbon::~IRibbon()
{
    delete ui;
}

void IRibbon::init(IDocument* doc)
{
    s_doc=doc;

    connect(ui->tb_bold,SIGNAL(clicked(bool)),doc->s_select,SLOT(setBold(bool)));
    connect(ui->tb_copy,SIGNAL(clicked()),doc->s_select,SLOT(copy()));
    connect(ui->tb_cut,SIGNAL(clicked()),doc->s_select,SLOT(cut()));
    connect(ui->tb_italic,SIGNAL(clicked(bool)),doc->s_select,SLOT(setItalic(bool)));
    connect(ui->tb_paste,SIGNAL(clicked()),doc->s_select,SLOT(paste()));
    connect(ui->tb_strike,SIGNAL(clicked(bool)),doc->s_select,SLOT(setStrike(bool)));
    connect(ui->tb_subscript,SIGNAL(clicked(bool)),doc->s_select,SLOT(setSubscript(bool)));
    connect(ui->tb_superscript,SIGNAL(clicked(bool)),doc->s_select,SLOT(setSuperscript(bool)));
    connect(ui->tb_underline,SIGNAL(clicked(bool)),doc->s_select,SLOT(setUnderlined(bool)));
    connect(ui->cb_font,SIGNAL(currentIndexChanged(QString)),doc->s_select,SLOT(setFonttype(QString)));
    connect(ui->cb_size,SIGNAL(valueChanged(int)),doc->s_select,SLOT(setFontsize(int)));
    connect(ui->tb_left,SIGNAL(clicked(bool)),doc->s_select,SLOT(setAlignLeft(bool)));
    connect(ui->tb_center,SIGNAL(clicked(bool)),doc->s_select,SLOT(setAlignCenter(bool)));
    connect(ui->tb_justify,SIGNAL(clicked(bool)),doc->s_select,SLOT(setAlignJustify(bool)));
    connect(ui->tb_right,SIGNAL(clicked(bool)),doc->s_select,SLOT(setAlignRight(bool)));
    connect(ui->tb_undo,SIGNAL(clicked()),this,SLOT(undo()));
    connect(ui->tb_fg,SIGNAL(clicked()),this,SLOT(selectColour()));
    connect(ui->tb_bg,SIGNAL(clicked()),this,SLOT(selectColour()));

    connect(doc->s_select,SIGNAL(boldChanged(bool)),ui->tb_bold,SLOT(setChecked(bool)));
    connect(doc->s_select,SIGNAL(canCutChanged(bool)),ui->tb_copy,SLOT(setEnabled(bool)));
    connect(doc->s_select,SIGNAL(canCutChanged(bool)),ui->tb_cut,SLOT(setEnabled(bool)));
    connect(doc->s_select,SIGNAL(italicChanged(bool)),ui->tb_italic,SLOT(setChecked(bool)));
    connect(doc->s_select,SIGNAL(canPasteChanged(bool)),ui->tb_paste,SLOT(setEnabled(bool)));
    connect(doc->s_select,SIGNAL(strikeChanged(bool)),ui->tb_strike,SLOT(setChecked(bool)));
    connect(doc->s_select,SIGNAL(subscriptChanged(bool)),ui->tb_subscript,SLOT(setChecked(bool)));
    connect(doc->s_select,SIGNAL(superscriptChanged(bool)),ui->tb_superscript,SLOT(setChecked(bool)));
    connect(doc->s_select,SIGNAL(underlinedChanged(bool)),ui->tb_underline,SLOT(setChecked(bool)));
    connect(doc->s_select,SIGNAL(fonttypeChanged(QString)),ui->cb_font,SLOT(setEditText(QString)));
    connect(doc->s_select,SIGNAL(fontsizeChanged(int)),ui->cb_size,SLOT(setValue(int)));
}

void IRibbon::selectColour()
{
    Q_ASSERT(sender()==ui->tb_fg||sender()==ui->tb_bg);
    QColor r = QColorDialog::getColor(Qt::white,this);
    if(!r.isValid()) return;
    if(sender()==ui->tb_fg) s_doc->s_select->setForeground(r);
    else s_doc->s_select->setBackground(r);
}
