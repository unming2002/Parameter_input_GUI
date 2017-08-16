#pragma once

#include "common.h"
#include "CTreeNodes.h"

#include <array>
#include <QPushButton>
#include <QMessageBox>

class CUltraUtility : public CGroupNode
{
public:
    class CAutoGenHexGrid : public CGroupNode
    {
    public:
        CAutoGenHexGrid(CTreeNode* pParent) : CGroupNode("auto_generate_hex_structure_grid", EGroup::NoGroup, pParent)
        {
            new CBooleanNode("enable", EGroup::NoGroup, false, this);
            new CIntegerNode("nx", EGroup::NoGroup, 101, { 2,10000,1 }, this);
            new CIntegerNode("ny", EGroup::NoGroup, 2, { 2,10000,1 }, this);
            new CIntegerNode("nz", EGroup::NoGroup, 2, { 2,10000,1 }, this);
            new CDoubleNode("dx", EGroup::NoGroup, 0.0002, 6, { 0,10000,0.0001 }, this);
            new CDoubleNode("dy", EGroup::NoGroup, 0.0002, 6, { 0,10000,0.0001 }, this);
            new CDoubleNode("dz", EGroup::NoGroup, 0.0002, 6, { 0,10000,0.0001 }, this);
            new CValueListNode<int>("boundary_settings", EGroup::NoGroup, QVector<QStringRef>() << 0, this);
        }
    };

public:
    CUltraUtility(CTreeNode* pParent) : CGroupNode("ultrautility", EGroup::NoGroup, pParent)
    {
        m_AutoGenHexGrid = new CAutoGenHexGrid(this);

    }


public:
    CAutoGenHexGrid *m_AutoGenHexGrid;
};
