// *************************************
// Classe gérant l'affichage des courbes
// *************************************

import { Component, ViewChild, ElementRef, OnInit } from '@angular/core';
import { MatRadioChange } from '@angular/material/radio';
import { FormControl } from '@angular/forms';
import { MAT_MOMENT_DATE_FORMATS, MomentDateAdapter, MAT_MOMENT_DATE_ADAPTER_OPTIONS} from '@angular/material-moment-adapter';
import { DateAdapter, MAT_DATE_FORMATS, MAT_DATE_LOCALE, MatDateFormats } from '@angular/material/core';

import { MesuresService } from '../mesures.service';

// Paramétrage des dates
export const MOMENT_DATE_FORMATS: MatDateFormats = {
  parse: {
    dateInput: 'D/MM/YYYY'
  },
  display: {
    dateInput: 'DD/MM/YYYY',
    monthYearLabel: 'MMMM Y',
    dateA11yLabel: 'LL',
    monthYearA11yLabel: 'MMMM Y'
  }
};

// Paramétrage des dates et du resize de la page
@Component({
  selector: 'app-curve',
  templateUrl: './curve.component.html',
  styleUrls: ['./curve.component.css'],
  host: {"(window:resize)":"onWindowResize($event)"},
  providers: [
    {provide: MAT_DATE_LOCALE, useValue: 'fr-FR'},
    {provide: DateAdapter, useClass: MomentDateAdapter, deps: [MAT_DATE_LOCALE, MAT_MOMENT_DATE_ADAPTER_OPTIONS]},
    {provide: MAT_DATE_FORMATS, useValue: MOMENT_DATE_FORMATS},
    {provide: MAT_MOMENT_DATE_ADAPTER_OPTIONS, useValue: {useUtc: true}}
  ]
})

// ************************************************
// Classe pour l'affichage de la courbe des mesures
// ************************************************
export class CurveComponent  implements OnInit {
  temperatureMin: number = 10;
  pressionMin: number = 1010;
  humiditeMin: number = 0;
  dateMin = new Date();
  timeMin: string = "00:00";  
  temperatureMax: number = 30;
  pressionMax: number = 1025;
  humiditeMax: number = 100;
  dateMax = new Date();
  timeMax: string = "23:59";

  // Canvas
  @ViewChild('canvas', { static: true })
  canvas: ElementRef<HTMLCanvasElement>;  
  
  private context: CanvasRenderingContext2D;

  // Constructeur
  constructor(private _adapter: DateAdapter<any>, private mesuresService: MesuresService) { }

  // ************************
  // Initialisation du Canvas
  // ************************
  ngOnInit(): void {
    this.context = this.canvas.nativeElement.getContext('2d');
    this.context.canvas.width = window.innerWidth;
  }

  // ********************
  // Resize de la fenêtre
  // ********************
  onWindowResize(event) {
    this.context.canvas.width = window.innerWidth;
  }

  // *************************************
  // Changement d'item sur le bouton radio
  // *************************************
  radioChange(event: MatRadioChange): void {
    switch(event.value) {
      case 'temperature': 
        this.mesuresService.getTemperatures(this.dateMin.toISOString().substring(0,10), this.timeMin, this.dateMax.toISOString().substring(0,10), this.timeMax)
        .subscribe((mesures: any[])=>{this.afficheCanvas(event.value, mesures);}); 
        break;
      case 'pression': 
        this.mesuresService.getPressions(this.dateMin.toISOString().substring(0,10), this.timeMin, this.dateMax.toISOString().substring(0,10), this.timeMax)
        .subscribe((mesures: any[])=>{this.afficheCanvas(event.value, mesures);}); 
        break;
      case 'humidite': 
        this.mesuresService.getHumidites(this.dateMin.toISOString().substring(0,10), this.timeMin, this.dateMax.toISOString().substring(0,10), this.timeMax)
        .subscribe((mesures: any[])=>{this.afficheCanvas(event.value, mesures);}); 
        break;
    }
  }

