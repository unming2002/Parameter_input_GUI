#pragma once

#include "CTreeNodes.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>

#pragma region definition of general file dialog
static const SFileDialogSetting gDisableFileSelect = { false, "", "", "" };
static const SFileDialogSetting gMeshFileSetting = { true, QObject::tr("Select a mesh file"), "", QObject::tr("Mesh file (*.uns);;All files (*.* *)") };
static const SFileDialogSetting gBoundaryFileSetting = { true, QObject::tr("Select a boundary file"), "", QObject::tr("Boundary file (*.json);;All files (*.* *)") };
static const SFileDialogSetting gMoleculeFileSetting = { true, QObject::tr("Select a molecule file"), "", QObject::tr("Molecule file (*.*);;All files (*.* *)") };
static const SFileDialogSetting gCollisionGroupFileSetting = { true, QObject::tr("Select a collision group file"), "", QObject::tr("Collision Group file (*.json);;All files (*.* *)") };
#pragma endregion

#pragma region load and save JSON file
static const QString qProjectFileFilter = QObject::tr("Project file (*.json);;All files (*.* *)");

template<class TJsonProcessorFunc>
inline bool loadJsonFileHelper(TJsonProcessorFunc funcProcessor)
{
	QString sFileName = QFileDialog::getOpenFileName(nullptr, QObject::tr("Open a project file"), "", qProjectFileFilter);
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
				if (funcProcessor(loadDoc.object()))
				{
					return true;
				}
				else
				{
					QMessageBox::critical(nullptr, QObject::tr("Project File Open Failed"), QObject::tr("The file format is not correct:\n\n  ") + sFileName);
				}
			}
			else
			{
				QMessageBox::critical(nullptr, QObject::tr("Project File Open Failed"), QObject::tr("The file is not a vaild JSON file:\n\n  ") + sFileName);
			}
		}
		else
		{
			QMessageBox::critical(nullptr, QObject::tr("Project File Open Failed"), QObject::tr("Can't read the project file:\n\n  ") + sFileName);
		}
	}
	return false;
}

inline bool saveJsonFileHelper(const QJsonObject& mJsonObject)
{
	QString sFileName = QFileDialog::getSaveFileName(nullptr, QObject::tr("Save the project file"), "", qProjectFileFilter);
	if (sFileName != "")
	{
		QJsonDocument saveDoc(mJsonObject);
		QFile saveFile(sFileName);

		if (saveFile.open(QIODevice::WriteOnly))
		{
			saveFile.write(saveDoc.toJson());
			return true;
		}

		QMessageBox::critical(nullptr, QObject::tr("Project File Save Failed"), QObject::tr("Can't save the project file:\n\n  ") + sFileName);
	}
	return false;
}
#pragma endregion
