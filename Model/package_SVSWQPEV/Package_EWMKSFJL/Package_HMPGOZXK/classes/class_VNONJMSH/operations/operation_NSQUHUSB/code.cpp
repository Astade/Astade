if (isMouseOver())
	dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("RED"),2,wxSOLID));
else
  dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("BLUE"),1,wxSOLID));

glVector m = absCalculateCenterPoint();

double angle;

if (width<0)
	angle = -20 / radius();
else
	angle = 20 / radius();

absGetStartPoint();
absGetEndPoint();

glVector it(lastStartPoint);
glVector it2(it);

int count = 360;
do
{
	it2 = it;
	it = it.RotateRadians(angle);
	if (myEndNode.isInElement(m+it))
		it = lastEndPoint;
	glVector start = m+it;
	glVector end = m+it2;
	dc.DrawLine(start.xCoord(),start.yCoord(),end.xCoord(),end.yCoord());
} while ((count-- > 0) && (it != lastEndPoint));
