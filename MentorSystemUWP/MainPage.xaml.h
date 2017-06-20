//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace MentorSystemUWP
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Rectangle_DoubleTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs^ e);
		void HoldingRectangle(Platform::Object^ sender, Windows::UI::Xaml::Input::HoldingRoutedEventArgs^ e);
		void EnteringRectangle(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void iconPanelImageTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
		void imagesPanelTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
		void ExitButtonClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void IconImage_ManipulationStarted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e);
		void IconImage_ManipulationDelta(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
		void IconImage_ManipulationCompleted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);

		void CreateButtonsColor();
		void CreateIconAnnotation(Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
		void ResetLineAnnotation();

		void EraseAllButtonClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void LinesButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void LinesButtonUnchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void PointsButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void PointsButtonUnchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void LineDrawing(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void LineStopped(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void PointerOverTrashBin(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void PointerLeftTrashBin(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
	};
}
