const socket = require("dgram").createSocket("udp4");
const Readline = require("readline");
const SERVER_HOSTNAME = "localhost";
const SERVER_PORT = 1111;
const USER_HOSTNAME = "localhost";
const rl = Readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
context = {
  reason: "connection closed",
  reconnect: true
}
var USER_PORT;
var userAddress = "";

let prompt = ">";
rl.setPrompt(prompt);

rl.prompt();
rl.question("What is your Name ? ", (userName) => {
  socket.bind(USER_PORT, USER_HOSTNAME);
  socket.on("listening", () => {
    userAddress = socket.address();
    let data = { header: { type: "connecting", }, };
    console.log("Successfully connected to server");
    let message = Buffer.from(JSON.stringify(data));
    socket.send(message, 0, message.length, SERVER_PORT, SERVER_HOSTNAME);
    rl.prompt();
  });

  socket.on("message", (data, rinfo) => {
    let messageObject = JSON.parse(data.toString());
    if (messageObject.header.type === "sending") {
      console.log(Buffer.from(messageObject.body.message).toString());
    } else {
      console.log("unknownsage");
    }
    if (messageObject.header.type === "close") {
      console.log(Buffer.from(messageObject.body.message).toString());
      process.exit();
    }
    rl.prompt();
  });

  socket.on("disconnect", (context) => {
    let data = { header: { type: "disconnecting", }, };
    console.log("Connection lost...");
    let message = Buffer.from(JSON.stringify(data));
    socket.send(message, 0, message.length, SERVER_PORT, SERVER_HOSTNAME);
  })

  rl.on("line", (input) => {
    let data = { header: { type: "sending", },
      body: { message: Buffer.from(`${userName} says "${input}"`).toJSON(), },
    };

    let message = Buffer.from(JSON.stringify(data));
    socket.send(message, 0, message.length, SERVER_PORT, SERVER_HOSTNAME);
    rl.prompt();
  });
});
