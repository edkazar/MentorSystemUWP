﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BINDING_DEBUG_OUTPUT
extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
#endif

#include "MainPage.xaml.h"

void ::MentorSystemUWP::MainPage::InitializeComponent()
{
    if (_contentLoaded)
    {
        return;
    }
    _contentLoaded = true;
    ::Windows::Foundation::Uri^ resourceLocator = ref new ::Windows::Foundation::Uri(L"ms-appx:///MainPage.xaml");
    ::Windows::UI::Xaml::Application::LoadComponent(this, resourceLocator, ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);
}

void ::MentorSystemUWP::MainPage::Connect(int __connectionId, ::Platform::Object^ __target)
{
    switch (__connectionId)
    {
        case 1:
            {
                this->contentPanel = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(__target);
            }
            break;
        case 2:
            {
                this->ColoredRectangle = safe_cast<::Windows::UI::Xaml::Shapes::Rectangle^>(__target);
                (safe_cast<::Windows::UI::Xaml::Shapes::Rectangle^>(this->ColoredRectangle))->DoubleTapped += ref new ::Windows::UI::Xaml::Input::DoubleTappedEventHandler(this, (void (::MentorSystemUWP::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs^))&MainPage::Rectangle_DoubleTapped);
                (safe_cast<::Windows::UI::Xaml::Shapes::Rectangle^>(this->ColoredRectangle))->DragEnter += ref new ::Windows::UI::Xaml::DragEventHandler(this, (void (::MentorSystemUWP::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::DragEventArgs^))&MainPage::Rectangle_DragEntered);
            }
            break;
        case 3:
            {
                this->inputPanel = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(__target);
            }
            break;
        case 4:
            {
                this->greetingOutput = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
            }
            break;
        case 5:
            {
                this->nameInput = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
            }
            break;
        case 6:
            {
                this->inputButton = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(this->inputButton))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::MentorSystemUWP::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::Button_Click);
            }
            break;
    }
    _contentLoaded = true;
}

::Windows::UI::Xaml::Markup::IComponentConnector^ ::MentorSystemUWP::MainPage::GetBindingConnector(int __connectionId, ::Platform::Object^ __target)
{
    __connectionId;         // unreferenced
    __target;               // unreferenced
    return nullptr;
}


