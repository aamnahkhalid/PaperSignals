
var firebase = require("firebase");

var config = {
    apiKey: "AIzaSyD-XN6r-tAl_Mf4rXO7bZuzdaNhj2zvpk4",
    authDomain: "hapkit-editor.firebaseapp.com",
    databaseURL: "https://hapkit-editor.firebaseio.com",
    projectId: "hapkit-editor",
    storageBucket: "hapkit-editor.appspot.com",
    messagingSenderId: "367478734991"
    };
firebase.initializeApp(config);

var database = firebase.database();
asyncCall().then(function(){
  database.goOffline();
});


async function asyncCall() {
	var result = true;
	for (n = 1; n <= 7 && result; n++) {
		const snapshot = await firebase.database().ref('/event' + n + '/implemented').once('value');
		console.log("child " + n + " just got reviewed");
		result = snapshot.val();
    	if (result === false) {
      		console.log("child " + n + " is empty");
    	}
	}
	if (result) {
		console.log("hello nothing is free here is current n "+ n); 
	}
}

  