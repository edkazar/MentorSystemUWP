///////////////////////////////////////////////////////////////////
/*
* Mentor System Application
* System for Telemementoring with Augmented Reality (STAR) Project
* Intelligent Systems and Assistive Technology (ISAT) Laboratory
* Purdue University School of Industrial Engineering
*
* Code programmed by: Edgar Javier Rojas Muñoz
* advised by the professor: Juan Pablo Wachs, Ph.D
*/
//---------------------------------------------------------------//
/*                        CODE OVERVIEW
* Name: ControlCenter.cpp
*
* Overview: .cpp of ControlCenter.h
*/
///////////////////////////////////////////////////////////////////

//Include its header file
#include "ControlCenter.h"

/*
* Method Overview: Constructor of the class
* Parameters: None
* Return: Instance of the class
*/
ControlCenter::ControlCenter()
{
	IconAnnotationSelected = 0;

	IconAnnotationPath = ref new String();
}

/*
* Method Overview: Retrieves the icon annotation selected flag
* Parameters: None
* Return: Value of the icon annotation selected
*/
int ControlCenter::getIconAnnotationSelectedFlag()
{
	return IconAnnotationSelected;
}

/*
* Method Overview: Sets the icon annotation selected flag
* Parameters: Value to set the flag to
* Return: None
*/
void ControlCenter::setIconAnnotationSelectedFlag(int pFlag)
{
	IconAnnotationSelected = pFlag;
}

/*
* Method Overview: Gets the path to the selected icon annotation
* Parameters: None
* Return: Path to the selected icon annotation
*/
String^ ControlCenter::getSelectedIconPath()
{
	return IconAnnotationPath;
}

/*
* Method Overview: Sets the path to the selected icon annotation
* Parameters: Path to the selected icon annotation
* Return: None
*/
//
void ControlCenter::setSelectedIconPath(String^ pPath)
{
	IconAnnotationPath = pPath;
}