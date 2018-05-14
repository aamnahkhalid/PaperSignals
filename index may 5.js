// // New Fulfillment based on Beta v.2 Firebase


'use strict';

const {dialogflow} = require('actions-on-google');
const functions = require('firebase-functions');
var firebase = require("firebase");
const app = dialogflow({debug: true});

//Code for updating firebase JSON
var config = {
    apiKey: "AIzaSyD-XN6r-tAl_Mf4rXO7bZuzdaNhj2zvpk4",
    authDomain: "hapkit-editor.firebaseapp.com",
    databaseURL: "https://hapkit-editor.firebaseio.com",
    projectId: "hapkit-editor",
    storageBucket: "hapkit-editor.appspot.com",
    messagingSenderId: "367478734991"
    };

firebase.initializeApp(config);






//define failure
async function firebaseCall(weather, city, intentName, time, data) {
  var n = 1;
  var result= true;
  while(true){
    await firebase.database().ref('/event'+n+'/implemented').once('value'){
        result = snapshot.val();
        console.log("child "+n+"just got reviewed");
        return;
    
});
        if (result === false) {
        console.log("child "+n+"is empty");
        database.ref('event'+(""+n)+'/intentName').set(intent_name);
        database.ref('event'+(""+n)+'/weatherIcon').set(weather);
        database.ref('event'+(""+n)+'/timestamp').set(time);
        database.ref('event'+(""+n)+'/city').set(city);
        database.ref('event'+(""+n)+'/implemented').set(true);
        database.ref('event'+(""+n)+'/tracking').set(true);

        conv.ask(`Alright, you are tracking ${weather} in ${city}! ` +
        `Would you like to track another weather event?.`);
        break;
    }
    n++;//move to next event slot
    
    if (n > 6){
      conv.ask("nothing is free here is current n "+ n+"what would you like to do?"); 
      break; 
    }
  }
}



app.intent('weather', (conv) => {
    var database = firebase.database();

    var weather = conv.parameters["weather"];
    var city = conv.parameters["geo-city"];
    let intent_name = conv.intent;
    let time = Date.now();

    firebaseCall(weather, city, intent_name, time, database).then(function(){
  database.goOffline();
});
  




});



exports.hapkitEditor = functions.https.onRequest(app);