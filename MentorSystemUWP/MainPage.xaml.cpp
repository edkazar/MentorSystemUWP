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


void MentorSystemUWP::MainPage::Rectangle_DragEntered(Platform::Object^ sender, Windows::UI::Xaml::DragEventArgs^ e)
{
	//ColoredRectangle->Fill = tealColor;
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

	if (myController->getIconAnnotationSelectedFlag())
	{
		greetingOutput->Text = "Selected Icon Path: " + myController->getSelectedIconPath();
		myController->setIconAnnotationSelectedFlag(1);
		myController->setSelectedIconPath(ref new String());
	}
}


void MentorSystemUWP::MainPage::ExitButtonClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Application::Current->Exit();

}
