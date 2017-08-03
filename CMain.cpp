#include "CMain.h"
#include "NodeUltrapica.h"
#include "NodeUltraUtility.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>

static const QString qProjectFileFilter = QObject::tr("Project file (*.json);;All files (*.*)");

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
		
		//TODO: undefined groups, replace "CGroupNode" with well-defined data class
		m_mapGroups["UltraFluMod"] = { new CGroupNode("UltraFluMod", m_pRootNode), ui.butFluMod };
		m_mapGroups["UltraSPARATS"] = { new CGroupNode("UltraSPARATS", m_pRootNode), ui.butSPARATS };
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
	}
}

void CMain::slotLoadProject()
{
	QString sFileName = QFileDialog::getOpenFileName(this, tr("Open a project file"), "", qProjectFileFilter);
	if (sFileName != "")
	{
		QFile loadFile(sFileName);
		if (loadFile.open(QIODevice::ReadOnly))
		{
			// Load JSON File
			QByteArray saveData = loadFile.readAll();
			QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
			if (!loadDoc.isNull())
			{
				QJsonObject mJsonObj = loadDoc.object();
				// Get first layer node (root)
				if (mJsonObj.contains("p3_multiphysics"))
				{
					// setup full data tree
					for (auto& rItem : m_mapGroups)
						m_pRootNode->addChild(rItem.second.pTreeNode);

					// read all data
					m_pRootNode->read(mJsonObj);

					QJsonObject mSubNode = mJsonObj["p3_multiphysics"].toObject();
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

					return;
				}
			}
		}
		QMessageBox::critical(this, tr("Project File Open Failed"), tr("Can't read the project file:\n\n  ") + sFileName);
	}
}

void CMain::slotSaveProject()
{
	QString sFileName = QFileDialog::getSaveFileName(this, tr("Save the project file"), "", qProjectFileFilter);
	if (sFileName != "")
	{
		// construct data tree that visible
		for (auto& rItem : m_mapGroups)
		{
			// re-add to root node for write
			if(!rItem.second.pButton->isHidden())
				m_pRootNode->addChild(rItem.second.pTreeNode);
		}

		// write JSON
		QJsonObject mObj;
		m_pRootNode->write(mObj);

		for (auto& rItem : m_mapGroups)
			m_pRootNode->removeChild(rItem.second.pTreeNode);

		//write to file
		QJsonDocument saveDoc(mObj);
		QFile saveFile(sFileName);
		if (saveFile.open(QIODevice::WriteOnly))
		{
			saveFile.write(saveDoc.toJson());
			return;
		}

		QMessageBox::critical(this, tr("Project File Save Failed"), tr("Can't save the project file:\n\n  ") + sFileName );
	}
}

void CMain::slotPreference()
{
}
