var app = require('express')();
var http = require('http').createServer(app);
var io = require('socket.io')(http);
const PORT = 2222;

io.on('connection', (socket) => {
    console.log('[new user connected]');
    socket.on('disconnect', () => {
        console.log('[user disconnect]');
    });
    let eventName = 'simple chat message';
    let broadcast = (msg) => {
        socket.broadcast.emit(eventName, msg) 
    } ;
    
    socket.on(eventName, (msg) => {
        console.log('[message]');
        setTimeout(broadcast, 1500, msg);
    });
});

http.listen(PORT, () => {
    console.log(`The server is listening on port ${PORT}`);
});

