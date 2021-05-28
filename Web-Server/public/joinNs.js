function joinNs(endpoint){
    if(nsSocket)
    {
        // check if is nsSocket is actually a socket (any one connected to it)
        nsSocket.close();
        // remove the eventListener
        // -------------
    }
    nsSocket = io(`http://localhost:8080${endpoint}`);
    nsSocket.on('nsRooms',(nsRooms)=>{
        let nsRoomsdiv = document.querySelector('.room-list');
        nsRoomsdiv.innerHTML = "";
        nsRooms.forEach((room)=>{
            let glyph;
            if (room.privateRoom) {
                glyph = 'lock'
            }
            else{
                glyph = 'globe' 
            }
        nsRoomsdiv.innerHTML += `<li class = "room"><span class="glyphicon glyphicon-${glyph}"></span>${room.roomTitle}</li>`
        })
        // add a click listener to each room
        let elements = Array.from(document.getElementsByClassName('room'));
        elements.forEach((element)=>{
            element.addEventListener('click',(event)=>{
                console.log("some one clicked",event.target.innerText);
                joinRoom(event.target.innerText);
            })
    })
    // join room automatically 
    const topRoom = document.querySelector('.room');
    const topRoomName = topRoom.innerText;
    joinRoom(topRoomName);
})
    nsSocket.on('messageToClients',(msg)=>{
        //console.log(msg);
        // const fullmsg = {
        //     text: msg,
        //     time: Date.now(),
        //     userName: "IamZoneWhoKnocks",
        //     avatar: 'https://via.placeholder.com/30'
        // }
        const newmsg = buildHTML(msg);
        document.querySelector('#messages').innerHTML += newmsg;
    })  
    document.querySelector('.message-form').addEventListener('submit',formSubmission)
}
function formSubmission(event){
    event.preventDefault();
    const newMessage = document.querySelector('#user-message').value;
    nsSocket.emit('newMessageToServer',{text: newMessage})
}
function buildHTML(msg) {
    // console.log(msg)
    const convertedDate = new Date(msg.time).toLocaleString();
    const newHTML = `
    <li>
        <div class="user-image">
            <img src=${msg.avatar} />
        </div>
        <div class="user-message">
            <div class="user-name-time">${msg.userName} <span>${convertedDate}</span></div>
            <div class="message-text">${msg.text.text}</div>
        </div>
    </li>`
    return newHTML;
}