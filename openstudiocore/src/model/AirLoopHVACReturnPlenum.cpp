/**********************************************************************
 *  Copyright (c) 2008-2013, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#include <model/AirLoopHVACReturnPlenum.hpp>
#include <model/AirLoopHVACReturnPlenum_Impl.hpp>
#include <model/AirLoopHVACZoneMixer.hpp>
#include <model/AirLoopHVACZoneMixer_Impl.hpp>
#include <model/AirLoopHVACSupplyPlenum.hpp>
#include <model/AirLoopHVACSupplyPlenum_Impl.hpp>
#include <model/AirLoopHVACZoneSplitter.hpp>
#include <model/AirLoopHVACZoneSplitter_Impl.hpp>
#include <model/ThermalZone.hpp>
#include <model/ThermalZone_Impl.hpp>
#include <model/Model.hpp>
#include <model/Model_Impl.hpp>
#include <model/AirLoopHVAC.hpp>
#include <model/AirLoopHVAC_Impl.hpp>
#include <model/Node.hpp>
#include <model/Node_Impl.hpp>
#include <utilities/idd/OS_AirLoopHVAC_ReturnPlenum_FieldEnums.hxx>
#include <utilities/core/Assert.hpp>

namespace openstudio {
namespace model {

namespace detail {

  AirLoopHVACReturnPlenum_Impl::AirLoopHVACReturnPlenum_Impl(const IdfObject& idfObject,
                                                             Model_Impl* model,
                                                             bool keepHandle)
    : Mixer_Impl(idfObject,model,keepHandle)
  {
    OS_ASSERT(idfObject.iddObject().type() == AirLoopHVACReturnPlenum::iddObjectType());
  }

  AirLoopHVACReturnPlenum_Impl::AirLoopHVACReturnPlenum_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                             Model_Impl* model,
                                                             bool keepHandle)
    : Mixer_Impl(other,model,keepHandle)
  {
    OS_ASSERT(other.iddObject().type() == AirLoopHVACReturnPlenum::iddObjectType());
  }

  AirLoopHVACReturnPlenum_Impl::AirLoopHVACReturnPlenum_Impl(const AirLoopHVACReturnPlenum_Impl& other,
                                                             Model_Impl* model,
                                                             bool keepHandle)
    : Mixer_Impl(other,model,keepHandle)
  {}

  const std::vector<std::string>& AirLoopHVACReturnPlenum_Impl::outputVariableNames() const
  {
    static std::vector<std::string> result;
    if (result.empty()){
    }
    return result;
  }

  IddObjectType AirLoopHVACReturnPlenum_Impl::iddObjectType() const {
    return AirLoopHVACReturnPlenum::iddObjectType();
  }

  boost::optional<ThermalZone> AirLoopHVACReturnPlenum_Impl::thermalZone() const {
    return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(OS_AirLoopHVAC_ReturnPlenumFields::ThermalZone);
  }

  bool AirLoopHVACReturnPlenum_Impl::setThermalZone(const boost::optional<ThermalZone>& thermalZone) {
    bool result(false);

    if( ! thermalZone )
    {
      resetThermalZone();
      result = true;
    }
    else if( (! thermalZone->getImpl<ThermalZone_Impl>()->airLoopHVACSupplyPlenum()) &&
             (! thermalZone->getImpl<ThermalZone_Impl>()->airLoopHVACReturnPlenum()) &&
             (thermalZone->equipment().size() == 0) &&
             (! thermalZone->useIdealAirLoads()) )
    {
      result = setPointer(OS_AirLoopHVAC_ReturnPlenumFields::ThermalZone, thermalZone.get().handle());
    }

    return result;
  }

  void AirLoopHVACReturnPlenum_Impl::resetThermalZone() {
    bool result = setString(OS_AirLoopHVAC_ReturnPlenumFields::ThermalZone, "");
    OS_ASSERT(result);
  }

  unsigned AirLoopHVACReturnPlenum_Impl::outletPort()
  {
    return OS_AirLoopHVAC_ReturnPlenumFields::OutletNode;
  }

  unsigned AirLoopHVACReturnPlenum_Impl::inletPort(unsigned branchIndex)
  {
    unsigned result;
    result = numNonextensibleFields();
    result = result + branchIndex;
    return result;
  }

  unsigned AirLoopHVACReturnPlenum_Impl::nextInletPort()
  {
    return inletPort( this->nextBranchIndex() );
  }

  bool AirLoopHVACReturnPlenum_Impl::addToNode(Node & node)
  {
    bool result = true;

    Model _model = model();

    // Is the node in this model
    if( node.model() != _model )
    {
      result = false;
    }

    // Is the node part of an air loop
    boost::optional<AirLoopHVAC> airLoop = node.airLoopHVAC();

    if( ! airLoop )
    {
      result = false;
    }

    // Is this plenum already connected to an air loop
    if( boost::optional<AirLoopHVAC> currentAirLoopHVAC = airLoopHVAC() )
    {
      result = false;
    }

    boost::optional<ModelObject> outletObj = node.outletModelObject();
    boost::optional<ModelObject> inletObj = node.inletModelObject();
    boost::optional<Mixer> mixer;

    // Is the immediate downstream object to the node a mixer
    if( result )
    {
      mixer = airLoop->demandMixer();

      if( ! (outletObj && mixer && (outletObj.get() == mixer.get()) ) ) 
      {
        result = false;
      }
    }

    // Make sure there is not already a return plenum
    if( result )
    {
      if(  inletObj && inletObj->optionalCast<AirLoopHVACReturnPlenum>() )
      {
        result = false;
      }
    }

    if( result )
    {
      unsigned inletObjectPort;
      unsigned outletObjectPort;
      boost::optional<ModelObject> inletModelObject;
      boost::optional<ModelObject> outletModelObject;

      inletModelObject = node;
      inletObjectPort = node.outletPort();
      outletModelObject = outletObj;
      outletObjectPort = node.connectedObjectPort(node.outletPort()).get();

      Node plenumOutletNode(_model);
      plenumOutletNode.createName();

      AirLoopHVACReturnPlenum thisObject = getObject<AirLoopHVACReturnPlenum>();

      _model.connect(inletModelObject.get(),inletObjectPort,thisObject,thisObject.nextInletPort());
      _model.connect(thisObject,thisObject.outletPort(),plenumOutletNode,plenumOutletNode.inletPort());
      _model.connect(plenumOutletNode,plenumOutletNode.outletPort(),outletModelObject.get(),outletObjectPort);
    }

    return result;
  }

  bool AirLoopHVACReturnPlenum_Impl::addBranchForZone(openstudio::model::ThermalZone & thermalZone)
  {
    boost::optional<StraightComponent> t_terminal;

    return addBranchForZoneImpl(thermalZone,t_terminal);
  }
  
  bool AirLoopHVACReturnPlenum_Impl::addBranchForZone(openstudio::model::ThermalZone & thermalZone, StraightComponent & terminal)
  {
    boost::optional<StraightComponent> t_terminal = terminal;

    return addBranchForZoneImpl(thermalZone,t_terminal);
  }

  bool AirLoopHVACReturnPlenum_Impl::addBranchForZoneImpl(openstudio::model::ThermalZone & thermalZone, boost::optional<StraightComponent> & terminal)
  {
    boost::optional<Splitter> splitter;
    boost::optional<Mixer> mixer = getObject<AirLoopHVACReturnPlenum>();

    boost::optional<AirLoopHVAC> t_airLoopHVAC = airLoopHVAC();

    if( ! t_airLoopHVAC )
    {
      return false;
    }

    std::vector<ModelObject> supplyPlenums;
    supplyPlenums = t_airLoopHVAC->demandComponents(t_airLoopHVAC->demandInletNode(),
                                                    mixer.get(),
                                                    AirLoopHVACSupplyPlenum::iddObjectType());

    if( supplyPlenums.size() == 1u )
    {
      splitter = supplyPlenums.front().cast<Splitter>();
    }
    else
    {
      splitter = t_airLoopHVAC->zoneSplitter();
    }

    BOOST_ASSERT(splitter);
    BOOST_ASSERT(mixer);

    return AirLoopHVAC_Impl::addBranchForZoneImpl(thermalZone,t_airLoopHVAC.get(),splitter.get(),mixer.get(),terminal);
  }

  std::vector<IdfObject> AirLoopHVACReturnPlenum_Impl::remove()
  {
    Model t_model = model();

    if( boost::optional<AirLoopHVAC> t_airLoopHVAC = airLoopHVAC() )
    {
      AirLoopHVACZoneMixer zoneMixer = t_airLoopHVAC->zoneMixer();
      std::vector<ModelObject> t_inletModelObjects = inletModelObjects();

      for( std::vector<ModelObject>::reverse_iterator it = t_inletModelObjects.rbegin();
           it != t_inletModelObjects.rend();
           ++it )
      {
        unsigned branchIndex = branchIndexForInletModelObject(*it); 
        unsigned t_inletPort = inletPort(branchIndex);
        unsigned connectedObjectOutletPort = connectedObjectPort(t_inletPort).get();

        t_model.connect(*it,connectedObjectOutletPort,zoneMixer,zoneMixer.nextInletPort());
      }

      boost::optional<ModelObject> mo = outletModelObject();
      OS_ASSERT(mo);
      boost::optional<Node> node = mo->optionalCast<Node>();
      OS_ASSERT(node);
      zoneMixer.removePortForBranch(zoneMixer.branchIndexForInletModelObject(node.get()));
      node->remove();
    }

    return Mixer_Impl::remove();
  }

} // detail

AirLoopHVACReturnPlenum::AirLoopHVACReturnPlenum(const Model& model)
  : Mixer(AirLoopHVACReturnPlenum::iddObjectType(),model)
{
  OS_ASSERT(getImpl<detail::AirLoopHVACReturnPlenum_Impl>());
}

IddObjectType AirLoopHVACReturnPlenum::iddObjectType() {
  return IddObjectType(IddObjectType::OS_AirLoopHVAC_ReturnPlenum);
}

boost::optional<ThermalZone> AirLoopHVACReturnPlenum::thermalZone() const {
  return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->thermalZone();
}

bool AirLoopHVACReturnPlenum::setThermalZone(const ThermalZone& thermalZone) {
  return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->setThermalZone(thermalZone);
}

void AirLoopHVACReturnPlenum::resetThermalZone() {
  getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->resetThermalZone();
}

unsigned AirLoopHVACReturnPlenum::outletPort()
{
  return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->outletPort();
}

unsigned AirLoopHVACReturnPlenum::inletPort(unsigned branchIndex)
{
  return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->inletPort(branchIndex);
}

unsigned AirLoopHVACReturnPlenum::nextInletPort()
{
  return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->nextInletPort();
}

bool AirLoopHVACReturnPlenum::addToNode(Node & node)
{
  return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->addToNode(node);
}

bool AirLoopHVACReturnPlenum::addBranchForZone(openstudio::model::ThermalZone & thermalZone)
{
  return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->addBranchForZone(thermalZone);
}

bool AirLoopHVACReturnPlenum::addBranchForZone(openstudio::model::ThermalZone & thermalZone, StraightComponent & terminal)
{
  return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->addBranchForZone(thermalZone,terminal);
}

/// @cond
AirLoopHVACReturnPlenum::AirLoopHVACReturnPlenum(boost::shared_ptr<detail::AirLoopHVACReturnPlenum_Impl> impl)
  : Mixer(impl)
{}
/// @endcond

} // model
} // openstudio

