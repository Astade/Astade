#include "AstadeFrame.h"
#include <wx/timer.h>
#include <wx/utils.h>

BEGIN_EVENT_TABLE(AstadeFrame,wxFrame)
	EVT_TREE_ITEM_EXPANDING(ID_ASTADETREE, AstadeFrame::ExpandNode)
	EVT_TREE_ITEM_COLLAPSED(ID_ASTADETREE, AstadeFrame::CollapseNode)
	EVT_TREE_ITEM_RIGHT_CLICK(ID_ASTADETREE,AstadeFrame::OnRightMouseClick)
 	EVT_TREE_SEL_CHANGED(ID_ASTADETREE,AstadeFrame::OnSelChanged)
 	EVT_UPDATE_UI(ID_ASTADETREE, AstadeFrame::DoUpdate)
	EVT_MENU(ID_ACTIVECONFIGURATION, AstadeFrame::SetAsActive)
	EVT_MENU(ID_ADDATTRIBUTES, AstadeFrame::AddAttributes)
	EVT_MENU(ID_ADDATTRIBUTE, AstadeFrame::AddAttribute)
	EVT_MENU(ID_ADDCLASSES, AstadeFrame::AddClassesFolder)
	EVT_MENU(ID_ADDCLASS, AstadeFrame::AddClass)
	EVT_MENU(ID_ADDCOMPONENTFOLDER, AstadeFrame::AddComponentFolder)
	EVT_MENU(ID_ADDCOMPONENT, AstadeFrame::AddComponent)
	EVT_MENU(ID_ADDCONFIGURATION, AstadeFrame::AddConfiguration)
	EVT_MENU(ID_ADDCONSTRUCTOR, AstadeFrame::AddConstructor)
	EVT_MENU(ID_ADDDESTRUCTOR, AstadeFrame::AddDestructor)
	EVT_MENU(ID_ADDOPERATIONS, AstadeFrame::AddOperations)
	EVT_MENU(ID_ADDOPERATION, AstadeFrame::AddOperation)
	EVT_MENU(ID_ADDRELATION, AstadeFrame::AddRelation)
	EVT_MENU(ID_ADDTOCOMPONENET, AstadeFrame::AddToComponent)
	EVT_MENU(ID_ADDPACKAGE, AstadeFrame::AddPackage)
	EVT_MENU(ID_ADDPARAMETERS, AstadeFrame::AddParameters)
	EVT_MENU(ID_ADDPARAMETER, AstadeFrame::AddParameter)
	EVT_MENU(ID_ADDRELATIONS, AstadeFrame::AddRelations)
	EVT_MENU(ID_ADDTYPES, AstadeFrame::AddTypes)
	EVT_MENU(ID_COMPLETERELATION, AstadeFrame::CompleteRelation)
	EVT_MENU(ID_EDIT, AstadeFrame::Edit)
	EVT_MENU(ID_EDITIMPLEMENTATION, AstadeFrame::EditImplementation)
	EVT_MENU(ID_EDITSPECIFICATION, AstadeFrame::EditSpecification)
	EVT_MENU(ID_FEATURES, AstadeFrame::Features)
	EVT_MENU(ID_GENCODE, AstadeFrame::CallCoder)
	EVT_MENU(ID_MNU_HELP, AstadeFrame::DisplayHelp)
	EVT_MENU(ID_MNU_INFO, AstadeFrame::DisplayInfo)
	EVT_MENU(ID_REGENERATE, AstadeFrame::Regenerate)
	EVT_MENU(ID_REMOVEFROMCOMPONENET, AstadeFrame::RemoveFromComponent)
	EVT_MENU(ID_SETEDITORS, AstadeFrame::DirDialog)
END_EVENT_TABLE()
