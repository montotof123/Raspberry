// Dessin de la LED allumée
function canvasOn() {
    var canvas = document.getElementById('led_canvas');
    var context = canvas.getContext('2d');
	context.beginPath(); //On démarre un nouveau tracé.
	context.arc(50, 50, 50, 0, Math.PI*2); //On trace la courbe délimitant notre forme
	context.fillStyle = "#0000FF"; // Bleu
	context.fill(); //On utilise la méthode fill(); si l'on veut une forme pleine
	context.closePath();
	var imgLed = document.getElementById('image_led');
	imgLed.src = "/templates/allume.jpg";
}

// Dessin de la LED eteinte
function canvasOff() {
    var canvas = document.getElementById('led_canvas');
    var context = canvas.getContext('2d');
	context.beginPath(); //On démarre un nouveau tracé.
	context.arc(50, 50, 50, 0, Math.PI*2); //On trace la courbe délimitant notre forme
	context.fillStyle = "#F5F5F5"; // Gris
	context.fill(); //On utilise la méthode fill(); si l'on veut une forme pleine
	context.closePath();
	var imgLed = document.getElementById('image_led');
	imgLed.src = "/templates/eteint.jpg";
}