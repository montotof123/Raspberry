//
// MainPage.xaml.cpp
// Implémentation de la classe MainPage.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace GestMontageComplet;

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
using namespace Windows::Devices::Gpio;
using namespace Windows::UI::Core;

// Pour plus d'informations sur le modèle d'élément Page vierge, consultez la page https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}

// ***************************
// Clic sur le bouton On rouge
// ***************************
void GestMontageComplet::MainPage::OnRedBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	timerRed->Stop();
	timerGreen->Stop();
	timerRedGreen->Stop();
	pinRed->Write(GpioPinValue::High);
}

// ******************************
// Clic sur le bouton Clign rouge
// ******************************
void GestMontageComplet::MainPage::ClignRedBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	timerRed->Start();
	timerGreen->Stop();
	timerRedGreen->Stop();
}

// *****************************************
// Inverse la led rouge pour le clignotement
// *****************************************
void GestMontageComplet::MainPage::ClignRed_Timer_Tick(Object ^sender, Object ^e)
{
	if (pinRed->Read() == GpioPinValue::High) {
		pinRed->Write(GpioPinValue::Low);
	}
	else {
		pinRed->Write(GpioPinValue::High);
	}
}

// ****************************
// Clic sur le bouton Of rouge
// ****************************
void GestMontageComplet::MainPage::OffRedBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	timerRed->Stop();
	timerGreen->Stop();
	timerRedGreen->Stop();
	pinRed->Write(GpioPinValue::Low);
}

// *****************************
// Clic sur le bouton Clign vert
// *****************************
void GestMontageComplet::MainPage::ClignGreenBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	timerRed->Stop();
	timerGreen->Start();
	timerRedGreen->Stop();
}

// *****************************************
// Inverse la led verte pour le clignotement
// *****************************************
void GestMontageComplet::MainPage::ClignGreen_Timer_Tick(Object ^sender, Object ^e)
{
	if (pinGreen->Read() == GpioPinValue::High) {
		pinGreen->Write(GpioPinValue::Low);
	}
	else {
		pinGreen->Write(GpioPinValue::High);
	}
}

// **************************
// Clic sur le bouton On vert
// **************************
void GestMontageComplet::MainPage::OnGreenBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	timerRed->Stop();
	timerGreen->Stop();
	timerRedGreen->Stop();
	pinGreen->Write(GpioPinValue::High);
}

// ***********************************
// Clic sur le bouton Clign rouge vert
// ***********************************
void GestMontageComplet::MainPage::ClignRedGreenBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	timerRed->Stop();
	timerGreen->Stop();
	timerRedGreen->Start();
}

// ***************************************************
// Inverse les led rouge et verte pour le clignotement
// ***************************************************
void GestMontageComplet::MainPage::ClignRedGreen_Timer_Tick(Object ^sender, Object ^e)
{
	if (pinRed->Read() == GpioPinValue::High) {
		pinRed->Write(GpioPinValue::Low);
		pinGreen->Write(GpioPinValue::High);
	}
	else {
		pinRed->Write(GpioPinValue::High);
		pinGreen->Write(GpioPinValue::Low);
	}
}
// ***************************
// Clic sur le bouton Off vert
// ***************************
void GestMontageComplet::MainPage::OffGreenBTN_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	timerRed->Stop();
	timerGreen->Stop();
	timerRedGreen->Stop();
	pinGreen->Write(GpioPinValue::Low);
}

// ***********************
// Appui sur le bouton Sw1
// ***********************
void GestMontageComplet::MainPage::Sw1_ValueChanged(GpioPin ^sender, GpioPinValueChangedEventArgs ^e)
{
	// Cette partie doit être asynchrone, sinon l'arrêt d'un timer dans une procedure d'interruption entraine un plantage du programme
	Dispatcher->RunAsync(
		CoreDispatcherPriority::Normal,
		ref new Windows::UI::Core::DispatchedHandler([this]()
	{
		timerRed->Stop();
		timerGreen->Stop();
		timerRedGreen->Stop();
		pinRed->Write(GpioPinValue::High);
		pinGreen->Write(GpioPinValue::Low);	
	}));
}

