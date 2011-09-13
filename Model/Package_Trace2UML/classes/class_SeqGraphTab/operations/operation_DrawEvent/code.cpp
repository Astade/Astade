int aEventID = dataBase->GetEventID(eventNumber);

if (aEventID == ID_RETURN ||
	aEventID == ID_GLOBALRETURN ||
	aEventID == ID_SELFRETURN)
{
	int stop = dataBase->GetDestinationIndex(eventNumber);
	if (thickness[stop] > 0)
		--thickness[stop];
}

if (aEventID == ID_TASKSWITCH)
	if (thickness[dataBase->GetSourceIndex(eventNumber)] > 0)
		--thickness[dataBase->GetSourceIndex(eventNumber)];

if (aEventID == ID_EXIST)
{
	if (thickness[dataBase->GetDestinationIndex(eventNumber)] < 0)
		thickness[dataBase->GetDestinationIndex(eventNumber)] = 0;
}

bool shouldDraw = true;

if (clip)
{
    int yPixel = dataBase->GetTime2Y(eventNumber);

    if (yPixel+10 < m_scroll || yPixel-80 > m_scrollEnd)
        shouldDraw = false;
}

if (!shouldDraw && aEventID != ID_RECEIVE && aEventID != ID_SELFRECEIVE
                && aEventID != ID_SEND    && aEventID != ID_SELFSEND)
{
	int stop = dataBase->GetDestinationIndex(eventNumber);
    if (aEventID == ID_GLOBALCALL ||
        aEventID == ID_CALL ||
        aEventID == ID_SELFCALL)
    {
		if (thickness[stop] < 0)
			thickness[stop] = 0;

		++thickness[stop];
    }
    else if (aEventID == ID_CREATE ||
        aEventID == ID_GLOBALCREATE)
    {
        thickness[stop] = 0;
    }
    else if (aEventID == ID_DELETE ||
        aEventID == ID_GLOBALDELETE)
    {
        thickness[stop] = -1;
    }
    dataBase->SetThickness(eventNumber,thickness);
    return;
}
else
    dataBase->SetThickness(eventNumber,thickness);

if (shouldDraw)
{
    dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("SEA GREEN")), 1, wxSOLID));
    dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("WHITE")), wxSOLID));

    //Uncomment for debugging
    //dc.DrawLine(0,dataBase->GetTime2Y(eventNumber),dataBase->GetGraphWidth(),dataBase->GetTime2Y(eventNumber));

    if (aEventID == ID_PAUSE)
        for (int i = 0; i < dataBase->GetClassCount(); i++)
            DrawPause(dc, i, eventNumber, thickness[i]);
    else
        for (int i = 0; i < dataBase->GetClassCount(); i++)
            DrawLifeLine(dc, i, eventNumber, thickness[i]);
}

