class Namespace{
    constructor(namspaceID,namespaceTitle,img,endpoint)
    {
        this.namespaceTitle = namespaceTitle;
        this.namspaceID = namspaceID;
        this.img = img;
        this.endpoint = endpoint;
        this.rooms = [];
    }
    addRoom(room){
        this.rooms.push(room);
    }
}
module.exports = Namespace;