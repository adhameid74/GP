// Bring in the room class
const Namespace =  require('../classes/Namespace');
const Room =  require('../classes/Room');

// Set up the namespaces
let namespaces = [];
let Chat = new Namespace(0,'Chat','https://img.icons8.com/bubbles/2x/chat.png','/Chat');
let Study = new Namespace(1,'Study','https://cdn0.iconfinder.com/data/icons/education-and-learning-round/128/22-512.png','/Study');
let Gamming = new Namespace(2,'Gamming','https://cdn2.iconfinder.com/data/icons/esports-malibu-vol-1/128/arena-512.png','/Gamming');

namespaces.push(Chat,Study,Gamming);

// Make the main room and add it to rooms. it will ALWAYS be 0
Chat.addRoom(new Room(0,'General chat','Chat'));
Chat.addRoom(new Room(1,'Private chat','Chat',true));
Chat.addRoom(new Room(2,'Other','Chat'));

Study.addRoom(new Room(0,'Study','Study'));
Study.addRoom(new Room(1,'Embedded system','Study'));
Study.addRoom(new Room(2,'GP','Study'));
Study.addRoom(new Room(3,'Courses','Study'));

Gamming.addRoom(new Room(0,'New Games','Gamming'));
Gamming.addRoom(new Room(1,'FIFA','Gamming'));
Gamming.addRoom(new Room(2,'Valorant','Gamming'));


module.exports = namespaces;