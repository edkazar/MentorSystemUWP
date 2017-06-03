//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

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
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

SolidColorBrush^ redColor;
SolidColorBrush^ greenColor;
SolidColorBrush^ tealColor;
SolidColorBrush^ goldColor;

MainPage::MainPage()
{
	InitializeComponent();

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
}

void MentorSystemUWP::MainPage::EnteringRectangle(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	ColoredRectangle->Fill = goldColor;
}