// ***********************
// Appui sur le bouton Sw2
// ***********************
void GestMontageComplet::MainPage::Sw2_ValueChanged(GpioPin ^sender, GpioPinValueChangedEventArgs ^e)
{
	// Cette partie doit être asynchrone, sinon l'arrêt d'un timer dans une procedure d'interruption entraine un plantage du programme
	Dispatcher->RunAsync(
		CoreDispatcherPriority::Normal,
		ref new Windows::UI::Core::DispatchedHandler([this]()
	{
		timerRed->Stop();
		timerGreen->Stop();
		timerRedGreen->Stop();
		pinRed->Write(GpioPinValue::Low);
		pinGreen->Write(GpioPinValue::High);
	}));
}

// *********************
// Chargement de la page
// *********************
void GestMontageComplet::MainPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Initialisation gpio
	auto gpio = GpioController::GetDefault();

	// Programmation des broches gpio
	pinRed = gpio->OpenPin(LED_RED);
	pinGreen = gpio->OpenPin(LED_GREEN);
	pinSw1 = gpio->OpenPin(SW1);
	pinSw2 = gpio->OpenPin(SW2);

	pinRed->SetDriveMode(GpioPinDriveMode::Output);
	pinGreen->SetDriveMode(GpioPinDriveMode::Output);
	pinSw1->SetDriveMode(GpioPinDriveMode::InputPullDown);
	pinSw2->SetDriveMode(GpioPinDriveMode::InputPullUp);

	// Interruption sur broche gpio avec switch
	pinSw1ChangedToken = pinSw1->ValueChanged += ref new TypedEventHandler<GpioPin^, GpioPinValueChangedEventArgs^>(this, &GestMontageComplet::MainPage::Sw1_ValueChanged);
	pinSw2ChangedToken = pinSw2->ValueChanged += ref new TypedEventHandler<GpioPin^, GpioPinValueChangedEventArgs^>(this, &GestMontageComplet::MainPage::Sw2_ValueChanged);

	// Timer clignotement led rouge
	timerRed = ref new DispatcherTimer();
	TimeSpan interval;
	interval.Duration = 200 * 1000 * 10;
	timerRed->Interval = interval;
	timerTokenRed = timerRed->Tick += ref new EventHandler<Object^>(this, &GestMontageComplet::MainPage::ClignRed_Timer_Tick);

	// Timer clignotement led verte
	timerGreen = ref new DispatcherTimer();
	interval.Duration = 400 * 1000 * 10;
	timerGreen->Interval = interval;
	timerTokenGreen = timerGreen->Tick += ref new EventHandler<Object^>(this, &GestMontageComplet::MainPage::ClignGreen_Timer_Tick);

	// Timer clignotement led rouge verte
	timerRedGreen = ref new DispatcherTimer();
	interval.Duration = 600 * 1000 * 10;
	timerRedGreen->Interval = interval;
	timerTokenRedGreen = timerRedGreen->Tick += ref new EventHandler<Object^>(this, &GestMontageComplet::MainPage::ClignRedGreen_Timer_Tick);
}

// ***********************
// Déchargement de la page
// ***********************
void GestMontageComplet::MainPage::Page_Unloaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Nettoyage des timer
	timerRed->Tick -= timerTokenRed;
	timerRed->Stop();
	timerRed = nullptr;

	timerGreen->Tick -= timerTokenRed;
	timerGreen->Stop();
	timerGreen = nullptr;

	timerRedGreen->Tick -= timerTokenRed;
	timerRedGreen->Stop();
	timerRedGreen = nullptr;

	// Désactive les broches gpio
	delete pinRed;
	pinRed = nullptr;

	delete pinGreen;
	pinGreen = nullptr;

	delete pinSw1;
	pinSw1 = nullptr;

	delete pinSw2;
	pinSw2 = nullptr;
}
