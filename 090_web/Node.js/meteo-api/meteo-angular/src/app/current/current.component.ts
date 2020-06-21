// ***********************************
// Classe gérant les mesures courantes
// ***********************************

import { Component, OnInit, Inject } from '@angular/core';
import { interval } from 'rxjs';

import { MesuresService } from '../mesures.service';
import { TendancesService } from '../tendances.service';

@Component({
  selector: 'app-current',
  templateUrl: './current.component.html',
  styleUrls: ['./current.component.css'],
  providers: [ 
    {provide: 'tendanceTemperature', useClass: TendancesService },
    {provide: 'tendancePression', useClass: TendancesService },
    {provide: 'tendanceHumidite', useClass: TendancesService }
  ]
})

// *********************************************
// Classe pour l'affichage de la dernière mesure
// *********************************************

export class CurrentComponent implements OnInit {
  // Interval en seconde pour le réaffichage de la dernière mesure
  private time: number = 30; 
  private subscription; 

  // Stockage des mesures courantes
  temperature: number;
  pression: number;
  humidite: number;

  // Injection des trois services tendances dans le constructeur
  constructor(private mesuresService: MesuresService,
    @Inject('tendanceTemperature') public tendanceTemperature: TendancesService,
    @Inject('tendancePression') public tendancePression: TendancesService,
    @Inject('tendanceHumidite') public tendanceHumidite: TendancesService
  ) { }

  // ****************************************************
  // Premier affichage de la mesure courante
  // Démarrage du timer d'affichage de la mesure courante
  // ****************************************************
  ngOnInit(): void {
    this.getMesure(true);
    let timer = interval(this.time * 1000);
    this.subscription = timer.subscribe(e => this.getMesure(false));
  }

  // *******************************************
  // Appel du service donnant la dernière mesure
  // Calcul de la tendance
  // *******************************************
  private getMesure(first: boolean) {
    this.mesuresService.getCurrentAll().subscribe((mesures: any[])=>{
      if(!first) {
        // Calcul de la tendance pour la température
        if(this.temperature < mesures[0].temperature) { 
          this.tendanceTemperature.incrementTendance();
        }

        if(this.temperature > mesures[0].temperature) { 
          this.tendanceTemperature.decrementTendance();
        }

        // Calcul de la tendance pour la pression
        if(this.pression < mesures[0].pression_niveau_mer) { 
          this.tendancePression.incrementTendance();
        }

        if(this.pression > mesures[0].pression_niveau_mer) { 
          this.tendancePression.decrementTendance();
        }

        // Calcul de la tendance pour l'humidité
        if(this.humidite < mesures[0].humidite) { 
          this.tendanceHumidite.incrementTendance();
        }

        if(this.humidite > mesures[0].humidite) { 
          this.tendanceHumidite.decrementTendance();
        }
      }

      // Stocke les mesures
      this.temperature = mesures[0].temperature;
      this.pression = mesures[0].pression_niveau_mer;
      this.humidite = mesures[0].humidite;
    })  
  }
}
