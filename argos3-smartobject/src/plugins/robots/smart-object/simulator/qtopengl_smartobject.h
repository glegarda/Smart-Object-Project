/**
 * @file <argos3/plugins/robots/object/simulator/qtopengl_smartobject.h>
 */

#ifndef QTOPENGL_SMARTOBJECT_H
#define QTOPENGL_SMARTOBJECT_H

namespace argos {
   class CQTOpenGLSmartObject;
   class CSmartObjectEntity;
}

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

namespace argos {

   class CQTOpenGLSmartObject {

   public:

      CQTOpenGLSmartObject();

      virtual ~CQTOpenGLSmartObject();

      virtual void Draw(CSmartObjectEntity& c_entity);

   protected:

      /** Sets a green plastic material */
      void SetGreenPlasticMaterial();
      /** Sets a red plastic material */
      void SetRedPlasticMaterial();
      /** Sets a bronze plastic material */
      void SetBronzePlasticMaterial();
      /** Sets a black plastic material */
      void SetBLackPlasticMaterial();
      /** Sets a colored LED material */
      void SetLEDMaterial(GLfloat f_red,
                          GLfloat f_green,
                          GLfloat f_blue);

      /** Renders the body */
      void RenderBody();
      /** A single LED of the ring */
      void RenderLED();

   private:

      /** Start of the display list index */
      GLuint m_unLists;

      /** E-puck wheel */
      GLuint m_unWheelList;

      /** Chassis display list */
      GLuint m_unChassisList;

      /** Body display list */
      GLuint m_unBodyList;
      GLuint m_unObjectList;

      /** LED display list */
      GLuint m_unLEDList;

      /** Number of vertices to display the round parts
          (wheels, chassis, etc.) */
      GLuint m_unVertices;

      /* Angle gap between two leds */
      GLfloat m_fLEDAngleSlice;

   };

}

#endif
