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



app.intent('weather', (conv) => {

    var weather = conv.parameters["weather"];
    var city = conv.parameters["geo-city"];
    let intent_name = conv.intent;
    let time = Date.now();
    var n = -1;
    const promise = firebase.database().ref('/last_event').once('value');
    const p2 = promise.then(snapshot =>{
        n = snapshot.val();
    });
        
    //     if (n >= 6){
    //         conv.ask("nothing is free here is current n "+ n+"what would you like to do?"); 
    //     }
    // });
      
        //     } else {
        //         const index = n+1;
        //         database.ref('event'+index+'/intentName').set(intent_name);
        //         database.ref('event'+index+'/weatherIcon').set(weather);
        //         database.ref('event'+index+'/timestamp').set(time);
        //         database.ref('event'+index+'/city').set(city);
        //         database.ref('event'+index+'/implemented').set(false);
        //         database.ref('event'+index+'/tracking').set(true);
        //         database.ref('last_pos').set(index);
    conv.ask( `Alright, you are tracking ${weather} in ${city}! Would you like to track another weather event?.`+String(n));
                

        //     }
        // } );
        
    // p2.catch(error=>{
    //     console.log(error);
    //     conv.close("I'm having internal errors");
    //     });
});


exports.hapkitEditor = functions.https.onRequest(app);