#pragma once

#include "common.h"
#include "CTreeNodes.h"

#include <array>
#include <QPushButton>
#include <QMessageBox>

class CUltrasparts : public CGroupNode
{
public:
    class CGridSystem : public CGroupNode
    {
    public:
        class CBoundaryTable : public CListGroup
        {
        public:
            class CBoundaryItem : public CListItemNode
            {
            public:
                CBoundaryItem(const QString& sName, const int& iID, const double& dTemp,CTreeNode* pParent) : CListItemNode(pParent)
                {
                    new CStringNode("name", sName, this);
                    new CIntegerNode("typeid", iID, { -10000,10000,1 }, this);
                    new CDoubleNode("Temperature" ,dTemp, 6, {0.0, 1000000.0, 1.0}, this);
                    new CDoubleNode("Vx", 0.0, 6, {-1000000.0 ,1000000.0, 1.0}, this);
                    new CDoubleNode("Vy", 0.0, 6, {-1000000.0, 1000000.0, 1.0}, this);
                    new CDoubleNode("Vz", 0.0, 6, {-1000000.0, 1000000.0, 1.0}, this);
                }
            };

        public:
            CBoundaryTable(CTreeNode* pParent) : CListGroup("boundary_table", gBoundaryFileSetting, pParent)
            {
                //TODO: load boundary table
                CBoundaryTable* pThis = this;
                QObject::connect(this, &CListGroup::fileSelected, [pThis](const QString& sFilename)
                {
                    QMessageBox::information(0,"Test", sFilename);
                });
            }

            CTreeNode* addListItem() override
            {
                return new CBoundaryItem("", 0, 300.0, this);
            }
        };


    public:
        CGridSystem(CTreeNode* pParent) : CGroupNode("grid_system", pParent)
        {
            new CComboBoxNode("geometry", { "2D", "3D", "Axisymmetric_Y", "Axisymmetric_X" }, 0, this);
            new CFileSelectNode("meshfile", "", gMeshFileSetting, this);

            new CBoundaryTable(this);
            //--new CAutoGenHexGrid(this);

            new CDoubleNode("scale", 1.0, 4, { 0,10000,1 }, this);
            new CDoubleNode("reference_cell_volume", 0.000000000001, 13, { 0,10000,0 }, this);
        }
    };

    class CTimeStepSetting : public CGroupNode
    {
    public:
        CTimeStepSetting(CTreeNode* pParent) : CGroupNode("time_step_setup", pParent)
        {
            new CDoubleNode("time_shift_s", 0.0, 4, { 0,1000,0.1 }, this);
            new CIntegerNode("total_steps", 10000, { 0,1000000,1 }, this);
            new CIntegerNode("total_cycles", 10, { 0,1000,1 }, this);
            new CDoubleNode("delta_t_s", 1.00E-12, 15, { 0,1000,0.1 }, this);
            new CIntegerNode("restart_tag", 0, { 0,1000,1 }, this);
        }
    };

    class CMonitorOptions : public CGroupNode
    {
    public:
        CMonitorOptions(CTreeNode* pParent) : CGroupNode("monitor_options", pParent)
        {
            new CIntegerNode("number_of_file_out_per_cycle", 20, { 0,1000,1 }, this);
            new CIntegerNode("number_of_step_per_monitor_out", 20, { 0,1000,1 }, this);
            new CIntegerNode("number_of_cycle_per_file_out", 2, { 0,1000,1 }, this);
            new CIntegerNode("sampling_cycle_size", 20, { 0,1000,1 }, this);
            new CIntegerNode("delta_cycle_of_restart_output", 50, { 0,1000,1 }, this);
            new CBooleanNode("debug_mode", false, this);
            new CBooleanNode("check_kinetic_energy", false, this);
        }
    };

    class CExternalField : public CGroupNode
    {
    public:
        class CAppliedVoltage : public CGroupNode
        {
        public:
            CAppliedVoltage(CTreeNode* pParent) : CGroupNode("applied_voltage", pParent)
            {
                new CDoubleNode("amplitude_V", 110, 2, { 0, 1000, 1 }, this);
                new CDoubleNode("radio_frequency_Hz", 13560000, 2, { 0, 100000000, 1 }, this);
            }
        };

