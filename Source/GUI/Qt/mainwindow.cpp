/*  Copyright (c) MediaArea.net SARL. All Rights Reserved.
 *
 *  Use of this source code is governed by a GPLv3+/MPLv2+ license that can
 *  be found in the License.html file in the root of the source tree.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "policiesmenu.h"
#include "ruleedit.h"

#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QActionGroup>
#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QLabel>
#include <QUrl>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QDialogButtonBox>
#if QT_VERSION >= 0x050200
    #include <QFontDatabase>
#endif
#include <sstream>

//***************************************************************************
// Constructor / Desructor
//***************************************************************************

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Groups
    QActionGroup* ToolGroup = new QActionGroup(this);
    ToolGroup->addAction(ui->actionConch);
    ToolGroup->addAction(ui->actionInfo);
    ToolGroup->addAction(ui->actionTrace);
    ToolGroup->addAction(ui->actionSchematron);
    ToolGroup->addAction(ui->actionPolicies);
    QActionGroup* FormatGroup = new QActionGroup(this);
    FormatGroup->addAction(ui->actionText);
    FormatGroup->addAction(ui->actionXml);
    
    // Visual elements
    Layout=new QVBoxLayout(this);
    ui->centralWidget->setLayout(Layout);
    MainText=NULL;
    DragDrop_Image=NULL;
    DragDrop_Text=NULL;
    policiesMenu = NULL;
    ruleEdit = NULL;

    // Drag n drop
    setAcceptDrops(true);

    // Window
    setWindowIcon(QIcon(":/icon/icon.png"));
    move(QApplication::desktop()->screenGeometry().width()/4, QApplication::desktop()->screenGeometry().height()/4);
    resize(QApplication::desktop()->screenGeometry().width()/2, QApplication::desktop()->screenGeometry().height()/2);

    // Default
    on_actionConch_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//***************************************************************************
// Functions
//***************************************************************************

//---------------------------------------------------------------------------
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

//---------------------------------------------------------------------------
void MainWindow::dropEvent(QDropEvent *Event)
{
    if (Event->mimeData()->hasUrls())
    {
        QList<QUrl> urls=Event->mimeData()->urls();

        C.List.clear();
        for (int Pos=0; Pos<urls.size(); Pos++)
            C.List.push_back(urls[Pos].toLocalFile().toStdWString());
    }

    Run();
}

void MainWindow::policy_to_delete(int index)
{
    //Delete policy
    C.policies.erase_policy(index);
}

//***************************************************************************
// Helpers
//***************************************************************************

//---------------------------------------------------------------------------
void MainWindow::Run()
{
    if (C.Tool == Core::tool_MediaPolicies)
    {
        displayPoliciesMenu();
        return;
    }

    if (C.List.empty())
    {
        createDragDrop();
        return;
    }
    createMainText();

    MainText->setPlainText(QString().fromStdWString(C.Run().c_str()));
}

//---------------------------------------------------------------------------
QString MainWindow::ask_for_schematron_file()
{
    QString file=QFileDialog::getOpenFileName(this, "Open file", "", "Schematron file (*.sch);;All (*.*)", 0, QFileDialog::DontUseNativeDialog);
    return file;
}

void MainWindow::exporting_to_schematron_file()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Policy"),
                                                    "", tr("Schematron (*.sch)"));

    //TODO: get policy number
    C.policies.export_schematron(filename.toStdString().c_str(), 0);
}

//***************************************************************************
// Slots
//***************************************************************************

//---------------------------------------------------------------------------
void MainWindow::on_actionOpen_triggered()
{
    QStringList List=QFileDialog::getOpenFileNames(this, "Open file", "", "Video files (*.avi *.mkv *.mov *.mxf *.mp4);;All (*.*)", 0, QFileDialog::DontUseNativeDialog);
    if (List.empty())
        return;

    C.List.clear();
    for (int Pos=0; Pos<List.size(); Pos++)
        C.List.push_back(List[Pos].toStdWString());

    Run();
}

//---------------------------------------------------------------------------
void MainWindow::on_actionCloseAll_triggered()
{
    C.List.clear();

    Run();
}

//---------------------------------------------------------------------------
void MainWindow::on_actionSavePolicies_triggered()
{
    exporting_to_schematron_file();
}

//---------------------------------------------------------------------------
void MainWindow::on_actionConch_triggered()
{
    ui->menuFormat->setEnabled(false);
    ui->actionText->setEnabled(false);
    ui->actionXml->setEnabled(false);
    ui->actionText->setChecked(true);

    C.Tool=Core::tool_MediaConch;
    C.Format=Core::format_Text;
    Run();
}

//---------------------------------------------------------------------------
void MainWindow::on_actionInfo_triggered()
{
    ui->menuFormat->setEnabled(true);
    ui->actionText->setEnabled(true);
    ui->actionXml->setEnabled(true);

    C.Tool=Core::tool_MediaInfo;
    Run();
}

//---------------------------------------------------------------------------
void MainWindow::on_actionTrace_triggered()
{
    ui->menuFormat->setEnabled(true);
    ui->actionText->setEnabled(true);
    ui->actionXml->setEnabled(true);

    C.Tool=Core::tool_MediaTrace;
    Run();
}

//---------------------------------------------------------------------------
void MainWindow::on_actionSchematron_triggered()
{
    if (!C.policies.policies.size() && !C.SchematronFile.length())
    {
        QString file = ask_for_schematron_file();
        if (file.length())
        {
            if (C.policies.import_schematron(file.toStdString().c_str()).length())
            {
                C.SchematronFile = file.toStdWString();
            }
        }
    }
    ui->menuFormat->setEnabled(true);
    ui->actionText->setEnabled(false);
    ui->actionXml->setEnabled(true);
    ui->actionXml->setChecked(true);

    C.Tool=Core::tool_MediaSchematron;
    Run();
}

//---------------------------------------------------------------------------
void MainWindow::on_actionPolicies_triggered()
{
    ui->menuFormat->setEnabled(true);
    ui->actionText->setEnabled(false);
    ui->actionXml->setEnabled(true);
    ui->actionXml->setChecked(true);

    C.Tool=Core::tool_MediaPolicies;
    Run();
}

//---------------------------------------------------------------------------
void MainWindow::on_actionText_triggered()
{
    C.Format=Core::format_Text;
    Run();
}

//---------------------------------------------------------------------------
void MainWindow::on_actionXml_triggered()
{
    C.Format=Core::format_Xml;
    Run();
}

//---------------------------------------------------------------------------
void MainWindow::on_actionChooseSchematron_triggered()
{
    QString file = ask_for_schematron_file();
    if (file.length())
    {
        if (C.policies.import_schematron(file.toStdString().c_str()).length())
        {
            C.SchematronFile = file.toStdWString();
        }
    }
    Run();
}

//---------------------------------------------------------------------------
void MainWindow::on_importSchematron()
{
    QString file = ask_for_schematron_file();
    String ret = C.policies.import_schematron(file.toStdString().c_str());
    if (ret.length() && policiesMenu) {
        policiesMenu->add_error(ret);
    }

    Run();
}

//---------------------------------------------------------------------------
void MainWindow::on_addNewPolicy()
{
    displayRuleEdit(-1);
}

//---------------------------------------------------------------------------
void MainWindow::on_editPolicy(int row, int)
{
    displayRuleEdit(row);
}

//---------------------------------------------------------------------------
void MainWindow::on_editPolicy()
{
    QList<QTableWidgetItem *> list = policiesMenu->get_policies_table()->selectedItems();
    if (list.isEmpty())
    {
        return;
    }

    QTableWidgetItem *item = list.first();

    if (!item)
    {
        return;
    }
    string name = item->text().toStdString();
    displayRuleEdit(item->row());
}

//---------------------------------------------------------------------------
void MainWindow::on_RuleEditRejected()
{
    clearVisualElements();
    displayPoliciesMenu();
}

//---------------------------------------------------------------------------
void MainWindow::on_RuleEditAccepted()
{
    string new_name = ruleEdit->get_new_name();
    if (!new_name.length())
    {
        ruleEdit->add_error(__T("Policy must have a name"));
        ruleEdit->show_errors();
        return;
    }

    const vector<Assert *> vec = ruleEdit->get_asserts();
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (!vec[i])
        {
            continue;
        }
        if (!vec[i]->description.length())
        {
            ruleEdit->add_error(__T("Assert must have a name"));
            ruleEdit->show_errors();
            return;
        }
    }

    //TODO: more than one policy
    int row = -1;
    if (policiesMenu)
    {
        QList<QTableWidgetItem *> list = policiesMenu->get_policies_table()->selectedItems();
        if (!list.isEmpty())
        {
            row = list.first()->row();
            if (new_name != list.first()->text().toStdString())
            {
                Policy *p = C.policies.policies[0];
                p->patterns[row]->name = new_name;
            }
        }
    }
    if (row == -1)
    {
        if (C.policies.policies.size() == 0)
        {
            Policy *p = new Policy;
            C.policies.policies.push_back(p);
        }
        Pattern *pat = new Pattern;
        pat->name = new_name;
        C.policies.policies[0]->patterns.push_back(pat);
        row = C.policies.policies[0]->patterns.size() - 1;
    }

    // TODO: More than one rule by pattern
    for (size_t i = 0; i < C.policies.policies[0]->patterns[row]->rules.size(); ++i)
    {
        delete C.policies.policies[0]->patterns[row]->rules[i];
    }
    C.policies.policies[0]->patterns[row]->rules.clear();

    Rule *r = new Rule;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (!vec[i])
        {
            continue;
        }
        Assert *a = new Assert(*vec[i]);
        r->asserts.push_back(a);
    }
    C.policies.policies[0]->patterns[row]->rules.push_back(r);

    clearVisualElements();
    displayPoliciesMenu();
}

//***************************************************************************
// Visual elements
//***************************************************************************

//---------------------------------------------------------------------------
void MainWindow::clearVisualElements()
{
    if (MainText)
    {
        Layout->removeWidget(MainText);
        delete MainText; MainText=NULL;
    }

    if (policiesMenu)
    {
        Layout->removeWidget(policiesMenu);
        delete policiesMenu; policiesMenu=NULL;
    }

    if (ruleEdit)
    {
        Layout->removeWidget(ruleEdit);
        delete ruleEdit;
        ruleEdit=NULL;
    }

    if (DragDrop_Image)
    {
        Layout->removeWidget(DragDrop_Image);
        Layout->removeWidget(DragDrop_Text);
        delete DragDrop_Image; DragDrop_Image=NULL;
        delete DragDrop_Text; DragDrop_Text=NULL;
    }
}

//---------------------------------------------------------------------------
void MainWindow::createMainText()
{
    if (MainText)
        return;

    clearVisualElements();

    MainText=new QPlainTextEdit(this);
    MainText->setReadOnly(true);
    #if QT_VERSION >= 0x050200
        MainText->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    #endif
    Layout->addWidget(MainText);
}

//---------------------------------------------------------------------------
void MainWindow::createDragDrop()
{
    if (DragDrop_Image)
        return;

    clearVisualElements();

    QFont Font;
    Font.setPointSize(Font.pointSize()*4);

    DragDrop_Image=new QLabel(this);
    DragDrop_Image->setAlignment(Qt::AlignCenter);
    DragDrop_Image->setPixmap(QPixmap(":/icon/dropfiles.png").scaled(256, 256));
    Layout->addWidget(DragDrop_Image);

    DragDrop_Text=new QLabel(this);
    DragDrop_Text->setAlignment(Qt::AlignCenter);
    DragDrop_Text->setFont(Font);
    QPalette Palette(DragDrop_Text->palette());
    Palette.setColor(QPalette::WindowText, Qt::darkGray);
    DragDrop_Text->setPalette(Palette);
    DragDrop_Text->setText("Drop video file(s) here");
    Layout->addWidget(DragDrop_Text);
}

//---------------------------------------------------------------------------
void MainWindow::createPoliciesMenu()
{
    if (policiesMenu) {
        policiesMenu->clear();
        return;
    }
    clearVisualElements();
    policiesMenu = new PoliciesMenu(this);
    QObject::connect(policiesMenu->get_schematron_button(), SIGNAL(clicked()),
                     this, SLOT(on_importSchematron()));
    QObject::connect(policiesMenu->get_addNewPolicy_button(), SIGNAL(clicked()),
                     this, SLOT(on_addNewPolicy()));
    QObject::connect(policiesMenu->get_policies_table(), SIGNAL(cellDoubleClicked(int, int)),
                     this, SLOT(on_editPolicy(int, int)));
    QObject::connect(policiesMenu->get_editPolicy_button(), SIGNAL(clicked()),
                     this, SLOT(on_editPolicy()));
}

//---------------------------------------------------------------------------
void MainWindow::displayPoliciesMenu()
{
    createPoliciesMenu();

    Layout->addWidget(policiesMenu);
    policiesMenu->show_errors();

    if (!C.policies.policies.size())
        return;
    //TODO: Pattern --> Policy
    vector<Pattern *>::iterator it = C.policies.policies[0]->patterns.begin();
    vector<Pattern *>::iterator ite = C.policies.policies[0]->patterns.end();
    for (; it != ite; ++it)
    {
        policiesMenu->add_policy((*it)->name);
    }
}

//---------------------------------------------------------------------------
void MainWindow::createRuleEdit()
{
    if (ruleEdit) {
        ruleEdit->clear();
        return;
    }

    policiesMenu->hide();
    ruleEdit = new RuleEdit(this);
    QObject::connect(ruleEdit->get_validation_button(), SIGNAL(accepted()),
                     this, SLOT(on_RuleEditAccepted()));
    QObject::connect(ruleEdit->get_validation_button(), SIGNAL(rejected()),
                     this, SLOT(on_RuleEditRejected()));
}

//---------------------------------------------------------------------------
void MainWindow::displayRuleEdit(int row)
{
    createRuleEdit();
    Layout->addWidget(ruleEdit);
    ruleEdit->show_errors();

    if (row != -1)
    {
        ruleEdit->set_name(C.policies.policies[0]->patterns[row]->name);
        for (size_t i = 0; i < C.policies.policies[0]->patterns[row]->rules.size(); ++i)
        {
            Rule *r = C.policies.policies[0]->patterns[row]->rules[i];
            for (size_t j = 0; j < r->asserts.size(); ++j)
            {
                ruleEdit->add_assert(r->asserts[j]);
            }
        }
    }
}

//***************************************************************************
// HELPER
//***************************************************************************

//---------------------------------------------------------------------------
QString MainWindow::getSelectedPolicyName()
{
    QList<QTableWidgetItem *> list = policiesMenu->get_policies_table()->selectedItems();

    if (list.isEmpty())
    {
        return QString();
    }

    QTableWidgetItem *item = list.first();

    return item->text();
}
