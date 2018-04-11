'use strict';
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
var ref = database.ref();
var lols;
ref.child('event2').once('value').then(function(dataSnapshot){
//                                                 lols= (dataSnapshot.val());
                                                 });
return console.log(lols);

