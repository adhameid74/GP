class Room{
    constructor(roomID,roomTitle,namespace,privateRoom = false){
        this.roomID = roomID;
        this.roomTitle = roomTitle;
        this.namespace = namespace;
        this.privateRoom = privateRoom;
        this.history = [];
    }
    addMessage(message){
        this.history.push(message);
    }
    clearHistory(){
        this.history = [];
    }
}
module.exports = Room;