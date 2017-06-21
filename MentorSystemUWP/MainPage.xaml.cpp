//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "ControlCenter.h"

using namespace MentorSystemUWP;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Shapes;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

ControlCenter^ myController;

SolidColorBrush^ redColor;
SolidColorBrush^ greenColor;
SolidColorBrush^ tealColor;
SolidColorBrush^ goldColor;

SolidColorBrush^ buttonCheckedColor;
SolidColorBrush^ buttonUncheckedColor;

Polyline^ LineAnnotation;

MainPage::MainPage()
{
	InitializeComponent();
	myController = ref new ControlCenter();

	redColor = ref new SolidColorBrush(Windows::UI::Colors::Red);
	greenColor = ref new SolidColorBrush(Windows::UI::Colors::Green);
	tealColor = ref new SolidColorBrush(Windows::UI::Colors::Teal);
	goldColor = ref new SolidColorBrush(Windows::UI::Colors::Gold);
	CreateButtonsColor();

	ResetLineAnnotation();

	ColoredRectangle->PointerEntered += ref new PointerEventHandler(this, &MainPage::EnteringRectangle);

	ColoredRectangle->Holding += ref new HoldingEventHandler(this, &MainPage::HoldingRectangle);
}

void MentorSystemUWP::MainPage::CreateButtonsColor()
{
	Windows::UI::Color tempRGBAColor;
	tempRGBAColor.R = 29;
	tempRGBAColor.G = 122;
	tempRGBAColor.B = 216;
	tempRGBAColor.A = 255;
	buttonCheckedColor = ref new SolidColorBrush(tempRGBAColor);

	tempRGBAColor.R = 182;
	tempRGBAColor.G = 175;
	tempRGBAColor.B = 175;
	tempRGBAColor.A = 255;
	buttonUncheckedColor = ref new SolidColorBrush(tempRGBAColor);
}

void MentorSystemUWP::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	greetingOutput->Text = "Hello, " + nameInput->Text + "!";
	ColoredRectangle->Fill = redColor;
}


void MentorSystemUWP::MainPage::Rectangle_DoubleTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs^ e)
{
	ColoredRectangle->Fill = greenColor;
}

void MentorSystemUWP::MainPage::HoldingRectangle(Platform::Object^ sender, Windows::UI::Xaml::Input::HoldingRoutedEventArgs^ e)
{
	ColoredRectangle->Fill = tealColor;

	Polyline^ polyline1 = ref new Polyline();
	polyline1->Stroke = ref new SolidColorBrush(Windows::UI::Colors::Aquamarine);
	polyline1->StrokeThickness = 5;

	PointCollection^ points = ref new PointCollection();
	points->Append(Windows::Foundation::Point(0, 0));
	points->Append(Windows::Foundation::Point(500, 10));
	polyline1->Points = points;

	polyline1->ManipulationStarted += ref new ManipulationStartedEventHandler(this, &MainPage::IconImage_ManipulationStarted);
	polyline1->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &MainPage::IconImage_ManipulationDelta);
	polyline1->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &MainPage::IconImage_ManipulationCompleted);
	polyline1->ManipulationMode = Windows::UI::Xaml::Input::ManipulationModes::Rotate;
	polyline1->ManipulationMode = polyline1->ManipulationMode + Windows::UI::Xaml::Input::ManipulationModes::Scale;
	polyline1->ManipulationMode = polyline1->ManipulationMode + Windows::UI::Xaml::Input::ManipulationModes::TranslateX;
	polyline1->ManipulationMode = polyline1->ManipulationMode + Windows::UI::Xaml::Input::ManipulationModes::TranslateY;
	polyline1->RenderTransform = ref new Windows::UI::Xaml::Media::CompositeTransform();

	drawingPanel->Children->Append(polyline1);
}

void MentorSystemUWP::MainPage::EnteringRectangle(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	ColoredRectangle->Fill = goldColor;
}

void MentorSystemUWP::MainPage::iconPanelImageTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{	
	auto selectedImage = dynamic_cast<Image^>(sender);
	auto selectedSource = dynamic_cast<BitmapImage^>(selectedImage->Source);
	Uri^ selectedUri = selectedSource->UriSource;

	myController->setIconAnnotationSelectedFlag(1);
	myController->setSelectedIconPath(selectedUri->AbsoluteUri);
}