        class CMagneticField : public CGroupNode
        {
        public:
            CMagneticField(CTreeNode* pParent) : CGroupNode("magnetic_field", pParent)
            {
                new CComboBoxNode("unit", { "Gauss", "Tesla" }, 0, this );
                new CBooleanNode("enable", false, this );
                new CDoubleNode("Bx",0,4,{ -100,100,1 }, this);
                new CDoubleNode("By",0,4,{ -100,100,1 }, this);
                new CDoubleNode("Bz",0,4,{ -100,100,1 }, this);
            }
        };

        class CGravity : public CGroupNode
        {
        public:
            CGravity(CTreeNode* pParent) : CGroupNode("gravity", pParent)
            {
                new CBooleanNode("enable", false, this);
                new CDoubleNode("gx",0,4,{ -100,100,1 }, this);
                new CDoubleNode("gy",0,4,{ -100,100,1 }, this);
                new CDoubleNode("gz", -9.8, 4, { -100,100,1 }, this);
            }
        };

    public:
        CExternalField(CTreeNode* pParent) : CGroupNode("external_field", pParent)
        {
            new CAppliedVoltage(this);
            new CMagneticField(this);
            new CGravity(this);
        }
    };

    class CMCCSetting : public CGroupNode
    {
    public:
        class CCollisionGroup : public CListGroup
        {
        public:
            class CCollisionItem : public CListItemNode
            {
            public:
                class CChannels : public CListGroup
                {
                public:
                    class CChannelItem : public CListItemNode
                    {
                    public:
                        CChannelItem(CTreeNode* pParent) : CListItemNode(pParent)
                        {
                            new CStringNode("name","", this);
                            new CValueListNode<QString>("product", {}, this);
                            new CDoubleNode("activation_energy", 0, 4, { 0,1000,1 }, this);
                            new CComboBoxNode("energy_transfer", {"Scattering", "Rebounce", "Elastic", "Exchange"}, 0, this);
                            new CComboBoxNode("energy_redistribution", { "NewParticle", "None" }, 1, this);
                        }
                    };

                public:
                    CChannels(CTreeNode* pParent) : CListGroup("channels", gDisableFileSelect, pParent) {}

                    CTreeNode* addListItem() override
                    {
                        return new CChannelItem(this);
                    }
                };

            public:
                CCollisionItem(CTreeNode* pParent) : CListItemNode(pParent)
                {
                    new CValueListNode<QString>("reactant", {}, this);
                    new CChannels(this);
                }
            };

        public:
            CCollisionGroup(CTreeNode* pParent) : CListGroup("collision_group", gDisableFileSelect, pParent) {}

            CTreeNode* addListItem() override
            {
                return new CCollisionItem(this);
            }
        };

    public:
        CMCCSetting(CTreeNode* pParent) : CGroupNode("mcc_setting", pParent)
        {
            // enable
            new CBooleanNode("enable", true, this);

            // number_of_relaxing_cycle
            new CIntegerNode("number_of_relaxing_cycle", 1, {0,100,1}, this);

            // selected_pair
            new CComboBoxNode("selected_pair", {"Cell_Max_Velocity", "All"}, 0, this );

            // collision_group
            new CCollisionGroup(this);
        }
    };

    class CSpecies : public CGroupNode
    {
    public:
        class CMolecule : public CListGroup
        {
        public:
            class CItem : public CListItemNode
            {
            public:
                CItem(CTreeNode* pParent) : CListItemNode(pParent)
                {
                    new CStringNode("name", "", this);
                    new CDoubleNode("mass_amu", 0, 4, { 0,1000,1 }, this);
                    new CDoubleNode("charge", 0, 4, { -1000,1000,1 }, this);
                    new CDoubleNode("T_eV", 0, 4, { 0,1000,1 }, this);
                    new CDoubleNode("num_den", 0, 4, { 0,1000,1 }, this);
                    new CDoubleNode("p_in_torr", 0, 4, { 0,1000,1 }, this);
                    new CIntegerNode("particle_per_cell", 0, { 0,1000,1 }, this);
                    new CIntegerNode("subcycling", 0, { 0,1000,1 }, this);
                    new CIntegerNode("weighting", 0, { 0,1000,1 }, this);
                }
            };

        public:
            CMolecule(CTreeNode* pParent) : CListGroup("molecule", gMoleculeFileSetting, pParent)
            {
                //TODO: load boundary table
                CMolecule* pThis = this;
                QObject::connect(this, &CListGroup::fileSelected, [pThis](const QString& sFilename)
                {
                    QMessageBox::information(nullptr, "Test", sFilename);
                });
            }

