/**
 * @file <argos3/plugins/robots/object/simulator/qtopengl_smartobject.cpp>
 */

#include "qtopengl_smartobject.h"
#include "smartobject_entity.h"
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/plugins/simulator/entities/led_equipped_entity.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_widget.h>

namespace argos {

   /****************************************/
   /****************************************/

   /* All measures are in meters */

   static const Real BODY_RADIUS                 = 0.065f;
   static const Real BODY_HEIGHT                 = 0.12f;      //original 0.08f                       

   static const Real LED_ELEVATION               = 0.085; //BODY_HEIGHT/2
   static const Real LED_HEIGHT                  = 0.035;  //0.04                               

   /****************************************/
   /****************************************/

   CQTOpenGLSmartObject::CQTOpenGLSmartObject() :
      m_unVertices(8),
      m_fLEDAngleSlice(360.0f / 8.0f) {
      /* Reserve the needed display lists */
      m_unLists = glGenLists(2);

      /* Assign indices for better referencing (later) */
      m_unBodyList    = m_unLists;
      m_unLEDList     = m_unLists + 1;
	   

      /* Create the body display list */
      glNewList(m_unBodyList, GL_COMPILE);
      RenderBody();
      glEndList();

      /* Create the LED display list */
      glNewList(m_unLEDList, GL_COMPILE);
      RenderLED();
      glEndList();
	  
   }

   /****************************************/
   /****************************************/