switch (dataBase->GetEventID(eventNumber))
{
	case ID_COMMENT:
		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("PURPLE")), 1, wxLONG_DASH));
		dc.DrawLine(0, dataBase->GetTime2Y(eventNumber)-14, dataBase->GetGraphWidth(), dataBase->GetTime2Y(eventNumber) - 14);
		dc.DrawText(dataBase->GetLabel(eventNumber), 14, dataBase->GetTime2Y(eventNumber) - 14);
	break;

	case ID_SEND:
	case ID_SELFSEND:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int stop  = dataBase->GetDestinationIndex(eventNumber);
		if (thickness[stop] < 0)
			thickness[stop] = 0;
		eventQueue[stop].push_back(eventNumber);

		if (start > stop)
			dataBase->SetSourceX(start,GetLeftSide(start));
		else
			dataBase->SetSourceX(start,GetRightSide(start));
	}
	break;

	case ID_NOTE:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int yPixel = dataBase->GetTime2Y(eventNumber)-6;
		int xPixel = dataBase->GetClassMiddle(start);
        int hight = dataBase->GetTime2Y(eventNumber) - dataBase->GetTime2Y(eventNumber-1) - 2;

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("WHITE")),1,wxSOLID ));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("WHITE")),wxSOLID));
		dc.DrawRectangle(xPixel-32+3, yPixel-hight+3, 102, hight);

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("RED")),1,wxSOLID ));

        dc.DrawLine(xPixel-22,yPixel-hight+3,xPixel+70,yPixel-hight+3);
        dc.DrawLine(xPixel-32,yPixel+3,xPixel+70,yPixel+3);
        dc.DrawLine(xPixel-32,yPixel+3,xPixel-32,yPixel-hight+10);
        dc.DrawLine(xPixel+70,yPixel-hight+3,xPixel+70,yPixel+3);

        dc.DrawLine(xPixel-32,yPixel-hight+10,xPixel-22,yPixel-hight+3);
        dc.DrawLine(xPixel-22,yPixel-hight+10,xPixel-22,yPixel-hight+3);
        dc.DrawLine(xPixel-32,yPixel-hight+10,xPixel-22,yPixel-hight+10);

        wxString name = dataBase->GetLabel(eventNumber) + wxS(" ");
        wxString lineText;
        int line = 0;
        do
        {
            lineText = name;
            wxCoord w,h;
            do
            {
                dc.GetTextExtent(lineText, &w, &h);
                if (w>94)
                    lineText.RemoveLast();
            } while (w > 98);

            while ((lineText.Find(' ') != wxNOT_FOUND || lineText.Find('-') != wxNOT_FOUND) &&
                   lineText.Last() != ' ' && lineText.Last() != '-')
                   lineText.RemoveLast();

            dc.DrawText(lineText, xPixel-29, yPixel-hight+12+(h*line));
            name.Remove(0,lineText.size());
            line++;
        } while (line < 5 && !name.empty());
	}
	break;

	case ID_STATECHANGE:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int yPixel = dataBase->GetTime2Y(eventNumber)-6;
		int xPixel = dataBase->GetClassMiddle(start);

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("BLUE")),1,wxSOLID ));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("YELLOW")),wxSOLID));
		dc.DrawRoundedRectangle(xPixel-42, yPixel-12, 84, 18, 3);

		wxString name = dataBase->GetLabel(eventNumber);
		wxCoord w,h;
		dc.GetTextExtent(name, &w, &h);
		dc.DrawText(name, xPixel-(w/2), yPixel-(h/2)-3);
	}
	break;

	case ID_GLOBALCALL:
	{
		int stop = dataBase->GetDestinationIndex(eventNumber);
		int startPixel;
		int stopPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber)-5;

		if (thickness[stop] < 0)
			thickness[stop] = 0;

		DrawStartExecution(dc, stop, yPixel);
		++thickness[stop];

		startPixel = 0;
		stopPixel = GetLeftSide(stop);

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("BLUE")), 1, wxSOLID));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("BLUE")), wxSOLID));
		DrawArrow(dc, startPixel, yPixel, stopPixel, yPixel, ARROWHEADSOLID, dataBase->GetLabel(eventNumber));
	}
	break;

	case ID_CALL:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int stop = dataBase->GetDestinationIndex(eventNumber);
		int startPixel;
		int stopPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber) - 5;

		if (thickness[stop] < 0)
			thickness[stop] = 0;

		DrawStartExecution(dc, stop, yPixel);
		++thickness[stop];

		if (start > stop)
		{
			startPixel = GetLeftSide(start);
			stopPixel = GetRightSide(stop);
		}
		else
		{
			startPixel = GetRightSide(start);
			stopPixel = GetLeftSide(stop);
		}

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("BLUE")), 1, wxSOLID));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("BLUE")), wxSOLID));
		DrawArrow(dc, startPixel, yPixel, stopPixel, yPixel, ARROWHEADSOLID, dataBase->GetLabel(eventNumber));
	}
	break;

	case ID_RECEIVE:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int stop  = dataBase->GetDestinationIndex(eventNumber);

		if (thickness[stop] < 0)
			thickness[stop] = 0;

		std::list<int>::iterator it;
		for (it = eventQueue[stop].begin(); it != eventQueue[stop].end(); ++it)
			if (dataBase->GetSourceIndex(*it) == start &&
				dataBase->GetLabel(*it) == dataBase->GetLabel(eventNumber))
				break;
		if (it != eventQueue[stop].end())
		{
			int startYPixel = dataBase->GetTime2Y(*it) - 3;
			eventQueue[stop].erase(it);

			int startPixel;
			int stopPixel;

			startPixel = dataBase->GetSourceX(start);

			if (start > stop)
				stopPixel = GetRightSide(stop);
			else
				stopPixel = GetLeftSide(stop);

			int stopYPixel = dataBase->GetTime2Y(eventNumber)-3;

			dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("BLUE")), 1, wxSOLID));
			dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("BLUE")), wxSOLID));
			DrawArrow(dc, startPixel, startYPixel, stopPixel, stopYPixel, ARROWHEADVEE, dataBase->GetLabel(eventNumber));
		}
		else
		{
			if (!eventQueue[stop].empty())
			{
				DrawLostEvent(dc,eventQueue[stop].front());
				eventQueue[stop].pop_front();
				DrawEvent(dc,eventNumber);
			}
			else
				DrawFoundEvent(dc,eventNumber);
		}
	}
	break;

	case ID_GLOBALRECEIVE:
	{
		int stop = dataBase->GetDestinationIndex(eventNumber);

		if (thickness[stop] < 0)
			thickness[stop] = 0;

		int startPixel = 0;
		int stopPixel;

		stopPixel = GetLeftSide(stop);

		int stopYPixel = dataBase->GetTime2Y(eventNumber)-3;
		int startYPixel = stopYPixel;

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("BLUE")), 1, wxSOLID));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("BLUE")), wxSOLID));
		DrawArrow(dc, startPixel, startYPixel, stopPixel, stopYPixel, ARROWHEADVEE, dataBase->GetLabel(eventNumber));
	}
	break;

	case ID_SELFRECEIVE:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int stop  = dataBase->GetDestinationIndex(eventNumber);

		if (thickness[stop] < 0)
			thickness[stop] = 0;

		std::list<int>::iterator it;
		for (it = eventQueue[stop].begin(); it != eventQueue[stop].end(); ++it)
			if (dataBase->GetSourceIndex(*it) == start &&
				dataBase->GetLabel(*it) == dataBase->GetLabel(eventNumber))
				break;
		if (it != eventQueue[stop].end())
		{
			int startYPixel = dataBase->GetTime2Y(*it) - 3;
			eventQueue[stop].erase(it);

			int startPixel = dataBase->GetSourceX(start);
			int stopPixel = GetRightSide(stop);
			int stopYPixel = dataBase->GetTime2Y(eventNumber) - 3;
			int midYPixel = startYPixel + (stopYPixel - startYPixel) / 2;

			dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("BLUE")), 1, wxSOLID));
			dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("BLUE")), wxSOLID));
			DrawArrow(dc, startPixel, startYPixel, startPixel+50, midYPixel, ARROWHEADNONE, dataBase->GetLabel(eventNumber));
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
		int yPixel = dataBase->GetTime2Y(eventNumber) - 12;

		if (thickness[stop] < 0)
			thickness[stop] = 0;

        int bogen = thickness[stop];
        if (bogen > MAXDEPTH)
            bogen = MAXDEPTH;

        bogen *= 4;
        bogen += 35;

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("BLUE")), 1, wxSOLID));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("BLUE")), wxSOLID));

		startPixel = dataBase->GetClassMiddle(dataBase->GetSourceIndex(eventNumber)) + bogen;
		stopPixel = GetRightSide(stop);
		DrawArrow(dc, startPixel, yPixel, stopPixel, yPixel, ARROWHEADNONE, dataBase->GetLabel(eventNumber));

		yPixel += 7;
		DrawStartExecution(dc,stop,yPixel);
		++thickness[stop];

		stopPixel = GetRightSide(stop);

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("BLUE")), 1, wxSOLID));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("BLUE")), wxSOLID));
		dc.DrawLine(startPixel, yPixel-7, startPixel, yPixel);
		DrawArrow(dc, startPixel, yPixel, stopPixel, yPixel, ARROWHEADSOLID, wxEmptyString);
	}
	break;

	case ID_GLOBALRETURN:
	{
		int start = dataBase->GetDestinationIndex(eventNumber);
		int startPixel;
		int stopPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber)-5;

		++thickness[start];
		startPixel = GetLeftSide(start);
		stopPixel = 0;
		--thickness[start];

		DrawEndExecution(dc, start, eventNumber);
		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("BLUE")), 1, wxSHORT_DASH));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("BLUE")), wxSOLID));
		DrawArrow(dc, startPixel,
					yPixel, stopPixel, yPixel, ARROWHEADVEE, dataBase->GetLabel(eventNumber));
	}
	break;

	case ID_RETURN:
	{
		int start = dataBase->GetDestinationIndex(eventNumber);
		int stop = dataBase->GetSourceIndex(eventNumber);
		int startPixel;
		int stopPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber) - 5;
		int relEvent = dataBase->GetRelEvent(eventNumber);
		if (relEvent == 0)
			relEvent = eventNumber-1;

		++thickness[start];
		if (start > stop)
		{
			startPixel = GetLeftSide(start, relEvent);
			stopPixel = GetRightSide(stop);
		}
		else
		{
			startPixel = GetRightSide(start);
			stopPixel = GetLeftSide(stop, relEvent);
		}
		--thickness[start];

		DrawEndExecution(dc, start, eventNumber);
		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("BLUE")), 1, wxSHORT_DASH));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("BLUE")), wxSOLID));
		DrawArrow(dc, startPixel,
					yPixel, stopPixel, yPixel, ARROWHEADVEE, dataBase->GetLabel(eventNumber));
	}
	break;

	case ID_TASKSWITCH:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int stop = dataBase->GetDestinationIndex(eventNumber);
		int startPixel;
		int stopPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber) - 5;

		if (thickness[stop] < 0)
			thickness[stop] = 0;

		DrawStartExecution(dc, stop, yPixel);
		++thickness[stop];

		++thickness[start];
		if (start > stop)
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

		DrawEndExecution(dc, start, eventNumber);
		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("BLUE")), 1, wxSHORT_DASH));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("BLUE")), wxSOLID));
		DrawArrow(dc, startPixel,
					yPixel, stopPixel, yPixel, ARROWHEADVEE, dataBase->GetLabel(eventNumber));
	}
	break;

	case ID_SELFRETURN:
	{
		int start = dataBase->GetDestinationIndex(eventNumber);
		DrawEndExecution(dc, start, eventNumber);
	}
	break;

	case ID_EXIST:
	case ID_CLASSBOX:
		DrawClassBox(dc, eventNumber, dataBase->GetDestinationIndex(eventNumber));
	break;

	case ID_CREATE:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int stop = dataBase->GetDestinationIndex(eventNumber);
		int startPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber) - dataBase->GetClassBoxHeight() / 2;

		if (start > stop)
			startPixel = GetLeftSide(start);
		else
			startPixel = GetRightSide(start);

		int offset = dataBase->GetClassBoxWidth(dataBase->GetDestinationIndex(eventNumber)) / 2;
		if (dataBase->GetSourceIndex(eventNumber) < dataBase->GetDestinationIndex(eventNumber))
			offset *= -1;

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("FOREST GREEN")), 1, wxSOLID));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("FOREST GREEN")), wxSOLID));
		DrawArrow(dc, startPixel,
					yPixel,
					dataBase->GetClassMiddle(dataBase->GetDestinationIndex(eventNumber))+offset,
					yPixel, ARROWHEADSOLID, wxS("create()"));
		thickness[dataBase->GetDestinationIndex(eventNumber)] = 0;
	}
	break;

	case ID_GLOBALCREATE:
	{
		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("FOREST GREEN")), 1, wxSOLID));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("FOREST GREEN")), wxSOLID));
		int yPixel = dataBase->GetTime2Y(eventNumber)-(dataBase->GetClassBoxHeight()/2);
		DrawArrow(dc, 0,
					yPixel,
					dataBase->GetClassMiddle(dataBase->GetDestinationIndex(eventNumber))-(dataBase->GetClassBoxWidth(dataBase->GetDestinationIndex(eventNumber))/2),
					yPixel, ARROWHEADSOLID, wxS("create()"));
		thickness[dataBase->GetDestinationIndex(eventNumber)] = 0;
	}
	break;

	case ID_DELETE:
	{
		int start = dataBase->GetSourceIndex(eventNumber);
		int stop = dataBase->GetDestinationIndex(eventNumber);
		int startPixel;
		int yPixel = dataBase->GetTime2Y(eventNumber) - 9;

		if (start > stop)
			startPixel = GetLeftSide(start);
		else
			startPixel = GetRightSide(start);

		DrawCross(dc, dataBase->GetClassMiddle(dataBase->GetDestinationIndex(eventNumber)), yPixel, wxS("SEA GREEN"));

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("RED")), 1, wxSOLID));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("RED")), wxSOLID));
		DrawArrow(dc, startPixel,
					yPixel,
					dataBase->GetClassMiddle(dataBase->GetDestinationIndex(eventNumber)),
					yPixel, ARROWHEADSOLID, wxS("delete()"));
		thickness[dataBase->GetDestinationIndex(eventNumber)] = -1;
	}
	break;

	case ID_GLOBALDELETE:
	{
		int yPixel = dataBase->GetTime2Y(eventNumber)-9;
		DrawCross(dc, dataBase->GetClassMiddle(dataBase->GetDestinationIndex(eventNumber)), yPixel, wxS("SEA GREEN"));

		dc.SetPen(*wxThePenList->FindOrCreatePen(wxTheColourDatabase->Find(wxS("RED")), 1, wxSOLID));
		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(wxTheColourDatabase->Find(wxS("RED")), wxSOLID));
		DrawArrow(dc, 0,
					yPixel,
					dataBase->GetClassMiddle(dataBase->GetDestinationIndex(eventNumber)),
					yPixel, ARROWHEADSOLID, wxS("delete()"));
		thickness[dataBase->GetDestinationIndex(eventNumber)] = -1;
	}
	break;
}

dataBase->SetThickness(eventNumber,thickness);
