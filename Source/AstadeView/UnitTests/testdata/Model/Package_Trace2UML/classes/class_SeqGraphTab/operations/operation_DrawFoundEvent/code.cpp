int start = dataBase->GetSourceIndex(eventNumber);
int stop = dataBase->GetDestinationIndex(eventNumber);
int startPixel;
int stopPixel;
int yPixel = dataBase->GetTime2Y(eventNumber)-5;

startPixel = dataBase->GetClassMiddle(start);
stopPixel = dataBase->GetClassMiddle(stop);

dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("RED"),1,wxSOLID ));
dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("RED"),wxSOLID));
dc.DrawCircle(startPixel, yPixel, 6);

dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("BLUE"),1,wxSOLID ));
dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("BLUE"),wxSOLID));
DrawArrow(dc, startPixel, yPixel, stopPixel, yPixel, ARROWHEADVEE, "");