   CQTOpenGLSmartObject::~CQTOpenGLSmartObject() {
      glDeleteLists(m_unLists, 2);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLSmartObject::Draw(CSmartObjectEntity& c_entity) {
      /* Place the chassis */
      glCallList(m_unChassisList);
      /* Place the body */
      glCallList(m_unBodyList);
      /* Place the LEDs */
      glPushMatrix();
      CLEDEquippedEntity& cLEDEquippedEntity = c_entity.GetLEDEquippedEntity();
      const UInt32 un_leds_per_led = cLEDEquippedEntity.GetLEDs().size()/8;

      for(UInt32 i = 0; i < 8; i++) {
         const CColor& cColor = cLEDEquippedEntity.GetLED(i*un_leds_per_led).GetColor();
         //glRotatef(-m_fLEDAngleSlice, 0.0f, 0.0f, 1.0f);
         SetLEDMaterial(cColor.GetRed(),
                        cColor.GetGreen(),
                        cColor.GetBlue());
         glCallList(m_unLEDList);
         glRotatef(m_fLEDAngleSlice, 0.0f, 0.0f, 1.0f);
      }
      glPopMatrix();
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLSmartObject::SetGreenPlasticMaterial() {
      const GLfloat pfColor[]     = {   0.0f, 1.0f, 0.0f, 1.0f };
      const GLfloat pfSpecular[]  = {   0.9f, 0.9f, 0.9f, 1.0f };
      const GLfloat pfShininess[] = { 100.0f                   };
      const GLfloat pfEmission[]  = {   0.0f, 0.0f, 0.0f, 1.0f };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLSmartObject::SetRedPlasticMaterial() {
      const GLfloat pfColor[]     = {   1.0f, 0.0f, 0.0f, 1.0f };
      const GLfloat pfSpecular[]  = {   0.9f, 0.9f, 0.9f, 1.0f };
      const GLfloat pfShininess[] = { 100.0f                   };
      const GLfloat pfEmission[]  = {   0.0f, 0.0f, 0.0f, 1.0f };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLSmartObject::SetBronzePlasticMaterial() {
      const GLfloat pfColor[]     = { 0.2125f, 0.1275f, 0.054f, 1.0f        };
      const GLfloat pfSpecular[]  = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
      const GLfloat pfShininess[] = { 25.6f                 		    };
      const GLfloat pfEmission[]  = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLSmartObject::SetLEDMaterial(GLfloat f_red,
                                       GLfloat f_green,
                                       GLfloat f_blue) {
      const GLfloat pfColor[]     = { f_red, f_green, f_blue, 1.0f };
      const GLfloat pfSpecular[]  = {  0.0f,    0.0f,   0.0f, 1.0f };
      const GLfloat pfShininess[] = {  0.0f                        };
      const GLfloat pfEmission[]  = { f_red, f_green, f_blue, 1.0f };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
   }

  void CQTOpenGLSmartObject::SetBLackPlasticMaterial() {
      const GLfloat pfColor[]     = { 0.0f, 0.0f, 0.0f, 0.0f };
      const GLfloat pfSpecular[]  = {  0.0f,    0.0f,   0.0f, 1.0f };
      const GLfloat pfShininess[] = {  0.0f                        };
      const GLfloat pfEmission[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
   }


   /****************************************/
   /****************************************/

   void CQTOpenGLSmartObject::RenderBody() {
      /* Set material */
      SetBronzePlasticMaterial();
      CVector2 cVertex(BODY_RADIUS, 0.0f);
      CRadians cAngle(-CRadians::TWO_PI / m_unVertices);

      /* Bottom part */
      glBegin(GL_POLYGON);
      glNormal3f(0.0f, 0.0f, -1.0f);
      for(GLuint i = 0; i <= m_unVertices; i++) {
         glVertex3f(cVertex.GetX(), cVertex.GetY(), 0.0f);
         cVertex.Rotate(cAngle);
      }
      glEnd();

      /* Side surface */
      cAngle = -cAngle;
      CVector2 cNormal(1.0f, 0.0f);
      cVertex.Set(BODY_RADIUS, 0.0f);
      glBegin(GL_QUAD_STRIP);
      for(GLuint i = 0; i <= m_unVertices; i++) {
         glNormal3f(cNormal.GetX(), cNormal.GetY(), 0.0f);
         //glVertex3f(cVertex.GetX(), cVertex.GetY(), BODY_HEIGHT/2);
         glVertex3f(cVertex.GetX(), cVertex.GetY(), LED_ELEVATION);
         glVertex3f(cVertex.GetX(), cVertex.GetY(), 0.0f);
         cVertex.Rotate(cAngle);
         cNormal.Rotate(cAngle);
      }
      glEnd();
   }


   /****************************************/
   /****************************************/

   void CQTOpenGLSmartObject::RenderLED() {
     /* Side surface */
     CVector2 cVertex(BODY_RADIUS, 0.0f);
     CRadians cAngle(CRadians::TWO_PI / m_unVertices);
     CVector2 cNormal(1.0f, 0.0f);
     glBegin(GL_QUAD_STRIP);
     for(GLuint i = 0; i <= m_unVertices /8; i++) {
         glNormal3f(cNormal.GetX(), cNormal.GetY(), 0.0f);
         glVertex3f(cVertex.GetX(), cVertex.GetY(), LED_ELEVATION + LED_HEIGHT);
         glVertex3f(cVertex.GetX(), cVertex.GetY(), LED_ELEVATION);
         cVertex.Rotate(cAngle);
         cNormal.Rotate(cAngle);
      }
      glEnd();
      /* Top surface */
      cVertex.Set(BODY_RADIUS, 0.0f);
      glBegin(GL_TRIANGLES);
      for(GLuint i = 0; i < m_unVertices /8; i++) {
         glVertex3f(0.0f, 0.0f, LED_ELEVATION + LED_HEIGHT);
         glVertex3f(cVertex.GetX(), cVertex.GetY(), LED_ELEVATION + LED_HEIGHT);
         cVertex.Rotate(cAngle); 
         glVertex3f(cVertex.GetX(), cVertex.GetY(), LED_ELEVATION + LED_HEIGHT);
      }
      glEnd();
	

      /* Top surface contours*/
      SetBLackPlasticMaterial();
      cVertex.Set(BODY_RADIUS, 0.0f);
      glBegin(GL_LINE_STRIP);
      for(GLuint i = 0; i < m_unVertices /8; i++) {
         glVertex3f(cVertex.GetX(), cVertex.GetY(), LED_ELEVATION + LED_HEIGHT);
         cVertex.Rotate(cAngle); 
         glVertex3f(cVertex.GetX(), cVertex.GetY(), LED_ELEVATION + LED_HEIGHT);
      }
      glEnd();

   }

   /****************************************/
   /****************************************/

   class CQTOpenGLOperationDrawObjectNormal : public CQTOpenGLOperationDrawNormal {
   public:
      void ApplyTo(CQTOpenGLWidget& c_visualization,
                   CSmartObjectEntity& c_entity) {
         static CQTOpenGLSmartObject m_cModel;
         c_visualization.DrawRays(c_entity.GetControllableEntity());
         c_visualization.DrawEntity(c_entity.GetEmbodiedEntity());
         m_cModel.Draw(c_entity);
      }
   };

   class CQTOpenGLOperationDrawObjectSelected : public CQTOpenGLOperationDrawSelected {
   public:
      void ApplyTo(CQTOpenGLWidget& c_visualization,
                   CSmartObjectEntity& c_entity) {
         c_visualization.DrawBoundingBox(c_entity.GetEmbodiedEntity());
      }
   };

   REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawNormal, CQTOpenGLOperationDrawObjectNormal, CSmartObjectEntity);

   REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawSelected, CQTOpenGLOperationDrawObjectSelected, CSmartObjectEntity);

   /****************************************/
   /****************************************/

}
