switch (event.GetId())
{
	case ID_240_180:
		xPixelSlider->SetValue(240);
		yPixelSlider->SetValue(180);
	break;

	case ID_320_240:
		xPixelSlider->SetValue(320);
		yPixelSlider->SetValue(240);
	break;

	case ID_640_480:
		xPixelSlider->SetValue(640);
		yPixelSlider->SetValue(480);
	break;

	case ID_800_600:
		xPixelSlider->SetValue(800);
		yPixelSlider->SetValue(600);
	break;

	case ID_1024_768:
		xPixelSlider->SetValue(1024);
		yPixelSlider->SetValue(768);
	break;

	case ID_1200_900:
		xPixelSlider->SetValue(1200);
		yPixelSlider->SetValue(900);
	break;

	case ID_1400_1050:
		xPixelSlider->SetValue(1400);
		yPixelSlider->SetValue(1050);
	break;

	case ID_1600_1200:
		xPixelSlider->SetValue(1600);
		yPixelSlider->SetValue(1200);
	break;

	case ID_1920_1440:
		xPixelSlider->SetValue(1920);
		yPixelSlider->SetValue(1440);
	break;

	case ID_2800_2100:
		xPixelSlider->SetValue(2800);
		yPixelSlider->SetValue(2100);
	break;

	case ID_3200_2400:
		xPixelSlider->SetValue(3200);
		yPixelSlider->SetValue(2400);
	break;

	case ID_4096_3072:
		xPixelSlider->SetValue(4096);
		yPixelSlider->SetValue(3072);
	break;

	case ID_6400_4800:
		xPixelSlider->SetValue(6400);
		yPixelSlider->SetValue(4800);
	break;
}

wxScrollEvent dummy;
OnSliderMove(dummy);