void MentorSystemUWP::MainPage::PreparePointAnnotation(Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	float initial_point_distance = 5.0f;
	float angle;
	float val = PI / 180.0f;

	int counter;

	//create enough points to make a round shape
	for (counter = 0; counter <= 360; counter = counter + 18)
	{
		//gets the new angle value
		angle = counter*val;

		//Calculates trigonometric values of the point
		float cosComponent = cos(angle)*initial_point_distance;
		float senComponent = sin(angle)*initial_point_distance;

		//Calculates the new point
		float transfX = ((cosComponent)-(senComponent));
		float transfY = ((senComponent)+(cosComponent));

		//assigns the results
		LineAnnotation->Points->Append(Windows::Foundation::Point((transfX)+(e->GetPosition(imagesPanel).X), (transfY)+(e->GetPosition(imagesPanel).Y)));

	}
}

void MentorSystemUWP::MainPage::imagesPanelTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	ColoredRectangle->Fill = tealColor;
	
	if (myController->getIconAnnotationSelectedFlag())
	{
		CreateIconAnnotation(e);

		myController->setIconAnnotationSelectedFlag(0);
		myController->setSelectedIconPath(ref new String());
	}
	else if (buttonPoints->IsChecked->Value)
	{
		PreparePointAnnotation(e);

		drawingPanel->Children->Append(LineAnnotation);

		ResetLineAnnotation();
	}
}

void MentorSystemUWP::MainPage::CreateIconAnnotation(Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	// Annotation path retrieval
	Uri^ iconUri = ref new Uri(myController->getSelectedIconPath());
	BitmapImage^ iconBitmap = ref new BitmapImage(iconUri);
	Image^ iconImage = ref new Image();
	iconImage->Source = iconBitmap;
	
	// Annotation dimension and position
	Point tappedPosition = e->GetPosition(imagesPanel);
	iconImage->Width = 150; iconImage->Height = 150;
	iconImage->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left;
	iconImage->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
	imagesPanel->Children->Append(iconImage);
	iconImage->Margin = *(ref new Thickness(tappedPosition.X, tappedPosition.Y, 0, 0));

	// Annotation manipulators
	iconImage->ManipulationStarted += ref new ManipulationStartedEventHandler(this, &MainPage::IconImage_ManipulationStarted);
	iconImage->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &MainPage::IconImage_ManipulationDelta);
	iconImage->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &MainPage::IconImage_ManipulationCompleted);
	iconImage->ManipulationMode = Windows::UI::Xaml::Input::ManipulationModes::Rotate;
	iconImage->ManipulationMode = iconImage->ManipulationMode + Windows::UI::Xaml::Input::ManipulationModes::Scale;
	iconImage->ManipulationMode = iconImage->ManipulationMode + Windows::UI::Xaml::Input::ManipulationModes::TranslateX;
	iconImage->ManipulationMode = iconImage->ManipulationMode + Windows::UI::Xaml::Input::ManipulationModes::TranslateY;
	iconImage->RenderTransform = ref new Windows::UI::Xaml::Media::CompositeTransform();
}

void MentorSystemUWP::MainPage::ExitButtonClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Application::Current->Exit();
}

void MentorSystemUWP::MainPage::IconImage_ManipulationStarted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e)
{
	if ("Windows.UI.Xaml.Controls.Image" == sender->GetType()->ToString())
	{
		auto selectedElement = dynamic_cast<Image^>(sender);
		selectedElement->Opacity = 0.4;
	}
	else
	{
		auto selectedElement = dynamic_cast<Polyline^>(sender);
		selectedElement->Opacity = 0.4;
	}
}


