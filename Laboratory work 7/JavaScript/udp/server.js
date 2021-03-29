const socket = require("dgram").createSocket("udp4");
const PORT = 1111;
const HOSTNAME = "localhost";

var clients = [];
socket.bind(PORT, HOSTNAME);
socket.on("listening", () => {
  const address = socket.address();
  console.log(`The server is listening on port ${address.port}`);
});

socket.on("message", (data, rinfo) => {
  let messageObject = JSON.parse(data.toString());
  if (messageObject.header.type === "sending") {
    let tasks = [];
    for (let client of clients) {
      if (client.address === rinfo.address && client.port === rinfo.port) {
        continue;
      }
      tasks.push(
        new Promise((resolve, reject) => {
          try {
            resolve(
              socket.send(data, 0, data.length, client.port, client.address)
            );
          } catch (error) {
            reject(0);
          }
        })
      );
    }
    Promise.all(tasks).then((result) => console.log("[message]"));
  } else if (messageObject.header.type === "connecting") {
    console.log(`[new user connected]`);
    clients.push({
      address: rinfo.address,
      port: rinfo.port,
    });
  } else if (messageObject.header.type === "disconnecting") {
    console.log(`[user disconnected]`);
    clients.push({
      address: rinfo.address,
      port: rinfo.port,
    });
  }
});