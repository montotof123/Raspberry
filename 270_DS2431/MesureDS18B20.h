/*
 * MesureDS18B20.h
 *
 *  Created on: 18 march 2017
 *      Author: totof
 * Mesure des thermometres 1-wire DALLAS DS18B20
 */

#ifndef _MESURE_DS18B20_H_
#define _MESURE_DS18B20_H_

namespace std {

class MesureDS18B20 {
    public:
		MesureDS18B20();
		MesureDS18B20(list<string>);
		
		bool isMesureOK() const;
		float getTemperature() const;
		
		virtual ~MesureDS18B20();

    private:
		bool mesureState;
		float temperature;
};
}

#endif /* _MESURE_DS18B20_H_ */