/**
 * @file <argos3/plugins/robots/object/simulator/dynamics2d_smartobject_model.h>
 * @author Piotr Rochala
 */

#ifndef DYNAMICS2D_SMARTOBJECT_MODEL_H
#define DYNAMICS2D_SMARTOBJECT_MODEL_H

namespace argos {
   class CDynamics2DGrippable;
   class CDynamics2DCylinderModel;
}

#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_stretchable_object_model.h>
#include <argos3/plugins/robots/smart-object/simulator/smartobject_entity.h>

namespace argos {

   class CDynamics2DSmartObjectModel : public CDynamics2DStretchableObjectModel {

   public:

      CDynamics2DSmartObjectModel(CDynamics2DEngine& c_engine,
                               CSmartObjectEntity& c_entity);
      virtual ~CDynamics2DSmartObjectModel() {}      

  private:

      CSmartObjectEntity& m_cSmartObjectEntity;
     // cpFloat m_fCylinderLinearFriction = 1.49;
     // cpFloat m_fCylinderAngularFriction = 1.49;
   };

}

#endif
