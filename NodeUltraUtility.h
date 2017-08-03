#pragma once

#include "CTreeNodes.h"

#include <array>
#include <QPushButton>
#include <QMessageBox>

#ifndef FileDialog_h
#define FileDialog_h

static const SFileDialogSetting gDisableFileSelect = {false, "", "", ""};
static const SFileDialogSetting gMeshFileSetting = { true, QObject::tr("Select a mesh file"), "", QObject::tr("Mesh file (*.uns);;All files (*.* *)") };
static const SFileDialogSetting gBoundaryFileSetting = { true, QObject::tr("Select a boundary file"), "", QObject::tr("Boundary file (*.inp);;All files (*.* *)") };
static const SFileDialogSetting gMoleculeFileSetting = { true, QObject::tr("Select a molecule file"), "", QObject::tr("Molecule file (*.*);;All files (*.* *)") };

#endif

class CUltraUtility : public CGroupNode
{
public:
    class CAutoGenHexGrid : public CGroupNode
    {
    public:
        CAutoGenHexGrid(CTreeNode* pParent) : CGroupNode("auto_generate_hex_structure_grid", pParent)
        {
            new CBooleanNode("enable", false, this);
            new CIntegerNode("nx", 101, { 2,10000,1 }, this);
            new CIntegerNode("ny", 2, { 2,10000,1 }, this);
            new CIntegerNode("nz", 2, { 2,10000,1 }, this);
            new CDoubleNode("dx", 0.0002, 6, { 0,10000,0.0001 }, this);
            new CDoubleNode("dy", 0.0002, 6, { 0,10000,0.0001 }, this);
            new CDoubleNode("dz", 0.0002, 6, { 0,10000,0.0001 }, this);
            new CValueListNode<int>("boundary_settings", QVector<QStringRef>() << 0, this);
        }
    };

public:
    CUltraUtility(CTreeNode* pParent) : CGroupNode("ultrautility", pParent)
    {
        m_AutoGenHexGrid = new CAutoGenHexGrid(this);

    }


public:
    CAutoGenHexGrid *m_AutoGenHexGrid;
};