void MentorSystemUWP::MainPage::IconImage_ManipulationDelta(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	Windows::UI::Xaml::Media::CompositeTransform^ myTransform;

	if ("Windows.UI.Xaml.Controls.Image" == sender->GetType()->ToString())
	{
		auto selectedElement = dynamic_cast<Image^>(sender);
		myTransform = dynamic_cast<CompositeTransform^>(selectedElement->RenderTransform);
	}
	else
	{
		auto selectedElement = dynamic_cast<Polyline^>(sender);
		myTransform = dynamic_cast<CompositeTransform^>(selectedElement->RenderTransform);
	}

	myTransform->Rotation += e->Delta.Rotation;
	myTransform->ScaleX *= e->Delta.Scale;
	myTransform->ScaleY *= e->Delta.Scale;
	myTransform->TranslateX += e->Delta.Translation.X;
	myTransform->TranslateY += e->Delta.Translation.Y;
}


void MentorSystemUWP::MainPage::IconImage_ManipulationCompleted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{
	if ("Windows.UI.Xaml.Controls.Image" == sender->GetType()->ToString())
	{
		auto selectedElement = dynamic_cast<Image^>(sender);
		selectedElement->Opacity = 1;

		if (TrashBinOpenImage->Opacity == 1)
		{
			unsigned int idx;
			imagesPanel->Children->IndexOf(selectedElement, &idx);
			imagesPanel->Children->RemoveAt(idx);
		}
	}
	else
	{
		auto selectedElement = dynamic_cast<Polyline^>(sender);
		selectedElement->Opacity = 1;

		if (TrashBinOpenImage->Opacity == 1)
		{
			unsigned int idx;
			drawingPanel->Children->IndexOf(selectedElement, &idx);
			drawingPanel->Children->RemoveAt(idx);
		}
	}
}



void MentorSystemUWP::MainPage::ResetLineAnnotation()
{
	LineAnnotation = ref new Polyline();
	LineAnnotation->Stroke = ref new SolidColorBrush(Windows::UI::Colors::Aquamarine);
	LineAnnotation->StrokeThickness = 7;
	LineAnnotation->ManipulationStarted += ref new ManipulationStartedEventHandler(this, &MainPage::IconImage_ManipulationStarted);
	LineAnnotation->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &MainPage::IconImage_ManipulationDelta);
	LineAnnotation->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &MainPage::IconImage_ManipulationCompleted);
	LineAnnotation->ManipulationMode = LineAnnotation->ManipulationMode + Windows::UI::Xaml::Input::ManipulationModes::TranslateX;
	LineAnnotation->ManipulationMode = LineAnnotation->ManipulationMode + Windows::UI::Xaml::Input::ManipulationModes::TranslateY;
	LineAnnotation->RenderTransform = ref new Windows::UI::Xaml::Media::CompositeTransform();
}

void MentorSystemUWP::MainPage::EraseAllButtonClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	imagesPanel->Children->Clear();
	drawingPanel->Children->Clear();
}

void MentorSystemUWP::MainPage::LinesButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	buttonLinesBorder->Background = buttonCheckedColor;
};


void MentorSystemUWP::MainPage::LinesButtonUnchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	buttonLinesBorder->Background = buttonUncheckedColor;
}


void MentorSystemUWP::MainPage::PointsButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	buttonPointsBorder->Background = buttonCheckedColor;
}


void MentorSystemUWP::MainPage::PointsButtonUnchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	buttonPointsBorder->Background = buttonUncheckedColor;
}


void MentorSystemUWP::MainPage::LineDrawing(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	if (buttonLines->IsChecked->Value)
	{
		LineAnnotation->Points->Append(Windows::Foundation::Point(e->GetCurrentPoint(imagesPanel)->Position.X, e->GetCurrentPoint(imagesPanel)->Position.Y));
	}
}

void MentorSystemUWP::MainPage::LineStopped(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	if (buttonLines->IsChecked->Value)
	{
		drawingPanel->Children->Append(LineAnnotation);

		ResetLineAnnotation();
	}
}


void MentorSystemUWP::MainPage::PointerOverTrashBin(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	TrashBinOpenImage->Opacity = 1;
	TrashBinClosedImage->Opacity = 0;
}


void MentorSystemUWP::MainPage::PointerLeftTrashBin(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	TrashBinOpenImage->Opacity = 0;
	TrashBinClosedImage->Opacity = 1;
}
