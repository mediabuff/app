#pragma once


#include "ca2/cube5/cube5.h"


namespace cube8
{

   class application;

} // namespace cube8

#define cubeApp(pcaapp) (*pcaapp->m_pappCube)
#define cubeApplication (cubeApp(get_app()))
#undef App
#define App(pcaapp) cubeApp(pcaapp)



#include "cube8_application.h"


