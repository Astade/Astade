BEGIN_EVENT_TABLE(ACPanel, wxScrolledWindow)
	EVT_MOTION(ACPanel::OnMouseMotion)
	EVT_LEAVE_WINDOW(ACPanel::OnLeave)
	EVT_ENTER_WINDOW(ACPanel::OnEnter)
	EVT_RIGHT_UP(ACPanel::OnRightClick)

	EVT_MENU(ID_DELETE, ACPanel::OnDelete)

END_EVENT_TABLE()
