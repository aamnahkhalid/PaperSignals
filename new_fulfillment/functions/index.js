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

var database = firebase.database();



async function asyncCall(conv, weather, city, intentName, time, data) {
    var noresult = true;
    for (n = 1; n < 7 && result; n++) {
        const snapshot = await firebase.database().ref('/event' + n + '/tracking').once('value');
        // For debugging
        //console.log("child " + n + " just got reviewed");
        result = snapshot.val();
        if (result === false) {
            noresult = false;
            database.ref('event'+(""+n)+'/intentName').set(intent_name);
            database.ref('event'+(""+n)+'/weatherIcon').set(weather);
            database.ref('event'+(""+n)+'/timestamp').set(time);
            database.ref('event'+(""+n)+'/city').set(city);
            database.ref('event'+(""+n)+'/implemented').set(false);
            database.ref('event'+(""+n)+'/tracking').set(true);
            return;
        }
    }
    //if no event slot found
    if (result) {
        conv.ask("nothing is free here is current n "+ n+"what would you like to do?"); 
        return; 
    }
}



app.intent('weather', (conv) => {

    var weather = conv.parameters["weather"];
    var city = conv.parameters["geo-city"];
    let intent_name = conv.intent;
    let time = Date.now();
    asyncCall().then(function(){
        database.goOffline();
    });
});



exports.hapkitEditor = functions.https.onRequest(app);