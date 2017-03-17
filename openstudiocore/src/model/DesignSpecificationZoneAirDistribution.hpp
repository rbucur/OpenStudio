/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) 2008-2017, Alliance for Sustainable Energy, LLC. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 *  following conditions are met:
 *
 *  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *  disclaimer.
 *
 *  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *  following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote
 *  products derived from this software without specific prior written permission from the respective party.
 *
 *  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative
 *  works may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without
 *  specific prior written permission from Alliance for Sustainable Energy, LLC.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER, THE UNITED STATES GOVERNMENT, OR ANY CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************************************************************/

#ifndef MODEL_DESIGNSPECIFICATIONZONEAIRDISTRIBUTION_HPP
#define MODEL_DESIGNSPECIFICATIONZONEAIRDISTRIBUTION_HPP

#include "ModelAPI.hpp"
#include "ModelObject.hpp"

namespace openstudio {

class Quantity;
class OSOptionalQuantity;

namespace model {

class Schedule;

namespace detail {

  class DesignSpecificationZoneAirDistribution_Impl;

} // detail

/** DesignSpecificationZoneAirDistribution is a ModelObject that wraps the OpenStudio IDD object 'OS:DesignSpecification:ZoneAirDistribution'. */
class MODEL_API DesignSpecificationZoneAirDistribution : public ModelObject {
 public:

  explicit DesignSpecificationZoneAirDistribution(const Model& model);

  virtual ~DesignSpecificationZoneAirDistribution() {}

  static IddObjectType iddObjectType();


  double zoneAirDistributionEffectivenessinCoolingMode() const;

  Quantity getZoneAirDistributionEffectivenessinCoolingMode(bool returnIP=false) const;

  bool isZoneAirDistributionEffectivenessinCoolingModeDefaulted() const;

  bool setZoneAirDistributionEffectivenessinCoolingMode(double zoneAirDistributionEffectivenessinCoolingMode);

  bool setZoneAirDistributionEffectivenessinCoolingMode(const Quantity& zoneAirDistributionEffectivenessinCoolingMode);

  void resetZoneAirDistributionEffectivenessinCoolingMode();


  double zoneAirDistributionEffectivenessinHeatingMode() const;

  Quantity getZoneAirDistributionEffectivenessinHeatingMode(bool returnIP=false) const;

  bool isZoneAirDistributionEffectivenessinHeatingModeDefaulted() const;

  bool setZoneAirDistributionEffectivenessinHeatingMode(double zoneAirDistributionEffectivenessinHeatingMode);

  bool setZoneAirDistributionEffectivenessinHeatingMode(const Quantity& zoneAirDistributionEffectivenessinHeatingMode);

  void resetZoneAirDistributionEffectivenessinHeatingMode();


  boost::optional<Schedule> zoneAirDistributionEffectivenessSchedule() const;

  bool setZoneAirDistributionEffectivenessSchedule(Schedule& schedule);

  void resetZoneAirDistributionEffectivenessSchedule();


  double zoneSecondaryRecirculationFraction() const;

  Quantity getZoneSecondaryRecirculationFraction(bool returnIP=false) const;

  bool isZoneSecondaryRecirculationFractionDefaulted() const;

  bool setZoneSecondaryRecirculationFraction(double zoneSecondaryRecirculationFraction);

  bool setZoneSecondaryRecirculationFraction(const Quantity& zoneSecondaryRecirculationFraction);

  void resetZoneSecondaryRecirculationFraction();

 protected:
  /// @cond
  typedef detail::DesignSpecificationZoneAirDistribution_Impl ImplType;

  explicit DesignSpecificationZoneAirDistribution(std::shared_ptr<detail::DesignSpecificationZoneAirDistribution_Impl> impl);

  friend class detail::DesignSpecificationZoneAirDistribution_Impl;
  friend class Model;
  friend class IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.model.DesignSpecificationZoneAirDistribution");
};

/** \relates DesignSpecificationZoneAirDistribution*/
typedef boost::optional<DesignSpecificationZoneAirDistribution> OptionalDesignSpecificationZoneAirDistribution;

/** \relates DesignSpecificationZoneAirDistribution*/
typedef std::vector<DesignSpecificationZoneAirDistribution> DesignSpecificationZoneAirDistributionVector;

} // model
} // openstudio

#endif // MODEL_DESIGNSPECIFICATIONZONEAIRDISTRIBUTION_HPP

