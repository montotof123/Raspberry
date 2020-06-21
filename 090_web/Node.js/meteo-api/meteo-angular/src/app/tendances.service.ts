// *******************************
// Service de calcul des tendances
// *******************************

import { Injectable } from '@angular/core';

// Non singleton
@Injectable()

export class TendancesService {

  //tendance 
  private tendance: number = 0;

  constructor() { }

  // ******************************************
  // Incrément de la tendance avec blocage à 10
  // ******************************************
  public incrementTendance(): void {
    this.tendance++;
    // Maximum à 10
    if(this.tendance > 10) {
      this.tendance = 10;
    }
  }

  // *******************************************
  // Décrément de la tendance avec blocage à -10
  // *******************************************
  public decrementTendance(): void {
    this.tendance--;
    // Minimum à -10
    if(this.tendance < -10) {
      this.tendance = -10;
    }
  }

  // ******************************
  // Donne la valeur de la tendance
  // ******************************
  public getTendance(): number {
    return this.tendance;
  }
}
