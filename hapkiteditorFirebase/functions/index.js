'use strict';
    var firebase = require("firebase");

    // var config = {
    // apiKey: "AIzaSyD-XN6r-tAl_Mf4rXO7bZuzdaNhj2zvpk4",
    // authDomain: "hapkit-editor.firebaseapp.com",
    // databaseURL: "https://hapkit-editor.firebaseio.com",
    // projectId: "hapkit-editor",
    // storageBucket: "hapkit-editor.appspot.com",
    // messagingSenderId: "367478734991"
    // };
    // firebase.initializeApp(config);



process.env.DEBUG = 'actions-on-google:*';
const App = require('actions-on-google').DialogflowApp;
const functions = require('firebase-functions');




exports.hapkitEditor = functions.https.onRequest((request, response) => {
  const app = new App({request, response});
 


// c. The function that sets weather tracking
  function weatherTracking (app) {
    // if (app.getUserConfirmation()) {
    // app.tell('Great! Now repeat the action for 20 seconds so that hapkit can register it');
    let weather_type = app.getArgument("weather");
    let city = app.getArgument("geo-city");
    // let timestamp = app.getDateTime();
    // let intent_name = app.getIntent();

    app.tell('Alright, your silly name is ' +
      weather_type + ' ' + city +
      '! I hope you like it. See you next time.');

    // var database = firebase.database();
    // database.ref('event1/intentName').set(intent_name);
    // database.ref('event1/weatherIcon').set(weather_type);
    // database.ref('event1/time').set(timestamp);
    // database.ref('event1/city').set(city);
    // database.ref('event1/tracking').set(true);
    // database.ref('event1/implemented').set(true);
        app.tell('Alright. Thanks for the demonstration!');

    console.log('Request headers: ' + JSON.stringify(request.headers));
     console.log('Request body: ' + JSON.stringify(request.body));




  // } else {
  //   app.tell('That\'s okay. Let\'s not do it now.');
  // }

  }

    // c. The function that sets time tracking
//   function dateWithoutTime (app) {
//     if (app.getUserConfirmation()) {
//     app.tell('Great! Now repeat the action for 20 seconds so that hapkit can register it');
//     let day = app.getContextArgument("time_wheel", 'date');
//     let recurring = app.getContextArgument("time_wheel", 'recurring_event' );
//     let intent_name = app.getIntent();
//     let recurBool = false;

//     if (recurring == 'true'){
//       recurBool=true;
//     }
//     let timestamp = app.getDateTime();

//     var database = firebase.database();
//     database.ref('event2/intentName').set(intent_name);
//     database.ref('event2/date').set(day);
//     database.ref('event2/time').set(timestamp);
//     database.ref('event2/recurring').set(recurBool);
//     database.ref('event2/tracking').set(true);
//     database.ref('event2/implemented').set(true);

//         app.tell('Alright. Thanks for the demonstration!');

//     console.log('Request headers: ' + JSON.stringify(request.headers));
//      console.log('Request body: ' + JSON.stringify(request.body));



//   }
//   else {
//     app.tell('That\'s okay. Let\'s not do it now.');
//   }
// }
//   function dateWithTime (app) {
//      if (app.getUserConfirmation()) {
//     app.tell('Great! Now repeat the action for 20 seconds so that hapkit can register it');
//     let day = app.getContextArgument("time_wheel", 'date');
//     let intent_name = app.getIntent();
//     let alertTime = app.getArgument('time');
//     let recurring = app.getContextArgument("time_wheel", 'recurring_event' );
//     let recurBool = false;
//     if (recurring == 'true'){
//       recurBool=true;
//     }
//     let timestamp = app.getDateTime();

//     var database = firebase.database();
//     database.ref('event2/intentName').set(intent_name);

//     database.ref('event3/date').set(day);
//     database.ref('event3/time').set(alertTime);
//     database.ref('event3/recurring').set(recurBool);
//     database.ref('event3/tracking').set(true);
//     database.ref('event3/implemented').set(true);

//         app.tell('Alright. Thanks for the demonstration!');

//     console.log('Request headers: ' + JSON.stringify(request.headers));
//      console.log('Request body: ' + JSON.stringify(request.body));

//   }else {
//     app.tell('That\'s okay. Let\'s not do it now.');
//   }
// }

  // d. build an action map, which maps intent names to functions
  let actionMap = new Map();
  actionMap.set("weather", weatherTracking);
  // actionMap.set("time_wheel-yes", dateWithTime);
  // actionMap.set(time_wheel-no, dateWithoutTime);




app.handleRequest(actionMap);
});