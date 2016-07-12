/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) 2008-2016, Alliance for Sustainable Energy, LLC. All rights reserved.
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

#ifndef ANALYSIS_WORKFLOWSTEP_IMPL_HPP
#define ANALYSIS_WORKFLOWSTEP_IMPL_HPP

#include "AnalysisAPI.hpp"
#include "AnalysisObject_Impl.hpp"

#include "InputVariable.hpp"

#include "../runmanager/lib/WorkItem.hpp"

namespace openstudio {
namespace analysis {

namespace detail {

  /** WorkflowStep_Impl is an AnalysisObject_Impl that is the implementation class for
   *  WorkflowStep. */
  class ANALYSIS_API WorkflowStep_Impl : public AnalysisObject_Impl {
   public:
    /** @name Constructors and Destructors */
    //@{

    WorkflowStep_Impl(const InputVariable& inputVariable);

    WorkflowStep_Impl(const runmanager::WorkItem& workItem);

    /** Constructor provided for deserialization; not for general use. */
    WorkflowStep_Impl(const boost::optional<InputVariable>& inputVariable,
                      const boost::optional<runmanager::WorkItem>& workItem);

    WorkflowStep_Impl(const WorkflowStep_Impl& other);

    virtual ~WorkflowStep_Impl() {}

    virtual AnalysisObject clone() const override;

    //@}
    /** @name Getters and Queries */
    //@{

    bool isInputVariable() const;

    bool isWorkItem() const;

    /** Returns this step's InputVariable. Modifications will automatically apply to and
     *  be registered by this WorkflowStep. Throws if not isInputVariable. */
    InputVariable inputVariable() const;

    /** Returns a dis-attached copy of this step's WorkItem. To change this step's data,
     *  modify the returned WorkItem and then pass the edited copy into set. Throws if not
     *  isWorkItem(). */
    runmanager::WorkItem workItem() const;

    /** Shortcut method for retrieving this WorkItem's runmanager::JobType. Throws if not
     *  isWorkItem(). */
    runmanager::JobType workItemType() const;

    /** Returns the type of the primary input file for this WorkflowStep. */
    boost::optional<FileReferenceType> inputFileType() const;

    /** Returns the type of the primary output file for this WorkflowStep. */
    boost::optional<FileReferenceType> outputFileType() const;

    /** Returns true if the proposedInputFileType and proposedOutputFileType would be acceptable
     *  for the current use of this WorflowStep. Returns false otherwise. */
    bool fileTypesAreCompatible(const boost::optional<FileReferenceType>& proposedInputFileType,
                                const boost::optional<FileReferenceType>& proposedOutputFileType) const;

    //@}
    /** @name Setters */
    //@{

    /** Sets this step to use inputVariable if such a change is compatible with this
     *  WorkflowStep's current use (in its parent Problem). */
    bool set(const InputVariable& inputVariable);

    /** Sets this step to use workItem if such a change is compatible with this
     *  WorkflowStep's current use (in its parent Problem). */
    bool set(const runmanager::WorkItem& workItem);

    //@}
    /** @name Protected in or Absent from Public Class */
    //@{

    virtual QVariant toVariant() const override;

    static WorkflowStep factoryFromVariant(const QVariant& variant, const VersionString& version);

    /// Relocate path data from originalBase to newBase.
    virtual void updateInputPathData(const openstudio::path& originalBase,
                                     const openstudio::path& newBase) override;

    //@}
   private:
    REGISTER_LOGGER("openstudio.analysis.WorkflowStep")

    boost::optional<InputVariable> m_inputVariable;
    boost::optional<runmanager::WorkItem> m_workItem;
  };

} // detail

} // analysis
} // openstudio

#endif // ANALYSIS_WORKFLOWSTEP_IMPL_HPP