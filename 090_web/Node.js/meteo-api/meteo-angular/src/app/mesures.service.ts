// ***********************************
// Service d'accès à l'API des mesures
// ***********************************

import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { HttpParams } from '@angular/common/http';

// Singleton
@Injectable({
  providedIn: 'root'
})

export class MesuresService {

  private REST_API_SERVER = "http://192.168.1.100:8081/api/meteo";
  private CURRENT_ALL = this.REST_API_SERVER + "/currentAll";
  private TEMPERATURES = this.REST_API_SERVER + "/courbeTemperature";
  private PRESSIONS = this.REST_API_SERVER + "/courbePression";
  private HUMIDITES = this.REST_API_SERVER + "/courbeHumidite";

  constructor(private httpClient: HttpClient) { }

  // ************************
  // Donne la dernière mesure
  // ************************
  public getCurrentAll() {
    return this.httpClient.get(this.CURRENT_ALL);
  }

  // *********************************************
  // Donne les temperatures dans une plage horaire
  // @Param date minimum
  // @Param time minimum
  // @Param date maximum
  // @Param date maximum
  // @return les mesures
  // *********************************************
  public getTemperatures(dateMin: string, timeMin: string, dateMax: string, timeMax: string) {
    return this.getMesures(this.TEMPERATURES, dateMin, timeMin, dateMax, timeMax);
  }

  // ******************************************
  // Donne les pressions dans une plage horaire
  // @Param date minimum
  // @Param time minimum
  // @Param date maximum
  // @Param date maximum
  // @return les mesures
  // ******************************************
  public getPressions(dateMin: string, timeMin: string, dateMax: string, timeMax: string) {
    return this.getMesures(this.PRESSIONS, dateMin, timeMin, dateMax, timeMax);
  }

  // *****************************************
  // Donne les humidite dans une plage horaire
  // @Param date minimum
  // @Param time minimum
  // @Param date maximum
  // @Param date maximum
  // @return les mesures
  // *****************************************
  public getHumidites(dateMin: string, timeMin: string, dateMax: string, timeMax: string) {
    return this.getMesures(this.HUMIDITES, dateMin, timeMin, dateMax, timeMax);
  }

  // ****************************************
  // Donne les mesures dans une plage horaire
  // @Param le type de mesure
  // @Param date minimum
  // @Param time minimum
  // @Param date maximum
  // @Param date maximum
  // @return les mesures
  // ***************************************** 
  private getMesures(typeMesure: string, dateMin: string, timeMin: string, dateMax: string, timeMax: string) {
    let params = new HttpParams();
    params = params.append('dateMin', dateMin);
    params = params.append('timeMin', timeMin);
    params = params.append('dateMax', dateMax);
    params = params.append('timeMax', timeMax);
    return this.httpClient.get(typeMesure, {params: params});
  }
}
