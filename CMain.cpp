#include "CMain.h"
#include "common.h"
#include "NodeUltrapica.h"
#include "NodeUltraUtility.h"
#include "NodeUltraSparts.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>

#include <iostream>

using namespace std;

CMain::CMain(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// Groupped nodes
	{
		m_mapGroups["ultrautility"] = { new CUltraUtility(nullptr),ui.butUtility };

		m_mapGroups["ultrapica"] = { new CUltrapica(nullptr), ui.butPICA };

		m_mapGroups["ultrasparts"] = { new CUltrasparts(nullptr), ui.butSPARTS };

		//TODO: undefined groups, replace "CGroupNode" with well-defined data class
		m_mapGroups["ultraflumod"] = { new CGroupNode("ultraflumod", CTreeNode::NoGroup, nullptr), ui.butFluMod };
		m_mapGroups["UltraNSMod"] = { new CGroupNode("UltraNSMod", CTreeNode::NoGroup, nullptr), ui.butNSMod };
		m_mapGroups["UltraProfiling"] = { new CGroupNode("UltraProfiling", CTreeNode::NoGroup, nullptr),ui.butProfiling };
		m_mapGroups["UltraChemRateMod"] = { new CGroupNode("UltraChemRateMod", CTreeNode::NoGroup, nullptr), ui.butChemRateMod };
	}

	m_pEditor = new CEditor();

	// setup for each groupped node
	CEditor* pEditor = m_pEditor;
	for (auto& rItem : m_mapGroups)
	{
		CTreeNode* pNode = rItem.second.pTreeNode;

		connect(rItem.second.pButton, &QPushButton::clicked, [pEditor, pNode]() {
			pEditor->setDataTree(pNode);
			pEditor->show();
		});

		rItem.second.pButton->hide();
		if(rItem.first == "ultrautility") rItem.second.pButton->show();
		if(rItem.first == "ultrapica") rItem.second.pButton->show();
		if(rItem.first == "ultrasparts") rItem.second.pButton->show();
		//if(rItem.first == "ultraflumod") rItem.second.pButton->show();
	}
}

void CMain::slotLoadProject()
{
	loadJsonFileHelper([this](const QJsonObject& mJsonObj) {
		for (auto& rItem : m_mapGroups)
		{
			if (mJsonObj.contains(rItem.first))
			{
				rItem.second.pButton->show();
				rItem.second.pTreeNode->read(mJsonObj);
			}
			else
			{
				rItem.second.pButton->hide();
			}
		}

		return true; //TODO: check if file is correct
		//}
	});
}

void CMain::slotSaveProject()
{
	// write JSON
	QJsonObject mObj;

	// construct data tree that visible
	for (auto& rItem : m_mapGroups)
	{
		if (!rItem.second.pButton->isHidden())
			rItem.second.pTreeNode->write(mObj);
	}

	saveJsonFileHelper(mObj);
}

void CMain::slotPreference()
{
}
