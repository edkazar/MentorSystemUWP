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

MainPage::MainPage()
{
	InitializeComponent();
	myController = ref new ControlCenter();

	redColor = ref new SolidColorBrush(Windows::UI::Colors::Red);
	greenColor = ref new SolidColorBrush(Windows::UI::Colors::Green);
	tealColor = ref new SolidColorBrush(Windows::UI::Colors::Teal);
	goldColor = ref new SolidColorBrush(Windows::UI::Colors::Gold);

	ColoredRectangle->PointerEntered += ref new PointerEventHandler(this, &MainPage::EnteringRectangle);

	ColoredRectangle->Holding += ref new HoldingEventHandler(this, &MainPage::HoldingRectangle);
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
	polyline1->StrokeThickness = 3;

	PointCollection^ points = ref new PointCollection();
	points->Append(Windows::Foundation::Point(0, 0));
	points->Append(Windows::Foundation::Point(500, 10));
	polyline1->Points = points;

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


void MentorSystemUWP::MainPage::imagesPanelTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	ColoredRectangle->Fill = tealColor;

	Point tappedPosition = e->GetPosition(imagesPanel);

	if (myController->getIconAnnotationSelectedFlag())
	{
		Uri^ iconUri = ref new Uri(myController->getSelectedIconPath());
		BitmapImage^ iconBitmap = ref new BitmapImage(iconUri);
		Image^ iconImage = ref new Image();
		iconImage->Source = iconBitmap;

		iconImage->Width = 150; iconImage->Height = 150;
		iconImage->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left;
		iconImage->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
		imagesPanel->Children->Append(iconImage);
		iconImage->Margin = *(ref new Thickness(tappedPosition.X, tappedPosition.Y, 0, 0));

		//iconImage->PointerMoved += ref new PointerEventHandler(this, &MainPage::DraggingImage);
		iconImage->ManipulationStarted += ref new ManipulationStartedEventHandler(this, &MainPage::IconImage_ManipulationStarted);
		iconImage->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &MainPage::IconImage_ManipulationDelta);
		iconImage->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &MainPage::IconImage_ManipulationCompleted);
		iconImage->ManipulationMode = iconImage->ManipulationMode + Windows::UI::Xaml::Input::ManipulationModes::TranslateX;
		iconImage->ManipulationMode = iconImage->ManipulationMode + Windows::UI::Xaml::Input::ManipulationModes::TranslateY;
		iconImage->RenderTransform = image_Transform;

		myController->setIconAnnotationSelectedFlag(0);
		myController->setSelectedIconPath(ref new String());
	}
}

void MentorSystemUWP::MainPage::ExitButtonClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Application::Current->Exit();
}

void MentorSystemUWP::MainPage::DraggingImage(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	Windows::UI::Input::PointerPoint^ currentPositionInPanel = e->GetCurrentPoint(imagesPanel);
	Windows::UI::Input::PointerPoint^ currentPositionInIcon = e->GetCurrentPoint(dynamic_cast<Image^>(sender));
	
	dynamic_cast<Image^>(sender)->Margin = *(ref new Thickness(((currentPositionInPanel->RawPosition.X) - (currentPositionInIcon->RawPosition.X)),
		((currentPositionInPanel->RawPosition.Y) - (currentPositionInIcon->RawPosition.Y)), 0, 0));

	greetingOutput->Text = "Tapped Location: (" + currentPositionInPanel->RawPosition.X.ToString() + "," + currentPositionInPanel->RawPosition.Y.ToString() + ")";
	//Windows::UI::Input::PointerPoint^ currentPosition = e->>GetCurrentPoint();
	//currentPosition->
	//currentPosition.Position
}

void MentorSystemUWP::MainPage::IconImage_ManipulationStarted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e)
{
	//greetingOutput->Text = "Icon name: " + dynamic_cast<Image^>(sender)->Name;
	auto selectedIcon = dynamic_cast<Image^>(sender);
	selectedIcon->Opacity = 0.4;
}


void MentorSystemUWP::MainPage::IconImage_ManipulationDelta(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	//auto selectedIcon = dynamic_cast<Image^>(sender);
	//selectedIcon->RenderTransform.TranslateX += e->Delta.Translation.X;
	this->image_Transform->TranslateX += e->Delta.Translation.X;
	this->image_Transform->TranslateY += e->Delta.Translation.Y;
}


void MentorSystemUWP::MainPage::IconImage_ManipulationCompleted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{
	auto selectedIcon = dynamic_cast<Image^>(sender);
	selectedIcon->Opacity = 1;
}
