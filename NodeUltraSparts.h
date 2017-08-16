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
                    new CStringNode("name", EGroup::NoGroup, sName, this);
                    new CIntegerNode("typeid", EGroup::NoGroup, iID, { -10000,10000,1 }, this);
                    new CDoubleNode("Temperature", EGroup::NoGroup, dTemp, 6, {0.0, 1000000.0, 1.0}, this);
                    new CDoubleNode("Vx", EGroup::NoGroup, 0.0, 6, {-1000000.0 ,1000000.0, 1.0}, this);
                    new CDoubleNode("Vy", EGroup::NoGroup, 0.0, 6, {-1000000.0, 1000000.0, 1.0}, this);
                    new CDoubleNode("Vz", EGroup::NoGroup, 0.0, 6, {-1000000.0, 1000000.0, 1.0}, this);
                }
            };

        public:
            CBoundaryTable(CTreeNode* pParent) : CListGroup("boundary_table", EGroup::NoGroup, gBoundaryFileSetting, pParent)
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
        CGridSystem(CTreeNode* pParent) : CGroupNode("grid_system", EGroup::NoGroup, pParent)
        {
            new CComboBoxNode("geometry", EGroup::NoGroup, { "2D", "3D", "Axisymmetric_Y", "Axisymmetric_X" }, 0, this);
            new CFileSelectNode("meshfile", EGroup::NoGroup, "", gMeshFileSetting, this);

            new CBoundaryTable(this);
            //--new CAutoGenHexGrid(this);

            new CDoubleNode("scale", EGroup::NoGroup, 1.0, 4, { 0,10000,1 }, this);
            new CDoubleNode("reference_cell_volume", EGroup::NoGroup, 0.000000000001, 13, { 0,10000,0 }, this);
        }
    };

    class CTimeStepSetting : public CGroupNode
    {
    public:
        CTimeStepSetting(CTreeNode* pParent) : CGroupNode("time_step_setup", EGroup::NoGroup, pParent)
        {
            new CDoubleNode("time_shift_s", EGroup::NoGroup, 0.0, 4, { 0,1000,0.1 }, this);
            new CIntegerNode("total_steps", EGroup::NoGroup, 10000, { 0,1000000,1 }, this);
            new CIntegerNode("total_cycles", EGroup::NoGroup, 10, { 0,1000,1 }, this);
            new CDoubleNode("delta_t_s", EGroup::NoGroup, 1.00E-12, 15, { 0,1000,0.1 }, this);
            new CIntegerNode("restart_tag", EGroup::NoGroup, 0, { 0,1000,1 }, this);
        }
    };

    class CMonitorOptions : public CGroupNode
    {
    public:
        CMonitorOptions(CTreeNode* pParent) : CGroupNode("monitor_options", EGroup::NoGroup, pParent)
        {
            new CIntegerNode("number_of_file_out_per_cycle", EGroup::NoGroup, 20, { 0,1000,1 }, this);
            new CIntegerNode("number_of_step_per_monitor_out", EGroup::NoGroup, 20, { 0,1000,1 }, this);
            new CIntegerNode("number_of_cycle_per_file_out", EGroup::NoGroup, 2, { 0,1000,1 }, this);
            new CIntegerNode("sampling_cycle_size", EGroup::NoGroup, 20, { 0,1000,1 }, this);
            new CIntegerNode("delta_cycle_of_restart_output", EGroup::NoGroup, 50, { 0,1000,1 }, this);
            new CBooleanNode("debug_mode", EGroup::NoGroup, false, this);
            new CBooleanNode("check_kinetic_energy", EGroup::NoGroup, false, this);
        }
    };

    class CExternalField : public CGroupNode
    {
    public:
        class CAppliedVoltage : public CGroupNode
        {
        public:
            CAppliedVoltage(CTreeNode* pParent) : CGroupNode("applied_voltage", EGroup::NoGroup, pParent)
            {
                new CDoubleNode("amplitude_V", EGroup::NoGroup, 110, 2, { 0, 1000, 1 }, this);
                new CDoubleNode("radio_frequency_Hz", EGroup::NoGroup, 13560000, 2, { 0, 100000000, 1 }, this);
            }
        };

        class CMagneticField : public CGroupNode
        {
        public:
            CMagneticField(CTreeNode* pParent) : CGroupNode("magnetic_field", EGroup::NoGroup, pParent)
            {
                new CComboBoxNode("unit", EGroup::NoGroup, { "Gauss", "Tesla" }, 0, this );
                new CBooleanNode("enable", EGroup::NoGroup, false, this );
                new CDoubleNode("Bx",EGroup::NoGroup, 0,4,{ -100,100,1 }, this);
                new CDoubleNode("By",EGroup::NoGroup, 0,4,{ -100,100,1 }, this);
                new CDoubleNode("Bz",EGroup::NoGroup, 0,4,{ -100,100,1 }, this);
            }
        };

        class CGravity : public CGroupNode
        {
        public:
            CGravity(CTreeNode* pParent) : CGroupNode("gravity", EGroup::NoGroup, pParent)
            {
                new CBooleanNode("enable", EGroup::NoGroup, false, this);
                new CDoubleNode("gx", EGroup::NoGroup, 0,4,{ -100,100,1 }, this);
                new CDoubleNode("gy", EGroup::NoGroup, 0,4,{ -100,100,1 }, this);
                new CDoubleNode("gz", EGroup::NoGroup, -9.8, 4, { -100,100,1 }, this);
            }
        };

    public:
        CExternalField(CTreeNode* pParent) : CGroupNode("external_field", EGroup::NoGroup, pParent)
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
                            new CStringNode("name", EGroup::NoGroup, "", this);
                            new CValueListNode<QString>("product", EGroup::NoGroup, {}, this);
                            new CDoubleNode("activation_energy", EGroup::NoGroup, 0, 4, { 0,1000,1 }, this);
                            new CComboBoxNode("energy_transfer", EGroup::NoGroup, {"Scattering", "Rebounce", "Elastic", "Exchange"}, 0, this);
                            new CComboBoxNode("energy_redistribution", EGroup::NoGroup, { "NewParticle", "None" }, 1, this);
                        }
                    };

                public:
                    CChannels(CTreeNode* pParent) : CListGroup("channels", EGroup::NoGroup, gDisableFileSelect, pParent) {}

                    CTreeNode* addListItem() override
                    {
                        return new CChannelItem(this);
                    }
                };

            public:
                CCollisionItem(CTreeNode* pParent) : CListItemNode(pParent)
                {
                    new CValueListNode<QString>("reactant", EGroup::NoGroup, {}, this);
                    new CChannels(this);
                }
            };

        public:
            CCollisionGroup(CTreeNode* pParent) : CListGroup("collision_group", EGroup::NoGroup, gDisableFileSelect, pParent) {}

            CTreeNode* addListItem() override
            {
                return new CCollisionItem(this);
            }
        };

    public:
        CMCCSetting(CTreeNode* pParent) : CGroupNode("mcc_setting", EGroup::NoGroup, pParent)
        {
            // enable
            new CBooleanNode("enable", EGroup::NoGroup, true, this);

            // number_of_relaxing_cycle
            new CIntegerNode("number_of_relaxing_cycle", EGroup::NoGroup, 1, {0,100,1}, this);

            // selected_pair
            new CComboBoxNode("selected_pair", EGroup::NoGroup, {"Cell_Max_Velocity", "All"}, 0, this );

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
                    new CStringNode("name", EGroup::NoGroup, "", this);
                    new CDoubleNode("mass_amu", EGroup::NoGroup, 0, 4, { 0,1000,1 }, this);
                    new CDoubleNode("charge", EGroup::NoGroup, 0, 4, { -1000,1000,1 }, this);
                    new CDoubleNode("T_eV", EGroup::NoGroup, 0, 4, { 0,1000,1 }, this);
                    new CDoubleNode("num_den", EGroup::NoGroup, 0, 4, { 0,1000,1 }, this);
                    new CDoubleNode("p_in_torr", EGroup::NoGroup, 0, 4, { 0,1000,1 }, this);
                    new CIntegerNode("particle_per_cell", EGroup::NoGroup, 0, { 0,1000,1 }, this);
                    new CIntegerNode("subcycling", EGroup::NoGroup, 0, { 0,1000,1 }, this);
                    new CIntegerNode("weighting", EGroup::NoGroup, 0, { 0,1000,1 }, this);
                }
            };

        public:
            CMolecule(CTreeNode* pParent) : CListGroup("molecule", EGroup::NoGroup, gMoleculeFileSetting, pParent)
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
        CSpecies(CTreeNode* pParent) : CGroupNode("species", EGroup::NoGroup, pParent)
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
                    new CStringNode("name", EGroup::NoGroup, "", this);
                    new CComboBoxNode("type", EGroup::NoGroup, {"SIN","COS","GROUND","NEUMANN"},0,this);
                    new CDoubleNode("voltage", EGroup::NoGroup, 0, 4, { 0,1000,1 }, this);
                    new CDoubleNode("frequency", EGroup::NoGroup, 1.36E+7, 2, { 0,1E+8,1 }, this);
                    new CDoubleNode("phaseShift", EGroup::NoGroup, 0, 4, { 0,1000,1 }, this);
                    new CDoubleNode("capacitor", EGroup::NoGroup, 0, 4, { 0,1000,1 }, this);
                }
            };

        public:
            CBoundary(CTreeNode* pParent) : CListGroup("boundary", EGroup::NoGroup, gBoundaryFileSetting, pParent){}

            CTreeNode* addListItem() override
            {
                return new CItem(this);
            }
        };

    public:
        CPoisson(CTreeNode* pParent) : CGroupNode("poisson", EGroup::NoGroup, pParent)
        {
            new CDoubleNode("relative_tolerance", EGroup::NoGroup, 1.0E-6, 8, {0,1.0E-6,1.0E-6 }, this);
            new CComboBoxNode("fvm_scheme", EGroup::NoGroup, {"Implicit"}, 0, this);
            new CFileSelectNode("meshfile", EGroup::NoGroup, "Grid.uns", gMeshFileSetting, this);
            new CStringNode("geometry", EGroup::NoGroup, "2D", this);
            new CFileSelectNode("boundary_table", EGroup::NoGroup, "BC.inp", gBoundaryFileSetting, this);
            new CBoundary(this);
            new CBooleanNode("update_permittivity", EGroup::NoGroup, false, this);
            new CComboBoxNode("pc_type", EGroup::NoGroup, {"PETSC_PCAMG"}, 0, this);
        }
    };

