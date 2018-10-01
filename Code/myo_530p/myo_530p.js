//require('leapjs/template/entry');
//
//var controller = new Leap.Controller()
//controller.on("frame", function(frame) {
//  console.log("Frame: " + frame.id + " @ " + frame.timestamp);
//});
//
//var frameCount = 0;
//controller.on("frame", function(frame) {
//  frameCount++;
//});
//
//setInterval(function() {
//  var time = frameCount/2;
//  console.log("received " + frameCount + " frames @ " + time + "fps");
//  frameCount = 0;
//}, 2000);
//
//controller.on('ready', function() {
//    console.log("ready");
//});
//controller.on('connect', function() {
//    console.log("connect");
//});
//controller.on('disconnect', function() {
//    console.log("disconnect");
//});
//controller.on('focus', function() {
//    console.log("focus");
//});
//controller.on('blur', function() {
//    console.log("blur");
//});
//controller.on('deviceConnected', function() {
//    console.log("deviceConnected");
//});
//controller.on('deviceDisconnected', function() {
//    console.log("deviceDisconnected");
//});
//
//controller.connect();
//console.log("\nWaiting for device to connect...");
//
//

////
var Myo = require('myo');
var Leap = require('leapjs');
var myMyo = Myo.create();
Myo.connect('com.stolksdorf.myAwesomeApp', require('ws'));//// version ws@1

var program = require('commander');
var _ = require('lodash');
var fs = require('fs')
var express = require('express');
var session = require('client-sessions');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var app = require('express')();
app.use(session({// crear una sesion, siempre q se suba una imagen
    cookieName: 'session',
    secret: '0GBlJZ9EKBt2Zbi2flRPvztczCewBxXKhbecerra@ece.ubc.ca',
    duration: 30 * 60 * 1000, // 30 min 
    activeDuration: 5 * 60 * 1000, //5 min 
}))
app.use(cookieParser()); // read cookies (needed for auth)
app.use(bodyParser.json()); // get information from html forms
app.use(bodyParser.urlencoded({extended: true}));
var http = require('http').Server(app);
var io = require('socket.io')(http);
var path = require('path');
var formidable = require('formidable');
var fs = require('fs');
var exec = require('child_process').exec;
var exec2 = require('child_process').execSync;

///------------------------------------////

var max_action = 1;
var last_action = 1;
var id = 0;
var idTosend = "-10";
var filename_;
var mensaje = "ss";
app.use(express.static(path.join(__dirname, 'public')));

//para cambiar directorios entre windows y maquina
var WINDOWS_ON = 1;


app.get('/leap', function (req, res) {

   
    res.sendFile(path.join(__dirname, 'views/leap.html'));

});


app.get('/mantenimiento', function (req, res) {

    console.log("Entro usuario Admin");
    res.sendFile(path.join(__dirname, 'views/mantenimiento.html'));

});



function execute(command, callback) {
    exec(command, function (error, stdout, stderr) {
        callback(stdout);
    });
}
;


var receiving_mouse = false;
var mouse_pos;
var file_string1 = "";
var file_string2 = "";
var file_string3 = "";
var file_string4 = "";

io.on('connection', function (socket) {
    console.log('a user connected');

    socket.on('chat message', function (msg) {
        console.log('message: ' + msg.usr);

        //emitir a todos los clientes
        //
        //el server recive el mensaje y lo reemite 
        // a el usuario final

        if (msg.usr === "everyone") {
            io.emit('chat message', {mensaje: msg.mensaje, froM: msg.who});

            //si quiero ejecutar un comando :D
            exec('dir', function (error, stdout, stderr) {
                console.log(error);
                console.log(stdout);
                console.log(stderr);
            });
        } else {
            io.sockets.in('user@' + msg.usr + '.co').emit('new_msg', {mensaje: msg.mensaje, froM: msg.who});
        }


    });




    socket.on('Give an id', function (msg) {
        id = id + 1;
        console.log('Give an id: ' + id);
        console.log('ddd:' + socket.id);
        socket.join('user@' + id + '.co'); // We are using room of socket io
        io.sockets.in('user@' + id + '.co').emit('get_id', id);

        //enviar a todos el id
        //io.emit('get_id', id);

    });


    socket.on('mouse', function (msg) {
        //console.log(msg);
        receiving_mouse = true;
        mouse_pos = msg;
        
//        console.log('pitch '+mouse_pos.pitch) ;
//        console.log('roll '+mouse_pos.roll) ;
//        console.log('yaw '+mouse_pos.yaw) ;
        
        //	io.sockets.in('user@'+msg.usr+'.co').emit('getattack', {attack: msg.attack,froM: msg.who});
    });
    
     socket.on('enable_adq', function (msg) {
        //console.log(msg);
     
        
        //	io.sockets.in('user@'+msg.usr+'.co').emit('getattack', {attack: msg.attack,froM: msg.who});
    });



    socket.on('save_data', function (msg) {
        receiving_mouse=false;
        
        fs.writeFile("emg_data", file_string1, function (err) {
            if (err) {
                return console.log(err);
            }

            console.log("The file 1 was saved!");
        });

        fs.writeFile("pitch_data", file_string2, function (err) {
            if (err) {
                return console.log(err);
            }

            console.log("The file 2 was saved!");
        });
        fs.writeFile("roll_data", file_string3, function (err) {
            if (err) {
                return console.log(err);
            }

            console.log("The file 3 was saved!");
        });
        
        fs.writeFile("yaw_data", file_string4, function (err) {
            if (err) {
                return console.log(err);
            }

            console.log("The file 4 was saved!");
        });




        file_string1 = "";
        file_string2 = "";
        file_string3 = "";
        file_string4 = "";

    });



    socket.on('join', function (data) {
        socket.join(data.email); // We are using room of socket io
    });


});

http.listen(3000, function () {
    console.log('listening on *:3000');


});

Myo.on('fist', function () {
    console.log('Hello Myo!');
    this.vibrate();
});

Myo.on('connected', function () {
    console.log('Connected!');
    this.streamEMG(true);
});

var emg_data;

Myo.on('emg', function (data) {
    emg_data = data;
    data_receive = true;
    var i;
    if (receiving_mouse === true) {
        
        file_string1 = file_string1 + emg_data + ';';
        file_string2 = file_string2 + mouse_pos.pitch + ',';
        file_string3 = file_string3 + mouse_pos.roll + ',';
        file_string4 = file_string4 + mouse_pos.yaw + ',';
    }
});

