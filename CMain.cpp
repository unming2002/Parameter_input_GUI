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

	// First layer node
	m_pRootNode = new CGroupNode("p3_multiphysics", nullptr);

	// Groupped nodes
	{
		m_mapGroups["ultrautility"] = { new CUltraUtility(m_pRootNode),ui.butUtility };

		m_mapGroups["ultrapica"] = { new CUltrapica(m_pRootNode), ui.butPICA };

		m_mapGroups["ultrasparts"] = { new CUltrasparts(m_pRootNode), ui.butSPARTS };

		//TODO: undefined groups, replace "CGroupNode" with well-defined data class
		m_mapGroups["ultraflumod"] = { new CGroupNode("ultraflumod", m_pRootNode), ui.butFluMod };
		m_mapGroups["UltraNSMod"] = { new CGroupNode("UltraNSMod", m_pRootNode), ui.butNSMod };
		m_mapGroups["UltraProfiling"] = { new CGroupNode("UltraProfiling", m_pRootNode),ui.butProfiling };
		m_mapGroups["UltraChemRateMod"] = { new CGroupNode("UltraChemRateMod", m_pRootNode), ui.butChemRateMod };
	}

	m_pEditor = new CEditor();

	// setup for each groupped node
	CEditor* pEditor = m_pEditor;
	for (auto& rItem : m_mapGroups)
	{
		CTreeNode* pNode = rItem.second.pTreeNode;

		m_pRootNode->removeChild(pNode);

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
		// Get first layer node (root)
		//if (mJsonObj.contains("p3_multiphysics"))
		//{
		// setup full data tree
		for (auto& it : mJsonObj.keys())
		{
			if (m_mapGroups.find(it.toUtf8().constData()) != m_mapGroups.end())
			{
				m_mapGroups[it.toUtf8().constData()].pTreeNode->read(mJsonObj);
			}
			else
			{
				std::cout << "Unknown key value:" << it.toUtf8().constData() << endl;
			}
		}

		for (auto& rItem : m_mapGroups)
			m_pRootNode->addChild(rItem.second.pTreeNode);


		// read all data
		//m_pRootNode->read(mJsonObj);

		//QJsonObject mSubNode = mJsonObj["p3_multiphysics"].toObject();

		QJsonObject mSubNode = mJsonObj;

		// check if grouped node existed
		for (auto& rItem : m_mapGroups)
		{
			if (mSubNode.contains(rItem.first.c_str()))
				rItem.second.pButton->show();
			else
				rItem.second.pButton->hide();

			// need to remove from parent for used in QTreeWidget
			m_pRootNode->removeChild(rItem.second.pTreeNode);
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
		// re-add to root node for write
		if (!rItem.second.pButton->isHidden())
			m_pRootNode->addChild(rItem.second.pTreeNode);

		if (!rItem.second.pButton->isHidden())
			rItem.second.pTreeNode->write(mObj);
	}

	// m_pRootNode->write(mObj);

	for (auto& rItem : m_mapGroups)
		m_pRootNode->removeChild(rItem.second.pTreeNode);

	saveJsonFileHelper(mObj);
}

void CMain::slotPreference()
{
}
