function joinRoom(roomName) {
    nsSocket.emit('joinRoom',roomName,(newNumberOfMembers)=>{
        document.querySelector('.curr-room-num-users').innerHTML = `${newNumberOfMembers} <span class="glyphicon glyphicon-user"></span>`
    });
    nsSocket.on('roomHistoryUpdate',(history)=>{
        console.log(history);
        const messageUl = document.querySelector('#messages');
        messageUl.innerHTML = "";
        history.forEach((msg)=>{
            const newMsg = buildHTML(msg);
            const currentMsges = messageUl.innerHTML;
            messageUl.innerHTML = currentMsges + newMsg;
        })
        messageUl.scrollTo(0,messageUl.scrollHeight);
    })
    nsSocket.on('updateNumberOfMembers',(numMembers)=>{
        document.querySelector('.curr-room-num-users').innerHTML = `${numMembers} <span class="glyphicon glyphicon-user"></span>`
        document.querySelector('.curr-room-text').innerText = `${roomName}`
    })
}