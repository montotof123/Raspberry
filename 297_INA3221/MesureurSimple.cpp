#include <iostream>
#include <wiringPi.h>

#include "GestionINA3221.h"
#include "GestionPinGPIO.h"

using namespace std;

GestionINA3221 ina3221;
GestionPinGPIO pv(GPIO06);  // suit le powerActiveFlag
GestionPinGPIO cri(GPIO13); // active low
GestionPinGPIO war(GPIO19); // active low
GestionPinGPIO tc(GPIO26);  // Suit le timingControlAlertFlag

int main() {
	pv.in();
	cri.in();
	war.in();
	tc.in();
	cout << "init         :" << hex << ina3221.init(ADDR_42) << endl;
	cout << "ti           :" << ina3221.getManufacturerID() << " " << ina3221.isManufacturerID() << endl;
	cout << "3220         :" << ina3221.getDieID() << " " << ina3221.isDieID() << endl;
	cout << "reset        :" << ina3221.reset() << endl;
	cout << "config       :" << ina3221.setConfiguration(Channel1On, Channel2On, Channel3On, Avg_16, VBUS_4156US, SBUS_332US, ShuntAndBusVoltageContinuous) << endl;
	cout << "channel1     :" << ina3221.isChannel1() << endl;
	cout << "channel2     :" << ina3221.isChannel2() << endl;
	cout << "channel3     :" << ina3221.isChannel3() << endl;
	cout << "Average      :" << ina3221.getAverage() << endl;
	cout << "Bus time     :" << ina3221.getBusVoltageConversionTime() << endl;
	cout << "Shunt time   :" << ina3221.getShuntVoltageConversionTime() << endl;
	cout << "Mode         :" << ina3221.getMode() << endl;
	cout << "CriticalAlert:" << ina3221.setCriticalShuntAlertLimit(Channel_1, 2) << " " << ina3221.getCriticalShuntAlertLimit(Channel_1) << endl;
	cout << "WarningAlert :" << ina3221.setWarningShuntAlertLimit(Channel_1, 1) << " " << ina3221.getWarningShuntAlertLimit(Channel_1) << endl;
	cout << "CriticalAlert:" << ina3221.setCriticalShuntAlertLimit(Channel_2, 2) << " " << ina3221.getCriticalShuntAlertLimit(Channel_2) << endl;
	cout << "WarningAlert :" << ina3221.setWarningShuntAlertLimit(Channel_2, 2) << " " << ina3221.getWarningShuntAlertLimit(Channel_2) << endl;
	cout << "Mask         :" << ina3221.setMaskEnable(SummationChannelControl1On, SummationChannelControl2On, SummationChannelControl3Off, WarningAlertLatchEnableOff, CriticalAlertLatchEnableOff) << dec << endl;
	cout << "Shunt Limit  :" << ina3221.setShuntVoltageSumLimit(3) << " " << ina3221.getShuntVoltageSumLimit() << endl;
	cout << "PowerUpper   :" << ina3221.setPowerValidUpperLimit(5) << " " << ina3221.getPowerValidUpperLimit() << endl;
	cout << "PowerLower   :" << ina3221.setPowerValidLowerLimit(5) << " " << ina3221.getPowerValidLowerLimit() << endl;
	delay(1000);

	for(int compteur = 0; ; compteur++) {
		bool conversion = false;
		while(!conversion){
			conversion  = ina3221.isConversionOk();
		}
		// Mesure
		float shuntVoltage1 = ina3221.getShuntVoltage_mV(Channel_1);
		float busVoltage1 = ina3221.getBusVoltage_V(Channel_1);
		float shuntVoltage2 = ina3221.getShuntVoltage_mV(Channel_2);
		float busVoltage2 = ina3221.getBusVoltage_V(Channel_2);
		float shuntVoltage3 = ina3221.getShuntVoltage_mV(Channel_3);
		float busVoltage3 = ina3221.getBusVoltage_V(Channel_3);
		float current1 = ina3221.getCurrent_mA(Channel_1);
		float current2 = ina3221.getCurrent_mA(Channel_2);
		float current3 = ina3221.getCurrent_mA(Channel_3);
		float power1 = ina3221.getPower_W(Channel_1);
		float power2 = ina3221.getPower_W(Channel_2);
		float power3 = ina3221.getPower_W(Channel_3);
		float sumShunt = ina3221.getShuntVoltageSum_mV();
		float sumCurrent = ina3221.getCurrentSum_mA();
		cout << endl << "num              :" << compteur << endl;
		cout << "Conversion ok    :" << conversion << endl;
		cout << "Canal 1" << endl;
		cout << "Bus voltage V    :" << busVoltage1 << endl;
		cout << "Shunt voltage mv :" << shuntVoltage1 << endl;
		cout << "Current mA       :" << current1 << endl;
		cout << "Power W          :" << power1 << endl;
		cout << "Warning          :" << ina3221.isWarningAlertFlagIndicator1() << endl;
		cout << "Critical         :" << ina3221.isCriticalAlertFlagIndicator1() << endl;
		cout << "Canal 2" << endl;
		cout << "Bus voltage V    :" << busVoltage2 << endl;
		cout << "Shunt voltage mv :" << shuntVoltage2 << endl;
		cout << "Current mA       :" << current2 << endl;
		cout << "Power W          :" << power2 << endl;
		cout << "Warning          :" << ina3221.isWarningAlertFlagIndicator2() << endl;
		cout << "Critical         :" << ina3221.isCriticalAlertFlagIndicator2() << endl;
		cout << "Canal 3" << endl;
		cout << "Bus voltage V    :" << busVoltage3 << endl;
		cout << "Shunt voltage mv :" << shuntVoltage3 << endl;
		cout << "Current mA       :" << current3 << endl;
		cout << "Power W          :" << power3 << endl;
		cout << "Sum" << endl;
		cout << "Sum cal1         :" << ina3221.isSummationChannelControl1() << endl; 
		cout << "Sum cal2         :" << ina3221.isSummationChannelControl2() << endl; 
		cout << "Sum cal3         :" << ina3221.isSummationChannelControl3() << endl; 
		cout << "Sum alert        :" << ina3221.isSummationAlertFlag() << endl; 
		cout << "Sum Shunt mv     :" << sumShunt << endl;
		cout << "Sum Current mA   :" << sumCurrent << endl;
		cout << "Voltage          :" << ina3221.isPowerValidAlertFlag() << endl; 
		cout << "Timing           :" << ina3221.isTimingControlAlertFlag() << endl; 
		cout << "PV               :" << pv.isOn() << endl;
		cout << "CRI              :" << cri.isOn() << endl;
		cout << "WAR              :" << war.isOn() << endl;
		cout << "TC               :" << tc.isOn() << endl;
	}
}
