
#include "dynamics2d_smartobject_model.h"
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_gripping.h>
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_engine.h>

namespace argos {


   static const Real OBJECT_MASS               = 2.4f;  //0.4 originally

   static const Real OBJECT_RADIUS             = 0.065f;
   static const Real OBJECT_HEIGHT             = 0.12f;  //0.08f, real = 0.115f

   /****************************************/
   /****************************************/

   CDynamics2DSmartObjectModel::CDynamics2DSmartObjectModel(CDynamics2DEngine& c_engine,
                                                      CSmartObjectEntity& c_entity) :
      CDynamics2DStretchableObjectModel(c_engine, c_entity),
      m_cSmartObjectEntity(c_entity){
      /* Create the body with initial position and orientation */
      cpBody* ptBody =
         cpSpaceAddBody(GetDynamics2DEngine().GetPhysicsSpace(),
                        cpBodyNew(OBJECT_MASS,
                                  cpMomentForCircle(OBJECT_MASS,
                                                    0.0f,
                                                    OBJECT_RADIUS + OBJECT_RADIUS,
                                                    cpvzero)));
      const CVector3& cPosition = GetEmbodiedEntity().GetOriginAnchor().Position;
      ptBody->p = cpv(cPosition.GetX(), cPosition.GetY());
      CRadians cXAngle, cYAngle, cZAngle;
      GetEmbodiedEntity().GetOriginAnchor().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
      cpBodySetAngle(ptBody, cZAngle.GetValue());
      /* Create the body shape */
      cpShape* ptShape =
         cpSpaceAddShape(GetDynamics2DEngine().GetPhysicsSpace(),
                         cpCircleShapeNew(ptBody,
                                          OBJECT_RADIUS,
                                          cpvzero));
      ptShape->e = 0.0; // No elasticity
      ptShape->u = 0.65; // Lots of friction  //0.7
      /* Constrain the actual base body to follow the diff steering control */
      //m_cDiffSteering.AttachTo(ptBody);
      
       /* The shape is grippable */
        /* SetGrippable(new CDynamics2DGrippable(GetEmbodiedEntity(),
                                               ptShape));*/
      
      /* Set the body so that the default methods work as expected */
      SetBody(ptBody, OBJECT_HEIGHT);
     /* Friction with ground */
      //SetLinearFriction(0.0f, c_engine.GetCylinderLinearFriction());
      //SetAngularFriction(0.0f, c_engine.GetCylinderAngularFriction());
     // SetLinearFriction(0.0f, m_fCylinderLinearFriction);
     // SetAngularFriction(0.0f, m_fCylinderAngularFriction);
             /* Friction with ground */
 	//SetLinearFriction(0.0f, 1.49f);
 	SetLinearFriction(0.0f, 1.7f);
 	SetAngularFriction(0.0f, 1.49f);
   }

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_DYNAMICS2D_OPERATIONS_ON_ENTITY(CSmartObjectEntity, CDynamics2DSmartObjectModel);

   /****************************************/
   /****************************************/

}
