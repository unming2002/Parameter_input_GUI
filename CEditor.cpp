#include "CEditor.h"
#include "common.h"

CEditor::CEditor(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//ui.treeWidget->setWindowTitle(QStringList() << "Key");

	#pragma region Header setting
	{
		ui.treeWidget->setHeaderLabels(QStringList() << "Key" << "Value");
		auto pHeader = ui.treeWidget->header();
		pHeader->setDefaultAlignment(Qt::AlignHCenter);
		pHeader->resizeSection(0, 290);
		pHeader->resizeSection(1, 100);
	}
	#pragma endregion

	QList<int> aSizes;
	aSizes << 400 << 220;
	ui.splitter->setSizes(aSizes);
}

CEditor::~CEditor()
{
	
}

void CEditor::setDataTree(CTreeNode * pNode)
{
	if (pNode != nullptr)
	{
		QTreeWidget* pTreeWidget = ui.treeWidget;
		pTreeWidget->insertTopLevelItem(0, pNode);
		pNode->forEachNode([pTreeWidget](CTreeNode* pNode) {
			pNode->setValueEditorToTreeWidget();
			pNode->setExpanded(true);
		});
	}
}

void CEditor::slotShowBasic()
{
	getTree()->hideNode(CTreeNode::BasicGroup, !ui.cbBasic->isChecked());
	updateShowAllStatus();
}

void CEditor::slotShowAdvance()
{
	getTree()->hideNode(CTreeNode::AdvanceGroup, !ui.cbAdvance->isChecked());
	updateShowAllStatus();
}

void CEditor::slotShowExpert()
{
	getTree()->hideNode(CTreeNode::ExpertGroup, !ui.cbExpert->isChecked());
	updateShowAllStatus();
}

void CEditor::slotShowAll()
{
	switch (ui.cbAll->checkState())
	{
	case Qt::Checked:
		ui.cbBasic->setChecked(true);
		ui.cbAdvance->setChecked(true);
		ui.cbExpert->setChecked(true);
		break;

	case Qt::Unchecked:
		ui.cbBasic->setChecked(false);
		ui.cbAdvance->setChecked(false);
		ui.cbExpert->setChecked(false);
		break;

	case Qt::PartiallyChecked:
		ui.cbAll->setCheckState(Qt::Checked);
		ui.cbBasic->setChecked(true);
		ui.cbAdvance->setChecked(true);
		ui.cbExpert->setChecked(true);
	}

	slotShowBasic();
	slotShowAdvance();
	slotShowExpert();
}

void CEditor::slotLoadFile()
{
	loadJsonFileHelper([this](const QJsonObject& mJsonObj) {
		CTreeNode* pNode = getTree();
		if(pNode!=nullptr)
			return pNode->read(mJsonObj);
		return false;
	});
}

void CEditor::slotSaveFile()
{
	CTreeNode* pNode = getTree();
	if (pNode != nullptr)
	{
		QJsonObject mJsonObj;
		pNode->write(mJsonObj);
		saveJsonFileHelper(mJsonObj);
	}
}

void CEditor::closeEvent(QCloseEvent*)
{
	CTreeNode* pNode = getTree();
	if (pNode != nullptr)
	{
		QTreeWidget* pTreeWidget = ui.treeWidget;
		pNode->forEachNode([pTreeWidget](CTreeNode* pSubNode) {
			pSubNode->removeValueEditorFromTreeWidget();
		});
		ui.treeWidget->takeTopLevelItem(0);
	}
}

void CEditor::showEvent(QShowEvent *event)
{
	slotShowBasic();
	slotShowAdvance();
	slotShowExpert();

	QWidget::showEvent(event);
}

void CEditor::updateShowAllStatus()
{
	if (ui.cbBasic->isChecked() && ui.cbAdvance->isChecked() && ui.cbExpert->isChecked())
		ui.cbAll->setCheckState(Qt::Checked);
	else if ((!ui.cbBasic->isChecked()) && (!ui.cbAdvance->isChecked()) && (!ui.cbExpert->isChecked()))
		ui.cbAll->setCheckState(Qt::Unchecked);
	else
		ui.cbAll->setCheckState(Qt::PartiallyChecked);
}

void CEditor::slotItemChanged(QTreeWidgetItem* pCurrent, QTreeWidgetItem* pPrevious)
{
	if (pCurrent != nullptr)
	{
		CTreeNode* pCurrNode = (CTreeNode*)pCurrent;
		ui.textEdit->setDocument(pCurrNode->m_pInforDocument);;
	}
}