  // **********************
  // Affichage de la courbe
  // **********************
  afficheCanvas(typeCourbe: string, mesures: any[]) {
    // Dimension du canvas
    this.context.canvas.height = window.innerHeight - 340;
    this.context.canvas.width = window.innerWidth - 10;
    
    // font gris
    this.context.beginPath();
    this.context.moveTo(0, 0);
    this.context.lineTo(0, this.context.canvas.height);
    this.context.lineTo(this.context.canvas.width, this.context.canvas.height);
    this.context.lineTo(this.context.canvas.width, 0);
    this.context.lineTo(0, 0);
    this.context.fillStyle = "rgba(20, 20, 20, 0.3)";
    this.context.fill();
    
    // entourage noir
    this.context.beginPath();
    this.context.moveTo(0, 0);
    this.context.lineTo(0, this.context.canvas.height);
    this.context.lineTo(this.context.canvas.width, this.context.canvas.height);
    this.context.lineTo(this.context.canvas.width, 0);
    this.context.lineTo(0, 0);
    this.context.strokeStyle = "black";
    this.context.stroke();

    // Calcul du pas des lignes horizontales en fonction de la mesure et des paramètres indiqués dans l'ihm
    let pasHorizontal;
    let minHorizontal;
    let maxHorizontal;
    let unite;
    switch(typeCourbe) {
      case "temperature": 
        if((this.temperatureMax -  this.temperatureMin) > 10) {
          pasHorizontal = 5;
        } else {
          pasHorizontal = 1;
        }
        minHorizontal = this.temperatureMin;
        maxHorizontal = this.temperatureMax;
        unite = '°';
        break;
      case "pression": 
        if((this.pressionMax - this.pressionMin) > 10) {
          pasHorizontal = 5;
        } else {
          pasHorizontal = 1;
        }
        minHorizontal = this.pressionMin;
        maxHorizontal = this.pressionMax;
        unite = ' hPa';
        break;
      case "humidite": 
        if((this.humiditeMax - this.humiditeMin) > 10) {
          pasHorizontal = 5;
        } else {
          pasHorizontal = 1;
        }
        minHorizontal = this.humiditeMin;
        maxHorizontal = this.humiditeMax;
        unite = ' %';
        break;
    }

    // Tracé des lignes horizontales
    let echelleHor = this.context.canvas.height / (maxHorizontal - minHorizontal)
    for(let compteur = minHorizontal; compteur < maxHorizontal; compteur += pasHorizontal) {
      this.context.beginPath();
      this.context.moveTo(0, this.context.canvas.height - (compteur - minHorizontal) * echelleHor);
      this.context.lineTo(this.context.canvas.width, this.context.canvas.height - (compteur - minHorizontal) * echelleHor);
      this.context.strokeStyle = "red";
      this.context.stroke();
      this.context.font = "10pt Calibri,Geneva,Arial";
      this.context.fillStyle = "red";
      this.context.fillText(compteur + unite, 5, this.context.canvas.height - (compteur - minHorizontal) * echelleHor - 5);	
    }

    // Conversion des dates html en date javascript pour calculler le temps
    let minDate = new Date(this.dateMin);
    let maxDate = new Date(this.dateMax);
    const dataMinTime = this.timeMin.split(':');
    const dataMaxTime = this.timeMax.split(':');
    minDate.setHours(parseInt(dataMinTime[0], 10));
    minDate.setMinutes(parseInt(dataMinTime[1], 10));
    maxDate.setHours(parseInt(dataMaxTime[0], 10));
    maxDate.setMinutes(parseInt(dataMaxTime[1], 10));
    // Interval de temps de la courbe
    const interval = (maxDate.getTime() - minDate.getTime()) / 1000;

    // Calcul du pas et des bornes pour les lignes verticales en fonction du temps de mesure demandé
    let pasVertical;
    let minVertical;
    const maxVertical = maxDate.getTime() / 1000;
    if(interval <= 3600) {
      // Une heure ou moins, interval de 5mn
      pasVertical = 300;
    } else if (interval <= 86400) {
      // Un jour ou moins, interval d'une heure
      pasVertical = 3600;
    } else {
      // plus d'un jour, interval de 12h
      pasVertical = 43200;
    }
    minVertical = minDate.getTime() / 1000 + pasVertical - (minDate.getTime() / 1000) % pasVertical;

    // Tracé des lignes verticales
    let echelleVer = this.context.canvas.width / interval;
    for(let compteur = minVertical; compteur <= maxVertical; compteur += pasVertical) {
      this.context.beginPath();
      this.context.moveTo((compteur - minDate.getTime() / 1000) * echelleVer, 0);
      this.context.lineTo((compteur - minDate.getTime() / 1000) * echelleVer, this.context.canvas.height);
      // Affichage de la date et de l'heure
      this.context.strokeStyle = "yellow";
      this.context.stroke();
      this.context.font = "10pt Calibri,Geneva,Arial";
      this.context.fillStyle = "yellow";
      let dateAff = new Date();
      dateAff.setTime(compteur * 1000);
      let optionsTime = {hour: "numeric", minute: "numeric", hour12: false};
      let valeurTime = new Intl.DateTimeFormat("fr-FR", optionsTime).format(dateAff);
      this.context.fillText(valeurTime, (compteur - minDate.getTime() / 1000) * echelleVer + 3, 10);
      let optionsDate = {month: "2-digit", day: "2-digit"};
      let valeurDate = new Intl.DateTimeFormat("fr-FR", optionsDate).format(dateAff);
      this.context.fillText(valeurDate, (compteur - minDate.getTime() / 1000) * echelleVer + 3, 22);
    }

    // Tracé de la courbe des mesures
    this.context.beginPath();
    let valMesure;
    switch(typeCourbe) {
      case "temperature": 
        valMesure = mesures[0].temperature;
        break;
      case "pression": 
        valMesure = mesures[0].pression;
        break;
      case "humidite": 
        valMesure = mesures[0].humidite;
        break;
    }
    this.context.moveTo(((mesures[0].nbsec - minDate.getTimezoneOffset() * 60)) * echelleVer, this.context.canvas.height - (valMesure - minHorizontal) * echelleHor);
    for(let compteur = 0; compteur != mesures.length; compteur++) {
      switch(typeCourbe) {
        case "temperature": 
          valMesure = mesures[compteur].temperature;
          break;
        case "pression": 
          valMesure = mesures[compteur].pression_niveau_mer;
          break;
        case "humidite": 
          valMesure = mesures[compteur].humidite;
          break;
      }
      this.context.lineTo(((mesures[compteur].nbsec - minDate.getTimezoneOffset() * 60)) * echelleVer, this.context.canvas.height - (valMesure - minHorizontal) * echelleHor);
    }
    this.context.strokeStyle = "green";
    this.context.stroke();
  }
}
