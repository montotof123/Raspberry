//
// MainPage.xaml.h
// Déclaration de la classe MainPage.
//

#pragma once

#include "MainPage.g.h"

namespace GestMontageComplet
{
	/// <summary>
	/// Une page vide peut être utilisée seule ou constituer une page de destination au sein d'un frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void OnRedBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ClignRedBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OffRedBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ClignGreenBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnGreenBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ClignRedGreenBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OffGreenBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Sw1_ValueChanged(Windows::Devices::Gpio::GpioPin ^sender, Windows::Devices::Gpio::GpioPinValueChangedEventArgs ^e);
		void Sw2_ValueChanged(Windows::Devices::Gpio::GpioPin ^sender, Windows::Devices::Gpio::GpioPinValueChangedEventArgs ^e);
		void ClignRed_Timer_Tick(Platform::Object ^sender, Platform::Object ^e);
		void ClignGreen_Timer_Tick(Platform::Object ^sender, Platform::Object ^e);
		void ClignRedGreen_Timer_Tick(Platform::Object ^sender, Platform::Object ^e);
		void Page_Unloaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		const int LED_RED = 27;
		const int LED_GREEN = 17;
		const int SW1 = 12;
		const int SW2 = 16;

		Windows::Devices::Gpio::GpioPin ^pinRed;
		Windows::Devices::Gpio::GpioPin ^pinGreen;
		Windows::Devices::Gpio::GpioPin ^pinSw1;
		Windows::Devices::Gpio::GpioPin ^pinSw2;

		Windows::Foundation::EventRegistrationToken pinSw1ChangedToken{};
		Windows::Foundation::EventRegistrationToken pinSw2ChangedToken{};

		Windows::UI::Xaml::DispatcherTimer ^timerRed;
		Windows::UI::Xaml::DispatcherTimer ^timerGreen;
		Windows::UI::Xaml::DispatcherTimer ^timerRedGreen;

		Windows::Foundation::EventRegistrationToken timerTokenRed{};
		Windows::Foundation::EventRegistrationToken timerTokenGreen{};
		Windows::Foundation::EventRegistrationToken timerTokenRedGreen{};
	};
}
