if (isMouseOver())
	dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("RED"),2,wxSOLID));
else
    dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("BLUE"),1,wxLONG_DASH));

dc.DrawLine(absDrawnStartPoint.xCoord(),absDrawnStartPoint.yCoord(),absDrawnEndPoint.xCoord(),absDrawnEndPoint.yCoord());

glVector dir = (absDrawnStartPoint - absDrawnEndPoint).Dir();
dir *= 14;

glVector p1 = dir.RotateDegree(30) + absDrawnEndPoint;
glVector p2 = dir.RotateDegree(-30) + absDrawnEndPoint;

if (isMouseOver())
	dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("RED"),2,wxSOLID));
else
    dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("BLUE"),1,wxSOLID));

dc.DrawLine(absDrawnEndPoint.xCoord(),absDrawnEndPoint.yCoord(),p1.xCoord(),p1.yCoord());
dc.DrawLine(absDrawnEndPoint.xCoord(),absDrawnEndPoint.yCoord(),p2.xCoord(),p2.yCoord());
const_cast<glIncludeExtend*>(this)->myLabel.Draw(dc);