public:
    CUltrasparts(CTreeNode* pParent) : CGroupNode("ultrasparts", EGroup::NoGroup, pParent)
    {
        m_pGridSystem = new CGridSystem(this);
        m_pTimeStepSetting = new CTimeStepSetting(this);
        m_pMonitorOptions = new CMonitorOptions(this);

        // particle_settings
        m_pParticleSettings = new CGroupNode("particle_settings", EGroup::NoGroup, this);
        {
            // maximum_particle_size
            new CIntegerNode("maximum_particle_size", EGroup::NoGroup, 1000000, { 1,10000000, 1 }, m_pParticleSettings);

            // particle_scaling_factor
            new CDoubleNode("particle_scaling_factor", EGroup::NoGroup, 1.2, 4, { 1.0,1000.0, 0.1 }, m_pParticleSettings);
        }

        m_pExternalField = new CExternalField(this);

        // interpolation
        m_pInterpolation = new CGroupNode("interpolation", EGroup::NoGroup, this);
        {
            new CComboBoxNode("particle_to_cell", EGroup::NoGroup, { "inversed_cartesian_volume", "no_interpolation" }, 0, m_pInterpolation);
        }

        // parallel_computing
        m_pParallelComputing = new CGroupNode("parallel_computing", EGroup::NoGroup, this);
        {
            // partition_domain
            new CComboBoxNode("partition_domain", EGroup::NoGroup, { "particle", "both" }, 0, m_pParallelComputing);

            // loading_balance_method
            new CComboBoxNode("loading_balance_method", EGroup::NoGroup, { "mixed", "max", "averaged" }, 0, m_pParallelComputing);

            // loading_balance_factor
            new CDoubleNode("loading_balance_factor", EGroup::NoGroup, 1.025, 4, { 1.01, 10.0, 0.01 }, m_pParallelComputing);
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
