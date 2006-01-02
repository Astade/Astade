dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("SEA GREEN"),1,wxSOLID));
dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("WHITE"),wxSOLID));

if ((dataBase->GetEventID(eventNumber)== ID_RETURN) ||
	(dataBase->GetEventID(eventNumber)==ID_GLOBALRETURN) ||
	(dataBase->GetEventID(eventNumber)==ID_SELFRETURN)
	)
	if (thickness[dataBase->GetDestinationIndex(eventNumber)] > 0)
		--thickness[dataBase->GetDestinationIndex(eventNumber)];

for (int i=0; i<dataBase->GetClassCount(); i++)
	DrawLifeLine(dc,i,eventNumber,thickness[i]);

switch (dataBase->GetEventID(eventNumber))
{
	case ID_COMMENT:
		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("PURPLE"),1,wxLONG_DASH ));
		dc.DrawLine(0,dataBase->GetTime2Y(eventNumber)-10,dataBase->GetGraphWidth(),dataBase->GetTime2Y(eventNumber)-10);
		dc.DrawText(dataBase->GetLabel(eventNumber),10,dataBase->GetTime2Y(eventNumber)-10);
	break;

	case ID_SEND:
	case ID_SELFSEND:
	{
		int stop = dataBase->GetDestinationIndex(eventNumber);
		if (thickness[stop] < 0)
			thickness[stop] = 0;

		eventQueue[dataBase->GetDestinationIndex(eventNumber)].push_back(eventNumber);
	}
	break;

	case ID_GLOBALCALL:
	{
		int stop = dataBase->GetDestinationIndex(eventNumber);
		int startPixel;
		int stopPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber);

		if (thickness[stop] < 0)
			thickness[stop] = 0;

		DrawStartExecution(dc,stop,yPixel);
		++thickness[stop];

		startPixel = 0;
		stopPixel = GetLeftSide(stop);

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("BLUE"),1,wxSOLID ));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("BLUE"),wxSOLID));
		DrawArrow(dc, startPixel, yPixel, stopPixel, yPixel, ARROWHEADSOLID, dataBase->GetLabel(eventNumber));
	}
	break;

	case ID_CALL:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int stop = dataBase->GetDestinationIndex(eventNumber);
		int startPixel;
		int stopPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber);

		if (thickness[stop] < 0)
			thickness[stop] = 0;

		DrawStartExecution(dc,stop,yPixel);
		++thickness[stop];

		if (start>stop)
		{
			startPixel = GetLeftSide(start);
			stopPixel = GetRightSide(stop);
		}
		else
		{
			startPixel = GetRightSide(start);
			stopPixel = GetLeftSide(stop);
		}

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("BLUE"),1,wxSOLID ));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("BLUE"),wxSOLID));
		DrawArrow(dc, startPixel, yPixel, stopPixel, yPixel, ARROWHEADSOLID, dataBase->GetLabel(eventNumber));
	}
	break;

	case ID_RECEIVE:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int stop = dataBase->GetDestinationIndex(eventNumber);

		if (thickness[stop] < 0)
			thickness[stop] = 0;

		if ((!eventQueue[stop].empty()) &&
			(dataBase->GetSourceIndex(eventQueue[stop].front()) == start) &&
			(dataBase->GetLabel(eventQueue[stop].front()) == dataBase->GetLabel(eventNumber))
			)
		{
			int startYPixel = dataBase->GetTime2Y(eventQueue[stop].front());
			eventQueue[stop].pop_front();

			int startPixel = dataBase->GetClassMiddle(start);
			int stopPixel = dataBase->GetClassMiddle(stop);
			int stopYPixel = dataBase->GetTime2Y(eventNumber);

			dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("BLUE"),1,wxSOLID ));
			dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("BLUE"),wxSOLID));
			DrawArrow(dc, startPixel, startYPixel, stopPixel, stopYPixel, ARROWHEADVEE, dataBase->GetLabel(eventNumber));
		}
		else
			DrawFoundEvent(dc,eventNumber);
	}
	break;

	case ID_SELFRECEIVE:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int stop = dataBase->GetDestinationIndex(eventNumber);

		if (thickness[stop] < 0)
			thickness[stop] = 0;

		if ((!eventQueue[stop].empty()) &&
			(dataBase->GetSourceIndex(eventQueue[stop].front()) == start) &&
			(dataBase->GetLabel(eventQueue[stop].front()) == dataBase->GetLabel(eventNumber))
			)
		{
			int startYPixel = dataBase->GetTime2Y(eventQueue[stop].front());
			eventQueue[stop].pop_front();

			int startPixel = dataBase->GetClassMiddle(start);
			int stopPixel = dataBase->GetClassMiddle(stop);
			int stopYPixel = dataBase->GetTime2Y(eventNumber);
			int midYPixel = startYPixel + (stopYPixel - startYPixel)/2;

			dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("BLUE"),1,wxSOLID ));
			dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("BLUE"),wxSOLID));
			DrawArrow(dc, startPixel, startYPixel, stopPixel+50, midYPixel, ARROWHEADNONE, dataBase->GetLabel(eventNumber));
			DrawArrow(dc, startPixel+50, midYPixel, stopPixel, stopYPixel, ARROWHEADVEE, wxEmptyString);
		}
		else
			DrawFoundEvent(dc,eventNumber);
	}
	break;

	case ID_SELFCALL:
	{
		int stop = dataBase->GetDestinationIndex(eventNumber);
		int startPixel;
		int stopPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber);

		if (thickness[stop] < 0)
			thickness[stop] = 0;

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("BLUE"),1,wxSOLID ));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("BLUE"),wxSOLID));

		startPixel = dataBase->GetClassMiddle(dataBase->GetSourceIndex(eventNumber)) + 50;
		stopPixel = GetRightSide(stop);
		DrawArrow(dc, startPixel, yPixel, stopPixel, yPixel, ARROWHEADNONE, dataBase->GetLabel(eventNumber));

		yPixel += 7;
		DrawStartExecution(dc,stop,yPixel);
		++thickness[stop];

		startPixel = dataBase->GetClassMiddle(dataBase->GetSourceIndex(eventNumber)) + 50;
		stopPixel = GetRightSide(stop);

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("BLUE"),1,wxSOLID ));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("BLUE"),wxSOLID));
		dc.DrawLine(startPixel,yPixel-7,startPixel,yPixel);
		DrawArrow(dc, startPixel, yPixel, stopPixel, yPixel, ARROWHEADSOLID, wxEmptyString);
	}
	break;

	case ID_GLOBALRETURN:
	{
		int start = dataBase->GetDestinationIndex(eventNumber);
		int startPixel;
		int stopPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber);

		++thickness[start];
		startPixel = GetLeftSide(start);
		stopPixel = 0;
		--thickness[start];

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("BLUE"),1,wxSHORT_DASH ));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("BLUE"),wxSOLID));
		DrawArrow(dc,startPixel,
					yPixel, stopPixel, yPixel,ARROWHEADVEE,dataBase->GetLabel(eventNumber));
		DrawEndExecution(dc,start,yPixel);
	}
	break;

	case ID_RETURN:
	{
		int start = dataBase->GetDestinationIndex(eventNumber);
		int stop = dataBase->GetSourceIndex(eventNumber);
		int startPixel;
		int stopPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber);

		++thickness[start];
		if (start>stop)
		{
			startPixel = GetLeftSide(start);
			stopPixel = GetRightSide(stop);
		}
		else
		{
			startPixel = GetRightSide(start);
			stopPixel = GetLeftSide(stop);
		}
		--thickness[start];

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("BLUE"),1,wxSHORT_DASH ));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("BLUE"),wxSOLID));
		DrawArrow(dc,startPixel,
					yPixel, stopPixel, yPixel,ARROWHEADVEE,dataBase->GetLabel(eventNumber));
		DrawEndExecution(dc,start,yPixel);
	}
	break;

	case ID_SELFRETURN:
	{
		int start = dataBase->GetDestinationIndex(eventNumber);
		int yPixel = dataBase->GetTime2Y(eventNumber);
		DrawEndExecution(dc,start,yPixel);
	}
	break;

	case ID_CLASSBOX:
		DrawClassBox(dc,eventNumber,dataBase->GetDestinationIndex(eventNumber));
	break;

	case ID_CREATE:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int stop = dataBase->GetDestinationIndex(eventNumber);
		int startPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber);

		if (start>stop)
			startPixel = GetLeftSide(start);
		else
			startPixel = GetRightSide(start);

		int offset = dataBase->GetClassBoxWidth()/2;
		if (dataBase->GetSourceIndex(eventNumber) < dataBase->GetDestinationIndex(eventNumber))
			offset *= -1;

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("FOREST GREEN"),1,wxSOLID ));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("FOREST GREEN"),wxSOLID));
		DrawArrow(dc,startPixel,
					yPixel,
					dataBase->GetClassMiddle(dataBase->GetDestinationIndex(eventNumber))+offset,
					yPixel,ARROWHEADSOLID,"create()");
		thickness[dataBase->GetDestinationIndex(eventNumber)] = 0;
	}
	break;

	case ID_EXIST:
		if (thickness[dataBase->GetDestinationIndex(eventNumber)] < 0)
			thickness[dataBase->GetDestinationIndex(eventNumber)] = 0;
	break;

	case ID_GLOBALCREATE:
		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("FOREST GREEN"),1,wxSOLID ));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("FOREST GREEN"),wxSOLID));
		DrawArrow(dc,0,
					dataBase->GetTime2Y(eventNumber),
					dataBase->GetClassMiddle(dataBase->GetDestinationIndex(eventNumber))-(dataBase->GetClassBoxWidth()/2),
					dataBase->GetTime2Y(eventNumber),ARROWHEADSOLID,"create()");
		thickness[dataBase->GetDestinationIndex(eventNumber)] = 0;
	break;

	case ID_DELETE:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int stop = dataBase->GetDestinationIndex(eventNumber);
		int startPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber);

		if (start>stop)
			startPixel = GetLeftSide(start);
		else
			startPixel = GetRightSide(start);

		DrawCross(dc,dataBase->GetClassMiddle(dataBase->GetDestinationIndex(eventNumber)),dataBase->GetTime2Y(eventNumber),"SEA GREEN");

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("RED"),1,wxSOLID ));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("RED"),wxSOLID));
		DrawArrow(dc,startPixel,
					yPixel,
					dataBase->GetClassMiddle(dataBase->GetDestinationIndex(eventNumber)),
					yPixel,ARROWHEADSOLID,"delete()");
		thickness[dataBase->GetDestinationIndex(eventNumber)] = -1;
	}
	break;

	case ID_GLOBALDELETE:
		DrawCross(dc,dataBase->GetClassMiddle(dataBase->GetDestinationIndex(eventNumber)),dataBase->GetTime2Y(eventNumber),"SEA GREEN");

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find("RED"),1,wxSOLID ));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find("RED"),wxSOLID));
		DrawArrow(dc,0,
					dataBase->GetTime2Y(eventNumber),
					dataBase->GetClassMiddle(dataBase->GetDestinationIndex(eventNumber)),
					dataBase->GetTime2Y(eventNumber),ARROWHEADSOLID,"delete()");
		thickness[dataBase->GetDestinationIndex(eventNumber)] = -1;
	break;

}