            CTreeNode* addListItem() override
            {
                return new CItem(this);
            }
        };

    public:
        CSpecies(CTreeNode* pParent) : CGroupNode("species", pParent)
        {
            m_pMolecule = new CMolecule(this);

        }

    public:
        CMolecule*	m_pMolecule;
        //CInitial*	m_pInitial;
    };

    class CPoisson : public CGroupNode
    {
    public:
        class CBoundary : public CListGroup
        {
        public:
            class CItem : public CListItemNode
            {
            public:
                CItem(CTreeNode* pParent) : CListItemNode(pParent)
                {
                    new CStringNode("name", "", this);
                    new CComboBoxNode("type", {"SIN","COS","GROUND","NEUMANN"},0,this);
                    new CDoubleNode("voltage", 0, 4, { 0,1000,1 }, this);
                    new CDoubleNode("frequency", 1.36E+7, 2, { 0,1E+8,1 }, this);
                    new CDoubleNode("phaseShift", 0, 4, { 0,1000,1 }, this);
                    new CDoubleNode("capacitor", 0, 4, { 0,1000,1 }, this);
                }
            };

        public:
            CBoundary(CTreeNode* pParent) : CListGroup("boundary", gBoundaryFileSetting, pParent){}

            CTreeNode* addListItem() override
            {
                return new CItem(this);
            }
        };

    public:
        CPoisson(CTreeNode* pParent) : CGroupNode("poisson", pParent)
        {
            new CDoubleNode("relative_tolerance", 1.0E-6, 8, {0,1.0E-6,1.0E-6 }, this);
            new CComboBoxNode("fvm_scheme", {"Implicit"}, 0, this);
            new CFileSelectNode("meshfile", "Grid.uns", gMeshFileSetting, this);
            new CStringNode("geometry", "2D", this);
            new CFileSelectNode("boundary_table", "BC.inp", gBoundaryFileSetting, this);
            new CBoundary(this);
            new CBooleanNode("update_permittivity", false, this);
            new CComboBoxNode("pc_type", {"PETSC_PCAMG"}, 0, this);
        }
    };

public:
    CUltrasparts(CTreeNode* pParent) : CGroupNode("ultrasparts", pParent)
    {
        m_pGridSystem = new CGridSystem(this);
        m_pTimeStepSetting = new CTimeStepSetting(this);
        m_pMonitorOptions = new CMonitorOptions(this);

        // particle_settings
        m_pParticleSettings = new CGroupNode("particle_settings",this);
        {
            // maximum_particle_size
            new CIntegerNode("maximum_particle_size", 1000000, { 1,10000000, 1 }, m_pParticleSettings);

            // particle_scaling_factor
            new CDoubleNode("particle_scaling_factor", 1.2, 4, { 1.0,1000.0, 0.1 }, m_pParticleSettings);
        }

        m_pExternalField = new CExternalField(this);

        // interpolation
        m_pInterpolation = new CGroupNode("interpolation", this);
        {
            new CComboBoxNode("particle_to_cell", { "inversed_cartesian_volume", "no_interpolation" }, 0, m_pInterpolation);
        }

        // parallel_computing
        m_pParallelComputing = new CGroupNode("parallel_computing", this);
        {
            // partition_domain
            new CComboBoxNode("partition_domain", { "particle", "both" }, 0, m_pParallelComputing);

            // loading_balance_method
            new CComboBoxNode("loading_balance_method", { "mixed", "max", "averaged" }, 0, m_pParallelComputing);

            // loading_balance_factor
            new CDoubleNode("loading_balance_factor", 1.025, 4, { 1.01, 10.0, 0.01 }, m_pParallelComputing);
        }

        m_pMCCSetting = new CMCCSetting(this);
        m_pSpecies = new CSpecies(this);
        m_pPoisson = new CPoisson(this);
    }

public:
    CGridSystem*		m_pGridSystem;
    CTimeStepSetting*	m_pTimeStepSetting;
    CMonitorOptions*	m_pMonitorOptions;
    CGroupNode*			m_pParticleSettings;
    CExternalField*		m_pExternalField;
    CGroupNode*			m_pInterpolation;
    CGroupNode*			m_pParallelComputing;
    CMCCSetting*		m_pMCCSetting;
    CSpecies*			m_pSpecies;
    CPoisson*			m_pPoisson;
};
