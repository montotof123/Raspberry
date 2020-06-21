// ***********************
// Routeur des URL d'accès
// ***********************

import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { CurrentComponent }  from './current/current.component';
import { CurveComponent }  from './curve/curve.component';
import { PageErrorComponent }  from './page-error/page-error.component';

// Liste des routes avec la classe appelée
const routes: Routes = [
  // Racine / revoie sur /current
  { path: '', redirectTo: '/current', pathMatch: 'full'},
  // Affichage de la dernière mesure
  { path: 'current', component: CurrentComponent},
  // Affichage de la courbe
  { path: 'curve', component: CurveComponent},
  // Autres routes entrainant une page d'erreur
  { path: '**', component: PageErrorComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})

export class AppRoutingModule { }
